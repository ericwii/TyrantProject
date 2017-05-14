#pragma once
#include "../../CommonUtilities/GrowingArray.h"

class BaseState;

class Game
{
public:
	Game();
	~Game();

	bool Init(WNDPROC aWindowProc);
	bool Destroy();

	void OnResize(const int aWidth, const int aHeight);
	void Pause();
	void UnPause();

	bool Update();
	void Render();
	
	Game& operator=(const Game&) = delete;

private:
	void UpdateUtilities();
	void UpdateDebugInput();

	Engine* myEngineInstance;
	CU::GrowingArray<BaseState*> myStates;
};
