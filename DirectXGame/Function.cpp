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