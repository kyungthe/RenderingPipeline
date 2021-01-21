#include "RenderingPipeline.h"
#include <cmath>
#include <vector>

using namespace std;

RenderingPipeline::RenderingPipeline(int InWidth, int InHeight) : Width(InWidth), Height(InHeight)
{
}

void RenderingPipeline::Excute()
{  
    float world[4][4] = {
        { 1.f, 0.f, 0.f, 0.f },
        { 0.f, 1.f, 0.f, 0.f },
        { 0.f, 0.f, 1.f, 0.f },
        { 0.f, 0.f, 0.f, 1.f }
    };

    float mTheta = 1.5f * 3.141592654f;
    float mPhi = 0.785398163f;
    float mRadius = 5.0f;

    float x = mRadius * sinf(mPhi) * cosf(mTheta);
    float z = mRadius * sinf(mPhi) * sinf(mTheta);
    float y = mRadius * cosf(mPhi);

    MyVector Position(x, y, z, 1.0f);
    MyVector Target(0.0f, 0.0f, 0.0f, 0.0f);
    MyVector Up(0.0f, 1.0f, 0.0f, 0.0f);

    MyMatrix WorldMatrix;
    MyMatrix ViewMatrix = GetViewMatrix(Position, Target, Up);
    MyMatrix ProjectionMatrix = GetProjectionMatrix(0.25f * 3.1415926535f, static_cast<float>(Width) / Height, 1.0f, 1000.0f);

    WorldViewProjectionMatrix = WorldMatrix * ViewMatrix * ProjectionMatrix;

    Vertex v1(-1.0f, -1.0f, -1.0f, 1.0f);
    Vertex v2(-1.0f, +1.0f, -1.0f, 1.0f);
    Vertex v3(+1.0f, +1.0f, -1.0f, 1.0f);
    Vertex v4(+1.0f, -1.0f, -1.0f, 1.0f);
    Vertex v5(-1.0f, -1.0f, +1.0f, 1.0f);
    Vertex v6(-1.0f, +1.0f, +1.0f, 1.0f);
    Vertex v7(+1.0f, +1.0f, +1.0f, 1.0f);
    Vertex v8(+1.0f, -1.0f, +1.0f, 1.0f);
    vector<Vertex> Vertices = { v1, v2, v3, v4, v5, v6, v7, v8 };

    for (int i = 0; i < Vertices.size(); ++i)
    {
        Vertex v = VertexShader(Vertices[i]);
        v = PixelShader(v);
    }
}

MyMatrix RenderingPipeline::GetViewMatrix(const MyVector& CameraPosition, const MyVector& TargetPosition, const MyVector& Up) const
{
    MyVector w = (TargetPosition - CameraPosition) / (TargetPosition - CameraPosition).Length();
    MyVector u = Up.Cross(w) / Up.Cross(w).Length();
    MyVector v = w.Cross(u);

    return MyMatrix(
        u.x, v.x, w.x, 0.0f,
        u.y, v.y, w.y, 0.0f,
        u.z, v.z, w.z, 0.0f,
        -CameraPosition.Dot(u), -CameraPosition.Dot(v), -CameraPosition.Dot(w), 1.0f
    );
}

MyMatrix RenderingPipeline::GetProjectionMatrix(const float FovAngleY, const float Aspect, float NearZ, float FarZ) const
{
    return MyMatrix(
        1 / (Aspect * tanf(FovAngleY / 2)), 0.0f, 0.0f, 0.0f,
        0.0f, 1 / tanf(FovAngleY / 2), 0.0f, 0.0f,
        0.0f, 0.0f, FarZ / (FarZ - NearZ), 1.0f,
        0.0f, 0.0f, -NearZ * FarZ / (FarZ - NearZ), 0.0f
    );
}

RenderingPipeline::Vertex RenderingPipeline::VertexShader(const Vertex InVertex) const
{
    Vertex OutVertex = InVertex;

    OutVertex.Position = OutVertex.Position * WorldViewProjectionMatrix;

    return OutVertex;
}

RenderingPipeline::Vertex RenderingPipeline::PixelShader(const Vertex InVertex) const
{
    return InVertex;
}
