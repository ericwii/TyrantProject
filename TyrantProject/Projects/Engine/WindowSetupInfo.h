#pragma once
#include "../CommonUtilities/String.h"

enum eWindowMode
{
	Fullscreen,
	Windowed_Fullscreen,
	Windowed
};


struct WindowSetupInfo
{
	WindowSetupInfo() {}
	WindowSetupInfo(eWindowMode mode) : windowMode(mode)
	{}
	WindowSetupInfo(eWindowMode mode, int resolutionX, int resolutionY)
		: windowMode(mode), resolution_X(resolutionX), resolution_Y(resolutionY)
	{}
	WindowSetupInfo(eWindowMode mode, int resolutionX, int resolutionY, string title)
		: windowMode(mode), resolution_X(resolutionX), resolution_Y(resolutionY), title(title)
	{}
	WindowSetupInfo(string title, int xResolution = 1080, int yResolution = 720, eWindowMode mode = eWindowMode::Windowed)
		: title(title), resolution_X(xResolution), resolution_Y(yResolution), windowMode(mode)
	{}

	~WindowSetupInfo() {}

	string title = "Tyrant Reborn";
	int resolution_X = 1080;
	int resolution_Y = 720;
	eWindowMode windowMode = eWindowMode::Windowed;
};