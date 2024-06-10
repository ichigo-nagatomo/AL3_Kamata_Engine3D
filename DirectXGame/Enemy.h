#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "EnemyBullet.h"

class GameScene;

class Player;

enum class Phase {
	Approach,
	Leave,
};

class Enemy {
public:
	Enemy();

	~Enemy();

	void Init(Model *model, Vector3 pos);

	void Update();

	void Draw(ViewProjection &viewProjection);

	void Fire();

	void ApproachInit();

	void ApproachUpdate();


	void SetPlayer(Player *player) { player_ = player; }

	Vector3 GetWorldPos();
	float GetRadius() { return radius_; }

	void OnCollision();
	bool IsDead() const { return isDead_; }

	void SetGameScene(GameScene *gameScene) { gameScene_ = gameScene; }
private:
	GameScene *gameScene_ = nullptr;

	WorldTransform worldTransform_;

	float radius_;

	Model *model_ = nullptr;

	uint32_t textureHandle_ = 0u;

	Phase phase_ = Phase::Approach;

	int32_t isShootTime_ = 60;

	/*std::list<EnemyBullet*> enemyBullets_;*/

	Player *player_ = nullptr;

	bool isDead_ = false;
};



