#pragma once
#include "Matrix4x4.h"
#include <cmath>
#include "Vector3.h"

//単位行列の作成
Matrix4x4 MakeIdentity4x4();

//行列の積
Matrix4x4 Multiply(const Matrix4x4 &matrix1 , const Matrix4x4 &matrix2);

//Scale
Matrix4x4 MakeScaleMatrix(const Vector3 &scale);

//Rotate
Matrix4x4 MakeRotateXMatrix(float radian);

Matrix4x4 MakeRotateYMatrix(float radian);

Matrix4x4 MakeRotateZMatrix(float radian);

Matrix4x4 MakeRotateMatrix(const Vector3 &rotate);

//Translate
Matrix4x4 MakeTranslateMatrix(const Vector3 &translate);

//Affine
Matrix4x4 MakeAffineMatrix(const Vector3 &scale , const Vector3 &rotate , const Vector3 &translate);

