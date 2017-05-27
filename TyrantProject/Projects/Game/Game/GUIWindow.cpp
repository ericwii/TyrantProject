#include "stdafx.h"
#include "GUIWindow.h"
#include "GUIManager.h"


GUIWindow::GUIWindow() : myLayer(-1), myIsActive(false)
{
}

GUIWindow::~GUIWindow()
{
}



void GUIWindow::Init(Instance& aCanvas, int aLayer)
{
	myCanvas = aCanvas;
	myLayer = aLayer;

	myChildInstances.Allocate(10);
	myChildTexts.Allocate(8);
	GUIManager::AddGUIWindow(this);
}

void GUIWindow::Init(Instance& aCanvas, Collider::Hitbox2D& aHitbox, int aLayer)
{
	myCanvas = aCanvas;
	myHitbox = aHitbox;
	myLayer = aLayer;

	myChildInstances.Allocate(10);
	myChildTexts.Allocate(8);
	GUIManager::AddGUIWindow(this);
}

void GUIWindow::Destroy()
{
	GUIManager::RemoveGUIWindow(this);
}

void GUIWindow::AddChildText(Text3D& someText, const Vector3<float>& aPosition)
{
	myChildTexts.Add(Text3D(someText));

	Text3D& newText = myChildTexts.GetLast();
	newText.SetText(someText.GetText());
	newText.SetPosition(aPosition);
	newText.SetCurrentOrientationAsOriginal();

	myCanvas.AddChild(&newText);
}

void GUIWindow::AddChildInstance(Instance& anInstance, const Vector3<float>& aPosition)
{
	myChildInstances.Add(Instance(anInstance));
	myChildInstances.GetLast().SetPosition(aPosition);
	myCanvas.AddChild(&myChildInstances.GetLast());
}


void GUIWindow::UpdateMouseInside(Vector2<float> aMousePosition, float aDeltaTime)
{
	aMousePosition;
	aDeltaTime;
}

void GUIWindow::Render()
{
	myCanvas.Render();
}


void GUIWindow::SetHitbox(Collider::Hitbox2D& aHitbox)
{
	myHitbox = aHitbox;
}

void GUIWindow::SetPosition(Vector3<float> aPosition)
{
	Vector3<float> delta = aPosition - myCanvas.GetPosition();
	myCanvas.SetPosition(myCanvas.GetPosition() + delta);
}