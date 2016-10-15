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

	void Render(const CU::Matrix44<float>& aParentSpace);
	void RenderWireFrame(const CU::Matrix44<float>& aParentSpace);

	inline void SetEffect(Effect* anEffect);

	inline const Effect* GetEffect() const;
	inline int GetVertexCount() const;
	inline int GetIndexCount() const;

private:
	bool InitVertexBuffer();
	bool InitIndexBuffer();

	CU::GrowingArray<Surface> mySurfaces;
	CU::GrowingArray<D3D11_INPUT_ELEMENT_DESC> myVertexFormat;

	Effect* myEffect;

	VertexIndexWrapper myIndexData;
	IndexBufferWrapper myIndexBuffer;
	VertexDataWrapper myVertexData;
	VertexBufferWrapper myVertexBuffer;

	ID3D11InputLayout* myVertexLayout;

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