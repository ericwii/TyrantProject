#pragma once
#include "GUIWindow.h"

class GUIManager
{
public:
	static void AddGUIWindow(GUIWindow* aWindow);
	static void RemoveGUIWindow(GUIWindow* aWindow);

	static void Update(float aDeltaTime);
	static void Render();

	static void RenderDebugHitboxes(Vector4<float> aColor = Vector4<float>(1.f,0,0,1.f));

private:
	static CU::GrowingArray<GUIWindow*> myGUIWindows;
};

