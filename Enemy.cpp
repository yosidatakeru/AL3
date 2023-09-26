#include "Enemy.h"
#include "Function.h"
#include <cassert>

    void Enemy::Initialize(Model* model, const Vector3& position, const Vector3& velocity) 
    {
	// NULLチェック
	assert(model);

	model_ = model;
	// 敵
	textureHandle_ = TextureManager::Load("Player6.png");
	// ワールド変数の初期化
	worldTransform_.Initialize();
	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;

	velocity_ = velocity;
    }

	// 座標を移動させる（1フレーム分の移動量を足しこむ）
   // worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
    const float EnemykRotSpeed = 0.80f;

	void Enemy::ApproachUpdate() {
	// 移動(ベクトルの加算)
	
		// 移動（ベクトル加算）
	worldTransform_.translation_.z -= EnemykRotSpeed;
	;
	// 指定の位置に到達したら離脱する
	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}

	
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
	switch (phase_) {
	case Phase::Approach:
	default:
		ApproachUpdate();

		break;

	case Phase::Leave:
		LeaveUpdate();
		break;
	}


	// Vector3 enemyPosition_;
	//  ワールドトランスの更新
	worldTransform_.UpdeateMatrix();
	// 座標を移動させる（1フレーム分の移動量を足しこむ）
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
    }

    void Enemy::Draw(ViewProjection& viewProjection_) 
    {
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
    }
