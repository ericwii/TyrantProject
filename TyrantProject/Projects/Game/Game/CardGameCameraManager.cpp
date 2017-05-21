#include "stdafx.h"
#include "CardGameCameraManager.h"

Vector3<float> currentPosition;
float defaultSpeed = 5.f;
float currentSpeed;
float currentLerp = 1.f;
float start = 0;
float target = 0;
float currentFinishWaitTime = 0;



void CardGameCameraManager::Update(float aDeltaTime)
{
	if (currentLerp < 1.f)
	{
		currentLerp = MIN(currentLerp + aDeltaTime * currentSpeed, 1.f);
		currentPosition.x = LERP(start, target, currentLerp);
		Engine::GetInstance()->GetCamera().SetPosition(currentPosition);
	}
	else if (currentFinishWaitTime > 0)
	{
		currentFinishWaitTime -= aDeltaTime;
	}
}

void CardGameCameraManager::SetLerpTarget(Vector3<float>& aTarget, float aWaitAfterFinish, float aSpeed)
{
	Vector3<float> cameraPos = Engine::GetInstance()->GetCamera().GetOrientation().GetPosition();

	if ((ABS(aTarget.x - cameraPos.x)) > -cameraPos.z || cameraPos.x > 0 && aTarget.x < -cameraPos.z)
	{
		if (aSpeed > 0)
		{
			currentSpeed = aSpeed;
		}
		else
		{
			currentSpeed = defaultSpeed;
		}
		currentFinishWaitTime = aWaitAfterFinish;
		currentLerp = 0;
		start = cameraPos.x;
		currentPosition.z = cameraPos.z;
		if (aTarget.x < -cameraPos.z)
		{
			target = 0;
		}
		else
		{
			target = aTarget.x + cameraPos.z;
		}
	}
}

bool CardGameCameraManager::IsMoving()
{
	return currentLerp < 1.f || currentFinishWaitTime > 0;
}


//Private Methods

CardGameCameraManager::CardGameCameraManager()
{
}

CardGameCameraManager::~CardGameCameraManager()
{
}
