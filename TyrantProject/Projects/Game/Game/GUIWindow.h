#pragma once
#include "../../Engine/Text3D.h"

class GUIWindow
{
	friend class GUIManager;

public:
	GUIWindow();
	~GUIWindow();

	void Init(Instance& aCanvas, int aLayer = 0);
	void Init(Instance& aCanvas, Collider::Hitbox2D& aHitbox, int aLayer = 0);
	void Destroy();

	void AddChildText(Text3D& someText, const Vector3<float>& aPosition);
	void AddChildInstance(Instance& anInstance, const Vector3<float>& aPosition);

	void SetHitbox(Collider::Hitbox2D& aHitbox);
	void SetPosition(Vector3<float> aPosition);
	inline void SetActive(bool anActive);

	inline Vector2<float> GetPosition();

protected:
	virtual void UpdateMouseInside(Vector2<float> aMousePosition, float aDeltaTime);
	virtual void Render();

	CU::GrowingArray<Instance> myChildInstances;
	CU::GrowingArray<Text3D> myChildTexts;
	Instance myCanvas;
	Collider::Hitbox2D myHitbox;
	int myLayer;
	bool myIsActive;
};


inline void GUIWindow::SetActive(bool anActive)
{
	myIsActive = anActive;
}

inline Vector2<float> GUIWindow::GetPosition()
{
	return myCanvas.GetPosition();
}