#include "stdafx.h"
#include "EffectText.h"

EffectText::EffectText() : myCharacterSizeVariable(nullptr)
{
}

EffectText::~EffectText()
{
}



bool EffectText::Init(const string& anEffectFile)
{
	Effect2D::Init(anEffectFile);

	myCharacterSizeVariable = myEffect->GetVariableByName("CharacterSize")->AsVector();

	if (myCharacterSizeVariable->IsValid() == false)
	{
		DEBUG_ASSERT(false, "Failed to find variable 'CharacterSize' in shader");
		return false;
	}

	return true;
}

void EffectText::Update()
{
	Effect2D::Update();
	myCharacterSizeVariable->SetFloatVector(EffectData::characterSize.array);
}