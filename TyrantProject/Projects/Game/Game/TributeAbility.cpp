#include "stdafx.h"
#include "TributeAbility.h"


TributeAbility::TributeAbility()
{
	myAbilityType = eAbilityTypes::eTribute;
	iconTexturePath = "Data/Textures/Icons/Skills/tributeIcon.png";
	myCardText = "Tribute";
}


TributeAbility::~TributeAbility()
{
}

void TributeAbility::OnTargeted(Card* aCaster, Card* aTarget, AbilityBase* aTargetingAbility)
{
	//need to check if it is buff so tribute casts chaosed strike back at the user

	if (aCaster->GetOwner() != aTarget->GetOwner() || aCaster->GetCardType() != eCardType::Assault)
	{
		return;
	}

	if ((rand() % 2) == 1)
	{
		if (aTargetingAbility->GetAbilityType() == eAbilityTypes::eProtect)
		{
			aCaster->AddStatusEffect(eStatusEffectType::Protect, aTargetingAbility->iconTexturePath, aTargetingAbility->GetNumber());
		}
		else if (aTargetingAbility->GetAbilityType() == eAbilityTypes::eAgument)
		{
			aCaster->AddStatusEffect(eStatusEffectType::Augment, aTargetingAbility->iconTexturePath, aTargetingAbility->GetNumber());
		}
		else if (aTargetingAbility->GetAbilityType() == eAbilityTypes::eHeal)
		{
			aCaster->Heal(aTargetingAbility->GetNumber());
		}
		else if (aTargetingAbility->GetAbilityType() == eAbilityTypes::eSupply)
		{
			aCaster->Heal(aTargetingAbility->GetNumber());
		}
		else if (aTargetingAbility->GetAbilityType() == eAbilityTypes::eRally)
		{
			aCaster->Rally(aTargetingAbility->GetNumber());
		}
		else if (aTargetingAbility->GetAbilityType() == eAbilityTypes::eCleanse)
		{
			aCaster->Cleanse();
		}
	}
}
