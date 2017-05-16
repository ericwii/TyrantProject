#include "stdafx.h"
#include "LegionAbility.h"


LegionAbility::LegionAbility(const string & aSuffix, char aNumber, eCardFaction aSpecificFaction): AbilityBase(aSuffix,aNumber,aSpecificFaction)
{
	myAbilityType = eAbilityTypes::eLegion;
	iconTexturePath = "Data/Textures/Icons/Skills/legionIcon.png";
}

LegionAbility::~LegionAbility()
{
}

void LegionAbility::OnPreCombat(Card * aCard)
{

	for (int i = 0; i < aCard->GetOwner()->GetAssaultCards().Size(); i++)
	{
		if (aCard->GetOwner()->GetAssaultCards()[i] == aCard)
		{

			if (i-1 >= 0)
			{
				if (aCard->GetOwner()->GetAssaultCards()[i - 1]->GetFaction() == aCard->GetFaction())
				{
					aCard->Heal(myNumber);
					aCard->Rally(myNumber);
				}
			}

			if (i+1 <= aCard->GetOwner()->GetAssaultCards().Size()-1)
			{
				if (aCard->GetOwner()->GetAssaultCards()[i + 1]->GetFaction() == aCard->GetFaction())
				{
					aCard->Heal(myNumber);
					aCard->Rally(myNumber);
				}
			}
		}
	}

}
