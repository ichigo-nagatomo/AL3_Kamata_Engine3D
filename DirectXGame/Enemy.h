#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "EnemyBullet.h"

enum class Phase {
	Approach,
	Leave,
};

class Enemy {
public:
	Enemy();

	~Enemy();

	void Init(Model *model);

	void Update();

	void Draw(ViewProjection &viewProjection);

	void Fire();

	void ApproachInit();

	void ApproachUpdate();

private:
	WorldTransform worldTransform_;

	Model *model_ = nullptr;

	uint32_t textureHandle_ = 0u;

	Phase phase_ = Phase::Approach;

	//弾
	std::list<EnemyBullet*> bullets_;

	int32_t isShootTime_ = 0;
};



