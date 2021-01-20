#pragma once

#include "MyMath.h"

class RenderingPipeline
{
public:
	RenderingPipeline(int InWidth, int InHeight);

	void Excute();

private:
	MyMatrix GetViewMatrix(const MyVector& CameraPosition, const MyVector& TargetPosition, const MyVector& Up);

	// FovAngleY	: 수직 시야각(라디안)
	// Aspect		: 종횡비(너비 / 높이)
	// NearZ		: 가까운 평면 거리
	// FarZ			: 먼 평면 거리
	MyMatrix GetProjectionMatrix(const float FovAngleY, const float Aspect, float NearZ, float FarZ);

private:
	struct Vertex
	{
	public:
		Vertex() : Position() {}
		Vertex(float InX, float InY, float InZ, float InW) : Position(InX, InY, InZ, InW) {}

		MyVector Position;
	};

	Vertex VertexShader(Vertex InVertex);
	Vertex PixelShader(Vertex InVertex);

private:
	int Width;
	int Height;
};

