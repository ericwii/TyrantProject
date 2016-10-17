#pragma once
#include "EffectTypes.h"
#include "Effect.h"
#include <unordered_map>


class EffectContainer
{
public:
	EffectContainer();
	~EffectContainer();

	Effect* GetEffect(const eEffectType anEffectType);

private:
	std::unordered_map<eEffectType, Effect*> myEffects;

	Effect* GetEffectFromType(const eEffectType anEffectType);
};
