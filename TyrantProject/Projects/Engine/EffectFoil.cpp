#include "stdafx.h"
#include "EffectFoil.h"


EffectFoil::EffectFoil() : Effect()
{
}

EffectFoil::~EffectFoil()
{
}


bool EffectFoil::Init(const string& aEffectFile)
{
	return Effect::Init(aEffectFile);
}

void EffectFoil::Update()
{
	Effect::Update();
}