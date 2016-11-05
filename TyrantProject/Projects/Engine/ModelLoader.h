#pragma once
#include "Model.h"

class ModelLoader
{
public:
	static Model* LoadDebugCube(float aCubeSize);
	static Model* LoadDebugTriangle(float aSize);
	static Model* LoadRectangle(const Vector2<float>& aSize, eEffectType anEffectType, const string& aTextureFile = string(), bool aDoubleSided = false);

private:
	ModelLoader();
	~ModelLoader();
};

