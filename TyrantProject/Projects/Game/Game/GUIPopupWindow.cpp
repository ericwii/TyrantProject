#include "stdafx.h"
#include "GUIPopupWindow.h"
#include "../../Input/InputManager.h"


GUIPopupWindow::GUIPopupWindow() : myCurrentDelay(0), myDelay(1.f), myOffset(0), myHasUpdatedThisFrame(false)
{
}

GUIPopupWindow::~GUIPopupWindow()
{
}


void GUIPopupWindow::Init(Instance& anInstance, float anOffset, float aPopupDelay)
{
	GUIWindow::Init(anInstance, 5);
	myOffset = anOffset;
	myDelay = aPopupDelay;
}




//Private Methods

void GUIPopupWindow::UpdateMouseInside(Vector2<float> aMousePosition, float aDeltaTime)
{
	if (myCurrentDelay < myDelay)
	{
		myCurrentDelay += aDeltaTime;

		if (myCurrentDelay >= myDelay)
		{
			Vector3<float> position(myHitbox.GetCenter() * 5.f, myCanvas.GetPosition().z);
			position.y *= -1;

			if (position.x < 0)
			{
				position.x += myOffset;
			}
			else
			{
				position.x -= myOffset;
			}

			if (position.y < 0)
			{
				position.y += myOffset;
			}
			else
			{
				position.y -= myOffset;
			}

			myCanvas.SetPosition(position);
		}
	}
	myHasUpdatedThisFrame = true;
}

void GUIPopupWindow::Render()
{
	if (myHasUpdatedThisFrame && myCurrentDelay >= myDelay)
	{
		GUIWindow::Render();
	}
	else if (!myHasUpdatedThisFrame)
	{
		myCurrentDelay = 0;
	}
	myHasUpdatedThisFrame = false;
}