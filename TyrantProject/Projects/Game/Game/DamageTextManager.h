#pragma once
#include "../../Engine/Text3D.h"

class CardGameTextManager
{
public:
	static void AddDamageText(char damage, const Vector2<float>& aPosition);
	static void AddHealingText(short healing, const Vector2<float>& aPosition);
	static void Update(float aDeltaTime);
	static void Render();

private:
	struct CardGameText
	{
		Text3D text;
		Vector2<float> position;
		float time = 0;
	};


	CU::GrowingArray<CardGameText> myTexts;
	TextFont* myFont;

	static CardGameTextManager* instance;

	CardGameTextManager();
	~CardGameTextManager();
};

