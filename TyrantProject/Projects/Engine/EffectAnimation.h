#pragma once

class EffectAnimation : public Effect
{
public:
	EffectAnimation();
	~EffectAnimation();

	bool Init(const string& anEffectFile) override;
	void Update() override;

private:
	ID3DX11EffectVectorVariable* myFrameSizeVariable;
	ID3DX11EffectVectorVariable* myFrameUvVariable;
	ID3DX11EffectScalarVariable* myFlipXVariable;
	ID3DX11EffectScalarVariable* myFlipYVariable;
};

