#include "EnemyBullet.h"
#include "cassert"
#include "TextureManager.h"

void EnemyBullet::Init(Model *model , const Vector3 &pos , const Vector3& velocity) {
	assert(model);

	model_ = model;
	textureHandle_ = TextureManager::Load("white1x1.png");

	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;

	velocity_ = velocity;
}

void EnemyBullet::Update() {
	worldTransform_.translation_.x += velocity_.x;
	worldTransform_.translation_.y += velocity_.y;
	worldTransform_.translation_.z += velocity_.z;

	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

	worldTransform_.UpdateMatrix();
}

void EnemyBullet::Draw(const ViewProjection &viewProjection) {
	model_->Draw(worldTransform_ , viewProjection , textureHandle_);
}
