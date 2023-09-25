#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"
#include "GameScene.h"
GameScene::GameScene() {}

GameScene::~GameScene() {
	// モデルの開放
	delete model_;
	// 自キャラの解放
	//delete player_;
	delete debugCamera_;

	  /// delete enemy_;
	delete enemy_;

	delete skydomeModel_;

	delete railCamera_;
}




void GameScene::Initialize() {

	

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	textureHandle_ = TextureManager::Load("sample.png");

	
	// 3Dモデルの生成
	model_ = Model::Create();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
	// 自キャラの生成
	player_ = new Player();
	// 自キャラの初期化
	player_->Initialize(model_, textureHandle_);

	// デバックカメラの生成
	debugCamera_ = new DebugCamera(720, 1280);


	// 天球

	// 生成
	skydome_ = new Skydome();

	// フォルダの名前を指定してね
	// 読み込むファイルと同じフォルダ名にしないと✕
	skydomeModel_ = Model::CreateFromOBJ("CelestialSphere", true);

	// テクスチャ読み込み
	skydomeTextureHandle_ = TextureManager::Load("CelestialSphere/uvChecker.png");

	// 天球の初期化
	skydome_->Initialize(skydomeModel_, skydomeTextureHandle_);

	
	// ビュープロジェクション
	// forZを適度に大きい値に変更する
	// 大きくしすぎるとZファイティングになるよ
	viewProjection_.farZ = 1200.0f;
	// 初期化
	viewProjection_.Initialize();


	// 軸方向表示の表示を有効化する
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	//敵/////////////
const float kEnemySpeed = -0.5f;
	Vector3 velocity(0, 0, kEnemySpeed);
	Vector3 enemyPosition(0, 1.0, 100);

	enemyModel_ = Model::Create();
	enemy_ = new Enemy();
	enemy_->Initialize(enemyModel_, enemyPosition, velocity);
	// 敵キャラにゲームシーンを渡す
	enemy_->SetGameScene(this);
	// 敵キャラに自キャラのアドレスを渡す
	enemy_->SetPlayer(player_);

	/////////////////////////

	railCamera_ = new RailCamera();

	// 初期化
	Vector3 radian = {0.0f, 0.0f,0.0f};

	railCamera_->Initialize(player_->GetWorldPosition(), radian);

	//親子関係
	//  親子関係を結ぶ
	//  自キャラとレールカメラの親子関係を結ぶ
	player_->SetParent(&railCamera_->GetWorldTransform());




}

void GameScene::AddEnemyBullet(EnemyBullet* enemyBullet) {
	// リストに登録する
	enemyBullets_.push_back(enemyBullet);
}



//これはあくまで定義下だけUpdateで呼び出さないと意味がない
void GameScene::CheckAllCollision() {
	// 判定対象AとBの座標
	Vector3 posA, posB;
	// 自弾
	Vector3 posC;
	Vector3 posD;
	// 自弾リストの取得
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	// 敵弾リストの取得
	const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();

#pragma region 自キャラと敵弾の当たり判定

	// 自キャラの座標
	posA = player_->GetWorldPosition();

	// 自キャラと敵弾全ての当たり判定
	for (EnemyBullet* bullet : enemyBullets) 
	{
		// 敵弾の座標
		posB = bullet->GetWorldPosition();

		// 座標AとBの距離を求める
		float distanceAB = 
		    (posB.x - posA.x) * (posB.x - posA.x) + 
			(posB.y - posA.y) * (posB.y - posA.y) + 
			(posB.z - posA.z) * (posB.z - posA.z);

		float RadiusAB = (player_->GetRadius() + bullet->GetRadius()) +
		               (player_->GetRadius() + bullet->GetRadius());

		if (distanceAB <=RadiusAB) {
		// 自キャラの衝突時コールバックを呼び出す
		player_->OnCollision();
		// 敵弾の衝突時コールバックを呼び出す
		bullet->OnCollision();

	}
		
	}

#pragma endregion

// ここが原因。自機の弾がすぐ消えてしまう
#pragma region 自弾と敵キャラの当たり判定

	// 敵キャラの位置
	posC = enemy_->GetWorldPosition();

	// 自キャラと敵弾全ての当たり判定
	for (PlayerBullet* playerBullet : playerBullets) {
		// 自弾の座標
		posD = playerBullet->GetWorldPosition();

		float distanceCD=
			(posC.x - posD.x) * (posC.x - posD.x) +
		    (posC.y - posD.y) * (posC.y - posD.y) +
			(posC.z - posD.z) * (posC.z - posD.z);
		// 座標CとDの距離を求める
		float RadiusCD = (player_->GetRadius() + playerBullet->GetRadius()) +
		                 (player_->GetRadius() + playerBullet->GetRadius());

		if (distanceCD <= RadiusCD) {
			// 敵キャラの衝突時コールバックを呼び出す
			enemy_->OnCollision();

			// 自弾の衝突時コールバックを呼び出す
			playerBullet->OnCollision();
		}

		
	}

#pragma endregion
}







void GameScene::Update()
{
	// 自キャラの更新
	player_->Update();

	debugCamera_->Update();

	// 敵
	enemy_->Update();

	skydome_->Update();

	CheckAllCollision();

	

	Matrix4x4 cameraMatrix = {};
	cameraMatrix.m[0][0] = 1.0f;
	cameraMatrix.m[0][1] = 0.0f;
	cameraMatrix.m[0][2] = 0.0f;
	cameraMatrix.m[0][3] = 0.0f;

	cameraMatrix.m[1][0] = 0.0f;
	cameraMatrix.m[1][1] = 1.0f;
	cameraMatrix.m[1][2] = 0.0f;
	cameraMatrix.m[1][3] = 0.0f;

	cameraMatrix.m[2][0] = 0.0f;
	cameraMatrix.m[2][1] = 0.0f;
	cameraMatrix.m[2][2] = 1.0f;
	cameraMatrix.m[2][3] = 0.0f;

	cameraMatrix.m[2][0] = 1280.0f;
	cameraMatrix.m[2][1] = 720.0f;
	cameraMatrix.m[2][2] = 1.0f;
	cameraMatrix.m[2][3] = 1.0f;

	#ifdef _DEBUG
	// デバックの頭文字
	if (input_->TriggerKey(DIK_Q)) {
		isDebgCameraActive_ = true;
	}

#endif
	if (isDebgCameraActive_) {
		railCamera_->Update();
		
		viewProjection_.matView = railCamera_->viewProjection_.matView;
		viewProjection_.matProjection = railCamera_->viewProjection_.matProjection;
		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {
		// ビュープロジェクション行列の更新と転送
		viewProjection_.UpdateMatrix();
	}


}






void GameScene::Draw() {

	;
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);


	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);
	
	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 自キャラの描画
	player_->Draw(viewProjection_);

	// 敵の描画
	enemy_->Draw(viewProjection_);

	skydome_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::GenerateEnemy(Vector3 position) {
	// 生成
	enemy_ = new Enemy();

	// 敵キャラにゲームシーンを渡す
	enemy_->SetGameScene(this);
}
