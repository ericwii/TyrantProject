#include "stdafx.h"
#include "SummonAbility.h"
#include "CardGameCameraManager.h"

float cameraWaitDelay = 0.5f;
float cameraSpeed = 10.f;


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



void SummonAbility::DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets)
{
	someTargets;
	Card* summonedCard = aCaster->GetOwner()->SummonCard(myCardToSummon);
	if (summonedCard != nullptr)
	{
		CardGameCameraManager::SetLerpTarget(summonedCard->GetPosition(), cameraWaitDelay, cameraSpeed);
	}
}

void SummonAbility::OnPreCombat(Card* aCard)
{
	if ((aCard->GetCardType() == eCardType::Commander || aCard->GetCardType() == eCardType::Structure) && aCard->GetCooldown() < 1)
	{
		AbilityStack::AddAbility(this, aCard, nullptr, nullptr, Vector2<float>());
	}
}

void SummonAbility::OnPlay(Card * aCard)
{
	if (mySuffix == " onplay")
	{
		AbilityStack::AddAbility(this, aCard, nullptr, nullptr, Vector2<float>());
	}
}

void SummonAbility::OnCalculateAttack(AttackData& data)
{
	if (data.attacker->GetCooldown() < 1 && mySuffix.Lenght() == 0)
	{
		AbilityStack::AddAbility(this, data.attacker, nullptr, nullptr, Vector2<float>());
	}
}

void SummonAbility::OnAttacked(Card * aUser, char & someDamage, Card * anAttacker)
{
	someDamage;
	anAttacker;

	if (mySuffix == " onattacked")
	{
		AbilityStack::AddAbility(this, aUser, nullptr, nullptr, Vector2<float>());
	}
}
