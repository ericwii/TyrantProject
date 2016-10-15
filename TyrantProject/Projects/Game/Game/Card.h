#pragma once
#include "../../Engine/Text.h"

class Card
{
public:
	Card();
	~Card();

	void LoadFromXMl(const string& anXmlFile);


private:
	Text myText;
	Instance myCanvas;
	Model* myIllustration;
};
