#pragma once

class Effect2D : public Effect
{
public:
	Effect2D();
	~Effect2D();

	virtual bool Init(const string& aEffectFile) override;
	virtual void Update() override;
	

private:
	ID3DX11EffectVectorVariable* myResolutionVariable;
	ID3DX11EffectVectorVariable* myPositionVariable;
	ID3DX11EffectVectorVariable* myColorVariable;
	ID3DX11EffectVectorVariable* myScaleVariable;
	ID3DX11EffectScalarVariable* myRotationVariable;
};