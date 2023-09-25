#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Player.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <DebugCamera.h>
#include"Enemy.h"
#include"Skydome.h"
#include"RailCamera.h"
#include"sstream"
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


	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollision();

	//弾リスト
	void AddEnemyBullet(EnemyBullet* enemyBullet);


	void generatedEnemy(Vector3 pos);

	void LoadEnemyPopDate();


	/// <summary>
	/// スクリプト実行
	/// </summary>
	void UpdateEnemyPopCommands();


private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	// 3Dモデル
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0;
	ViewProjection viewProjection_;
	Player* player_ = nullptr;
	bool isDebgCameraActive_ = false;
	DebugCamera* debugCamera_ = nullptr;
	Model* enemyModel_ = nullptr;
	Enemy* enemy_ = nullptr;

	// 敵弾リスト
	std::list<EnemyBullet*> enemyBullets_;

	// 敵発生コマンド
	std::stringstream enemyPopCommands;

	#pragma region 天球のメンバ変数
	// テクスチャハンドル
	uint32_t skydomeTextureHandle_ = 0u;

	// 3Dモデル
	Model* skydomeModel_ = nullptr;

	// 天球ポインタ
	Skydome* skydome_ = nullptr;
	RailCamera* railCamera_ = nullptr;

	// 待機フラグ
	bool isEnemyStay = false;

	// 待機タイマー
	uint32_t enemyStayTimer = 0;

	// 敵リスト
	std::list<Enemy*> enemys_;
};