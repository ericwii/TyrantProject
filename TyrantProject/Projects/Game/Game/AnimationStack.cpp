#include "stdafx.h"
#include "AnimationStack.h"

CU::GrowingArray<Animation> AnimationStack::myAnimations = CU::GrowingArray<Animation>(16);


bool AnimationStack::IsEmpty()
{
	return myAnimations.Size() < 1;
}

void AnimationStack::Update(float aDeltaTime)
{
	for (int i = 0; i < myAnimations.Size(); ++i)
	{
		myAnimations[i].Update(aDeltaTime);

		if (myAnimations[i].IsPlaying() == false)
		{
			myAnimations.RemoveCyclicAtIndex(i);
			--i;
		}
	}
}

void AnimationStack::Render()
{
	for (int i = 0; i < myAnimations.Size(); ++i)
	{
		myAnimations[i].Render();
	}
}

void AnimationStack::AddAnimation(const Animation& anAnimation)
{
	myAnimations.Add(anAnimation);
}

void AnimationStack::AddAnimation(const AnimationData& someData, const Vector3<float>& aPosition, const Vector2<float>& aSize, float aRotation)
{
	Animation newAnimation;
	newAnimation.Init(someData, aPosition, aSize);
	myAnimations.Add(newAnimation);

	myAnimations.GetLast().SetRotation(aRotation);
	myAnimations.GetLast().Play();
}