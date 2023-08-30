#include "PlayerBullet.h"
#include <cassert>

void PlayerBullet::Initalize(Model* model, const Vector3& position, const Vector3& velocity) 
{
	// NULLポインタチェック
	assert(model);

	model_ = model;
	// テクスチャ読み込む
	textureHandle_ = TextureManager::Load("tex1.png");
	// ワールド変数の初期化
	worldTransform_.Initialize();
	// position初期座標
	// 因数で受け取った初期座標をセット
	worldTransform_.translation_ = position;

	// 引数で受けっとた速度
	velociy_ = velocity;
}

void PlayerBullet::Update() 
{
	// ワールドトランスの更新
	worldTransform_.UpdeateMatrix();

	// 座標を移動させる（1フレーム分の移動量を足しこむ）
	worldTransform_.translation_ = Add(worldTransform_.translation_, velociy_);

    // 時間経過デス
	if (--deathTimer_ <= 0) 
	{
		isDead_ = true;
	}
}

void PlayerBullet::Draw(ViewProjection& viewProjection_) 
{
	// モデルの描画
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
}
