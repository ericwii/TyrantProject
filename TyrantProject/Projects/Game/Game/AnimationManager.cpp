#include "stdafx.h"
#include "AnimationManager.h"

CU::GrowingArray<Animation> AnimationManager::myAnimations = CU::GrowingArray<Animation>(16);


bool AnimationManager::IsEmpty()
{
	return myAnimations.Size() < 1;
}

void AnimationManager::Update(float aDeltaTime)
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

void AnimationManager::Render()
{
	for (int i = 0; i < myAnimations.Size(); ++i)
	{
		myAnimations[i].Render();
	}
}

void AnimationManager::AddAnimation(const Animation& anAnimation)
{
	myAnimations.Add(anAnimation);
}

void AnimationManager::AddAnimation(const AnimationData& someData, const Vector3<float>& aPosition, const Vector2<float>& aSize, float aRotation, bool aflipX, bool aflipY)
{
	Animation newAnimation;
	newAnimation.Init(someData, aPosition, aSize);
	myAnimations.Add(newAnimation);

	myAnimations.GetLast().SetRotation(aRotation);
	myAnimations.GetLast().SetFlip(aflipX,aflipY);
	myAnimations.GetLast().Play();
}