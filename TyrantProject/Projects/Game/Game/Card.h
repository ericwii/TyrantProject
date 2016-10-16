#pragma once
#include "../../Engine/Text.h"

class Card
{
public:
	Card();
	~Card();

	void Render();

	void LoadFromXMl(const string& anXmlFile);


private:
	Instance myCanvas;
};
