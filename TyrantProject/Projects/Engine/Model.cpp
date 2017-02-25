#include "stdafx.h"
#include "Model.h"


Model::Model() : myEffect(nullptr), myVertexLayout(nullptr), myIsNullObject(true), myAlpha(1.f)
{
}

Model::~Model()
{
}




void Model::Destroy()
{
	myIsNullObject = true;

	if (myVertexLayout != nullptr)
	{
		myVertexLayout->Release();
	}
	if (myVertexBuffer.vertexBuffer != nullptr)
	{
		myVertexBuffer.vertexBuffer->Release();
	}
	if (myIndexBuffer.indexBuffer != nullptr)
	{
		myIndexBuffer.indexBuffer->Release();
	}
}

void Model::Render(const CU::Matrix44<float>& aParentSpace, unsigned int aPassIndex)
{
	DEBUG_ASSERT(myIsNullObject == false, "Cannot render a model that is not loaded");
	DEBUG_ASSERT(myEffect != nullptr, "Cannot render a model with no effect set");

	EffectData::worldMatrix = aParentSpace;
	EffectData::position = aParentSpace.GetTranslation();
	EffectData::alpha = myAlpha;

	ID3D11DeviceContext* context = GET_DIRECTX().GetDeviceContext();

	context->IASetInputLayout(myVertexLayout);
	context->IASetVertexBuffers(myVertexBuffer.startSlot, myVertexBuffer.numberOfBuffers, &myVertexBuffer.vertexBuffer, &myVertexBuffer.stride, &myVertexBuffer.byteOffset);
	context->IASetIndexBuffer(myIndexBuffer.indexBuffer, myIndexBuffer.indexBufferFormat, myIndexBuffer.byteOffset);

	D3DX11_TECHNIQUE_DESC techniqueDescription;
	myEffect->GetTechnique()->GetDesc(&techniqueDescription);
	myEffect->Update();

	for (unsigned short i = 0; i < mySurfaces.Size(); ++i)
	{
		mySurfaces[i].UpdateShaderVariables();

		myEffect->GetTechnique()->GetPassByIndex(aPassIndex)->Apply(0, context);
		context->DrawIndexed(myIndexData.numberOfIndexes, 0, 0);	
	}
}

void Model::RenderWireFrame(const CU::Matrix44<float>& aParentSpace)
{
	GET_DIRECTX().EnableWireframe();
	Render(aParentSpace);
	GET_DIRECTX().DisableWireframe();
}

void Model::AddTexture(const string& aShaderVariableName, const string& aTextureFile, int surfaceIndex)
{
	mySurfaces[surfaceIndex].AddTexture(aShaderVariableName, aTextureFile);
}


//Private methods

bool Model::InitVertexBuffer()
{
	const int size = myVertexFormat.Size();
	D3D11_INPUT_ELEMENT_DESC* VertexLayoutLatest = new D3D11_INPUT_ELEMENT_DESC[size];
	for (unsigned short i = 0; i < size; ++i)
	{
		VertexLayoutLatest[i] = myVertexFormat[i];
	}

	D3DX11_PASS_DESC passDescription;
	HRESULT hr;

	myEffect->GetTechnique()->GetPassByIndex(0)->GetDesc(&passDescription);

	hr = Engine::GetInstance()->GetDirectX().GetDevice()->CreateInputLayout(VertexLayoutLatest,
		size,
		passDescription.pIAInputSignature,
		passDescription.IAInputSignatureSize,
		&myVertexLayout);

	if (FAILED(hr))
	{
		PRINT_HRES_ERROR(hr, "Failed to create input layout");
		DEBUG_ASSERT(false, "Failed to create input layout for model");
		return false;
	}


	D3D11_BUFFER_DESC vbd;
	ZeroMemory(&vbd, sizeof(vbd));
	vbd.Usage = D3D11_USAGE_DEFAULT;
	vbd.ByteWidth = myVertexData.size;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vInitData;
	vInitData.pSysMem = myVertexData.vertexData;

	hr = Engine::GetInstance()->GetDirectX().GetDevice()->CreateBuffer(&vbd, &vInitData, &myVertexBuffer.vertexBuffer);
	if (FAILED(hr))
	{
		PRINT_HRES_ERROR(hr, "Failed to create vertex buffer");
		DEBUG_ASSERT(false, "Failed to create vertex buffer for model");
		return false;
	}
	// Set vertex buffer
	myVertexBuffer.stride = myVertexData.stride;
	myVertexBuffer.byteOffset = 0;
	myVertexBuffer.startSlot = 0;
	myVertexBuffer.numberOfBuffers = 1;
	return true;
}

bool Model::InitIndexBuffer()
{
	D3D11_BUFFER_DESC indexBufferData;
	indexBufferData.Usage = D3D11_USAGE_DEFAULT;
	indexBufferData.ByteWidth = myIndexData.size;
	indexBufferData.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferData.CPUAccessFlags = 0;
	indexBufferData.MiscFlags = 0;
	indexBufferData.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subData;
	subData.pSysMem = myIndexData.indexData;

	HRESULT hr = Engine::GetInstance()->GetDirectX().GetDevice()->CreateBuffer(&indexBufferData, &subData, &myIndexBuffer.indexBuffer);
	if (FAILED(hr))
	{
		PRINT_HRES_ERROR(hr, "Failed to create index buffer");
		DEBUG_ASSERT(false, "Failed to create index buffer for model");
	}
	myIndexBuffer.byteOffset = 0;
	myIndexBuffer.indexBufferFormat = myIndexData.format;
	return true;
}