#pragma once
#include "WindowSetupInfo.h"

#pragma warning (push, 0))
#include <d3d11.h>
#pragma warning (pop)

class DirectX
{
	friend class Engine;

public:
	DirectX();
	~DirectX();

	void DisableZBuffer();
	void EnableZBuffer();
	void EnableWireframe();
	void DisableWireframe();
	void EnableAlphaBlend();
	void DisableAlphaBlend();

	inline ID3D11DeviceContext* GetDeviceContext();
	inline ID3D11Device* GetDevice();

	bool IsInitialized();

private:

	bool SetupWindow(WNDPROC aWindowProc, const WindowSetupInfo& setupInfo);
	bool InitDirectX(WNDPROC aWindowProc, const WindowSetupInfo& setupInfo);
	void ClearScreen(float aColor[4]);
	void Present();

	bool SetupDirectX(const WindowSetupInfo& setupInfo);
	bool DeviceSetup(const WindowSetupInfo& setupInfo);
	bool StencilBufferSetup(const int aWidth, const int aHeight);
	bool SwapChainSetup();
	bool ViewPortSetup(const int aWidth, const int aHeight);
	void InitDepthBufferStates();
	void InitRasterizerStates();
	void InitBlendStates();



	HWND myWindowHandle;
	D3D_DRIVER_TYPE myDriverType;
	D3D_FEATURE_LEVEL myFeatureLevel;

	ID3D11Device* myDevice;
	ID3D11DeviceContext* myDeviceContext;
	ID3D11Texture2D* myDepthBuffer;

	ID3D11DepthStencilView* myDepthBufferView;
	ID3D11DepthStencilState* myDepthStencilState_EnableZBuffer;
	ID3D11DepthStencilState* myDepthStencilState_DisableZBuffer;

	ID3D11RenderTargetView* myRenderTargetView;
	IDXGISwapChain* mySwapChain;

	ID3D11BlendState* myBlendState_Alpha;
	ID3D11BlendState* myBlendState_NoAlpha;

	ID3D11RasterizerState* myRasterizerState_Wireframe;
	ID3D11RasterizerState* myResterizerState_Regular;

	unsigned int myMSAAQuality;
	unsigned int myMSAACount;
	bool myUseMSAA;
	bool myIsInitialized;
};

inline ID3D11DeviceContext* DirectX::GetDeviceContext()
{
	return myDeviceContext;
}

inline ID3D11Device* DirectX::GetDevice()
{
	return myDevice;
}