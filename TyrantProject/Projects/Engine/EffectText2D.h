#pragma once
#include "Effect2D.h"

class EffectText2D : public Effect2D
{
public:
	EffectText2D();
	~EffectText2D();

	bool Init(const string& anEffectFile);
	void Update() override;

private:
	ID3DX11EffectVectorVariable* myCharacterSizeVariable;
};

