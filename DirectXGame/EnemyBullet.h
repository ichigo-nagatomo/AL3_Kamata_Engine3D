#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "AffineMatrix.h"
#include "Function.h"

class EnemyBullet {
public:
	void Init(Model *model , const Vector3 &pos, const Vector3& velocity);

	void Update();

	void Draw(const ViewProjection &viewProjection);

	Vector3 GetWorldPos();
	float GetRadius() { return radius_; }

	void OnCollision();

private:
	WorldTransform worldTransform_;

	float radius_;

	Model *model_ = nullptr;

	uint32_t textureHandle_ = 0u;


	Vector3 velocity_;

	static const int32_t kLifeTime = 60 * 5;
	int32_t deathTimer_ = kLifeTime;
	bool isDead_ = false;

public:
	bool IsDead() const { return isDead_; }
};

