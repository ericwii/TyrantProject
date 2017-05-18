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
	virtual void OnKill(Card* aCard, Card* aKilledCard);
	virtual void OnPreCombat(Card* aCard);
	virtual void OnBeforeAttack(Card* aCard, Card*& currentTarget, char& someDamage);
	virtual void OnCleanUp(Card* aCard);
	virtual void OnTargeted(Card* aTarget);
	virtual void OnAttacked(Card* aUser ,char& someDamage, Card* anAttacker);
	virtual void OnCommanderAttack(Card*& aCurrentTarget, Card* aUser);
	virtual void OnDamageDealt(Card* aCard, Card* aDamagedCard, char someDamage);
	virtual void DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets);


	const eAbilityTypes GetAbilityType();
	const char GetNumber();

	string iconTexturePath;
protected:

	enum eFindTargetCondition
	{
		None = 0,
		IsDamaged = 2,
		HasAttack = 4,
		IsOffCooldown = 8,
		IsOffCooldownNextTurn = 16
	};

	eAbilityTypes myAbilityType;
	CU::GrowingArray<Card*> myTargets;
	string mySuffix;
	eCardFaction mySpecificFaction;
	char myNumber;

	Card* FindTarget(CU::GrowingArray<Card*>& cards, int conditions = 0);
	CU::GrowingArray<Card*>& FindAllTargets(CU::GrowingArray<Card*>& cards, int conditions = 0);
	CU::GrowingArray<Card*>& FindAdjecentTargets(Card* aSearcher, CU::GrowingArray<Card*>& cards, int conditions = 0);
	
private:

	bool CheckConditions(Card* aCard, int conditions);
};