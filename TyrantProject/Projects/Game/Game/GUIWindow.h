#pragma once
#include "../../Engine/Text3D.h"

class GUIWindow
{
	friend class GUIManager;

public:
	GUIWindow();
	~GUIWindow();

	void Init(Instance& aCanvas, int aRenderLayer = 0, int aHitboxLayer = 0);
	void Init(Instance& aCanvas, Collider::Hitbox2D& aHitbox, int aRenderLayer = 0, int aHitboxLayer = 0);
	void Destroy();

	void AddChildCopy(Instance& anInstance, const Vector3<float>& aPosition);
	void AddChildCopy(Text3D& someText, const Vector3<float>& aPosition);
	void AddChild(Instance* anInstance);
	void AddChild(Text3D* someText);

	void RemoveChild(Instance* anInstance);
	void RemoveChild(Text3D* someText);

	void SetHitboxLayer(int aLayer);
	void SetHitbox(Collider::Hitbox2D& aHitbox);
	void SetPosition(Vector3<float> aPosition);
	inline void SetActive(bool anActive);

	inline Vector3<float> GetPosition();
	inline const Hitbox2D& GetHitbox();

protected:
	virtual void UpdateMouseInside(Vector2<float> aMousePosition, float aDeltaTime);
	virtual void Render();

	CU::GrowingArray<Instance> myChildInstanceCopies;
	CU::GrowingArray<Text3D> myChildTextCopies;
	Instance myCanvas;
	Collider::Hitbox2D myHitbox;
	int myHitboxLayer;
	int myRenderLayer;
	bool myIsActive;
};


inline void GUIWindow::SetActive(bool anActive)
{
	myIsActive = anActive;
}

inline Vector3<float> GUIWindow::GetPosition()
{
	return myCanvas.GetPosition();
}

inline const Hitbox2D& GUIWindow::GetHitbox()
{
	return myHitbox;
}