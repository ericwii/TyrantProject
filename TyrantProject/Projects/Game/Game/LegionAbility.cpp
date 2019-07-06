#include "stdafx.h"
#include "LegionAbility.h"


Vector2<float> legionAnimationSize(0.3f, 0.5f);
AnimationData legionAnimation = AnimationData
(
	"Data/Textures/Animations/refreshGreenAnimation.png",
	5,
	1,
	20.f,
	false
	);


LegionAbility::LegionAbility(const string & aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData): AbilityBase(aSuffix,aNumber,aSpecificFaction, aCardData)
{
	myAbilityType = eAbilityTypes::eLegion;
	iconTexturePath = "Data/Textures/Icons/Skills/legionIcon.png";
	myCardText.Insert("Legion", 0);
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
					//AnimationManager::AddAnimation(legionAnimation,aCard->GetPosition(),legionAnimationSize);
				}
			}
		}
	}

}
