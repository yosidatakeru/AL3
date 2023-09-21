#include "EnemyBullet.h"
#include <Function.h>
#include<cassert>


EnemyBullet::EnemyBullet()
{

};

EnemyBullet::~EnemyBullet()
{

}
void EnemyBullet::Initialize(Model* model, Vector3& position, const Vector3& velocity)
{
	model_ = model;
	textureHandle_ = TextureManager::Load("debugfont.png");

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	kVelocity_ = velocity;
};



void EnemyBullet::Update() 
{
	worldTransform_.translation_ = Add(worldTransform_.translation_, kVelocity_);
	worldTransform_.UpdeateMatrix();

}

// 衝突を検出したら呼び出されるコールバック関数
void EnemyBullet::OnCollision() { isDead_ = true; }



void EnemyBullet::Draw(const ViewProjection& viewProjection) 
{
	if (isDead_ == false) 
	{
		model_->Draw(worldTransform_, viewProjection, textureHandle_);
	}
}




Vector3 EnemyBullet::GetWorldPosition() 
{
	Vector3 worldPos;

	// ワールド行列の「平行移動成分」を取得(ワールド座標)
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}