#include "Enemy.h"
#include "Function.h"
#include <cassert>
//#include"Player.h"
#include <imgui.h>
#include "GameScene.h"

#include "ImGuiManager.h"

Enemy::~Enemy()
{
	
	delete model_;
}




    void Enemy::Initialize(Model* model, const Vector3& position) 
    {
	// NULLチェック
	assert(model);

	phase_ = Phase::Approach;
	


	model_ = model;
	// 敵
	textureHandle_ = TextureManager::Load("Player6.png");
	// ワールド変数の初期化
	worldTransform_.Initialize();
	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
	//velocity_ = velocity;
	//Fire();
	PhaseInitialize();
	

    }



	// 座標を移動させる（1フレーム分の移動量を足しこむ）
   // worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
    const float EnemykRotSpeed = 0.80f;

	void Enemy::ApproachUpdate() 
	{
	// 指定の位置に到達したら離脱する
	if (worldTransform_.translation_.z < 0.0f) 
	{
		phase_ = Phase::Leave;
	}

	FireTimer--;
	if (FireTimer <= 0) 
	{
		Fire();
		FireTimer = kFireInterval;
	}

    }




	 void Enemy::PhaseInitialize() 
	 { 
		 FireTimer = kFireInterval;
	 }



	



    void Enemy::LeaveUpdate() 
	{
	// 移動(ベクトルを加算)
	// 移動（ベクトル加算）
	worldTransform_.translation_.z += EnemykRotSpeed;
	if (worldTransform_.translation_.z > 100.0f) 
	{
		phase_ = Phase::Approach;
	}
    }

   



void Enemy::Update() 
{
	//敵の動き
	switch (phase_) 
	{

	case Phase::Approach:
	default:
		ApproachUpdate();

		break;

	case Phase::Leave:
		LeaveUpdate();
		break;
	}



	/*for (EnemyBullet* bullet : bullets_)
	{
		bullet->Update();
	}*/
	
	//  ワールドトランスの更新
	worldTransform_.UpdeateMatrix();
	// 座標を移動させる（1フレーム分の移動量を足しこむ）
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
	
	
	// Enemyデバッグ
	ImGui::Begin("EnemyDebug1");

	// float3入力ボックス
	ImGui::InputFloat3("EnemyPosition", &worldTransform_.translation_.x);
	// float3スライダー
	ImGui::SliderFloat3("EnemySlider", &worldTransform_.translation_.x, 0.0f, 40.0f);

	ImGui::End();
}



Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}


Vector3 Enemy::LerpFanc(Vector3 v1, Vector3 v2) 
{
	Vector3 result;

	result.x = v2.x - v1.x;
	result.y = v2.y - v1.y;
	result.z = v2.z - v1.z;

	return result;
}

void Enemy::OnCollision() {}




    void Enemy::Draw(ViewProjection& viewProjection_) 
    {

	model_->Draw(worldTransform_, viewProjection_, textureHandle_);

	/* for (EnemyBullet* bullet : bullets_) 
	 {

		bullet->Draw(viewProjection_);
	 }*/
	
    }





	void Enemy::Fire()
	{
	const float kBulletSpeed = -1.0f;

	
Vector3 PlayerPos = player_->GetWorldPosition();
	Vector3 EnemyPos = GetWorldPosition();

	Vector3 PiEnLerp = LerpFanc(EnemyPos, PlayerPos);

	Vector3 PiEnNormalize = Normalize(PiEnLerp);

	Vector3 velocity = PiEnNormalize;
	velocity = TransformNormal(velocity, worldTransform_.matWorld_);

	
	// intealize
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);
	// 弾をGameSceneに登録する
	gameScene_->AddEnemyBullet(newBullet);
	////bullets_.push_back(newBullet);

	if (isDead_ == false) {
		// 弾を生成し、初期化
		EnemyBullet* newEnemyBullet = new EnemyBullet();
		newEnemyBullet->Initialize(model_, worldTransform_.translation_, velocity);

		// 弾を登録する
		// bullets_に要素を追加
		gameScene_->AddEnemyBullet(newEnemyBullet);
		// bullets_.push_back(newEnemyBullet);
	}
	
    }


	