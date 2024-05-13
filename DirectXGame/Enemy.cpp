#include "Enemy.h"
#include "cassert"
#include "TextureManager.h"

void Enemy::Init(Model *model) {
	assert(model);

	model_ = model;
	textureHandle_ = TextureManager::Load("FalcomStamp3.png");

	worldTransform_.Initialize();

	worldTransform_.translation_.y = 2.0f;
}

void Enemy::Update() {
	worldTransform_.translation_.z -= 0.1f;

	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(ViewProjection &viewProjection) {
	model_->Draw(worldTransform_ , viewProjection , textureHandle_);
}
