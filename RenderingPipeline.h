#pragma once

#include "MyMath.h"

class RenderingPipeline
{
public:
	RenderingPipeline(int InWidth, int InHeight);

	void Excute();

private:
	MyMatrix GetViewMatrix(const MyVector& CameraPosition, const MyVector& TargetPosition, const MyVector& Up) const;

	// FovAngleY	: ���� �þ߰�(����)
	// Aspect		: ��Ⱦ��(�ʺ� / ����)
	// NearZ		: ����� ��� �Ÿ�
	// FarZ			: �� ��� �Ÿ�
	MyMatrix GetProjectionMatrix(const float FovAngleY, const float Aspect, float NearZ, float FarZ) const;

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
	int Width;
	int Height;

	MyMatrix WorldViewProjectionMatrix;
};

