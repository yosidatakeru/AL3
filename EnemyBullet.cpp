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

void EnemyBullet::Draw(const ViewProjection& viewProjection) 
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
