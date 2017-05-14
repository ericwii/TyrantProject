#pragma once
#include "Card.h"
#include "Player.h"
#include "AbilityTypes.h"

class AbilityBase
{
public:
	AbilityBase();
	AbilityBase(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction);
	~AbilityBase();


	virtual void OnPlay(Card* aCard);
	virtual void OnDeath(Card* aCard);
	virtual void OnCombatDamaged(char someDamage, Card* aCard, Card* anAttacker);
	virtual void OnKill(Card* aCard);
	virtual void OnPreCombat(Card* aCard);
	virtual void OnCleanUp(Card* aCard);
	virtual void OnTargeted(Card* aTarget);
	virtual void OnAttacked(char& someDamage, Card* anAttacker);
	virtual void OnCommanderAttack(Card*& aCurrentTarget, Card* aUser);
	virtual void DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets);


	const eAbilityTypes GetAbilityType();
	const char GetNumber();

	string iconTexturePath;
protected:

	eAbilityTypes myAbilityType;
	CU::GrowingArray<Card*> myTargets;
	string mySuffix;
	eCardFaction mySpecificFaction;
	char myNumber;

	Card* FindTarget(CU::GrowingArray<Card*>& cards);
	Card* FindTargetOffCoolDown(CU::GrowingArray<Card*>& cards);
	CU::GrowingArray<Card*>& FindAllTargets(CU::GrowingArray<Card*>& cards);
	CU::GrowingArray<Card*>& FindAllTargetsOffCoolDown(CU::GrowingArray<Card*>& cards);
	
};