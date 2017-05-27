#include "stdafx.h"
#include "Text3D.h"
#include "VertexLayouts.h"
#include "TextFont.h"


Text3D::Text3D() : myFont(nullptr), myCharacterSpace(1.f)
{
}

Text3D::Text3D(const Text3D& aText)
{
	myFont = aText.myFont;
	myTextPositioning = aText.myTextPositioning;
	myCharacterScale = aText.myCharacterScale;
	myCharacterSpace = aText.myCharacterSpace;
	myOrientation = aText.GetOrientation();
	myColor = aText.myColor;

	InitVertexBuffer();
	InitInputLayout();
	SetText(aText.myText);
}

Text3D::~Text3D()
{
}

void Text3D::Destroy()
{
	if (myVertexBuffer.vertexBuffer != nullptr)
	{
		myVertexBuffer.vertexBuffer->Release();
	}
}

void Text3D::Init(TextFont* aFont)
{
	DEBUG_ASSERT(myFont == nullptr, "Text should not be initialized more than once");
	myFont = aFont;

	InitVertexBuffer();
	InitInputLayout();
	myColor.Set(1.f, 1.f, 1.f, 1.f);
	myCharacterScale.Set(1.f, 1.f);
	myTextPositioning = eTextPositioning::eLeft;
}

void Text3D::Render()
{
	DEBUG_ASSERT(myFont != nullptr, "Can't render uninitialized text");
	if (myFont == nullptr) return;

	UpdateShaderVariables();

	DrawPass(0,static_cast<unsigned int>(myText.Lenght()));
}

void Text3D::SetColor(const Vector4<float>& aColor)
{
	myColor = aColor;
}

void Text3D::SetOrientation(const CU::Matrix44<float>& anOrientation)
{
	myOrientation = anOrientation;
}

void Text3D::SetPosition(const Vector3<float>& aPosition)
{
	myOrientation.SetPosition(aPosition);
}

void Text3D::SetCharacterScale(const Vector2<float>& aScale)
{
	myCharacterScale = aScale;

	if (myText.Lenght() > 0) SetText(myText);
}

void Text3D::SetCharacterScale(float aScale)
{
	myCharacterScale.Set(aScale, aScale);

	if (myText.Lenght() > 0) SetText(myText);
}

void Text3D::SetText(const string& someText)
{
	DEBUG_ASSERT(myFont != nullptr, "Can't set text without initializing with a font");
	DEBUG_ASSERT(someText.Lenght() <= TEXT_MAX_CHARACTER_COUNT, "Trying set a text with to many characters");

	myText = someText;
	
	const char* text = someText.c_str();
	int size = someText.Lenght();
	
	VertexPositionUV currentVertex;
	Vector3<float> currentPosition;
	Vector3<float> strideDeltaPos(1.f, 0, 0);
	strideDeltaPos *= (myFont->myNormalizedCharacterSize.x * myCharacterScale.x) * myCharacterSpace;
	if (myTextPositioning == eTextPositioning::eLeft)
	{
		for (int i = 0; i < size; ++i)
		{
			currentVertex.position = currentPosition;
			currentVertex.position.w = 1.f;
			currentVertex.UV = myFont->GetCharacterUV(text[i]);
	
			myVertexes[i] = currentVertex;
			currentPosition += strideDeltaPos;
		}
	}
	else if (myTextPositioning == eTextPositioning::eRight)
	{
		for (int i = size-1; i >= 0; --i)
		{
			currentVertex.position = currentPosition;
			currentVertex.position.w = 1.f;
			currentVertex.UV = myFont->GetCharacterUV(text[i]);

			myVertexes[i] = currentVertex;
			currentPosition -= strideDeltaPos;
		}
	}
	
	UpdateVertexBuffer(size);
}

void Text3D::SetAlpha(float anAlpha)
{
	myColor.w = anAlpha;
}


//Private methods

void Text3D::InitVertexBuffer()
{
	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;
	vertexBufferDesc.ByteWidth = sizeof(VertexPositionUV) * TEXT_MAX_CHARACTER_COUNT;

	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = reinterpret_cast<char*>(&myVertexes[0]);

	myVertexBuffer.stride = sizeof(VertexPositionUV);
	myVertexBuffer.byteOffset = 0;
	myVertexBuffer.startSlot = 0;
	myVertexBuffer.numberOfBuffers = 1;

	ID3D11Device* device = GET_DIRECTX().GetDevice();
	HRESULT hr = device->CreateBuffer(&vertexBufferDesc
		, &initData
		, &myVertexBuffer.vertexBuffer);

	if (FAILED(hr))
	{
		PRINT_HRES_ERROR(hr, "Failed to create vertex buffer for text");
		DEBUG_ASSERT(false, "Failed to create vertex buffer for text");
	}
}

void Text3D::InitInputLayout()
{
	int size = 2;
	D3D11_INPUT_ELEMENT_DESC* layoutDescription = new D3D11_INPUT_ELEMENT_DESC[size];
	layoutDescription[0] = VertexLayout_PositionUV[0];
	layoutDescription[1] = VertexLayout_PositionUV[1];
	

	D3DX11_PASS_DESC passDescription;
	HRESULT hr;

	myFont->GetEffect()->GetTechnique()->GetPassByIndex(0)->GetDesc(&passDescription);

	hr = Engine::GetInstance()->GetDirectX().GetDevice()->CreateInputLayout(layoutDescription,
		size,
		passDescription.pIAInputSignature,
		passDescription.IAInputSignatureSize,
		&myVertexLayout);

	if (FAILED(hr))
	{
		PRINT_HRES_ERROR(hr, "Failed to create input layout");
		DEBUG_ASSERT(false, "Failed to create input layout for text");
	}
}

void Text3D::UpdateShaderVariables()
{
	myFont->mySurface.UpdateShaderVariables();
	EffectData::worldMatrix = myOrientation;
	EffectData::color.Set(myColor);
	EffectData::scale.Set(myCharacterScale);
	EffectData::characterSize.Set(myFont->myNormalizedCharacterSize);

	myFont->myTextEffect->Update();
}

void Text3D::UpdateVertexBuffer(int aVertexCount)
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ID3D11DeviceContext* context = GET_DIRECTX().GetDeviceContext();

	HRESULT hr = context->Map(myVertexBuffer.vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	DEBUG_ASSERT(hr == S_OK, "Failed to map vertex buffer for text");

	if (mappedResource.pData != nullptr)
	{
		VertexPositionUV* data = (VertexPositionUV*)mappedResource.pData;
		memcpy(data, &myVertexes[0], sizeof(VertexPositionUV) * aVertexCount);
	}

	context->Unmap(myVertexBuffer.vertexBuffer, 0);
}

void Text3D::DrawPass(unsigned int aPassIndex, unsigned int aVertexCount)
{
	ID3D11DeviceContext* context = GET_DIRECTX().GetDeviceContext();

	context->IASetInputLayout(myVertexLayout);
	context->IASetVertexBuffers(
		myVertexBuffer.startSlot, myVertexBuffer.numberOfBuffers,
		&myVertexBuffer.vertexBuffer, &myVertexBuffer.stride,
		&myVertexBuffer.byteOffset);

	myFont->myTextEffect->GetTechnique()->GetPassByIndex(aPassIndex)->Apply(0, context);
	context->Draw(aVertexCount, 0);
}