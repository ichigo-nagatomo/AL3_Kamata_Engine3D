#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "EnemyBullet.h"

class Player;

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


	void SetPlayer(Player *player) { player_ = player; }

	Vector3 GetWorldPos();
	float GetRadius() { return radius_; }

	void OnCollision();
	const std::list<EnemyBullet *> &GetBullets() const { return bullets_; }
private:
	WorldTransform worldTransform_;

	float radius_;

	Model *model_ = nullptr;

	uint32_t textureHandle_ = 0u;

	Phase phase_ = Phase::Approach;

	//弾
	std::list<EnemyBullet*> bullets_;

	int32_t isShootTime_ = 0;


	Player *player_ = nullptr;
};



