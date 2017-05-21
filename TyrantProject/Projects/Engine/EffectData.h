#pragma once

struct EffectData
{
	static CU::Matrix44<float> worldMatrix;
	static CU::Matrix44<float> viewMatrix;
	static CU::Matrix44<float> projectionMatrix;
	
	static Vector4<float> color;
	static Vector4<float> position;

	static Vector2<float> scale;
	static Vector2<float> resolution;
	static Vector2<float> characterSize;
	static Vector2<float> animationFrameSize;
	static Vector2<float> animationUV;

	static float rotation_2D;
	static float alpha;
	static bool flipX;
	static bool flipY;

private:
	EffectData() = default;
	~EffectData() = default;
};
