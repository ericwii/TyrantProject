#pragma once
#include "VertexLayouts.h"
#include "VertexStructs.h"
#include "ShaderBufferStructs.h"
#include "Surface.h"

class Effect;

class Model
{
	friend class ModelLoader;

public:
	Model();
	~Model();

	void Destroy();

	void Render(const CU::Matrix44<float>& aParentSpace, unsigned int aPassIndex = 0);
	void RenderWireFrame(const CU::Matrix44<float>& aParentSpace);

	void AddTexture(const string& aShaderVariableName, const string& aTextureFile, int surfaceIndex = 0);
	inline void SetEffect(Effect* anEffect);
	inline void SetAlpha(float anAlpha);

	inline const Effect* GetEffect() const;
	inline int GetVertexCount() const;
	inline int GetIndexCount() const;
	inline Texture* GetTexture(const string& aShaderVariableName, int aSurfaceIndex = 0);

private:
	bool InitVertexBuffer();
	bool InitIndexBuffer();

	CU::GrowingArray<Surface> mySurfaces;
	CU::GrowingArray<D3D11_INPUT_ELEMENT_DESC> myVertexFormat;

	VertexIndexWrapper myIndexData;
	IndexBufferWrapper myIndexBuffer;
	VertexDataWrapper myVertexData;
	VertexBufferWrapper myVertexBuffer;

	Effect* myEffect;
	ID3D11InputLayout* myVertexLayout;

	float myAlpha;
	bool myIsNullObject;
};

inline void Model::SetEffect(Effect* anEffect)
{
	myEffect = anEffect;
	
	for (int i = 0; i < mySurfaces.Size(); ++i)
	{
		mySurfaces[i].SetEffect(anEffect);
	}
}

inline void Model::SetAlpha(float anAlpha)
{
	myAlpha = anAlpha;
}

inline const Effect* Model::GetEffect() const
{
	return myEffect;
}

inline int Model::GetVertexCount() const
{
	return myVertexData.numberOfOfVertexes;
}

inline int Model::GetIndexCount() const
{
	return myIndexData.numberOfIndexes;
}

Texture* Model::GetTexture(const string& aShaderVariableName, int aSurfaceIndex)
{
	return mySurfaces[aSurfaceIndex].GetTexture(aShaderVariableName);
}