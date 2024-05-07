#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "AffineMatrix.h"


class Player {
public:
	//初期化
	void Init(Model *model , uint32_t textureHandle);

	//更新
	void Update();

	//描画
	void Draw(ViewProjection &viewProjection);

private:
	WorldTransform worldTransform_;

	Model *model_ = nullptr;

	uint32_t textureHandle_ = 0u;

	//キーボード
	Input *input_ = nullptr;

	float inputFloat3[3] = {0, 0, 0};

};