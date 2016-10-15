#include "stdafx.h"

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

void Engine::RenderDebugText(const string& someText, const Vector2<float>& aPosition, float aScale)
{
	myDebugText.SetPosition(aPosition);
	myDebugText.SetText(someText);
	myDebugText.SetCharacterScale(aScale);
	myDebugText.Render();
}


//Private methods

Engine::Engine()
{
	clearColor[0] = 0.4f;
	clearColor[1] = 0.61f;
	clearColor[2] = 0.94f;
	clearColor[3] = 1.f;
}

Engine::~Engine()
{
}

void Engine::OnStart()
{
	EffectData::viewMatrix = myCamera.GetInverse();
	EffectData::projectionMatrix = myCamera.GetProjection();
	EffectData::resolution = myResolution;

	TextFont* debugTextFont = myFontContainer.GetFont("Data/Fonts/debugFont.dds");
	if (debugTextFont != nullptr)
	{
		myDebugText.Init(debugTextFont);
	}
	else
	{
		OutputDebugStringA("Failed to intialize debug font");
	}

	directX.EnableAlphaBlend();
}
