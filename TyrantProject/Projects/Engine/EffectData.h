#pragma once

struct EffectData
{
	static CU::Matrix44<float> worldMatrix;
	static CU::Matrix44<float> viewMatrix;
	static CU::Matrix44<float> projectionMatrix;
	
	static Vector4<float> color;
	static Vector4<float> position;

	static Vector3<float> scale;

	static Vector2<float> resolution;
	static Vector2<float> characterSize;

	static float rotation_2D;

private:
	EffectData() = default;
	~EffectData() = default;
};
