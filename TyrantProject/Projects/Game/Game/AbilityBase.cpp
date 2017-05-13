#include "stdafx.h"
#include "AbilityBase.h"


AbilityBase::AbilityBase() : myNumber(0)
{
}

AbilityBase::AbilityBase(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction) : mySuffix(aSuffix), myNumber(aNumber), mySpecificFaction(aSpecificFaction)
{
}

AbilityBase::~AbilityBase()
{
}




void AbilityBase::OnPlay(Card* aCard) { aCard; }
void AbilityBase::OnDeath(Card* aCard) { aCard; }
void AbilityBase::OnDamaged(Card* aCard) { aCard; }
void AbilityBase::OnKill(Card* aCard) { aCard; }
void AbilityBase::OnPreCombat(Card* aCard) { aCard; }
void AbilityBase::OnTargeted(Card* aTarget) { aTarget; }
void AbilityBase::OnAttacked(char& someDamage){ someDamage; }
void AbilityBase::DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets)
{
	aCaster;
	someTargets;
}


//Protected Methods

Card* AbilityBase::FindTarget(CU::GrowingArray<Card*>& cards)
{
	if (cards.Size() > 0)
	{
		int randomIndex = rand() % cards.Size();
		for (int searchCount = 0; searchCount < cards.Size(); ++searchCount)
		{
			if (!cards[randomIndex]->IsDying() && (mySpecificFaction != eCardFaction::Action || cards[randomIndex]->GetFaction() == mySpecificFaction))
			{
				return cards[randomIndex];
			}

			++randomIndex;
			randomIndex %= cards.Size();
		}
	}
	return nullptr;
}
