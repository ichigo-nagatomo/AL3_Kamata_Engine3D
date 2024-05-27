#include "Skydome.h"
#include "cassert"

void Skydome::Init(Model *model) {
	assert(model);

	model_ = model;

	worldTransform_.Initialize();
}

void Skydome::Update() {
	worldTransform_.TransferMatrix();
}

void Skydome::Draw(ViewProjection &viewProjection) {
	model_->Draw(worldTransform_ , viewProjection);
}