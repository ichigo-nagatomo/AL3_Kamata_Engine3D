#include "Function.h"

Vector3 Vector3Add(const Vector3 &v1 , const Vector3 &v2) {
	Vector3 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;

	return result;
}

Vector3 TransformNormal(const Vector3 &v , const Matrix4x4 &m) {
	Vector3 result {
		v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
		v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
		v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2]
	};

	return result;
}

Vector3 Transform(const Vector3& vector, const Matrix4x4 &matrix) {
	Vector3 result;
	// 各成分を計算
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + matrix.m[3][3];

	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;


	return result;
}

float AtoBLength(const Vector3 &v1, const Vector3 &v2) {
	Vector3 saveVec3 = Subtract(v1 , v2);
	float length = sqrtf(saveVec3.x * saveVec3.x + saveVec3.y * saveVec3.y + saveVec3.z * saveVec3.z);
	return length;
}

Vector3 Normalize(const Vector3 &v) {
	Vector3 result;
	float length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	return result = {v.x / length, v.y / length, v.z / length};
}

//加算
Vector3 Add(const Vector3 &v1 , const Vector3 &v2) {
	Vector3 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}

//減算
Vector3 Subtract(const Vector3 &v1 , const Vector3 &v2) {
	Vector3 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}

//スカラー倍
Vector3 MultiplyVec3(float scaler , const Vector3 &v) {
	Vector3 result;
	result.x = v.x * scaler;
	result.y = v.y * scaler;
	result.z = v.z * scaler;
	return result;
}

//逆行列
Matrix4x4 Inverse(const Matrix4x4& matrix) {
	Matrix4x4 result;

	result.m[0][0] = (matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][3] +
					  matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][1] +
					  matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][2] -
					  matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][1] -
					  matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][3] -
					  matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][2]);

	result.m[0][1] = (-matrix.m[0][1] * matrix.m[2][2] * matrix.m[3][3] -
					  matrix.m[0][2] * matrix.m[2][3] * matrix.m[3][1] -
					  matrix.m[0][3] * matrix.m[2][1] * matrix.m[3][2] +
					  matrix.m[0][3] * matrix.m[2][2] * matrix.m[3][1] +
					  matrix.m[0][2] * matrix.m[2][1] * matrix.m[3][3] +
					  matrix.m[0][1] * matrix.m[2][3] * matrix.m[3][2]);

	result.m[0][2] = (matrix.m[0][1] * matrix.m[1][2] * matrix.m[3][3] +
					  matrix.m[0][2] * matrix.m[1][3] * matrix.m[3][1] +
					  matrix.m[0][3] * matrix.m[1][1] * matrix.m[3][2] -
					  matrix.m[0][3] * matrix.m[1][2] * matrix.m[3][1] -
					  matrix.m[0][2] * matrix.m[1][1] * matrix.m[3][3] -
					  matrix.m[0][1] * matrix.m[1][3] * matrix.m[3][2]);

	result.m[0][3] = (-matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][3] -
					  matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][1] -
					  matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][2] +
					  matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][1] +
					  matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][3] +
					  matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][2]);

	result.m[1][0] = (-matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][3] -
					  matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][0] -
					  matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][2] +
					  matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][0] +
					  matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][3] +
					  matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][2]);

	result.m[1][1] = (matrix.m[0][0] * matrix.m[2][2] * matrix.m[3][3] +
					  matrix.m[0][2] * matrix.m[2][3] * matrix.m[3][0] +
					  matrix.m[0][3] * matrix.m[2][0] * matrix.m[3][2] -
					  matrix.m[0][3] * matrix.m[2][2] * matrix.m[3][0] -
					  matrix.m[0][2] * matrix.m[2][0] * matrix.m[3][3] -
					  matrix.m[0][0] * matrix.m[2][3] * matrix.m[3][2]);

	result.m[1][2] = (-matrix.m[0][0] * matrix.m[1][2] * matrix.m[3][0] -
					  matrix.m[0][2] * matrix.m[1][3] * matrix.m[3][0] -
					  matrix.m[0][3] * matrix.m[1][0] * matrix.m[3][2] +
					  matrix.m[0][3] * matrix.m[1][2] * matrix.m[3][0] +
					  matrix.m[0][2] * matrix.m[1][0] * matrix.m[3][3] +
					  matrix.m[0][0] * matrix.m[1][3] * matrix.m[3][2]);

	result.m[1][3] = (matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][3] +
					  matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][0] +
					  matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][2] -
					  matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][0] -
					  matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][3] -
					  matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][2]);

	result.m[2][0] = (matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][3] +
					  matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][0] +
					  matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][1] -
					  matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][0] -
					  matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][3] -
					  matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][1]);

	result.m[2][1] = (-matrix.m[0][0] * matrix.m[2][1] * matrix.m[3][3] -
					  matrix.m[0][1] * matrix.m[2][3] * matrix.m[3][0] -
					  matrix.m[0][3] * matrix.m[2][0] * matrix.m[3][1] +
					  matrix.m[0][3] * matrix.m[2][1] * matrix.m[3][0] +
					  matrix.m[0][1] * matrix.m[2][0] * matrix.m[3][3] +
					  matrix.m[0][0] * matrix.m[2][3] * matrix.m[3][1]);

	result.m[2][2] = (matrix.m[0][0] * matrix.m[1][1] * matrix.m[3][3] +
					  matrix.m[0][1] * matrix.m[1][3] * matrix.m[3][0] +
					  matrix.m[0][3] * matrix.m[1][0] * matrix.m[3][1] -
					  matrix.m[0][3] * matrix.m[1][1] * matrix.m[3][0] -
					  matrix.m[0][1] * matrix.m[1][0] * matrix.m[3][3] -
					  matrix.m[0][0] * matrix.m[1][3] * matrix.m[3][1]);

	result.m[2][3] = (-matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][3] -
					  matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][0] -
					  matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][1] +
					  matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][0] +
					  matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][3] +
					  matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][1]);

	result.m[3][0] = (-matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][2] -
					  matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][0] -
					  matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][1] +
					  matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][0] +
					  matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][2] +
					  matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][1]);

	result.m[3][1] = (matrix.m[0][0] * matrix.m[2][1] * matrix.m[3][2] +
					  matrix.m[0][1] * matrix.m[2][2] * matrix.m[3][0] +
					  matrix.m[0][2] * matrix.m[2][0] * matrix.m[3][1] -
					  matrix.m[0][2] * matrix.m[2][1] * matrix.m[3][0] -
					  matrix.m[0][1] * matrix.m[2][0] * matrix.m[3][2] -
					  matrix.m[0][0] * matrix.m[2][2] * matrix.m[3][1]);

	result.m[3][2] = (-matrix.m[0][0] * matrix.m[1][1] * matrix.m[3][2] -
					  matrix.m[0][1] * matrix.m[1][2] * matrix.m[3][0] -
					  matrix.m[0][2] * matrix.m[1][0] * matrix.m[3][1] +
					  matrix.m[0][2] * matrix.m[1][1] * matrix.m[3][0] +
					  matrix.m[0][1] * matrix.m[1][0] * matrix.m[3][2] +
					  matrix.m[0][0] * matrix.m[1][2] * matrix.m[3][1]);

	result.m[3][3] = (matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] +
					  matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] +
					  matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1] -
					  matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] -
					  matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] -
					  matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1]);

	return result;
}

Vector3 MultiplyV2M(const Vector3 &v , const Matrix4x4 &m) {
	Vector3 result;
	float w = 1.0f; // 同次座標のw成分を1に設定

	result.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + w * m.m[3][0];
	result.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + w * m.m[3][1];
	result.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + w * m.m[3][2];

	return result;
}

//ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float left , float top , float width , float height , float minDepth , float maxDepth) {
	Matrix4x4 matrix;
	matrix.m[0][0] = width / 2.0f;
	matrix.m[0][1] = 0.0f;
	matrix.m[0][2] = 0.0f;
	matrix.m[0][3] = 0.0f;
	matrix.m[1][0] = 0.0f;
	matrix.m[1][1] = -(height / 2.0f);
	matrix.m[1][2] = 0.0f;
	matrix.m[1][3] = 0.0f;
	matrix.m[2][0] = 0.0f;
	matrix.m[2][1] = 0.0f;
	matrix.m[2][2] = maxDepth - minDepth;
	matrix.m[2][3] = 0.0f;
	matrix.m[3][0] = left + (width / 2.0f);
	matrix.m[3][1] = top + (height / 2.0f);
	matrix.m[3][2] = minDepth;
	matrix.m[3][3] = 1.0f;

	return matrix;
}

//行列の積
Matrix4x4 MultiplyM2M(const Matrix4x4 &matrix1 , const Matrix4x4 &matrix2) {
	Matrix4x4 result;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = 0;
			for (int k = 0; k < 4; ++k) {
				result.m[i][j] += matrix1.m[i][k] * matrix2.m[k][j];
			}
		}
	}

	return result;
}