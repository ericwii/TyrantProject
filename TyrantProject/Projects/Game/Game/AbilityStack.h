#pragma once

class Card;

class AbilityStack
{
public:

	static void Init();
	static void Update(float aDeltaTime);
	static void Render();
	static void AddAbility(AbilityBase* anAbility, Card* aCaster, CU::GrowingArray<Card*> someTargets, AnimationData* someAnimationData, Vector2<float>& anAnimationSize, float aDelayFromAnimation = 0);
	static void AddAbility(AbilityBase* anAbility, Card* aCaster, Card* aTarget, AnimationData* someAnimationData, Vector2<float>& anAnimationSize, float aDelayFromAnimation = 0);

	static bool IsEmpty();


private:
	struct StoredAbility
	{
		CU::GrowingArray<Card*> targets;
		Vector2<float> animationSize;
		AnimationData* animationData;
		AbilityBase* ability;
		Card* caster;
		float delayFromAnimation;
	};

	static CU::GrowingArray<StoredAbility> myAbilities;
};

