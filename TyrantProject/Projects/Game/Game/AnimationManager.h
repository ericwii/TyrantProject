#pragma once

class AnimationManager
{
public:
	static void Update(float aDeltaTime);
	static void Render();
	static void AddAnimation(const Animation& anAnimation);
	static void AddAnimation(const AnimationData& someData, const Vector3<float>& aPosition, const Vector2<float>& aSize, float aRotation = 0, bool aflipX = false, bool aflipY = false);

	static bool IsEmpty();

private:
	static CU::GrowingArray<Animation> myAnimations;
};