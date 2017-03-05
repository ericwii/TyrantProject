#include "stdafx.h"
#include "AbilityBase.h"


AbilityBase::AbilityBase() : myNumber(0)
{
}

AbilityBase::AbilityBase(const string& aSuffix, char aNumber) : mySuffix(aSuffix), myNumber(aNumber)
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