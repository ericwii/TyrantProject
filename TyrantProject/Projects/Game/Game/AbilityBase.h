#pragma once
#include "Card.h"
#include "Player.h"

class AbilityBase
{
public:
	AbilityBase();
	AbilityBase(const string& aSuffix, char aNumber);
	~AbilityBase();


	virtual void OnPlay(Card* aCard);
	virtual void OnDeath(Card* aCard);
	virtual void OnDamaged(Card* aCard);
	virtual void OnKill(Card* aCard);
	virtual void OnPreCombat(Card* aCard);
	virtual void OnTargeted(Card* aTarget);
	virtual void OnAttacked(char& someDamage);
	virtual void DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets);

	string iconTexturePath;
protected:
	string mySuffix;
	char myNumber;
};