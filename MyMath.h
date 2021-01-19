#pragma once
class MyVector
{
public:
    MyVector();
    MyVector(float InX, float InY, float InZ, float InW);
    MyVector(const MyVector& InMyVector);

    MyVector operator-() const;
    MyVector operator-(MyVector InMyVector);
    MyVector operator/(float Value);
    MyVector& operator=(MyVector& InMyVector);

    float Dot(MyVector InMyVector);
    MyVector Cross(MyVector InMyVector);
    float Length();
    void Normalize();

private:
    MyVector LengthSq();

public:
	float x, y, z, w;
};

class MyMatrix
{
public:
    MyMatrix();
    MyMatrix(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33
    );


private:
    union
    {
        MyVector v[4];
        struct
        {
            float _11, _12, _13, _14;
            float _21, _22, _23, _24;
            float _31, _32, _33, _34;
            float _41, _42, _43, _44;
        };
        float m[4][4];
    };
};

