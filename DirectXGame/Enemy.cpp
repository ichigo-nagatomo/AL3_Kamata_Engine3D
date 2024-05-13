#include "Enemy.h"
#include "cassert"
#include "TextureManager.h"

Enemy::Enemy() {

}

Enemy::~Enemy() {
	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}
}

void Enemy::Init(Model *model) {
	assert(model);

	model_ = model;
	textureHandle_ = TextureManager::Load("FalcomStamp3.png");

	worldTransform_.Initialize();

	worldTransform_.translation_ = {5.0f, 2.0f, 5.0f};
}

void Enemy::Update() {
	
	switch (phase_) {
		case Phase::Approach:
		default:
			worldTransform_.translation_.z -= 0.1f;

			/*Fire();*/
			/*ApproachInit();*/
			ApproachUpdate();

			//弾更新
			for (EnemyBullet* bullet : bullets_) {
				bullet->Update();
			}

			bullets_.remove_if([](EnemyBullet *bullet) {
				if (bullet->IsDead()) {
					delete bullet;
					return true;
				}
				return false;
			});

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
	const float kBulletSpeed = 0.5f;
	Vector3 velocity(0 , 0 , kBulletSpeed);

	velocity = TransformNormal(velocity , worldTransform_.matWorld_);

	EnemyBullet *newBullet = new EnemyBullet();
	newBullet->Init(model_ , worldTransform_.translation_, velocity);

	bullets_.push_back(newBullet);
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

void Enemy::Draw(ViewProjection &viewProjection) {
	model_->Draw(worldTransform_ , viewProjection , textureHandle_);

	//弾描画
	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}
