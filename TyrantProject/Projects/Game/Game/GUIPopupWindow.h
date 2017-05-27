#pragma once
#include "GUIWindow.h"

class GUIPopupWindow : public GUIWindow
{
public:
	GUIPopupWindow();
	~GUIPopupWindow();

	void Init(Instance& anInstance, float anOffset, float aPopupDelay = 0.3f);

private:
	void UpdateMouseInside(Vector2<float> aMousePosition, float aDeltaTime) override;
	void Render() override;

	float myOffset;
	float myCurrentDelay;
	float myDelay;
	bool myHasUpdatedThisFrame;
};

