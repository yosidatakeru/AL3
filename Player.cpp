#include "Player.h"
#include "Function.h"
#include <ImguiManager.h>
#include <cassert>
#include<WinApp.h>


// デストラクタ
Player::~Player() 
{
	for (PlayerBullet* bullet : bullets_) 
	{
		delete bullet;
	}

	
	// スプライトの解放
	delete sprite2DReticle_;
}


void Player::Initialize(Model* model, uint32_t textureHandle) {
	assert(model);
	// 引数として受け取ったデータをメンバ変数に記録する
	this->model_ = model;
	this->textureHandle_ = textureHandle;
	ReticleTextureHandle_ = TextureManager::Load("reticle.png");
	// ワールド変数の初期化
	worldTransform_.Initialize();

	// シングルトンインスタンスを取得
	input_ = Input::GetInstance();

	// スプライト生成
	sprite2DReticle_ = Sprite::Create(
	    ReticleTextureHandle_, {640.0f, 500.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	
	//レティクル
	worldTransform3DReticle_.Initialize();
}
void Player::Update(ViewProjection& viewProjection) {


	//////////////////
	// 時期の3dレティクルの距離
	const float kDistancePlayerTo3DReticle = 50.0f;

	// じきから3Dレティクルへの距離
	Vector3 offset = {0, 0, 1.0f};

	offset = TransformNormal(offset, worldTransform_.matWorld_);

	// ベクトルの長さを整える
	offset = {
	    Normalize(offset).x * kDistancePlayerTo3DReticle,
	    Normalize(offset).y * kDistancePlayerTo3DReticle,
	    Normalize(offset).z * kDistancePlayerTo3DReticle,
	};
	Vector3 newOffset = Add(offset, GetWorldPosition());
	// 3Dベクトルの座標を設定
	worldTransform3DReticle_.translation_ = newOffset;
	worldTransform3DReticle_.UpdeateMatrix();
	worldTransform3DReticle_.TransferMatrix();


	
	// 3Dレティクルのワールド座標から、ワールド座標を取得
     position2DReticle_ = GetReticleWorldPosition();

	// ビューポート行列
	matViewport_ = MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);

	// ビュー行悦人プロジェクション行列、ビューポート行列を合成する
     matViewProjectionViewport_ =
	    Multiply(viewProjection.matView, Multiply(viewProjection.matProjection, matViewport_));

	// ワールド->スクリーン座標変換(ここで3Dから2Dになる)
	position2DReticle_ = Transform(position2DReticle_, matViewProjectionViewport_);

	// スプライトにレティクルに座標指定
	sprite2DReticle_->SetPosition(Vector2(position2DReticle_.x, position2DReticle_.y));

	//////////////////////////


	////行列を定数バッファに転送する
	worldTransform_.TransferMatrix();

	//レティクル定義
	//ReticleUpdate(viewProjection);
	////移動ベクトルの設定
	////基本斜め移動

	////キャラクターの移動ベクトル
	Vector3 move = {0.0f, 0.0f, 0.0f};

	////キャラクターの移動速度
	const float kCharacterSpeed = 0.2f;

	////押した方向で移動ベクトルを変更（左右）
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	} else {
		move.x = 0.0f;
		move.y = 0.0f;
	}

	if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	} else {
		move.x = 0.0f;
		move.y = 0.0f;
	}

	// 回転速さ[ラジアン/frame]
	const float kRotSpeed = 0.02f;
	// 押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	}
	if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}

	//攻撃
	Attack();

	for (PlayerBullet* bullet : bullets_) 
	{
		bullet->Update();
	}
	

	// 移動の限界
	const float MOVE_LIMITX = 30.0f;
	const float MOVE_LIMITY = 18.0f;

	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -MOVE_LIMITX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, MOVE_LIMITX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -MOVE_LIMITY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, MOVE_LIMITY);
	// 座標移動（ベクトルの加算）
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
	////平行移動行列

	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.UpdeateMatrix();
	
	
	//弾の寿命
	bullets_.remove_if([](PlayerBullet* bullet)
		{
		if (bullet->IsDead()) 
		{
			delete bullet;
			return true;
		}
		return false;

	});


	// 画面に座標を出す
	ImGui::Begin("Player");

	ImGui::InputFloat3("PlayerPosition", &worldTransform_.translation_.x);
	ImGui::SliderFloat3("PlayerSlide", &worldTransform_.translation_.x, -20.0f, 30.0f);

	ImGui::End();
}

void Player::Attack() 
{

	if (input_->TriggerKey(DIK_SPACE)) 
	{
		
		Vector3 velocity(0, 0, kBulletSpeed);


		// 弾を生成し、初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initalize(model_, worldTransform_.translation_, velocity);
		
		

		velocity = Subtract(GetReticleWorldPosition(), GetWorldPosition());
		velocity = Normalize(velocity);
		velocity = {
		    Normalize(velocity).x * kBulletSpeed,
		    Normalize(velocity).y * kBulletSpeed,
		    Normalize(velocity).z * kBulletSpeed,
		};
		
		//回転に合わせる
		velocity = TransformNormal(velocity, worldTransform_.matWorld_);


		
		// 弾を登録する
		bullets_.push_back(newBullet);
	}
}

void Player::OnCollision() {}



void Player::Draw(ViewProjection& viewProjection_) {
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	
	model_->Draw(worldTransform3DReticle_, viewProjection_, ReticleTextureHandle_);
	
	for (PlayerBullet* bullet : bullets_) 
	{
		bullet->Draw(viewProjection_);
	}

}


Vector3 Player::GetWorldPosition() 
{
	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}


void Player::ReticleUpdate(ViewProjection viewProjection) 
{
	
}

Vector3 Player::GetReticleWorldPosition() {

	// ワールド座標を取得
	Vector3 worldPos{};

	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}


void Player::DrawUI() 
{
	// 2Dレティクル描画
	sprite2DReticle_->Draw();
}

void Player::SetParent(const WorldTransform* parent) {

	// 親子関係を結ぶ
	worldTransform_.parent_ = parent;
}