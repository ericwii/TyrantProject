#pragma once

class Card;

class AbilityStack
{
public:
	static void Update(float aDeltaTime);
	static void AddAbility(AbilityBase* anAbility, Card* aCaster, CU::GrowingArray<Card*> someTargets, float aDelay = 0);
	static void AddAbility(AbilityBase* anAbility, Card* aCaster, Card* aTarget, float aDelay = 0);

	static bool IsEmpty();

private:
	struct StoredAbility
	{
		AbilityBase* ability;
		Card* caster;
		CU::GrowingArray<Card*> targets;
		float delay;
	};

	static CU::GrowingArray<StoredAbility> myAbilities;
	static int myCurrentAbilityIndex;
	static float myDelayTimer;
};

