#include "WorldTransform.h"
#include "AffineMatrix.h"

void WorldTransform::UpdateMatrix() {
	matWorld_ = MakeAffineMatrix(scale_ , rotation_ , translation_);
	TransferMatrix();
}