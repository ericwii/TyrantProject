#pragma once
#include "../../CommonUtilities/VectorOnStack.h"

class FPS_Counter
{
public:
	FPS_Counter();
	~FPS_Counter();

	void AddFrame(float deltaTime);
	void RenderFrameRate();

private:
	CU::VectorOnStack<float, 100> myFrameStack;
	string myFrameRate;
};

