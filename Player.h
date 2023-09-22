#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Function.h"
#include "Input.h"
#include"PlayerBullet.h"
#include<list>
#include<Sprite.h>
class Player {

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();
	/// <summary>
	/// 自キャラ
	/// </summary>
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle);

	/// <summary>
	/// 更新
	/// </summary>
	void Update(ViewProjection &viewProjection);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection& viewProjection_);

	/// <summary>
	// 攻撃
	/// </summary>
	void Attack();

	//// 弾
	std::list<PlayerBullet*> bullets_;
	//プレイヤーの位置
	Vector3 GetWorldPosition();

	// ワールド座標を取得
	Vector3 GetReticleWorldPosition();

	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

	// 弾リストを取得
	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; };

	const float_t GetRadius() { return radius_; };

	/// <summary>
	/// UI描画
	/// </summary>
	void DrawUI();


// <summary>
	/// 親となるワールドトランスフォームをセット
	/// </summary>
	/// <param name="parent"></param>
	void SetParent(const WorldTransform* parent);


	//レティクルの位置
	void ReticleUpdate(ViewProjection viewProjection);
	
	private:
	// ワールド変換データ

		const float kBulletSpeed = 5.0f;
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Player* player_ = nullptr;
	// キーボード入力
	Input* input_ = nullptr;
	// 弾
	PlayerBullet* bullet_ = nullptr;
	//Vector3 velociy_;

	const float_t radius_ = 2.0f;

	// 3Dレティクル用ワールドトランスフォーム
	WorldTransform worldTransform3DReticle_;


		// テクスチャハンドル
	uint32_t ReticleTextureHandle_ = 0u;

	/* ----- 2DReticle 2Dレティクル ----- */

	// スプライト生成
	Sprite* sprite2DReticle_ = nullptr;

	// レティクルの2D座標
	Vector3 position2DReticle_;

	// ビューポート行列
	Matrix4x4 matViewport_;

	// ビュー行列とプロジェクション行列
	Matrix4x4 matViewProjectionViewport_;

	// ビュープロジェクションビューポート合成行列
	Matrix4x4 matVPV_;

	// 合成行列の逆行列
	Matrix4x4 matInverseVPV_;

	// スクリーン座標
	Vector3 posNear_;
	Vector3 posFar_;

	// スプライトの座標取得用
	Vector2 spritePosition_;

	// マウス座標
	POINT mousePosition_;

	HWND hwnd = nullptr;
	
	// マウス例の方向
	Vector3 mouseDirection_;

	// カメラから照準オブジェクトの距離
	const float kDistanceTestObject = 100.0f;


};