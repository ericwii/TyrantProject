#include "stdafx.h"
#include "VertexLayouts.h"
#include "../CommonUtilities/Intersection.h"

Engine* Engine::instance = nullptr;


bool Engine::Start(WNDPROC aWindowProc, WindowSetupInfo windowInfo)
{
	if (instance == nullptr)
	{
		instance = new Engine();
		if (instance->directX.SetupWindow(aWindowProc, windowInfo))
		{
			if (instance->directX.InitDirectX(aWindowProc, windowInfo))
			{
				instance->myResolution.x = static_cast<float>(windowInfo.resolution_X);
				instance->myResolution.y = static_cast<float>(windowInfo.resolution_Y);
				instance->myCamera.Init(Vector3<float>(0, 0, 0), windowInfo.resolution_X, windowInfo.resolution_Y);
				instance->OnStart();
				
				return true;
			}
		}
	}
	return false;
}

Engine* Engine::GetInstance()
{
	return instance;
}

void Engine::SetClearColor(const Vector4<float>& aColor)
{
	clearColor[0] = aColor.x;
	clearColor[1] = aColor.y;
	clearColor[2] = aColor.z; 
	clearColor[3] = aColor.w;
}

void Engine::ShutDown()
{

}

void Engine::PresentBackBuffer()
{
	if (directX.IsInitialized())
	{
		EffectData::viewMatrix = myCamera.GetInverse();
		EffectData::projectionMatrix = myCamera.GetProjection();

		directX.Present();
		directX.ClearScreen(clearColor);
	}
}

void Engine::ResizeScreen(const int aWidth, const int aHeight, bool aKeepRelativeSize)
{
	if (aKeepRelativeSize)
	{
		myCamera.SetScreenSize(aWidth, aHeight);
	}

	//Don't know when you would want to change the viewports dimensions, seems to make everything wierd.
}

void Engine::RenderDebugText(const string& someText, const Vector2<float>& aPosition, float aScale, Vector4<float> aColor)
{
	myDebugText.SetPosition(aPosition);
	myDebugText.SetCharacterScale(aScale);
	myDebugText.SetColor(aColor);
	myDebugText.SetText(someText);
	myDebugText.Render();
}

void Engine::RenderDebugLine(Vector2<float> aPoint, Vector2<float> aSecondPoint, Vector4<float> aColor)
{
	myDebugLineVertexes[0].position = Vector4<float>(aPoint, 0, 1.f);
	myDebugLineVertexes[0].color = aColor;
	myDebugLineVertexes[1].position = Vector4<float>(aSecondPoint, 0, 1.f);
	myDebugLineVertexes[1].color = aColor;

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ID3D11DeviceContext* context = directX.GetDeviceContext();

	HRESULT hr = context->Map(myDebugLineVertexBuffer.vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	DEBUG_ASSERT(hr == S_OK, "Failed to map vertex buffer for debug line");

	if (mappedResource.pData != nullptr)
	{
		VertexPositionColor* data = (VertexPositionColor*)mappedResource.pData;
		memcpy(data, myDebugLineVertexes, sizeof(VertexPositionColor) * 2);
	}
	context->Unmap(myDebugLineVertexBuffer.vertexBuffer, 0);

	context->IASetInputLayout(myDebugLineInputLayout);
	context->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINELIST);
	context->IASetVertexBuffers(
		myDebugLineVertexBuffer.startSlot, myDebugLineVertexBuffer.numberOfBuffers,
		&myDebugLineVertexBuffer.vertexBuffer, &myDebugLineVertexBuffer.stride,
		&myDebugLineVertexBuffer.byteOffset);

	myDebugLineEffect->GetTechnique()->GetPassByIndex(0)->Apply(0, context);
	context->Draw(2, 0);
}

void Engine::RenderDebugHitbox2D(const Collider::Hitbox2D& aHitbox, Vector4<float> aColor)
{
	RenderDebugLine(aHitbox.GetCorner(aHitbox.Top_Left), aHitbox.GetCorner(aHitbox.Top_Right), aColor);
	RenderDebugLine(aHitbox.GetCorner(aHitbox.Top_Right), aHitbox.GetCorner(aHitbox.Bottom_Right), aColor);
	RenderDebugLine(aHitbox.GetCorner(aHitbox.Bottom_Right), aHitbox.GetCorner(aHitbox.Bottom_Left), aColor);
	RenderDebugLine(aHitbox.GetCorner(aHitbox.Bottom_Left), aHitbox.GetCorner(aHitbox.Top_Left), aColor);
}


//Private methods

Engine::Engine()
{
	clearColor[0] = 0.4f;
	clearColor[1] = 0.61f;
	clearColor[2] = 0.94f;
	clearColor[3] = 1.f;

	//clearColor[0] = 0;
	//clearColor[1] = 0;
	//clearColor[2] = 0;
	//clearColor[3] = 1.f;
}

Engine::~Engine()
{
}

void Engine::OnStart()
{
	EffectData::viewMatrix = myCamera.GetInverse();
	EffectData::projectionMatrix = myCamera.GetProjection();
	EffectData::resolution = myResolution;

	TextFont* debugTextFont = myFontContainer.GetFont("Data/Fonts/debugFont.dds", eEffectType::Text2D);
	if (debugTextFont != nullptr)
	{
		myDebugText.Init(debugTextFont);
	}
	else
	{
		OutputDebugStringA("Failed to intialize debug font");
	}

	directX.EnableAlphaBlend();
	directX.DisableZBuffer();

	InitDebugLine();
}

void Engine::InitDebugLine()
{
	myDebugLineEffect = myEffectContainer.GetEffect(eEffectType::VertexColored2D);

	//Vertex buffer
	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;
	vertexBufferDesc.ByteWidth = sizeof(VertexPositionColor) * 2;

	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = reinterpret_cast<char*>(myDebugLineVertexes);

	myDebugLineVertexBuffer.stride = sizeof(VertexPositionColor);
	myDebugLineVertexBuffer.byteOffset = 0;
	myDebugLineVertexBuffer.startSlot = 0;
	myDebugLineVertexBuffer.numberOfBuffers = 1;

	ID3D11Device* device = directX.GetDevice();
	HRESULT hr = device->CreateBuffer(&vertexBufferDesc
		, &initData
		, &myDebugLineVertexBuffer.vertexBuffer);

	if (FAILED(hr))
	{
		PRINT_HRES_ERROR(hr, "Failed to create vertex buffer for debug line");
		DEBUG_ASSERT(false, "Failed to create vertex buffer for debug line");
	}



	//Input layout
	int size = 2;
	D3D11_INPUT_ELEMENT_DESC* layoutDescription = new D3D11_INPUT_ELEMENT_DESC[size];
	layoutDescription[0] = VertexLayout_PositionColor[0];
	layoutDescription[1] = VertexLayout_PositionColor[1];

	D3DX11_PASS_DESC passDescription;

	myDebugLineEffect->GetTechnique()->GetPassByIndex(0)->GetDesc(&passDescription);

	hr = Engine::GetInstance()->GetDirectX().GetDevice()->CreateInputLayout(layoutDescription,
		size,
		passDescription.pIAInputSignature,
		passDescription.IAInputSignatureSize,
		&myDebugLineInputLayout);

	if (FAILED(hr))
	{
		PRINT_HRES_ERROR(hr, "Failed to create input layout");
		DEBUG_ASSERT(false, "Failed to create input layout for text");
	}
}
