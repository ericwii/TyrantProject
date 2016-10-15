#pragma once
#include "EffectTypes.h"
#include <unordered_map>

class Effect;
class Effect2D;

class EffectContainer
{
public:
	EffectContainer();
	~EffectContainer();

	Effect* GetEffect(const eEffectType3D anEffectType);
	Effect2D* GetEffect(const eEffectType2D anEffectType);

private:
	std::unordered_map<eEffectType3D, Effect*> my3DEffects;
	std::unordered_map<eEffectType2D, Effect2D*> my2DEffects;

	Effect* GetEffectFromType(const eEffectType3D anEffectType);
	Effect2D* GetEffectFromType(const eEffectType2D anEffectType);
};
