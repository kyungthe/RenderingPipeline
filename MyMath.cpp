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

MyVector MyVector::operator-(MyVector InVector) const
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
	 v{ MyVector(),
		MyVector(),
		MyVector(),
		MyVector() }
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
