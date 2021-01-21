#include "MyMath.h"
#include <Windows.h>
#include <cmath>

MyVector::MyVector()
{
	x = y = z = w = 0.f;

	//OutputDebugString(L"MyVector Constructor\n");
}

MyVector::MyVector(float InX, float InY, float InZ, float InW)
{
	x = InX;
	y = InY;
	z = InZ;
	w = InW;

	//OutputDebugString(L"MyVector Constructor\n");
}

MyVector::MyVector(const MyVector& InMyVector)
{
	x = InMyVector.x;
	y = InMyVector.y;
	z = InMyVector.z;
	w = InMyVector.w;
}

MyVector MyVector::operator-() const
{
	return MyVector(-x, -y, -z, -w);
}

MyVector MyVector::operator-(const MyVector& InVector) const
{
	return MyVector(x - InVector.x, y - InVector.y, z - InVector.z, w);
}

MyVector MyVector::operator/(float Value) const
{	
	return MyVector(x / Value, y / Value, z / Value, w);
}

MyVector& MyVector::operator=(const MyVector& InMyVector)
{
	x = InMyVector.x;
	y = InMyVector.y;
	z = InMyVector.z;
	w = InMyVector.w;

	return *this;
}

MyVector MyVector::operator*(const MyMatrix& InMyMatrix) const
{
	return MyVector(
		x * InMyMatrix._11 + y * InMyMatrix._21 + z * InMyMatrix._31 + w * InMyMatrix._41,
		x * InMyMatrix._12 + y * InMyMatrix._22 + z * InMyMatrix._32 + w * InMyMatrix._42,
		x * InMyMatrix._13 + y * InMyMatrix._23 + z * InMyMatrix._33 + w * InMyMatrix._43,
		x * InMyMatrix._14 + y * InMyMatrix._24 + z * InMyMatrix._34 + w * InMyMatrix._44
	);
}

float MyVector::Dot(MyVector InMyVector) const
{
	return x * InMyVector.x + y * InMyVector.y + z * InMyVector.z;
}

MyVector MyVector::Cross(MyVector InMyVector) const
{
	return MyVector(
		y * InMyVector.z - z * InMyVector.y,
		z * InMyVector.x - x * InMyVector.z,
		x * InMyVector.y - y * InMyVector.x,
		0.0f
	);
}

float MyVector::Length() const
{
	MyVector result = LengthSq();
	
	return sqrtf(result.x + result.y + result.z);
}

void MyVector::Normalize()
{
	float length = Length();

	x /= length;
	y /= length;
	z /= length;
	w /= length;
}

MyVector MyVector::LengthSq() const
{
	return MyVector(x * x, y * y, z * z, 0.0f);
}

MyMatrix::MyMatrix() :
	 v{ MyVector(1.0f, 0.0f, 0.0f, 0.0f),
		MyVector(0.0f, 1.0f, 0.0f, 0.0f),
		MyVector(0.0f, 0.0f, 1.0f, 0.0f),
		MyVector(0.0f, 0.0f, 0.0f, 1.0f) }
{
}

MyMatrix::MyMatrix
(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33
) : v{	MyVector(m00, m01, m02, m03),
		MyVector(m10, m11, m12, m13),
		MyVector(m20, m21, m22, m23),
		MyVector(m30, m31, m32, m33)}
{
}

MyMatrix::MyMatrix(const MyMatrix& other)
{
	v[0] = other.v[0];
	v[1] = other.v[1];
	v[2] = other.v[2];
	v[3] = other.v[3];
}

MyMatrix MyMatrix::operator*(const MyMatrix& other)
{
	MyMatrix mResult;
	// Cache the invariants in registers
	float x = m[0][0];
	float y = m[0][1];
	float z = m[0][2];
	float w = m[0][3];
	// Perform the operation on the first row
	mResult.m[0][0] = (other.m[0][0] * x) + (other.m[1][0] * y) + (other.m[2][0] * z) + (other.m[3][0] * w);
	mResult.m[0][1] = (other.m[0][1] * x) + (other.m[1][1] * y) + (other.m[2][1] * z) + (other.m[3][1] * w);
	mResult.m[0][2] = (other.m[0][2] * x) + (other.m[1][2] * y) + (other.m[2][2] * z) + (other.m[3][2] * w);
	mResult.m[0][3] = (other.m[0][3] * x) + (other.m[1][3] * y) + (other.m[2][3] * z) + (other.m[3][3] * w);
	// Repeat for all the other rows
	x = m[1][0];
	y = m[1][1];
	z = m[1][2];
	w = m[1][3];
	mResult.m[1][0] = (other.m[0][0] * x) + (other.m[1][0] * y) + (other.m[2][0] * z) + (other.m[3][0] * w);
	mResult.m[1][1] = (other.m[0][1] * x) + (other.m[1][1] * y) + (other.m[2][1] * z) + (other.m[3][1] * w);
	mResult.m[1][2] = (other.m[0][2] * x) + (other.m[1][2] * y) + (other.m[2][2] * z) + (other.m[3][2] * w);
	mResult.m[1][3] = (other.m[0][3] * x) + (other.m[1][3] * y) + (other.m[2][3] * z) + (other.m[3][3] * w);
	x = m[2][0];
	y = m[2][1];
	z = m[2][2];
	w = m[2][3];
	mResult.m[2][0] = (other.m[0][0] * x) + (other.m[1][0] * y) + (other.m[2][0] * z) + (other.m[3][0] * w);
	mResult.m[2][1] = (other.m[0][1] * x) + (other.m[1][1] * y) + (other.m[2][1] * z) + (other.m[3][1] * w);
	mResult.m[2][2] = (other.m[0][2] * x) + (other.m[1][2] * y) + (other.m[2][2] * z) + (other.m[3][2] * w);
	mResult.m[2][3] = (other.m[0][3] * x) + (other.m[1][3] * y) + (other.m[2][3] * z) + (other.m[3][3] * w);
	x = m[3][0];
	y = m[3][1];
	z = m[3][2];
	w = m[3][3];
	mResult.m[3][0] = (other.m[0][0] * x) + (other.m[1][0] * y) + (other.m[2][0] * z) + (other.m[3][0] * w);
	mResult.m[3][1] = (other.m[0][1] * x) + (other.m[1][1] * y) + (other.m[2][1] * z) + (other.m[3][1] * w);
	mResult.m[3][2] = (other.m[0][2] * x) + (other.m[1][2] * y) + (other.m[2][2] * z) + (other.m[3][2] * w);
	mResult.m[3][3] = (other.m[0][3] * x) + (other.m[1][3] * y) + (other.m[2][3] * z) + (other.m[3][3] * w);
	return mResult;
}

MyMatrix& MyMatrix::operator=(const MyMatrix& other)
{
	v[0] = other.v[0];
	v[1] = other.v[1];
	v[2] = other.v[2];
	v[3] = other.v[3];

	return *this;
}
