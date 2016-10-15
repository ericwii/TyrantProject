#pragma once
#include "../../Engine/Text.h"

class Card
{
public:
	Card();
	~Card();


private:
	Text myText;
	Instance myCanvas;
	Model* myIllustration;
};
