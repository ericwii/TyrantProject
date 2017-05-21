#pragma once

class Card;
	struct StoredAbility
	{
		CU::GrowingArray<Card*> targets;
		Vector2<float> animationSize;
		AnimationData* animationData = nullptr;
		AbilityBase* ability = nullptr;
		Card* caster = nullptr;
		float delayFromAnimation = 0.0f;
		bool animationFlipX = false;
		bool animationFlipY = false;
		float animationRotation = 0.0f;
	};

class AbilityStack
{
public:

	static void Init();
	static void Update(float aDeltaTime);
	static void Render();
	static void AddAbility(StoredAbility aStoredAbility);
	static void AddAbility(AbilityBase* anAbility, Card* aCaster, CU::GrowingArray<Card*> someTargets, AnimationData* someAnimationData, Vector2<float>& anAnimationSize, float aDelayFromAnimation = 0);
	static void AddAbility(AbilityBase* anAbility, Card* aCaster, Card* aTarget, AnimationData* someAnimationData, Vector2<float>& anAnimationSize, float aDelayFromAnimation = 0);

	static bool IsEmpty();


private:

	static CU::GrowingArray<StoredAbility> myAbilities;
};

