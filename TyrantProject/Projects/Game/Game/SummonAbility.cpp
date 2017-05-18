#include "stdafx.h"
#include "SummonAbility.h"


SummonAbility::SummonAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction) : AbilityBase(aSuffix, aNumber, aSpecificFaction)
{
	iconTexturePath = "Data/Textures/Icons/Skills/summonIcon.png";
	myAbilityType = eAbilityTypes::eSummon;

	myCardToSummon = mySuffix;
	for (int i = 0; i < aSuffix.Lenght(); ++i)
	{
		if (aSuffix[i] == ' ')
		{
			myCardToSummon = aSuffix.SubStr(0, i);
			break;

			//if (i + 1 < aSuffix.Lenght())
			//{
			//	mySuffix.SetAsSubStr(i + 1);
			//}
			//else
			//{
			//	mySuffix = "";
			//}
		}
	}
	if (myCardToSummon.Lenght() < mySuffix.Lenght())
	{
		mySuffix.SetAsSubStr(myCardToSummon.Lenght());
	}
	else
	{
		mySuffix = "";
	}
}

SummonAbility::~SummonAbility()
{
}


void SummonAbility::OnPreCombat(Card* aCard)
{
	aCard;
}

void SummonAbility::OnPlay(Card * aCard)
{
	if (mySuffix == " onplay")
	{
		aCard->GetOwner()->SummonCard(myCardToSummon);
	}
}

void SummonAbility::OnBeforeAttack(Card * aCard, Card *& currentTarget, char & someDamage)
{
	currentTarget;
	someDamage;

	if (aCard->GetCooldown() < 1 && mySuffix.Lenght() == 0)
	{
		aCard->GetOwner()->SummonCard(myCardToSummon);
	}
}
