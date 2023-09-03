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

private:
	uint32_t textureHandle_=0u;
	Model* model_;
	WorldTransform worldTransform_;

	Vector3 kVelocity_ = {};

	bool isDead_ = false;
};