#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"
#include <assert.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

Vector3 Vector3Add(const Vector3 &v1 , const Vector3 &v2);

Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);

Vector3 Transform(const Vector3 &vector , const Matrix4x4 &matrix);

float AtoBLength(const Vector3 &v1, const Vector3 &v2);

Vector3 Normalize(const Vector3 &v);

//加算
Vector3 Add(const Vector3 &v1 , const Vector3 &v2);

//減算
Vector3 Subtract(const Vector3 &v1 , const Vector3 &v2);

//スカラー倍
Vector3 MultiplyVec3(float scaler , const Vector3 &v);

Matrix4x4 Inverse(const Matrix4x4 &matrix);

Vector3 MultiplyV2M(const Vector3 &v , const Matrix4x4 &m);

Matrix4x4 MakeViewportMatrix(float left , float top , float width , float height , float minDepth , float maxDepth);

Matrix4x4 MultiplyM2M(const Matrix4x4 &matrix1 , const Matrix4x4 &matrix2);