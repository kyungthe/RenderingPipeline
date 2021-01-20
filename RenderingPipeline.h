#pragma once

#include "MyMath.h"

class RenderingPipeline
{
public:
	void Excute();

private:
	MyMatrix GetViewMatrix(const MyVector& CameraPosition, const MyVector& TargetPosition, const MyVector& Up);
};

