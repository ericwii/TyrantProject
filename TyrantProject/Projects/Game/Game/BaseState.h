#pragma once


class BaseState
{
public:
	BaseState();
	~BaseState();

	virtual void OnEnter() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void OnExit() = 0;
};

