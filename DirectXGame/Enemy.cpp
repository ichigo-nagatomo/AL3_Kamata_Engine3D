#include "Enemy.h"
#include "cassert"
#include "TextureManager.h"

void Enemy::Init(Model *model) {
	assert(model);

	model_ = model;
	textureHandle_ = TextureManager::Load("FalcomStamp3.png");

	worldTransform_.Initialize();

	worldTransform_.translation_.y = 2.0f;
	worldTransform_.translation_.z = 5.0f;
}

void Enemy::Update() {
	
	switch (phase_) {
		case Phase::Approach:
		default:
			worldTransform_.translation_.z -= 0.1f;

			if (worldTransform_.translation_.z < 0.0f) {
				phase_ = Phase::Leave;
			}
			break;

		case Phase::Leave:
			worldTransform_.translation_.x += 0.1f;
			worldTransform_.translation_.y += 0.1f;
			break;
	}

	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(ViewProjection &viewProjection) {
	model_->Draw(worldTransform_ , viewProjection , textureHandle_);
}
