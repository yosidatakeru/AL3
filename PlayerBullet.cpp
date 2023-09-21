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

// 衝突を検出したら呼び出されるコールバック関数
void PlayerBullet::OnCollision() { isDead_ = true; }


// ワールド座標を取得
Vector3 PlayerBullet::GetWorldPosition()
{
	Vector3 worldPos;

	// ワールド行列の「平行移動成分」を取得(ワールド座標)
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}


void PlayerBullet::Draw(ViewProjection& viewProjection_) 
{
	if (isDead_ == false)
	{
		//モデルの描画
		 model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	}
	
}
