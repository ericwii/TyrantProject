#include "stdafx.h"
#include "StunAbility.h"


Vector2<float> stunAnimationSize(1.5f, 2.f);
AnimationData stunAnimation = AnimationData
(
	"Data/Textures/Animations/stunAnimation.png",
	8,
	2,
	20.f,
	false
	);


StunAbility::StunAbility()
{
	myAbilityType = eAbilityTypes::eStun;
	iconTexturePath = "Data/Textures/Icons/Skills/stunIcon.png";
}


StunAbility::~StunAbility()
{
}

void StunAbility::OnAttacked(Card * aUser, char & someDamage, Card * anAttacker)
{
	aUser;
	someDamage;
	AnimationManager::AddAnimation(stunAnimation, anAttacker->GetPosition(), stunAnimationSize);
	anAttacker->AddStatusEffect(eStatusEffectType::Stun);
}
