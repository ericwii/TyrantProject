#include "stdafx.h"
#include "GUIManager.h"

CU::GrowingArray<GUIWindow*> GUIManager::myGUIWindows = CU::GrowingArray<GUIWindow*>(16);


void GUIManager::AddGUIWindow(GUIWindow* aWindow)
{
	int insertIndex = 0;
	for (int i = myGUIWindows.Size() - 1; i >= 0; --i)
	{
		if (aWindow->myRenderLayer >= myGUIWindows[i]->myRenderLayer)
		{
			insertIndex = i + 1;
			break;
		}
	}

	myGUIWindows.AddAtIndex(insertIndex, aWindow);
}

void GUIManager::RemoveGUIWindow(GUIWindow* aWindow)
{
	for (int i = 0; i < myGUIWindows.Size(); ++i)
	{
		if (myGUIWindows[i] == aWindow)
		{
			myGUIWindows.RemoveNonCyclicAtIndex(i);
			break;
		}
	}
}


GUIWindow* currentWindow;
Vector2<float> mousePosition;
int bestIndex;
void GUIManager::Update(float aDeltaTime)
{
	mousePosition = InputManager::Mouse.GetWindowPosition(Engine::GetInstance()->GetWindowHandle(), Engine::GetInstance()->GetResolution());

	bestIndex = -1;
	for (int i = myGUIWindows.Size() - 1; i >= 0; --i)
	{
		currentWindow = myGUIWindows[i];
		if (currentWindow->myIsActive && currentWindow->myHitbox.Inside(mousePosition))
		{
			if (bestIndex < 0 || currentWindow->myHitboxLayer > myGUIWindows[bestIndex]->myHitboxLayer)
			{
				bestIndex = i;
			}
		}
	}

	if (bestIndex != -1)
	{
		myGUIWindows[bestIndex]->UpdateMouseInside(mousePosition, aDeltaTime);
	}
}

void GUIManager::Render()
{
	for (int i = 0; i < myGUIWindows.Size(); ++i)
	{
		if (myGUIWindows[i]->myIsActive)
		{
			myGUIWindows[i]->Render();
		}
	}
}

void GUIManager::RenderDebugHitboxes(Vector4<float> aColor)
{
	Engine* engineInstance = Engine::GetInstance();

	for (int i = 0; i < myGUIWindows.Size(); ++i)
	{
		engineInstance->RenderDebugHitbox2D(myGUIWindows[i]->myHitbox, aColor);
	}
}