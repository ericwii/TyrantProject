#pragma once
#include "BaseState.h"
#include "Player.h"
#include "CardGameManager.h"


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
	void ChangePhase();

	Player myPlayerUser;
	Player myPlayerOpponent;
	Instance myBackground;
	Instance myDeckGUI;
	eGamePhase myCurrentPhase;
	bool myGameIsOver;

	bool myUsersTurn;
};

