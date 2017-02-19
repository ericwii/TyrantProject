#pragma once
#include "../../Engine/Text3D.h"

class DamageTextManager
{
public:
	static void AddDamageText(char damage, const Vector2<float>& aPosition);
	static void Update(float aDeltaTime);
	static void Render();

private:
	struct DamageText
	{
		Text3D text;
		Vector2<float> position;
		float time = 0;
	};


	CU::GrowingArray<DamageText> myDamageTexts;
	TextFont* myFont;

	static DamageTextManager* instance;


	DamageTextManager();
	~DamageTextManager();
};

