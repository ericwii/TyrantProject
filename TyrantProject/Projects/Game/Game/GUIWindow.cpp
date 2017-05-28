#include "stdafx.h"
#include "GUIWindow.h"
#include "GUIManager.h"


GUIWindow::GUIWindow() : myRenderLayer(-1), myHitboxLayer(-1), myIsActive(false)
{
}

GUIWindow::~GUIWindow()
{
}



void GUIWindow::Init(Instance& aCanvas, int aRenderLayer, int aHitboxLayer)
{
	myCanvas = aCanvas;
	myRenderLayer = aRenderLayer;
	myHitboxLayer = aHitboxLayer;

	myChildInstanceCopies.Allocate(10);
	myChildTextCopies.Allocate(8);
	GUIManager::AddGUIWindow(this);
}

void GUIWindow::Init(Instance& aCanvas, Collider::Hitbox2D& aHitbox, int aRenderLayer, int aHitboxLayer)
{
	myCanvas = aCanvas;
	myHitbox = aHitbox;
	myRenderLayer = aRenderLayer;
	myHitboxLayer = aHitboxLayer;

	myChildInstanceCopies.Allocate(10);
	myChildTextCopies.Allocate(8);
	GUIManager::AddGUIWindow(this);
}

void GUIWindow::Destroy()
{
	GUIManager::RemoveGUIWindow(this);
}

void GUIWindow::AddChildCopy(Instance& anInstance, const Vector3<float>& aPosition)
{
	myChildInstanceCopies.Add(Instance(anInstance));
	myChildInstanceCopies.GetLast().SetPosition(aPosition);
	myCanvas.AddChild(&myChildInstanceCopies.GetLast());
}

void GUIWindow::AddChildCopy(Text3D& someText, const Vector3<float>& aPosition)
{
	myChildTextCopies.Add(Text3D(someText));

	Text3D& newText = myChildTextCopies.GetLast();
	newText.SetText(someText.GetText());
	newText.SetPosition(aPosition);
	newText.SetCurrentOrientationAsOriginal();

	myCanvas.AddChild(&newText);
}

void GUIWindow::AddChild(Instance* anInstance)
{
	myCanvas.AddChild(anInstance);
}

void GUIWindow::AddChild(Text3D* someText)
{
	myCanvas.AddChild(someText);
}

void GUIWindow::RemoveChild(Instance* anInstance)
{
	myCanvas.RemoveChild(anInstance);
}

void GUIWindow::RemoveChild(Text3D* someText)
{
	myCanvas.RemoveChild(someText);
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

void GUIWindow::SetHitboxLayer(int aLayer)
{
	myHitboxLayer = aLayer;
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