#pragma once
#include <Matrix4x4.h>
#include <Vector3.h>

    Vector3
    Add(const Vector3 v1, const Vector3 v2);

// Scale
Matrix4x4 MakeScaleMatrix(const Vector3 scale);
// Rotate
Matrix4x4 MakeRotateXMatrix(float radian);

Matrix4x4 MakeRotateYMatrix(float radian);

Matrix4x4 MakeRotateZMatrix(float radian);

Matrix4x4 Multiply(const Matrix4x4 m1, const Matrix4x4 m2);

Matrix4x4 MakeRotateXYZMatrix(float radianX, float radianY, float radianZ);

//// Translate
Matrix4x4 MakeTranslateMatrix(Vector3 translate);

Vector3 Transform(const Vector3 vector, const Matrix4x4 matrix);

// AffineMatrix
Matrix4x4 MakeAffineMatrix(const Vector3 scale, const Vector3 rotate, const Vector3 translate);

Matrix4x4 Inverse(const Matrix4x4 m);

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

float Cot(float theta);

// Projection
Matrix4x4 MakeOrthographicMatrix(
    float left, float top, float right, float bottom, float neaClip, float farClip);

Matrix4x4 MakeViewportMatrix(
    float left, float top, float width, float height, float minDepth, float maxDepth);


// Translate
Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);