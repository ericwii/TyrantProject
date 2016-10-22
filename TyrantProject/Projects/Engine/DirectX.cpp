#include "stdafx.h"
#include "DirectX.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")


DirectX::DirectX() : myWindowHandle(nullptr), myIsInitialized(false), myMSAACount(1), myMSAAQuality(0)
{
	myDevice = nullptr;
	myDeviceContext = nullptr;
	myDepthBuffer = nullptr;
	myDepthBufferView = nullptr;
	myRenderTargetView = nullptr;
	mySwapChain = nullptr;

	myRasterizerState_Wireframe = nullptr;
	myResterizerState_Regular = nullptr;
	myBlendState_NoAlpha = nullptr;
	myBlendState_Alpha = nullptr;
	myDepthStencilState_DisableZBuffer = nullptr;
	myDepthStencilState_EnableZBuffer = nullptr;
}

DirectX::~DirectX()
{
}


bool DirectX::SetupWindow(WNDPROC aWindowProc, const WindowSetupInfo& setupInfo)
{
	//Register window
	WNDCLASSEXA wcex;
	HINSTANCE hInstance = GetModuleHandle(NULL);

	wcex.cbSize = sizeof(WNDCLASSEXA);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = aWindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(107));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(108));

	LPCSTR titleString = setupInfo.title.c_str();
	wcex.lpszMenuName = titleString;
	wcex.lpszClassName = titleString;

	if (RegisterClassExA(&wcex) == false)
	{
		return false;
	}

	//Create window
	RECT windowRect = { 0,0, setupInfo.resolution_X, setupInfo.resolution_Y };
	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

	myWindowHandle = CreateWindowExA(NULL,
		titleString, titleString,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		NULL, NULL,
		hInstance,
		NULL);

	switch(setupInfo.windowMode)
	{
		case(eWindowMode::Fullscreen):
		{
			ShowWindow(myWindowHandle, SW_SHOWMAXIMIZED);
			break;
		}
		case(eWindowMode::Windowed_Fullscreen) :
		{
			ShowWindow(myWindowHandle, SW_MAXIMIZE);
			break;
		}
		case(eWindowMode::Windowed) :
		{
			ShowWindow(myWindowHandle, 1);
			break;
		}
		default:
		{
			ShowWindow(myWindowHandle, 1);
			break;
		}
	}

	
	return true;
}

bool DirectX::InitDirectX(WNDPROC aWindowProc, const WindowSetupInfo& setupInfo)
{
	if (myWindowHandle == nullptr)
	{
		DEBUG_ASSERT(myWindowHandle != nullptr, "Cannot initialize DirectX before a window is created");
		return false;
	}

	if (SetupDirectX(setupInfo) == false)
	{
		return false;
	}

	InitDepthBufferStates();
	InitRasterizerStates();
	InitBlendStates();

	myIsInitialized = true;
	return true;
}

void DirectX::ClearScreen(float aColor[4])
{
	myDeviceContext->ClearRenderTargetView(myRenderTargetView, aColor);
	myDeviceContext->ClearDepthStencilView(myDepthBufferView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void DirectX::Present()
{
	HRESULT hr = mySwapChain->Present(0, 0);

	if (FAILED(hr))
	{
		PRINT_HRES_ERROR(hr, "Failed to present the front buffer!\n");
		return;
	}

	myDeviceContext->OMSetRenderTargets(1, &myRenderTargetView, myDepthBufferView);
}

bool DirectX::IsInitialized()
{
	return myIsInitialized;
}

void DirectX::DisableZBuffer()
{
	myDeviceContext->OMSetDepthStencilState(myDepthStencilState_DisableZBuffer, 1);
}
void DirectX::EnableZBuffer()
{
	myDeviceContext->OMSetDepthStencilState(myDepthStencilState_EnableZBuffer, 1);
}

void DirectX::EnableWireframe()
{
	myDeviceContext->RSSetState(myRasterizerState_Wireframe);
}
void DirectX::DisableWireframe()
{
	myDeviceContext->RSSetState(myResterizerState_Regular);
}

void DirectX::EnableAlphaBlend()
{
	float blendfactor[4] = { 0.f, 0.f, 0.f, 0.f };
	UINT samlpleMask = 0xffffffff;
	myDeviceContext->OMSetBlendState(myBlendState_Alpha, blendfactor, samlpleMask);
}
void DirectX::DisableAlphaBlend()
{
	float blendfactor[4] = { 0.f, 0.f, 0.f, 0.f };
	UINT samlpleMask = 0xffffffff;
	myDeviceContext->OMSetBlendState(myBlendState_NoAlpha, blendfactor, samlpleMask);
}


//Private methods

bool DirectX::SetupDirectX(const WindowSetupInfo& setupInfo)
{
	if (DeviceSetup(setupInfo) &&
		SwapChainSetup() &&
		StencilBufferSetup(setupInfo.resolution_X, setupInfo.resolution_Y) &&
		ViewPortSetup(setupInfo.resolution_X, setupInfo.resolution_Y))
	{
		return true;
	}

	return false;
}

bool DirectX::DeviceSetup(const WindowSetupInfo& setupInfo)
{
	UINT createDeviceFlags = 0;

#if defined (DEBUG) || defined (_DEBUG)
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	HRESULT result =
		D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE,
			0, createDeviceFlags,
			0, 0, D3D11_SDK_VERSION,
			&myDevice, &myFeatureLevel,
			&myDeviceContext);

	if (FAILED(result))
	{
		PRINT_HRES_ERROR(result, "Failed to create the device and swap chain!");
		return false;
	}

	//swap chain

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferDesc.Width = setupInfo.resolution_X;
	swapChainDesc.BufferDesc.Height = setupInfo.resolution_Y;
	swapChainDesc.OutputWindow = myWindowHandle;
	swapChainDesc.Windowed = !(setupInfo.windowMode == eWindowMode::Fullscreen);
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.Flags = 0;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	unsigned int m4xMsaaQuality = 0;

	result = myDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m4xMsaaQuality);

	if (FAILED(result))
	{
		PRINT_HRES_ERROR(result, "\nSystem does not support 4xmsaa\n");
		myUseMSAA = false;
	}
	else
	{
		myUseMSAA = true;
		myMSAACount = 4;
	    myMSAAQuality = m4xMsaaQuality - 1;
	}

	swapChainDesc.SampleDesc.Count = myMSAACount;
	swapChainDesc.SampleDesc.Quality = myMSAAQuality;

	IDXGIFactory* idxgiFactory = nullptr;

	result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&idxgiFactory);

	if (FAILED(result))
	{
		PRINT_HRES_ERROR(result, "Failed to create DXGI Factory");
		return false;
	}

	result = idxgiFactory->CreateSwapChain(myDevice, &swapChainDesc, &mySwapChain);

	if (FAILED(result))
	{
		PRINT_HRES_ERROR(result, "Failed create Swap chain!");
		return false;
	}

	idxgiFactory->Release();

	return true;
}

bool DirectX::StencilBufferSetup(const int aWidth, const int aHeight)
{
	HRESULT hr = S_OK;

	// Create depth stencil texture
	D3D11_TEXTURE2D_DESC depthBufferInfo;
	depthBufferInfo.Width = aWidth;
	depthBufferInfo.Height = aHeight;
	depthBufferInfo.MipLevels = 1;
	depthBufferInfo.ArraySize = 1;
	depthBufferInfo.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferInfo.SampleDesc.Count = myMSAACount;
	depthBufferInfo.SampleDesc.Quality = myMSAAQuality;
	depthBufferInfo.Usage = D3D11_USAGE_DEFAULT;
	depthBufferInfo.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferInfo.CPUAccessFlags = 0;
	depthBufferInfo.MiscFlags = 0;

	hr = myDevice->CreateTexture2D(&depthBufferInfo, NULL, &myDepthBuffer);
	if (FAILED(hr))
	{
		PRINT_HRES_ERROR(hr, "Failed to create the depth buffer!");
	}

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC stencilViewInfo;
	ZeroMemory(&stencilViewInfo, sizeof(stencilViewInfo));
	stencilViewInfo.Format = depthBufferInfo.Format;

	if (myUseMSAA == true)
	{
		stencilViewInfo.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	}
	else
	{
		stencilViewInfo.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	}

	stencilViewInfo.Texture2D.MipSlice = 0;
	hr = myDevice->CreateDepthStencilView(myDepthBuffer, &stencilViewInfo, &myDepthBufferView);
	if (FAILED(hr))
	{
		PRINT_HRES_ERROR(hr, "Failed to create depth stencil view!");
		return false;
	}

	return true;
}

bool DirectX::SwapChainSetup()
{
	HRESULT hr = S_OK;

	ID3D11Texture2D* backBuffer = nullptr;
	hr = mySwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);

	if (FAILED(hr))
	{
		PRINT_HRES_ERROR(hr, "Failed to get back buffer from swap chain!");
		return false;
	}


	hr = myDevice->CreateRenderTargetView(backBuffer, NULL, &myRenderTargetView);

	if (FAILED(hr))
	{
		PRINT_HRES_ERROR(hr, "Failed to create render target view!");
		return false;
	}

	backBuffer->Release();

	myDeviceContext->OMSetRenderTargets(1, &myRenderTargetView, myDepthBufferView);

	return true;
}

bool DirectX::ViewPortSetup(const int aWidth, const int aHeight)
{
	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = static_cast<float>(aWidth);
	vp.Height = static_cast<float>(aHeight);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	myDeviceContext->RSSetViewports(1, &vp);

	return true;
}

void DirectX::InitDepthBufferStates()
{
	//Init enabled z buffer state

	D3D11_DEPTH_STENCIL_DESC  stencilDescEnabled;
	ZeroMemory(&stencilDescEnabled, sizeof(stencilDescEnabled));

	stencilDescEnabled.DepthEnable = true;
	stencilDescEnabled.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	stencilDescEnabled.DepthFunc = D3D11_COMPARISON_LESS;
	stencilDescEnabled.StencilEnable = true;
	stencilDescEnabled.StencilReadMask = 0xFF;
	stencilDescEnabled.StencilWriteMask = 0xFF;
	stencilDescEnabled.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	stencilDescEnabled.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	stencilDescEnabled.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	stencilDescEnabled.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	stencilDescEnabled.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	stencilDescEnabled.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	stencilDescEnabled.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	stencilDescEnabled.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	HRESULT hr = myDevice->CreateDepthStencilState(&stencilDescEnabled, &myDepthStencilState_EnableZBuffer);
	if (FAILED(hr))
	{
		PRINT_HRES_ERROR(hr, "Failed creating depth stencil state with enabled z buffer");
		return;
	}


	//Init disabled z buffer buffer state

	D3D11_DEPTH_STENCIL_DESC  stencilDescDisabled;
	ZeroMemory(&stencilDescDisabled, sizeof(stencilDescDisabled));

	stencilDescDisabled.DepthEnable = false;
	stencilDescDisabled.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	stencilDescDisabled.DepthFunc = D3D11_COMPARISON_LESS;
	stencilDescDisabled.StencilEnable = true;
	stencilDescDisabled.StencilReadMask = 0xFF;
	stencilDescDisabled.StencilWriteMask = 0xFF;
	stencilDescDisabled.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	stencilDescDisabled.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	stencilDescDisabled.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	stencilDescDisabled.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	stencilDescDisabled.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	stencilDescDisabled.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	stencilDescDisabled.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	stencilDescDisabled.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	hr = myDevice->CreateDepthStencilState(&stencilDescDisabled, &myDepthStencilState_DisableZBuffer);
	if (FAILED(hr))
	{
		PRINT_HRES_ERROR(hr, "Failed creating depth stencil state with disabled z buffer");
		return;
	}
}

void DirectX::InitRasterizerStates()
{
	D3D11_RASTERIZER_DESC rasterWireframeDesc;
	ZeroMemory(&rasterWireframeDesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterWireframeDesc.CullMode = D3D11_CULL_NONE;
	rasterWireframeDesc.FillMode = D3D11_FILL_WIREFRAME;
	myDevice->CreateRasterizerState(&rasterWireframeDesc, &myRasterizerState_Wireframe);


	D3D11_RASTERIZER_DESC rasterRegularDesc;
	ZeroMemory(&rasterRegularDesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterRegularDesc.CullMode = D3D11_CULL_BACK;
	rasterRegularDesc.FillMode = D3D11_FILL_SOLID;
	myDevice->CreateRasterizerState(&rasterRegularDesc, &myResterizerState_Regular);
}

void DirectX::InitBlendStates()
{
	//Init alpha blendstate
	D3D11_BLEND_DESC alphaBlendDesc;
	alphaBlendDesc.AlphaToCoverageEnable = false;
	alphaBlendDesc.IndependentBlendEnable = false;
	alphaBlendDesc.RenderTarget[0].BlendEnable = TRUE;
	alphaBlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	alphaBlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	alphaBlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	alphaBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_INV_DEST_ALPHA;
	alphaBlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	alphaBlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	alphaBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	alphaBlendDesc.RenderTarget[0].RenderTargetWriteMask = 0x0f;

	HRESULT hr = myDevice->CreateBlendState(&alphaBlendDesc, &myBlendState_Alpha);
	if (hr != S_OK)
	{
		PRINT_HRES_ERROR(hr, "Failed to create alpha blendstate");
		return;
	}

	//Init no alpha blendstate
	D3D11_BLEND_DESC noalphaBlendDesc;
	ZeroMemory(&noalphaBlendDesc, sizeof(D3D11_BLEND_DESC));
	noalphaBlendDesc.RenderTarget[0].BlendEnable = FALSE;
	noalphaBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = myDevice->CreateBlendState(&noalphaBlendDesc, &myBlendState_NoAlpha);
	if (hr != S_OK)
	{
		PRINT_HRES_ERROR(hr, "Failed to create no alpha blendstate");
	}
}