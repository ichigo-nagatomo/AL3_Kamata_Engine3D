#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "AffineMatrix.h"
#include "PlayerBullet.h"
#include <list>
#include "Function.h"

class Player {
public:
	Player();

	~Player();

	//初期化
	void Init(Model *model , uint32_t textureHandle);

	//更新
	void Update();

	//描画
	void Draw(ViewProjection &viewProjection);

	void Attack();


	Vector3 GetWorldPos();

private:
	WorldTransform worldTransform_;

	Model *model_ = nullptr;

	uint32_t textureHandle_ = 0u;

	//キーボード
	Input *input_ = nullptr;

	float inputFloat3[3] = {0, 0, 0};

	//弾
	std::list<PlayerBullet*> bullets_;

};