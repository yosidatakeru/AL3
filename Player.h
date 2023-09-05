#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Function.h"
#include "Input.h"
#include"PlayerBullet.h"
#include<list>
class Player {

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();
	/// <summary>
	/// 自キャラ
	/// </summary>
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection& viewProjection_);

	/// <summary>
	// 攻撃
	/// </summary>
	void Attack();

	//// 弾
	std::list<PlayerBullet*> bullets_;

	Vector3 GetWorldPosition();


private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Player* player_ = nullptr;
	// キーボード入力
	Input* input_ = nullptr;
	// 弾
	PlayerBullet* bullet_ = nullptr;
	//Vector3 velociy_;
};