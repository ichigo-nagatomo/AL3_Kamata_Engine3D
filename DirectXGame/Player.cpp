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

	//回転
	const float kRotSpeed = 0.02f;

	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	} else if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}

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

	//攻撃処理
	Attack();

	//弾更新
	if (bullet_) {
		bullet_->Update();
	}

	const float kMoveLimitX = 30.0f;
	const float kMoveLimitY = 10.0f;

	worldTransform_.translation_.x = max(worldTransform_.translation_.x , -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x , +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y , -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y , +kMoveLimitY);

	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;

	worldTransform_.UpdateMatrix();

	inputFloat3[0] = worldTransform_.translation_.x;
	inputFloat3[1] = worldTransform_.translation_.y;
	inputFloat3[2] = worldTransform_.translation_.z;

	ImGui::Begin("Debug");
	ImGui::SliderFloat3("Player" , (float*)&worldTransform_.translation_.x , -50.0f , 50.0f);
	ImGui::End();

}

void Player::Attack() {
	if (input_->TriggerKey(DIK_SPACE)) {
		PlayerBullet *newBullet = new PlayerBullet();
		newBullet->Init(model_ , worldTransform_.translation_);

		bullet_ = newBullet;
	}
}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_ , viewProjection , textureHandle_);

	//弾描画
	if (bullet_) {
		bullet_->Draw(viewProjection);
	}


#ifdef _DEBUG
	
#endif
}