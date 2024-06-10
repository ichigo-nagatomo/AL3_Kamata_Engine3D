#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include "DebugCamera.h"
#include "Enemy.h"
#include "Skydome.h"
#include "RailCamara.h"
#include <sstream>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();


	void CheckAllCollisions();


	void AddEnemyBullet(EnemyBullet *enemyBullet);
	const std::list<EnemyBullet *> &GetBullets() const { return enemyBullets_; }

	void EnemyInit(Vector3 pos);
	void LoadEnemyPopData();
	void UpdateEnemyCommands();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	
	//テクスチャハンドル
	uint32_t textureHandle_ = 0;

	//3Dモデル
	Model *model_ = nullptr;

	//ビュープロジェクション
	ViewProjection viewProjection_;

	//自キャラ
	Player *player_ = nullptr;

	//敵
	/*Enemy *enemy_ = nullptr;*/
	std::list<Enemy*> enemies_;

	//弾
	std::list<EnemyBullet*> enemyBullets_;

	std::stringstream enemyPopCommands;
	bool isWait = false;
	int waitTimer_;

	DebugCamera *debugCamera_ = nullptr;

	bool isDebugCamaraActive_ = false;

	//天球
	Model *skyModeModel_ = nullptr;
	Skydome *modelSkydome_ = nullptr;


	RailCamara *railCamara_ = nullptr;
};
