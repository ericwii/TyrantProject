#pragma once

class EffectText3D : public Effect
{
public:
	EffectText3D();
	~EffectText3D();

	bool Init(const string& anEffectFile) override;
	void Update() override;

private:
	ID3DX11EffectVectorVariable* myCharacterSizeVariable;
	ID3DX11EffectVectorVariable* myScaleVariable;
	ID3DX11EffectVectorVariable* myColorVariable;
};

