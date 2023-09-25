#pragma once
#pragma once
#include <Model.h>
#include <ViewProjection.h>
#include <WorldTransform.h>
#include <Player.h>


class EnemyBullet {
public:
	EnemyBullet();
	~EnemyBullet();

	void Initialize(Model* model, Vector3& position, const Vector3& velocity);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

	// ワールド座標を取得
	Vector3 GetWorldPosition();

	float_t GetRadius() { return radius_; }

	bool IsDead() const { return isDead_; }

private:
	uint32_t textureHandle_=0u;
	Model* model_;
	WorldTransform worldTransform_;

	Vector3 kVelocity_ = {};

	bool isDead_ = false;

	
    const float_t radius_ = 1.0f;
};