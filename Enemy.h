#pragma once
#include <ViewProjection.h>
#include "Model.h"
#include "WorldTransform.h"
#include "EnemyBullet.h"

class Player;

class Enemy 
{
public:
	~Enemy();

	Vector3 velocity_;
	//	//Vector3 velociy_;
	//	/// <summary>
	//	/// 初期化
	//	/// </summary>
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);
	//
	//	/// <summary>
	//	/// 更新
	//	/// </summary>
	void Update();
	//
	//	/// <summary>
	//	/// 描画
	//	/// </summary>
	void Draw(ViewProjection& viewProjection_);

	//Vector3 GetEnemyPosition() { return enemyPosition_; }
	//Vector3 GetEnemyVelocity() { return enemyVelocity_; }

	void ApproachUpdate();

	void LeaveUpdate();

	//攻撃フェイズ初期化
	void PhaseInitialize();

	void Fire();

	void SetPlayer(Player* player) { player_ = player; }

	Vector3 GetWorldPosition();

	Vector3 LerpFanc(Vector3 v1, Vector3 v2);

private:
	// ワールドトランスホーム:
	WorldTransform worldTransform_;
	// モデルポインター
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	
	std::list<EnemyBullet*> bullets_;


	// enum宣言
	enum class Phase 
	{
		Approach, // 接近
		Leave,    // 離脱
	};
	Phase phase_ = Phase();

	static const int kFireInterval = 60;

	int32_t FireTimer = 0;

	Player* player_ = nullptr;



};