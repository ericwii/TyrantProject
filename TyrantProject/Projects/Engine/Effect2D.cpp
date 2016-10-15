#include "stdafx.h"
#include "Effect2D.h"

Effect2D::Effect2D() : Effect()
{
}

Effect2D::~Effect2D()
{
}


bool Effect2D::Init(const string& anEffectFile)
{
	if (Effect::Init(anEffectFile, true))
	{
		myResolutionVariable = myEffect->GetVariableByName("Resolution")->AsVector();
		DEBUG_ASSERT(myResolutionVariable->IsValid(), "Failed to find variable 'Resolution' in shader");

		myPositionVariable = myEffect->GetVariableByName("Position")->AsVector();
		DEBUG_ASSERT(myResolutionVariable->IsValid(), "Failed to find variable 'Position' in shader");

		myScaleVariable = myEffect->GetVariableByName("Scale")->AsVector();
		DEBUG_ASSERT(myResolutionVariable->IsValid(), "Failed to find variable 'Scale' in shader");

		myColorVariable = myEffect->GetVariableByName("Color")->AsVector();
		DEBUG_ASSERT(myResolutionVariable->IsValid(), "Failed to find variable 'Color' in shader");

		myRotationVariable = myEffect->GetVariableByName("Rotation")->AsScalar();
		DEBUG_ASSERT(myResolutionVariable->IsValid(), "Failed to find variable 'Rotation' in shader");

		return true;
	}

	return false;
}

void Effect2D::Update() 
{
	myColorVariable->SetFloatVector(EffectData::color.array);
	myPositionVariable->SetFloatVector(EffectData::position.array);
	myScaleVariable->SetFloatVector(EffectData::scale.array);
	myRotationVariable->SetFloat(EffectData::rotation_2D);
}


