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
#include<sstream>
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

	// 登録用の関数 
	void AddEnemyBullet(EnemyBullet* enemyBullet);

	void GenerateEnemy(Vector3 position);

	/// <summary>
	/// 敵発生データの読み込み
	/// </summary>
	void LoadEnemyPopDate();

	/// <summary>
	/// スクリプト実行
	/// </summary>
	void UpdateEnemyPopCommands();

private: // メンバ変数

	/* ----- Player 自キャラ ----- */

	Player* player_ = nullptr;

	/* ----- Enemy 敵キャラ ----- */

	Model* enemyModel_ = nullptr;
	Enemy* enemy_ = nullptr;

	
	uint32_t enemyTexture_ = 0;
	// 引っ越し
	// 1.敵弾リストを敵からゲームシーンに引っ越す
	std::list<EnemyBullet*> enemyBullets_;

		// さっさと引っ越し
	std::list<Enemy*> enemyes_;

	// 敵発生コマンド
	std::stringstream enemyPopCommands;

	// 待機タイマー
	uint32_t enemyStayTimer = 0;

	// 待機フラグ
	bool isEnemyStay = false;

	// 待機中フラグ
	bool isWait_;
	/* ----- SkyDome 天球 ----- */

	// テクスチャハンドル
	uint32_t skydomeTextureHandle_ = 0u;

	// 3Dモデル
	Model* skydomeModel_ = nullptr;

	// 天球ポインタ
	Skydome* skydome_ = nullptr;
	RailCamera* railCamera_ = nullptr;

	
	

	/* ----- Camera カメラ ----- */
	DirectXCommon* dxCommon_ = nullptr;
	bool isDebgCameraActive_ = false;
	DebugCamera* debugCamera_ = nullptr;

	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	// 3Dモデル
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0;
	ViewProjection viewProjection_;
	
	


	
	

	
	
	

	
};