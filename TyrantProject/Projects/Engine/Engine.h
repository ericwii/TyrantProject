#pragma once
#include "DirectX.h"
#include "TextureContainer.h"
#include "EffectContainer.h"
#include "FontContainer.h"
#include "Camera.h"
#include "Text2D.h"

class Engine
{
public:

	static bool Start(WNDPROC aWindowProc, WindowSetupInfo windowInfo = WindowSetupInfo());
	static Engine* GetInstance();

	void SetClearColor(const Vector4<float>& aColor);

	void ShutDown();
	void PresentBackBuffer();
	void ResizeScreen(const int aWidth, const int aHeight, bool aKeepRelativeSize = false);
	void RenderDebugText(const string& someText, const Vector2<float>& aPosition, float aScale = 1.f);

	inline DirectX& GetDirectX();
	inline TextureContainer& GetTextureContainer();
	inline EffectContainer& GetEffectContainer();
	inline FontContainer& GetFontContainer();
	inline Camera& GetCamera();
	inline const Vector2<float>& GetResolution();
	inline HWND GetWindowHandle();

private:
	Engine();
	~Engine();

	void OnStart();

	DirectX directX;
	TextureContainer myTextureContainer;
	EffectContainer myEffectContainer;
	FontContainer myFontContainer;
	Camera myCamera;
	Text2D myDebugText;
	Vector2<float> myResolution;

	float clearColor[4];
	static Engine* instance;
};

inline DirectX& Engine::GetDirectX()
{
	return directX;
}

inline TextureContainer& Engine::GetTextureContainer()
{
	return myTextureContainer;
}

inline EffectContainer& Engine::GetEffectContainer()
{
	return myEffectContainer;
}

inline FontContainer& Engine::GetFontContainer()
{
	return myFontContainer;
}

inline Camera& Engine::GetCamera()
{
	return myCamera;
}

inline const Vector2<float>& Engine::GetResolution()
{
	return myResolution;
}

inline HWND Engine::GetWindowHandle()
{
	return directX.myWindowHandle;
}
