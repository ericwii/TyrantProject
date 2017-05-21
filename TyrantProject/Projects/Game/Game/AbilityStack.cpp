#include "stdafx.h"
#include "AbilityStack.h"
#include "AbilityBase.h"
#include "CardGameCameraManager.h"

CU::GrowingArray<StoredAbility> AbilityStack::myAbilities = CU::GrowingArray<StoredAbility>(4);
float myDelayTimer = 0;
int myCurrentAbilityIndex = -1;
bool myHasPlayedAnimations = false;
bool myShowAbilityFrame = false;

string abilityFrameTexturePath = "Data/Textures/Icons/abilityFrame.png";
Card* myAbilityFrameUser;
Instance myAbilityFrameInstance;



void AbilityStack::Init()
{
	Model* abilityFrameModel = ModelLoader::LoadRectangle(Vector2<float>(1.6f, 2.1f), eEffectType::Textured, abilityFrameTexturePath);
	myAbilityFrameInstance.Init(abilityFrameModel);
}

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

					if (target != nullptr && !target->IsDying())
					{
						AnimationManager::AddAnimation(*currentAbility.animationData, target->GetPosition(), currentAbility.animationSize,currentAbility.animationRotation,currentAbility.animationFlipX,currentAbility.animationFlipY);
					}
					else
					{
						currentAbility.targets.RemoveCyclicAtIndex(i);
						--i;
					}
				}
			}

			myAbilityFrameUser = currentAbility.caster;
			myAbilityFrameInstance.SetPosition(myAbilityFrameUser->GetPosition());
			myShowAbilityFrame = true;
			myHasPlayedAnimations = true;
			CardGameCameraManager::SetLerpTarget(myAbilityFrameUser->GetPosition());
		}
	}
	else if(myShowAbilityFrame && AnimationManager::IsEmpty())
	{
		myShowAbilityFrame = false;
	}
}

void AbilityStack::Render()
{
	if (myShowAbilityFrame && !myAbilityFrameUser->IsDying())
	{
		myAbilityFrameInstance.Render();
	}
}

void AbilityStack::AddAbility(StoredAbility aStoredAbility)
{
	myAbilities.Add(aStoredAbility);

	if (myCurrentAbilityIndex == -1)
	{
		myCurrentAbilityIndex = 0;
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