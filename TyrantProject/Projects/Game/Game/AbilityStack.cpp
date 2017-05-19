#include "stdafx.h"
#include "AbilityStack.h"
#include "AbilityBase.h"

CU::GrowingArray<AbilityStack::StoredAbility> AbilityStack::myAbilities = CU::GrowingArray<AbilityStack::StoredAbility>(4);
float AbilityStack::myDelayTimer = 0;
int AbilityStack::myCurrentAbilityIndex = -1;
bool AbilityStack::myHasPlayedAnimations = false;




void AbilityStack::Update(float aDeltaTime)
{
	if (myCurrentAbilityIndex != -1)
	{
		if (myHasPlayedAnimations)
		{
			myDelayTimer += aDeltaTime;
			if (myDelayTimer >= myAbilities[myCurrentAbilityIndex].delayFromAnimation)
			{
				myDelayTimer = 0;

				StoredAbility& currentAbility = myAbilities[myCurrentAbilityIndex];
				currentAbility.ability->DoAction(currentAbility.caster, currentAbility.targets);

				myAbilities.RemoveNonCyclicAtIndex(myCurrentAbilityIndex);
				myCurrentAbilityIndex = myAbilities.Size() - 1;
				myHasPlayedAnimations = false;
			}
		}
		else if (AnimationManager::IsEmpty())
		{
			StoredAbility& currentAbility = myAbilities[myCurrentAbilityIndex];

			if (currentAbility.animationData != nullptr)
			{
				for (int i = 0; i < currentAbility.targets.Size(); ++i)
				{
					Card* target = currentAbility.targets[i]->OnTargeted(currentAbility.ability);

					if (target != nullptr)
					{
						AnimationManager::AddAnimation(*currentAbility.animationData, target->GetPosition(), currentAbility.animationSize);
					}
					else
					{
						currentAbility.targets.RemoveCyclicAtIndex(i);
						--i;
					}
				}
			}
			myHasPlayedAnimations = true;
		}
	}
}

void AbilityStack::AddAbility(AbilityBase* anAbility, Card* aCaster, CU::GrowingArray<Card*> someTargets, AnimationData* someAnimationData, Vector2<float>& anAnimationSize, float aDelayFromAnimation)
{
	StoredAbility newAbility;
	newAbility.ability = anAbility;
	newAbility.caster = aCaster;
	newAbility.animationData = someAnimationData;
	newAbility.animationSize = anAnimationSize;
	newAbility.delayFromAnimation = aDelayFromAnimation;
	newAbility.targets = someTargets;

	myAbilities.Add(newAbility);

	if (myCurrentAbilityIndex == -1)
	{
		myCurrentAbilityIndex = 0;
	}
}

void AbilityStack::AddAbility(AbilityBase* anAbility, Card* aCaster, Card* aTarget, AnimationData* someAnimationData, Vector2<float>& anAnimationSize, float aDelayFromAnimation)
{
	StoredAbility newAbility;
	newAbility.ability = anAbility;
	newAbility.caster = aCaster;
	newAbility.animationData = someAnimationData;
	newAbility.animationSize = anAnimationSize;
	newAbility.delayFromAnimation = aDelayFromAnimation;
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