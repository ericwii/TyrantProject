#pragma once
#include "BaseState.h"
#include "Player.h"


class CardGameState : public BaseState
{
public:
	CardGameState();
	~CardGameState();

	void OnEnter() override;
	void Update() override;
	void Render() override;
	void OnExit() override;

private:
	Player myPlayerUser;
	Player myPlayerOpponent;
	Instance myBackground;
	Instance myDeckGUI;
};

