#pragma once
#include <ViewProjection.h>
#include <WorldTransform.h>

class RailCamera {
public:
	// 初期化
	void Initialize(Vector3 worldCoodinate, Vector3 rotateRadian);

	// 更新
	void Update();

	
	ViewProjection viewProjection_;
	/// <summary>
	/// ワールド変換データを取得
	/// </summary>
	WorldTransform& GetWorldTransform() { return worldTransform_; };

private:
	
	 //ワールドトランスフォーム
	WorldTransform worldTransform_;

	 //ビュープロジェクション
	
};