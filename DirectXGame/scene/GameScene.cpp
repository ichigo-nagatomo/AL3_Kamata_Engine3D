#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"
#include <fstream>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	/*delete enemy_;*/
	for (Enemy* enemy : enemies_) {
		delete enemy;
	}
	for (EnemyBullet* bullet : enemyBullets_) {
		delete bullet;
	}
	delete debugCamera_;
	delete modelSkydome_;
	delete railCamara_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	textureHandle_ = TextureManager::Load("uvChecker.png");

	model_ = Model::Create();

	viewProjection_.Initialize();

	railCamara_ = new RailCamara();
	railCamara_->Init({0, 0, 0}, {0, 0, 0});

	TextureManager::Load("target.png");

	player_ = new Player();
	Vector3 playerPos(0 , 0 , 20);
	player_->Init(model_ , textureHandle_, playerPos);
	player_->SetParent(&railCamara_->GetWorldTransform());

	Enemy *newEnemy = new Enemy();
	newEnemy->Init(model_ , {5.0f, 2.0f, 15.0f});
	newEnemy->SetPlayer(player_);
	newEnemy->SetGameScene(this);
	enemies_.push_back(newEnemy);
	

	debugCamera_ = new DebugCamera(1280 , 720);

	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	skyModeModel_ = Model::CreateFromOBJ("skydome" , true);
	modelSkydome_ = new Skydome();
	modelSkydome_->Init(skyModeModel_);

	LoadEnemyPopData();
}

void GameScene::EnemyInit(Vector3 pos) {
	Enemy *newEnemy = new Enemy();
	newEnemy->Init(model_ , {pos.x, pos.y, pos.z});
	newEnemy->SetPlayer(player_);
	newEnemy->SetGameScene(this);
	enemies_.push_back(newEnemy);
}

void GameScene::Update() {
	modelSkydome_->Update();

	player_->Update(viewProjection_);

	for (Enemy* enemy : enemies_) {
		if (enemy) {
			enemy->Update();
		}
	}

	enemies_.remove_if([](Enemy *enemy) {
		if (enemy->IsDead()) {
			delete enemy;
			return true;
		}
		return false;
	});

	
	//弾更新
	for (EnemyBullet* bullet : enemyBullets_) {
		bullet->Update();
	}

	enemyBullets_.remove_if([](EnemyBullet *bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	UpdateEnemyCommands();

	CheckAllCollisions();

	railCamara_->Update();

	viewProjection_.matView = railCamara_->GetViewProjection().matView;
	viewProjection_.matProjection = railCamara_->GetViewProjection().matProjection;
	viewProjection_.TransferMatrix();

#ifdef _DEBUG
	if (input_->TriggerKey(DIK_C)) {
		isDebugCamaraActive_ = true;
	}
#endif

	if (isDebugCamaraActive_) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;

		viewProjection_.TransferMatrix();
	} else {
		/*viewProjection_.UpdateMatrix();*/
	}
}

void GameScene::AddEnemyBullet(EnemyBullet *enemyBullet) {
	enemyBullets_.push_back(enemyBullet);
}

void GameScene::LoadEnemyPopData() {
	std::ifstream file;
	file.open("Resources/enemyPop.csv");
	assert(file.is_open());

	enemyPopCommands << file.rdbuf();

	file.close();
}

void GameScene::UpdateEnemyCommands() {
	if (isWait) {
		waitTimer_--;
		if (waitTimer_ <= 0) {
			isWait = false;
		}
		return;
	}

	std::string line;

	while (getline(enemyPopCommands, line)) {

		std::istringstream line_stream(line);

		std::string word;

		getline(line_stream , word , ',');

		if (word.find("//") == 0) {
			continue;
		}

		if (word.find("POP") == 0) {
			getline(line_stream , word , ',');
			float x = (float)std::atof(word.c_str());

			getline(line_stream , word , ',');
			float y = (float)std::atof(word.c_str());

			getline(line_stream , word , ',');
			float z = (float)std::atof(word.c_str());

			EnemyInit(Vector3(x , y , z));

		} else if (word.find("WAIT") == 0) {
			getline(line_stream , word , ',');

			int32_t waitTime = atoi(word.c_str());

			isWait = true;
			waitTimer_ = waitTime;

			break;
		}
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
	modelSkydome_->Draw(viewProjection_);

	player_->Draw(viewProjection_);

	for (Enemy* enemy : enemies_) {
		if (enemy) {
			enemy->Draw(viewProjection_);
		}
	}
	

	//弾描画
	for (EnemyBullet* bullet : enemyBullets_) {
		bullet->Draw(viewProjection_);
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	player_->DrawUI();

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
	const  std::list<EnemyBullet *> &enemyBullets = GetBullets();

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
	for (Enemy* enemy : enemies_) {
		posA = enemy->GetWorldPos();
		for (PlayerBullet *bullet : playerBullets) {
			posB = bullet->GetWorldPos();

			float length = AtoBLength(posA , posB);

			if (length <= enemy->GetRadius() + bullet->GetRadius()) {
				enemy->OnCollision();

				bullet->OnCollision();
			}
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
