#pragma once
#include "Effect2D.h"

class EffectText : public Effect2D
{
public:
	EffectText();
	~EffectText();

	bool Init(const string& anEffectFile);
	void Update() override;

private:
	ID3DX11EffectVectorVariable* myCharacterSizeVariable;
};

