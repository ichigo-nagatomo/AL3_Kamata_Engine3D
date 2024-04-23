#include "Player.h"
#include "cassert"
#include "AffineMatrix.h"
#include "ImGuiManager.h"

void Player::Init(Model *model , uint32_t textureHandle) {
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;

	worldTransform_.Initialize();

	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();

}

void Player::Update() {
	worldTransform_.TransferMatrix();

	//キャラクターの移動ベクトル
	Vector3 move = {0.0f, 0.0f, 0.0f};

	//キャラクター移動の速さ
	const float kCharacterSpeed = 0.2f;
	//押した方向で移動ベクトルを変更（左右）
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}

	//押した方向で移動ベクトルを変更（上下）
	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}

	const float kMoveLimitX = 30.0f;
	const float kMoveLimitY = 10.0f;

	worldTransform_.translation_.x = max(worldTransform_.translation_.x , -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x , +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y , -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y , +kMoveLimitY);

	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;

	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_ , worldTransform_.rotation_ , worldTransform_.translation_);


	ImGui::Begin("Debug");
	/*ImGui::SliderFloat3("Player" ,  , -100.0f , 100.0f);*/
	ImGui::End();

}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_ , viewProjection , textureHandle_);
}