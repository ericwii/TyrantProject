#pragma once

struct ID3DX11EffectShaderResourceVariable;
class Texture;
class Effect;

class Surface
{
public:
	Surface();
	~Surface();

	void UpdateShaderVariables();

	inline void SetEffect(Effect* anEffect);
	inline void SetPrimologyType(const D3D11_PRIMITIVE_TOPOLOGY& aPrimologyType);
	bool AddTexture(const string& aShaderVariableName, const string& aTextureFileName);

private:
	CU::GrowingArray<ID3DX11EffectShaderResourceVariable*> myShaderVariables;
	CU::GrowingArray<Texture*> myTextures;
	D3D11_PRIMITIVE_TOPOLOGY myPrimologyType;
	Effect* myEffect;
};

inline void Surface::SetEffect(Effect* anEffect)
{
	myEffect = anEffect;
}

inline void Surface::SetPrimologyType(const D3D11_PRIMITIVE_TOPOLOGY& aPrimologyType)
{
	myPrimologyType = aPrimologyType;
}