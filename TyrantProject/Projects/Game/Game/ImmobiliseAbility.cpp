#include "stdafx.h"
#include "ImmobiliseAbility.h"

Vector2<float> immobilizeAnimationSize(2.f, 2.f);
AnimationData immobilizeAnimation = AnimationData
(
	"Data/Textures/Animations/ImmobilizeAnimation.png",
	8,
	2,
	20.f,
	false
	);



ImmobiliseAbility::ImmobiliseAbility()
{
	myAbilityType = eAbilityTypes::eImmobilise;
	iconTexturePath = "Data/Textures/Icons/Skills/immobilizeIcon.png";
}


ImmobiliseAbility::~ImmobiliseAbility()
{
}

void ImmobiliseAbility::OnDamageDealt(Card * aCard, Card * aDamagedCard, char someDamage)
{
	aCard;
	someDamage;

	if ((rand() % 2) == 1)
	{
		aDamagedCard->AddStatusEffect(eStatusEffectType::Immobilize);
		AnimationManager::AddAnimation(immobilizeAnimation, aDamagedCard->GetPosition(), immobilizeAnimationSize);
	}
}
