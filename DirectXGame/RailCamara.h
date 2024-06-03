#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Function.h"

class RailCamara {
public:
	void Init(const Vector3 &pos, const Vector3& radian);
	void Update();

	const ViewProjection& GetViewProjection() { return viewProjection_; }

	const WorldTransform& GetWorldTransform() { return worldTransform_; }

private:
	WorldTransform worldTransform_;

	ViewProjection viewProjection_;

};

