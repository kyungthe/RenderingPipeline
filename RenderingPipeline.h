#pragma once

#include "MyMath.h"

class RenderingPipeline
{
public:
	RenderingPipeline(int InWidth, int InHeight);

	void Excute();

private:
	MyMatrix GetViewMatrix(const MyVector& CameraPosition, const MyVector& TargetPosition, const MyVector& Up);

	// FovAngleY	: ���� �þ߰�(����)
	// Aspect		: ��Ⱦ��(�ʺ� / ����)
	// NearZ		: ����� ��� �Ÿ�
	// FarZ			: �� ��� �Ÿ�
	MyMatrix GetProjectionMatrix(const float FovAngleY, const float Aspect, float NearZ, float FarZ);

private:
	int Width;
	int Height;
};

