#pragma once
#include "Card.h"
#include "Player.h"

struct OnComingAction
{
	Card* source = nullptr;
	Card* target = nullptr;
	char number = 0;
	bool hostile = false;
};

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
	virtual void OnAttacked(OnComingAction& anAction);
	virtual void OnTargeted(OnComingAction& anAction);

protected:
	string mySuffix;
	char myNumber;
	string myIconTexturePath;
};

