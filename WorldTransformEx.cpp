#include "WorldTransform.h"
#include <Function.h>

void WorldTransform::UpdeateMatrix() 
{
	// スケール.回転.平行移動を合成して行列を計算する
	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);
	// 定数バッファ転送
	TransferMatrix();
}