#include "stdafx.h"
#include "EffectAnimation.h"


EffectAnimation::EffectAnimation() : myFrameSizeVariable(nullptr), myFrameUvVariable(nullptr)
{
}

EffectAnimation::~EffectAnimation()
{
}


bool EffectAnimation::Init(const string& anEffectFile)
{
	Effect::Init(anEffectFile);

	myFrameSizeVariable = myEffect->GetVariableByName("FrameSize")->AsVector();
	if (myFrameSizeVariable->IsValid() == false)
	{
		DEBUG_ASSERT(false, "Failed to find variable 'FrameSize' in shader");
		return false;
	}

	myFrameUvVariable = myEffect->GetVariableByName("FrameUV")->AsVector();
	if (myFrameSizeVariable->IsValid() == false)
	{
		DEBUG_ASSERT(false, "Failed to find variable 'FrameUV' in shader");
		return false;
	}

	myFlipXVariable = myEffect->GetVariableByName("FlipX")->AsScalar();
	if (myFlipXVariable->IsValid() == false)
	{
		DEBUG_ASSERT(false, "Failed to find variable 'FlipX' in shader");
		return false;
	}

	myFlipYVariable = myEffect->GetVariableByName("FlipY")->AsScalar();
	if (myFlipYVariable->IsValid() == false)
	{
		DEBUG_ASSERT(false, "Failed to find variable 'FlipY' in shader");
		return false;
	}

	return true;
}

void EffectAnimation::Update()
{
	Effect::Update();

	myFrameSizeVariable->SetFloatVector(EffectData::animationFrameSize.array);
	myFrameUvVariable->SetFloatVector(EffectData::animationUV.array);

	myFlipXVariable->SetBool(EffectData::flipX);
	myFlipYVariable->SetBool(EffectData::flipY);
}