#include "Player.h"
#include "Function.h"
#include <ImguiManager.h>
#include <cassert>
#include "RailCamera.h"


// デストラクタ
Player::~Player() 
{
	for (PlayerBullet* bullet : bullets_) 
	{
		delete bullet;
	}
}


void Player::Initialize(Model* model, Vector3 position) {
	assert(model);
	// 引数として受け取ったデータをメンバ変数に記録する
	this->model_ = model;
	textureHandle_ = TextureManager::Load("sample.png");

	worldTransform_.translation_ = position;
	// ワールド変数の初期化
	worldTransform_.Initialize();

	// シングルトンインスタンスを取得
	input_ = Input::GetInstance();

	//SetParent(&railCamera_->GetWorldTransform());
}




void Player::Update() {
	////行列を定数バッファに転送する
	worldTransform_.TransferMatrix();

	////移動ベクトルの設定
	////基本斜め移動
	const float kCharacterSpeed = 0.5f;
	////キャラクターの移動ベクトル
	Vector3 move = {0.0f, 0.0f,0.0f};

	

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
		const float kBulletSpeed = 5.0f;
		Vector3 velocity(0, 0, kBulletSpeed);


		velocity = TransformNormal(velocity, worldTransform_.matWorld_);
		// 弾を生成し、初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initalize(model_, GetWorldPosition(), velocity);

		

		// 弾を登録する
		bullets_.push_back(newBullet);
	}
}

void Player::OnCollision() {}

void Player::Draw(ViewProjection& viewProjection_) {
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	
	
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

void Player::SetParent(const WorldTransform* parent) {

	// 親子関係を結ぶ
	worldTransform_.parent_ = parent;
}
