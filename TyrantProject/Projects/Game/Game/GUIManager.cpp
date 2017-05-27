#include "stdafx.h"
#include "GUIManager.h"

CU::GrowingArray<GUIWindow*> GUIManager::myGUIWindows = CU::GrowingArray<GUIWindow*>(16);


void GUIManager::AddGUIWindow(GUIWindow* aWindow)
{
	int insertIndex = 0;
	for (int i = myGUIWindows.Size() - 1; i >= 0; --i)
	{
		if (aWindow->myLayer >= myGUIWindows[i]->myLayer)
		{
			insertIndex = i + 1;
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


Vector2<float> mousePosition;
void GUIManager::Update(float aDeltaTime)
{
	mousePosition = InputManager::Mouse.GetWindowPosition(Engine::GetInstance()->GetWindowHandle(), Engine::GetInstance()->GetResolution());

	for (int i = myGUIWindows.Size() - 1; i >= 0; --i)
	{
		if (myGUIWindows[i]->myIsActive && myGUIWindows[i]->myHitbox.Inside(mousePosition))
		{
			myGUIWindows[i]->UpdateMouseInside(mousePosition, aDeltaTime);
			break;
		}
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