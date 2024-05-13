#pragma once
#include "Model.h"
#include "WorldTransform.h"

enum class Phase {
	Approach,
	Leave,
};

class Enemy {
public:
	void Init(Model *model);

	void Update();

	void Draw(ViewProjection &viewProjection);

private:
	WorldTransform worldTransform_;

	Model *model_ = nullptr;

	uint32_t textureHandle_ = 0u;

	Phase phase_ = Phase::Approach;
};



