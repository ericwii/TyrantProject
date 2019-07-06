#pragma once
#include "Card.h"
#include "Player.h"
#include "AbilityTypes.h"

struct AttackData
{
	AttackData() : attackAnimation(nullptr)
	{
	}

	AnimationData* attackAnimation;
	Card* extraTargets[2];
	Card* mainTarget;
	Card* attacker;
	char amountOfAttacks;
};


class AbilityBase
{
public:
	AbilityBase(CardData& aCardData);
	AbilityBase(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData);
	~AbilityBase();


	virtual void DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets);
	virtual void OnPlay(Card* aCard);
	virtual void OnDeath(Card* aCard);
	virtual void OnTargeted(Card* aTarget, AbilityBase* aTargetingAbility);
	virtual void OnKill(Card* aCard, Card* aKilledCard);
	virtual void OnPriority(Card* aCard);
	virtual void OnPreCombat(Card* aCard);
	virtual void OnCleanUp(Card* aCard);


	virtual void OnCalculateAttack(AttackData& data);
	virtual void OnAttack(Card* defendingCard, char& someDamage);
	virtual void OnAttacked(Card* aUser ,char& someDamage, Card* anAttacker);
	virtual void OnCommanderAttack(Card*& aCurrentTarget, Card* aUser);
	virtual void OnCombatDamaged(char someDamage, Card* aCard, Card* anAttacker);
	virtual void OnDamageDealt(Card* aCard, Card* aDamagedCard, char someDamage);


	const string& GetCardText();
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
		IsOffCooldownNextTurn = 16,
		CanBeCleansed = 32,
		CanBeTargetedByFriendly = 64,
	};

	CardData* myCardsData;
	eAbilityTypes myAbilityType;
	CU::GrowingArray<Card*> myTargets;
	string mySuffix;
	string myCardText;
	eCardFaction mySpecificFaction;
	char myNumber;

	Card* FindTarget(CU::GrowingArray<Card*>& cards, int conditions = 0);
	CU::GrowingArray<Card*>& FindAllTargets(CU::GrowingArray<Card*>& cards, int conditions = 0);
	CU::GrowingArray<Card*>& FindAdjecentTargets(Card* originalTarget);
	
private:

	void SetCardText();
	bool CheckConditions(Card* aCard, int conditions);
};