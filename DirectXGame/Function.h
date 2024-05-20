#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"
#include <assert.h>
#define _USE_MATH_DEFINES
#include <math.h>

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