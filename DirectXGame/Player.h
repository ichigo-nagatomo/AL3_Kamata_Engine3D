#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "AffineMatrix.h"
#include "PlayerBullet.h"
#include <list>
#include "Function.h"
#include "Sprite.h"

class Player {
public:
	Player();

	~Player();

	//初期化
	void Init(Model *model , uint32_t textureHandle, Vector3 pos);

	//更新
	void Update(const ViewProjection &viewProjection);

	//描画
	void Draw(ViewProjection &viewProjection);

	void Attack();


	Vector3 GetWorldPos();
	float GetRadius() { return radius_; }

	void OnCollision();
	const std::list<PlayerBullet *> &GetBullets() const { return bullets_; }


	void SetParent(const WorldTransform *parent);

	void DrawUI();

	Vector3 Get3DReticleWorldPos();

private:
	WorldTransform worldTransform_;

	float radius_;

	Model *model_ = nullptr;

	uint32_t textureHandle_ = 0u;

	//キーボード
	Input *input_ = nullptr;

	float inputFloat3[3] = {0, 0, 0};

	//弾
	std::list<PlayerBullet*> bullets_;

	WorldTransform worldTransform3DReticle_;

	Sprite *sprite2DReticle_ = nullptr;
};