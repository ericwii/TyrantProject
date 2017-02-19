#include "stdafx.h"
#include "DamageTextManager.h"

Vector4<float> textColor(1.f, 0, 0, 1.f);
Vector2<float> textStartOffset(0.3f, -0.5f);
Vector2<float> textMovementPerSecond(0, 1.5f);
float textCharacterSpace = 0.7f;
float textDiplayTime = 0.5f;
float textSize = 8.f;

DamageTextManager* DamageTextManager::instance = new DamageTextManager();

DamageTextManager::DamageTextManager() : myDamageTexts(16), myFont(nullptr)
{
}

DamageTextManager::~DamageTextManager()
{
}



void DamageTextManager::AddDamageText(char damage, const Vector2<float>& aPosition)
{
	if (instance->myFont == nullptr)
	{
		instance->myFont = Engine::GetInstance()->GetFontContainer().GetFont("Data/Fonts/debugFont.dds", eEffectType::Text3D);
	}

	DamageText newText;
	newText.text.Init(instance->myFont);

	string text("-");
	text += damage;
	newText.position = aPosition + textStartOffset;
	newText.text.SetText(text);
	newText.text.SetCharacterSpace(textCharacterSpace);
	newText.text.SetPosition(newText.position);
	newText.text.SetCharacterScale(textSize);
	newText.text.SetColor(textColor);

	instance->myDamageTexts.Add(newText);
}

void DamageTextManager::Update(float aDeltaTime)
{
	DamageText* currentText;
	for (int i = 0; i < instance->myDamageTexts.Size(); ++i)
	{
		currentText = &instance->myDamageTexts[i];
		currentText->position += textMovementPerSecond * aDeltaTime;
		currentText->text.SetPosition(currentText->position);
		currentText->time += aDeltaTime;
	
		if (currentText->time > textDiplayTime)
		{
			instance->myDamageTexts.RemoveCyclicAtIndex(i);
			--i;
		}
	}
}

void DamageTextManager::Render()
{
	for (int i = 0; i < instance->myDamageTexts.Size(); ++i)
	{
		instance->myDamageTexts[i].text.Render();
	}
}