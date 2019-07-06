#include "stdafx.h"
#include "ImmobilizeAbility.h"

Vector2<float> immobilizeAnimationSize(1.5f, 2.f);
AnimationData immobilizeAnimation = AnimationData
(
	"Data/Textures/Animations/ImmobilizeAnimation.png",
	8,
	2,
	20.f,
	false
	);



ImmobilizeAbility::ImmobilizeAbility(CardData& aCardData) : AbilityBase(aCardData)
{
	myAbilityType = eAbilityTypes::eImmobilise;
	iconTexturePath = "Data/Textures/Icons/Skills/immobilizeIcon.png";
	myCardText = "Immobilize";
}


ImmobilizeAbility::~ImmobilizeAbility()
{
}

void ImmobilizeAbility::OnDamageDealt(Card * aCard, Card * aDamagedCard, char someDamage)
{
	aCard;
	someDamage;

	if (aDamagedCard->GetCardType() != eCardType::Assault)
		return;

	if ((rand() % 2) == 1)
	{
		aDamagedCard->AddStatusEffect(eStatusEffectType::Immobilize);
		AnimationManager::AddAnimation(immobilizeAnimation, aDamagedCard->GetPosition(), immobilizeAnimationSize);
	}
}
