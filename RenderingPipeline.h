#pragma once

#include "MyMath.h"
#include <Windows.h>

class RenderingPipeline
{
public:
	RenderingPipeline(int InWidth, int InHeight, HDC InHdc);

	void Excute();

private:
	MyMatrix GetViewMatrix(const MyVector& CameraPosition, const MyVector& TargetPosition, const MyVector& Up) const;

	// FovAngleY	: ���� �þ߰�(����)
	// Aspect		: ��Ⱦ��(�ʺ� / ����)
	// NearZ		: ����� ��� �Ÿ�
	// FarZ			: �� ��� �Ÿ�
	MyMatrix GetProjectionMatrix(const float FovAngleY, const float Aspect, float NearZ, float FarZ) const;

	MyMatrix GetViewportMatrix(const float StartX, const float StartY, const float Width, const float Height, const float MaxZ, const float MinZ);

private:
	struct Vertex
	{
	public:
		Vertex() : Position() {}
		Vertex(float InX, float InY, float InZ, float InW) : Position(InX, InY, InZ, InW) {}

		MyVector Position;
	};

	Vertex VertexShader(const Vertex InVertex) const;
	Vertex PixelShader(const Vertex InVertex) const;

private:
	HDC Hdc;

	int Width;
	int Height;

	MyMatrix WorldViewProjectionMatrix;
};

