#include "stdafx.h"
#include "DamageTextManager.h"

Vector4<float> damageColor(1.f, 0, 0, 1.f);
Vector4<float> healingColor(0, 1.f, 0, 1.f);
Vector2<float> textStartOffset(0.3f, -0.5f);
Vector2<float> textMovementPerSecond(0, 1.5f);
float textCharacterSpace = 0.7f;
float textDiplayTime = 0.5f;
float textSize = 8.f;

CardGameTextManager* CardGameTextManager::instance = new CardGameTextManager();

CardGameTextManager::CardGameTextManager() : myTexts(16), myFont(nullptr)
{
}

CardGameTextManager::~CardGameTextManager()
{
}



void CardGameTextManager::AddDamageText(char damage, const Vector2<float>& aPosition)
{
	if (instance->myFont == nullptr)
	{
		instance->myFont = Engine::GetInstance()->GetFontContainer().GetFont("Data/Fonts/debugFont.dds", eEffectType::Text3D);
	}

	CardGameText newText;
	newText.text.Init(instance->myFont);

	string text("-");
	text += damage;
	newText.position = aPosition + textStartOffset;
	newText.text.SetText(text);
	newText.text.SetCharacterSpace(textCharacterSpace);
	newText.text.SetPosition(newText.position);
	newText.text.SetCharacterScale(textSize);
	newText.text.SetColor(damageColor);

	instance->myTexts.Add(newText);
}

void CardGameTextManager::AddHealingText(short healing, const Vector2<float>& aPosition)
{
	if (instance->myFont == nullptr)
	{
		instance->myFont = Engine::GetInstance()->GetFontContainer().GetFont("Data/Fonts/debugFont.dds", eEffectType::Text3D);
	}

	CardGameText newText;
	newText.text.Init(instance->myFont);

	string text('+');
	text += healing;
	newText.position = aPosition + textStartOffset;
	newText.text.SetText(text);
	newText.text.SetCharacterSpace(textCharacterSpace);
	newText.text.SetPosition(newText.position);
	newText.text.SetCharacterScale(textSize);
	newText.text.SetColor(healingColor);

	instance->myTexts.Add(newText);
}

void CardGameTextManager::Update(float aDeltaTime)
{
	CardGameText* currentText;
	for (int i = 0; i < instance->myTexts.Size(); ++i)
	{
		currentText = &instance->myTexts[i];
		currentText->position += textMovementPerSecond * aDeltaTime;
		currentText->text.SetPosition(currentText->position);
		currentText->time += aDeltaTime;
	
		if (currentText->time > textDiplayTime)
		{
			instance->myTexts.RemoveCyclicAtIndex(i);
			--i;
		}
	}
}

void CardGameTextManager::Render()
{
	for (int i = 0; i < instance->myTexts.Size(); ++i)
	{
		instance->myTexts[i].text.Render();
	}
}