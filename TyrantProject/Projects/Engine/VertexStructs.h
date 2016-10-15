#pragma once
#include "../CommonUtilities/Vector4.h"

enum eVertexType
{
	Vertex_Position_Color,
	Vertex_Position_UV,
	Vertex_Position_Normal,
	Vertex_Position_Color_UV,
	Vertex_Position_Normal_UV,
	Vertex_Position_Normal_UV_Tangent,
	NumberOfVertexTypes
};


struct VertexPositionNormal
{
	VertexPositionNormal() {};
	VertexPositionNormal(const Vector4<float>& aPosition, const Vector4<float>& aNormal)
		: position(aPosition), normal(aNormal)
	{
	}

	Vector4<float> position;
	Vector4<float> normal;
};

struct VertexPositionColor
{
	VertexPositionColor() {};
	VertexPositionColor(const Vector4<float>& aPosition, const Vector4<float>& aColor)
		: position(aPosition), color(aColor)
	{
	}

	Vector4<float> position;
	Vector4<float> color;
};

struct VertexPositionUV
{
	VertexPositionUV() {};
	VertexPositionUV(const Vector4<float>& aPosition, const Vector2<float>& anUV)
		: position(aPosition), UV(anUV)
	{
	}

	Vector4<float> position;
	Vector2<float> UV;
};

struct VertexPositionColorUV
{
	VertexPositionColorUV() {};
	VertexPositionColorUV(const Vector4<float>& aPosition, const Vector4<float>& aColor, const Vector2<float>& anUV)
		: position(aPosition), color(aColor), UV(anUV)
	{
	}

	Vector4<float> position;
	Vector4<float> color;
	Vector2<float> UV;
};

struct VertexPositionNormalUV
{
	VertexPositionNormalUV() {};
	VertexPositionNormalUV(const Vector4<float>& aPosition, const Vector4<float>& aNormal, const Vector2<float>& anUV)
		: position(aPosition), normal(aNormal), UV(anUV)
	{
	}

	Vector4<float> position;
	Vector4<float> normal;
	Vector2<float> UV;
};

struct VertexPositionNormalUVTangent
{
	VertexPositionNormalUVTangent() {};
	VertexPositionNormalUVTangent(const Vector4<float>& aPosition, const Vector4<float>& aNormal, const Vector2<float>& anUV, const Vector4<float> aTangent)
		: position(aPosition), normal(aNormal), UV(anUV), tangent(aTangent)
	{
	}

	Vector4<float> position;
	Vector4<float> normal;
	Vector4<float> tangent;
	Vector2<float> UV;
};