#include "Enemy.h"
#include "cassert"
#include "TextureManager.h"
#include "Player.h"
#include "GameScene.h"

Enemy::Enemy() {

}

Enemy::~Enemy() {
	
}

void Enemy::Init(Model *model, Vector3 pos) {
	assert(model);

	model_ = model;
	textureHandle_ = TextureManager::Load("FalcomStamp3.png");

	worldTransform_.Initialize();

	worldTransform_.translation_ = {pos.x, pos.y, pos.z};

	radius_ = 1.5f;
}

void Enemy::Update() {
	
	switch (phase_) {
		case Phase::Approach:
		default:
			worldTransform_.translation_.z -= 0.02f;

			/*Fire();*/
			/*ApproachInit();*/
			ApproachUpdate();

			

			if (worldTransform_.translation_.z < 0.0f) {
				/*phase_ = Phase::Leave;*/
			}
			break;

		case Phase::Leave:
			worldTransform_.translation_.x += 0.1f;
			worldTransform_.translation_.y += 0.1f;
			break;
	}

	worldTransform_.UpdateMatrix();
}

void Enemy::Fire() {
	assert(player_);

	const float kBulletSpeed = 1.0f;

	Vector3 subVec3(Subtract(player_->GetWorldPos(), GetWorldPos()));

	subVec3 = Normalize(subVec3);

	Vector3 velocity = MultiplyVec3(kBulletSpeed, subVec3);

	EnemyBullet *newBullet = new EnemyBullet();
	newBullet->Init(model_ , worldTransform_.translation_, velocity);
	gameScene_->AddEnemyBullet(newBullet);
	
	/*if (input_->TriggerKey(DIK_SPACE)) {
		
	}*/
}

void Enemy::ApproachInit() {
	isShootTime_ = 60;
}

void Enemy::ApproachUpdate() {
	isShootTime_--;

	if (isShootTime_ <= 0) {
		Fire();

		ApproachInit();
	}
}

Vector3 Enemy::GetWorldPos() {
	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Enemy::Draw(ViewProjection &viewProjection) {
	model_->Draw(worldTransform_ , viewProjection , textureHandle_);
}

void Enemy::OnCollision() {
	isDead_ = true;
}
