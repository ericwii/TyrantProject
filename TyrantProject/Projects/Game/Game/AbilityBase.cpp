#include "stdafx.h"
#include "AbilityBase.h"


AbilityBase::AbilityBase(CardData& aCardData) : myCardText("Not Implemented"), myNumber(0)
{
}

AbilityBase::AbilityBase(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData) : myCardText("Not Implemented"), mySuffix(aSuffix), myNumber(aNumber), mySpecificFaction(aSpecificFaction), myCardsData(&aCardData)
{
	if (mySuffix.Lenght() > 0 && mySuffix.Find("all") > -1)
	{
		myTargets.Allocate(8);
	}

	myCardText = " ";
	if (mySuffix.Lenght() > 0)
	{
		SetCardText();
	}
	else if(myNumber > 0)
	{
		myCardText += myNumber;
	}
}

AbilityBase::~AbilityBase()
{
}




void AbilityBase::OnPlay(Card* aCard) { aCard; }
void AbilityBase::OnDeath(Card* aCard) { aCard; }
void AbilityBase::OnAttack(Card* defendingCard, char& someDamage) { defendingCard; someDamage; }
void AbilityBase::OnCombatDamaged(char someDamage, Card* aCard, Card* anAttacker) { someDamage; aCard; anAttacker; }
void AbilityBase::OnKill(Card* aCard, Card* aKilledCard) { aCard; aKilledCard; }
void AbilityBase::OnPreCombat(Card* aCard) { aCard; }
void AbilityBase::OnPriority(Card* aCard) { aCard; }
void AbilityBase::OnCalculateAttack(AttackData& data) { data; }
void AbilityBase::OnCleanUp(Card * aCard) { aCard; }
void AbilityBase::OnTargeted(Card* aTarget, AbilityBase* aTargetingAbility) { aTarget; aTargetingAbility; }
void AbilityBase::OnAttacked(Card* aUser, char& someDamage, Card* anAttacker) { someDamage; anAttacker; aUser; }
void AbilityBase::OnCommanderAttack(Card*& aCurrentTarget, Card* aUser) { aCurrentTarget; aUser; }
void AbilityBase::OnDamageDealt(Card * aCard, Card * aDamagedCard, char someDamage) { aCard; aDamagedCard; someDamage; }
void AbilityBase::DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets) { aCaster; someTargets; }

const string& AbilityBase::GetCardText()
{
	return myCardText;
}

const eAbilityTypes AbilityBase::GetAbilityType()
{
	return myAbilityType;
}

const char AbilityBase::GetNumber()
{
	return myNumber;
}


//Protected Methods

Card* AbilityBase::FindTarget(CU::GrowingArray<Card*>& cards, int conditions)
{
	if (cards.Size() > 0)
	{
		int randomIndex = rand() % cards.Size();
		for (int searchCount = 0; searchCount < cards.Size(); ++searchCount)
		{
			if (!cards[randomIndex]->IsDying() && 
				(mySpecificFaction == eCardFaction::Action || cards[randomIndex]->GetFaction() == mySpecificFaction) &&
				CheckConditions(cards[randomIndex], conditions))
			{
				return cards[randomIndex];
			}

			++randomIndex;
			randomIndex %= cards.Size();
		}
	}
	return nullptr;
}

CU::GrowingArray<Card*>& AbilityBase::FindAllTargets(CU::GrowingArray<Card*>& cards, int conditions)
{
	myTargets.RemoveAll();
	Card* currentTarget;

	if (mySpecificFaction == eCardFaction::Action)
	{
		for (int i = cards.Size() - 1; i >= 0; --i)
		{
			currentTarget = cards[i];

			if (currentTarget != nullptr && !currentTarget->IsDying() && CheckConditions(currentTarget, conditions))
			{
				myTargets.Add(currentTarget);
			}
		}
	}
	else
	{
		for (int i = cards.Size() - 1; i >= 0; --i)
		{
			currentTarget = cards[i];

			if (currentTarget != nullptr && !currentTarget->IsDying() && currentTarget->GetFaction() == mySpecificFaction && CheckConditions(currentTarget, conditions))
			{
				myTargets.Add(currentTarget);
			}
		}
	}

	return myTargets;
}

CU::GrowingArray<Card*>& AbilityBase::FindAdjecentTargets(Card * originalTarget)
{
	myTargets.RemoveAll();
	CU::GrowingArray<Card*>& cardsToSearch = originalTarget->GetOwner()->GetAssaultCards();

	for (int i = 0; i < cardsToSearch.Size(); ++i)
	{
		if (cardsToSearch[i] == originalTarget)
		{
			if (i > 0 && cardsToSearch[i - 1]->IsDying() == false)
			{
				myTargets.Add(cardsToSearch[i - 1]);
			}

			if (i + 1 < cardsToSearch.Size() && cardsToSearch[i + 1]->IsDying() == false)
			{
				myTargets.Add(cardsToSearch[i + 1]);
			}

			break;
		}
	}

	return myTargets;
}


//Private Methods

void AbilityBase::SetCardText()
{
	bool hasAllSuffix = false;
	bool hasOnPlaySuffix = false;

	if (mySuffix.Find("all") != -1)
	{
		hasAllSuffix = true;
		myCardText += "All ";
	}

	if (mySuffix.Find("onplay") != -1)
	{
		hasOnPlaySuffix = true;
	}

	if (mySpecificFaction != eCardFaction::Action)
	{
		switch (mySpecificFaction)
		{
			case BloodThirsty:
			{
				myCardText += "BloodThirsty ";
				break;
			}
			case Imperial:
			{
				myCardText += "Imperial ";
				break;
			}
			case Raider:
			{
				myCardText += "Raider ";
				break;
			}
			case Righteous:
			{
				myCardText += "Righteous ";
				break;
			}
			case Xeno:
			{
				myCardText += "Xeno ";
				break;
			}
			default:
			{
				break;
			}
		}
	}

	if (myNumber > 0)
	{
		myCardText += myNumber;
		myCardText += " ";
	}

	if (hasAllSuffix)
	{
		if (mySuffix.Lenght() > 3)
		{
			myCardText += mySuffix.SubStr(3);
		}
	}
	else
	{
		myCardText += mySuffix;
	}

	//removes the "onplay" part of the card text for action cards 
	if (myCardsData->cardType == eCardType::Action)
	{
		const char onPlayLenght = 6;
		myCardText = myCardText.SubStr(0, myCardText.Lenght() - onPlayLenght);
	}
}

bool AbilityBase::CheckConditions(Card* aCard, int conditions)
{
	if (conditions == 0) return true;

	bool meetsConditions = true;

	if (conditions >= eFindTargetCondition::IsOffCooldown)
	{
		if (conditions & eFindTargetCondition::IsOffCooldown)
		{
			meetsConditions &= aCard->GetCooldown() < 1;
		}
		else if (conditions & eFindTargetCondition::IsOffCooldownNextTurn)
		{
			meetsConditions &= aCard->GetCooldown() < 2;
		}
	}

	if (conditions & eFindTargetCondition::CanBeCleansed)
	{
		meetsConditions &= (aCard->HasNegativeStatusEffect() && aCard->GetStatusEffectNumber(eStatusEffectType::Phase) < 1);
	}
	if (conditions & eFindTargetCondition::HasAttack)
	{
		meetsConditions &= aCard->GetAttack() > 0;
	}
	if (conditions & eFindTargetCondition::IsDamaged)
	{
		meetsConditions &= !aCard->IsAtMaxHealth();
	}

	if (conditions & eFindTargetCondition::CanBeTargetedByFriendly)
	{
		meetsConditions &= aCard->GetStatusEffectNumber(eStatusEffectType::Phase) < 1;
	}

	return meetsConditions;
}