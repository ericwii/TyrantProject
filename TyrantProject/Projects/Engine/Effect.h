#pragma once

struct ID3DX11Effect;
struct ID3DX11EffectTechnique;
struct ID3DX11EffectScalarVariable;
struct ID3DX11EffectMatrixVariable;
struct ID3DX11EffectVectorVariable;
struct ID3DX11EffectShaderResourceVariable;

class Effect
{
public:
	Effect();
	~Effect();

	virtual bool Init(const string& anEffectFile);
	virtual void Update();

	inline const string& GetFileName() const;
	inline ID3DX11Effect* GetEffect();
	inline ID3DX11EffectTechnique* GetTechnique();

protected:
	string myFileName;

	ID3DX11Effect* myEffect;
	ID3DX11EffectTechnique* myTechnique;

	ID3DX11EffectMatrixVariable* myProjectionMatrixVariable;
	ID3DX11EffectMatrixVariable* myViewMatrixVariable;
	ID3DX11EffectMatrixVariable* myWorldMatrixVariable;
	ID3DX11EffectScalarVariable* myAlphaVariable;
};

inline const string& Effect::GetFileName() const
{
	return (myFileName);
}

inline ID3DX11Effect* Effect::GetEffect()
{
	return (myEffect);
}

inline ID3DX11EffectTechnique* Effect::GetTechnique()
{
	return (myTechnique);
}