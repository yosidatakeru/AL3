#pragma once
#include <Matrix4x4.h>
#include <Vector3.h>

 #pragma once

#include "Matrix4x4.h"
#include "Vector3.h"
#include <cmath>

Vector3 Add(const Vector3 v1, const Vector3 v2);
Matrix4x4 Multiply(const Matrix4x4 m1, const Matrix4x4 m2);

Matrix4x4 MakeScaleMatrix(const Vector3 scale);
Matrix4x4 MakeRotateXMatrix(float radian);

Matrix4x4 MakeRotateYMatrix(float radian);
Matrix4x4 MakeRotateZMatrix(float radian);

Matrix4x4 MakeRotateXYZMatrix(float radianX, float radianY, float radianZ);

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);

float Dot(const Vector3& v1, const Vector3& v2);

float Length(const Vector3& v);

Vector3 Normalize(const Vector3& v);

// Matrix4x4の逆行列計算
Matrix4x4 Inverse(const Matrix4x4 m);