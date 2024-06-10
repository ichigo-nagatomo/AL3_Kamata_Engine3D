#include "RailCamara.h"
#include "ImGuiManager.h"

void RailCamara::Init(const Vector3 &pos, const Vector3& radian) {
	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
	worldTransform_.rotation_ = radian;


	viewProjection_.Initialize();

}

void RailCamara::Update() {
	worldTransform_.translation_ = Add(worldTransform_.translation_, {0, 0, 0.01f});
	/*worldTransform_.rotation_ = Add(worldTransform_.rotation_ , {0, 0.001f, 0});*/

	worldTransform_.UpdateMatrix();

	viewProjection_.matView = Inverse(worldTransform_.matWorld_);

	ImGui::Begin("Camara");
	ImGui::SliderFloat3("Camara T" , (float*)&worldTransform_.translation_.x , -10.0f , 10.0f);
	ImGui::SliderFloat3("Camara R" , (float*)&worldTransform_.rotation_.x, -1.0f , 1.0f);
	ImGui::End();
}
