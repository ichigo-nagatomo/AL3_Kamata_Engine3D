#include "AffineMatrix.h"


Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 result;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (i == j) {
				result.m[i][j] = 1.0f;
			} else {
				result.m[i][j] = 0.0f;
			}
		}
	}

	return result;
}

//行列の積
Matrix4x4 Multiply(const Matrix4x4 &matrix1 , const Matrix4x4 &matrix2) {
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

//Scale
Matrix4x4 MakeScaleMatrix(const Vector3 &scale) {
	Matrix4x4 matrix;

	matrix = MakeIdentity4x4();

	matrix.m[0][0] = scale.x;
	matrix.m[1][1] = scale.y;
	matrix.m[2][2] = scale.z;

	return matrix;
}

//Rotate
Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 result;

	result = MakeIdentity4x4();

	result.m[1][1] = std::cos(radian);
	result.m[1][2] = std::sin(radian);
	result.m[2][1] = std::sin(-radian);
	result.m[2][2] = std::cos(radian);

	return result;
}

Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 result;

	result = MakeIdentity4x4();

	result.m[0][0] = std::cos(radian);
	result.m[0][2] = std::sin(-radian);
	result.m[2][0] = std::sin(radian);
	result.m[2][2] = std::cos(radian);

	return result;
}

Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 result;

	result = MakeIdentity4x4();

	result.m[0][0] = std::cos(radian);
	result.m[0][1] = std::sin(radian);
	result.m[1][0] = std::sin(-radian);
	result.m[1][1] = std::cos(radian);

	return result;
}

Matrix4x4 MakeRotateMatrix(const Vector3 &rotate) {
	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 matrix = Multiply(rotateXMatrix , Multiply(rotateYMatrix , rotateZMatrix));
	return matrix;
}

//Translate
Matrix4x4 MakeTranslateMatrix(const Vector3 &translate) {
	Matrix4x4 matrix;
	matrix = MakeIdentity4x4();

	matrix.m[3][0] = translate.x;
	matrix.m[3][1] = translate.y;
	matrix.m[3][2] = translate.z;

	return matrix;
}

//Affine
Matrix4x4 MakeAffineMatrix(const Vector3 &scale , const Vector3 &rotate , const Vector3 &translate) {
	Matrix4x4 scaleMa = MakeScaleMatrix(scale);
	Matrix4x4 rotateMa = MakeRotateMatrix(rotate);
	Matrix4x4 translateMa = MakeTranslateMatrix(translate);

	Matrix4x4 matrix = Multiply(scaleMa , Multiply(rotateMa , translateMa));
	return matrix;
}
