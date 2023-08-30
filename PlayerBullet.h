#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include"Function.h"
/// <summary>
/// 自キャラの弾
/// </summary>
class PlayerBullet
{

public:

		Vector3 velociy_;

		bool IsDead() const { return isDead_; }
	/// <summary>
	/// 初期化
	/// </summary>
	//<param name ="model">モデル</param>
	//<param name ="position">初期座標</param>
	    void Initalize(Model* model, const Vector3& position, const Vector3& velocity);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection& viewProjection_);

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;

	// 寿命
	static const int32_t kLifeTime = 60 * 5;


	// デストタima
	int32_t deathTimer_ = kLifeTime;

	// デスフラグ
	bool isDead_ = false;
};