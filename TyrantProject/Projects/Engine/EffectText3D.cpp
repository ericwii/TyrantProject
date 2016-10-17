#include "stdafx.h"
#include "EffectText3D.h"


EffectText3D::EffectText3D() : Effect(), 
myColorVariable(nullptr), myCharacterSizeVariable(nullptr), myScaleVariable(nullptr)
{
}

EffectText3D::~EffectText3D()
{
}


bool EffectText3D::Init(const string& anEffectFile)
{
	Effect::Init(anEffectFile);

	myCharacterSizeVariable = myEffect->GetVariableByName("CharacterSize")->AsVector();
	if (myCharacterSizeVariable->IsValid() == false)
	{
		DEBUG_ASSERT(false, "Failed to find variable 'CharacterSize' in shader");
		return false;
	}

	myColorVariable = myEffect->GetVariableByName("Color")->AsVector();
	if (myColorVariable->IsValid() == false)
	{
		DEBUG_ASSERT(false, "Failed to find variable 'Color' in shader");
		return false;
	}

	myScaleVariable = myEffect->GetVariableByName("Scale")->AsVector();
	if (myScaleVariable->IsValid() == false)
	{
		DEBUG_ASSERT(false, "Failed to find variable 'Scale' in shader");
		return false;
	}

	return true;
}

void EffectText3D::Update()
{
	Effect::Update();

	myCharacterSizeVariable->SetFloatVector(EffectData::characterSize.array);
	myColorVariable->SetFloatVector(EffectData::color.array);
	myScaleVariable->SetFloatVector(EffectData::scale.array);
}