#include "stdafx.h"
#include "CrushAbility.h"


CrushAbility::CrushAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction): AbilityBase(aSuffix,aNumber,aSpecificFaction)
{
	iconTexturePath = "Data/Textures/Icons/Skills/crushIcon.png";
	myAbilityType = eAbilityTypes::eCrush;
}


CrushAbility::~CrushAbility()
{
}

void CrushAbility::OnKill(Card * aCard, Card* aKilledCard)
{
	if (aKilledCard->GetCardType() != eCardType::Structure)
	{
		Card* target = aCard->GetOwner()->GetOpponent()->GetCommander();
		CommonUtilities::VectorOnStack<AbilityBase*, 3> abilities;
		for (int i = 0; i < aCard->GetOwner()->GetOpponent()->GetStructureCards().Size(); i++)
		{
			abilities = aCard->GetOwner()->GetOpponent()->GetStructureCards()[i]->GetAbilities();
			for (int j = 0; j < abilities.Size(); j++)
			{
				abilities[j]->OnCommanderAttack(target, aCard->GetOwner()->GetOpponent()->GetStructureCards()[i]);
			}

			if (target != aCard->GetOwner()->GetOpponent()->GetCommander())
			{
				break;
			}
		}
		target->TakeDamage(myNumber);
	}


}
