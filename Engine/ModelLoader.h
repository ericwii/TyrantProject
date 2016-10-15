#pragma once
#include "Model.h"

class ModelLoader
{
public:
	static Model* LoadDebugCube(float aCubeSize);
	static Model* LoadDebugTriangle(float aSize);
	static Model* LoadRectangle3D(const Vector2<float>& aSize, eEffectType3D anEffectType, const string& aTextureFile = string());

private:
	ModelLoader();
	~ModelLoader();
};

