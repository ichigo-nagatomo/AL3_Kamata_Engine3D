#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	delete enemy_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	textureHandle_ = TextureManager::Load("uvChecker.png");

	model_ = Model::Create();

	viewProjection_.Initialize();

	player_ = new Player();
	player_->Init(model_ , textureHandle_);

	enemy_ = new Enemy();
	enemy_->Init(model_);
	enemy_->SetPlayer(player_);

	debugCamera_ = new DebugCamera(1280 , 720);

	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
}

void GameScene::Update() {
	player_->Update();

	if (enemy_) {
		enemy_->Update();
	}

	CheckAllCollisions();

#ifdef _DEBUG
	/*if (input_->TriggerKey(DIK_SPACE)) {
		isDebugCamaraActive_ = true;
	}*/
#endif

	if (isDebugCamaraActive_) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;

		viewProjection_.TransferMatrix();
	} else {
		viewProjection_.UpdateMatrix();
	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	player_->Draw(viewProjection_);

	if (enemy_) {
		enemy_->Draw(viewProjection_);
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollisions() {
	Vector3 posA , posB;

	const  std::list<PlayerBullet *> &playerBullets = player_->GetBullets();
	const  std::list<EnemyBullet *> &enemyBullets = enemy_->GetBullets();

	//PtoEB
#pragma region
	posA = player_->GetWorldPos();

	for (EnemyBullet *bullet : enemyBullets) {
		posB = bullet->GetWorldPos();

		float length = AtoBLength(posA , posB);

		if (length <= player_->GetRadius() + bullet->GetRadius()) {
			player_->OnCollision();

			bullet->OnCollision();
		}
	}
#pragma endregion

	//EtoPB
#pragma region
	posA = enemy_->GetWorldPos();

	for (PlayerBullet *bullet : playerBullets) {
		posB = bullet->GetWorldPos();

		float length = AtoBLength(posA , posB);

		if (length <= enemy_->GetRadius() + bullet->GetRadius()) {
			enemy_->OnCollision();

			bullet->OnCollision();
		}
	}
#pragma endregion

	//PBtoEB
#pragma region
	for (PlayerBullet *playerBullet : playerBullets) {
		posA = playerBullet->GetWorldPos();
		for (EnemyBullet *enemyBullet : enemyBullets) {
			posB = enemyBullet->GetWorldPos();

			float length = AtoBLength(posA , posB);

			if (length <= playerBullet->GetRadius() + enemyBullet->GetRadius()) {
				playerBullet->OnCollision();

				enemyBullet->OnCollision();
			}
		}
	}
#pragma endregion

}
