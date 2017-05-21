#pragma once


class CardGameCameraManager
{
public:
	static void Update(float aDeltaTime);
	static void SetLerpTarget(Vector3<float>& aTarget, float aWaitAfterFinish = 0, float aSpeed = 0);

	static bool IsMoving();

private:
	CardGameCameraManager();
	~CardGameCameraManager();
};

