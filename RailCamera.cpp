#include "RailCamera.h"
#include <Function.h>
#include<imgui.h>

void RailCamera::Initialize(Vector3 worldCoodinate, Vector3 rotateRadian) 
{
	
	/*	worldTransform_.Initialize();
	worldTransform_.translation_ = worldCoodinate;

		worldTransform_.rotation_ = rotateRadian;

		viewProjection_.Initialize();
		viewProjection_.farZ = 1200.0f;*/

	// ワールドトランスフォームの初期設定
	worldTransform_.translation_.x = worldCoodinate.x;
	worldTransform_.translation_.y = worldCoodinate.y;
	worldTransform_.translation_.z = worldCoodinate.z - 10.0f;

	worldTransform_.rotation_ = rotateRadian;
	worldTransform_.Initialize();

	// ビュープロジェクションの初期化
	viewProjection_.farZ = 1200.0f;

	viewProjection_.Initialize();
}
//
void RailCamera::Update() 
{
	    // 移動量の加算
	    worldTransform_.translation_ = Add(worldTransform_.translation_, {0.0f, 0.0f, 0.2f});

	    // 回転量の加算
	    Vector3 rotate = {0.0f, 0.0f, 0.0f};
	    worldTransform_.rotation_ = Add(worldTransform_.rotation_, rotate);

	    // ワールド行列の再計算
	    // ここで問題
	    worldTransform_.UpdeateMatrix();

	    // カメラオブジェクトのワールド行列からビュー行列を計算する
	    viewProjection_.matView = Inverse(worldTransform_.matWorld_);

		// カメラの座標を画面表示する処理
	    ImGui::Begin("RailCamera");
	    ImGui::SliderFloat3("translate", &worldTransform_.translation_.x, -100.0f, 100.0f);
	    ImGui::SliderFloat3("rotate", &worldTransform_.rotation_.x, -10.0f, 10.0f);
	    ImGui::End();
}



