#include "Player.h"
#include "cassert"
#include "AffineMatrix.h"
#include "ImGuiManager.h"
#include "TextureManager.h"
#include "WinApp.h"
#include "ViewProjection.h"


Player::Player() {

}

Player::~Player() {
	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}
	delete sprite2DReticle_;
}

void Player::Init(Model *model , uint32_t textureHandle, Vector3 playerPos) {
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;

	worldTransform_.Initialize();

	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();

	worldTransform_.translation_ = playerPos;

	radius_ = 1.5f;

	worldTransform3DReticle_.Initialize();

	uint32_t textureReticle = TextureManager::Load("target.png");
	sprite2DReticle_ = Sprite::Create(textureReticle ,
									  {worldTransform3DReticle_.translation_.x, worldTransform3DReticle_.translation_.y} ,
									  {255, 255, 255, 255} ,
									  {0.5f, 0.5f});
}

void Player::Update(const ViewProjection &viewProjection) {
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
	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}

	bullets_.remove_if([](PlayerBullet *bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

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


	const float kDistancePlayerTo3DReticle = 50.0f;

	Vector3 offset = {0, 0, 1.0f};

	offset = TransformNormal(offset , worldTransform_.matWorld_);

	offset = MultiplyVec3(kDistancePlayerTo3DReticle, Normalize(offset));

	worldTransform3DReticle_.translation_ = Add(GetWorldPos(), offset);

	worldTransform3DReticle_.UpdateMatrix();


	//
	Vector3 positionReticle = Get3DReticleWorldPos();

	Matrix4x4 matViewport = MakeViewportMatrix(0 , 0 , WinApp::kWindowWidth , WinApp::kWindowHeight , 0 , 1);

	Matrix4x4 matViewProjectionViewport =
		MultiplyM2M(viewProjection.matView , MultiplyM2M(viewProjection.matProjection , matViewport));

	positionReticle = Transform(positionReticle , matViewProjectionViewport);

	sprite2DReticle_->SetPosition(Vector2(positionReticle.x , positionReticle.y));
}

void Player::Attack() {

	if (input_->TriggerKey(DIK_SPACE)) {
		const float kBulletSpeed = 1.0f;
		Vector3 velocity;

		velocity = Subtract(worldTransform3DReticle_.translation_ , GetWorldPos());
		velocity = MultiplyVec3(kBulletSpeed , Normalize(velocity));

		/*velocity = TransformNormal(velocity , worldTransform_.matWorld_);*/

		PlayerBullet *newBullet = new PlayerBullet();
		newBullet->Init(model_ , GetWorldPos() , velocity);

		bullets_.push_back(newBullet);
	}
}

Vector3 Player::GetWorldPos() {
	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

Vector3 Player::Get3DReticleWorldPos() {
	Vector3 worldPos;

	worldPos.x = worldTransform3DReticle_.matWorld_.m[3][0];
	worldPos.y = worldTransform3DReticle_.matWorld_.m[3][1];
	worldPos.z = worldTransform3DReticle_.matWorld_.m[3][2];

	return worldPos;
}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_ , viewProjection , textureHandle_);

	model_->Draw(worldTransform3DReticle_ , viewProjection);

	//弾描画
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}


#ifdef _DEBUG
	
#endif
}

void Player::DrawUI() {
	sprite2DReticle_->Draw();
}

void Player::OnCollision() {
	
}

void Player::SetParent(const WorldTransform *parent) {
	worldTransform_.parent_ = parent;
}