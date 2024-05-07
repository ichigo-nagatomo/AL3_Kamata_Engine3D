#include "PlayerBullet.h"
#include "cassert"
#include "TextureManager.h"

void PlayerBullet::Init(Model *model , const Vector3 &pos) {
	assert(model);

	model_ = model;
	textureHandle_ = TextureManager::Load("white1x1.png");

	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
}

void PlayerBullet::Update() {
	worldTransform_.UpdateMatrix();
}

void PlayerBullet::Draw(const ViewProjection &viewProjection) {
	model_->Draw(worldTransform_ , viewProjection , textureHandle_);
}
