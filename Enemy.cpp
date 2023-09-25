#include "Enemy.h"
#include "Function.h"
#include <cassert>
//#include"Player.h"



Enemy::~Enemy()
{
	//弾の解放処理
	//複数出たのでfor文で解放しよう
	for (EnemyBullet* bullet : bullets_) 
	{
		delete bullet;
	}
	delete model_;
}




    void Enemy::Initialize(Model* model, const Vector3& pos) 
    {
	// NULLチェック
	assert(model);

	
	


	model_ = model;
	// 敵
	textureHandle_ = TextureManager::Load("Player6.png");
	// ワールド変数の初期化
	worldTransform_.Initialize();
	// 引数で受け取った初期座標をセット
	worldTransform_.Initialize();
	worldTransform_.translation_.x = pos.x;
	worldTransform_.translation_.y = pos.y;
	worldTransform_.translation_.z = pos.z;
	
	//Fire();
	PhaseInitialize();
	
	phase_ = Phase::Approach;
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



	for (EnemyBullet* bullet : bullets_)
	{
		bullet->Update();
	}
	
	//  ワールドトランスの更新
	worldTransform_.UpdeateMatrix();
	// 座標を移動させる（1フレーム分の移動量を足しこむ）
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
	
	

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

	for (EnemyBullet* bullet : bullets_) 
	{

		bullet->Draw(viewProjection_);
	}
	
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

	bullets_.push_back(newBullet);
    }
