#pragma once

struct ID3DX11EffectShaderResourceVariable;
class Texture;
class Effect;

struct SurfaceData
{
	SurfaceData() : shaderVariable(nullptr), texture(nullptr)
	{
	}

	SurfaceData(ID3DX11EffectShaderResourceVariable* aShaderVariable, Texture* aTexture, const string& aShaderVariableName)
	{
		shaderVariable = aShaderVariable;
		texture = aTexture;
		shaderVariableName = aShaderVariableName;
	}

	ID3DX11EffectShaderResourceVariable* shaderVariable;
	Texture* texture;
	string shaderVariableName;
};

class Surface
{
public:
	Surface();
	~Surface();

	void UpdateShaderVariables();

	inline void SetEffect(Effect* anEffect);
	inline void SetPrimologyType(const D3D11_PRIMITIVE_TOPOLOGY& aPrimologyType);
	bool AddTexture(const string& aShaderVariableName, const string& aTextureFileName);

	inline Texture* GetTexture(const string& aShaderVariableName);

private:
	CU::GrowingArray<SurfaceData> myData;
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

inline Texture* Surface::GetTexture(const string& aShaderVariableName)
{
	for (int i = 0; i < myData.Size(); ++i)
	{
		if (myData[i].shaderVariableName == aShaderVariableName)
		{
			return myData[i].texture;
		}
	}
	return nullptr;
}