#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "AffineMatrix.h"

class PlayerBullet {
public:
	void Init(Model *model , const Vector3 &pos);

	void Update();

	void Draw(const ViewProjection &viewProjection);

private:
	WorldTransform worldTransform_;

	Model *model_ = nullptr;

	uint32_t textureHandle_ = 0u;
};

