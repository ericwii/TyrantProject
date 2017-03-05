#include "stdafx.h"
#include "AbilityStack.h"
#include "AbilityBase.h"

CU::GrowingArray<AbilityStack::StoredAbility> AbilityStack::myAbilities = CU::GrowingArray<AbilityStack::StoredAbility>(4);
float AbilityStack::myDelayTimer = 0;
int AbilityStack::myCurrentAbilityIndex = -1;




void AbilityStack::Update(float aDeltaTime)
{
	if (myCurrentAbilityIndex != -1)
	{
		myDelayTimer += aDeltaTime;
		if (myDelayTimer >= myAbilities[myCurrentAbilityIndex].delay)
		{
			myDelayTimer = 0;

			StoredAbility& currentAbility = myAbilities[myCurrentAbilityIndex];
			currentAbility.ability->DoAction(currentAbility.caster, currentAbility.targets);

			myAbilities.RemoveNonCyclicAtIndex(myCurrentAbilityIndex);
			myCurrentAbilityIndex = myAbilities.Size() - 1;
		}
	}
}

void AbilityStack::AddAbility(AbilityBase* anAbility, Card* aCaster, CU::GrowingArray<Card*> someTargets, float aDelay)
{
	StoredAbility newAbility;
	newAbility.ability = anAbility;
	newAbility.caster = aCaster;
	newAbility.delay = aDelay;
	newAbility.targets = someTargets;

	myAbilities.Add(newAbility);

	if (myCurrentAbilityIndex == -1)
	{
		myCurrentAbilityIndex = 0;
	}
}

void AbilityStack::AddAbility(AbilityBase* anAbility, Card* aCaster, Card* aTarget, float aDelay)
{
	StoredAbility newAbility;
	newAbility.ability = anAbility;
	newAbility.caster = aCaster;
	newAbility.delay = aDelay;
	newAbility.targets.Allocate(1);
	newAbility.targets.Add(aTarget);

	myAbilities.Add(newAbility);

	if (myCurrentAbilityIndex == -1)
	{
		myCurrentAbilityIndex = 0;
	}
}

bool AbilityStack::IsEmpty()
{
	return myAbilities.Size() < 1;
}