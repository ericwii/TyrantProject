#include "stdafx.h"
#include "FPS_Counter.h"


FPS_Counter::FPS_Counter() : myFrameRate("FPS: 0")
{
}

FPS_Counter::~FPS_Counter()
{
}


void FPS_Counter::AddFrame(float deltaTime)
{
	myFrameStack.Add(deltaTime);

	if (myFrameStack.IsFull())
	{
		float sum = 0;
		for (int i = 0; i < myFrameStack.Size(); ++i)
		{
			sum += myFrameStack[i];
		}
		sum /= myFrameStack.Size();
		myFrameStack.Clear();

		myFrameRate = "FPS: ";
		myFrameRate += (int)(1.f / sum);
	}
}

void FPS_Counter::RenderFrameRate()
{
	Engine::GetInstance()->RenderDebugText(myFrameRate, Vector2<float>(-1.f, -1.f), 0.6f, Vector4<float>(1.f, 0, 0, 1.f));
}