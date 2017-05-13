#pragma once
#include "Card.h"
#include "Player.h"

class AbilityBase
{
public:
	AbilityBase();
	AbilityBase(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction);
	~AbilityBase();


	virtual void OnPlay(Card* aCard);
	virtual void OnDeath(Card* aCard);
	virtual void OnDamaged(Card* aCard);
	virtual void OnKill(Card* aCard);
	virtual void OnPreCombat(Card* aCard);
	virtual void OnCleanUp(Card* aCard);
	virtual void OnTargeted(Card* aTarget);
	virtual void OnAttacked(char& someDamage);
	virtual void DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets);

	string iconTexturePath;
protected:

	CU::GrowingArray<Card*> myTargets;
	string mySuffix;
	eCardFaction mySpecificFaction;
	char myNumber;

	Card* FindTarget(CU::GrowingArray<Card*>& cards);
	CU::GrowingArray<Card*>& FindAllTargets(CU::GrowingArray<Card*>& cards);
};