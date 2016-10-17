#include "stdafx.h"
#include "EffectText2D.h"

EffectText2D::EffectText2D() : myCharacterSizeVariable(nullptr)
{
}

EffectText2D::~EffectText2D()
{
}



bool EffectText2D::Init(const string& anEffectFile)
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

void EffectText2D::Update()
{
	Effect2D::Update();
	myCharacterSizeVariable->SetFloatVector(EffectData::characterSize.array);
}