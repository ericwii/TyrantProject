#pragma once


class Card;


class CCardHand
{
public:
	CCardHand();
	~CCardHand();
	
	void Render();

	CU::GrowingArray<Card*>& GetCards();

	Card* ChooseCardToPlay();


private:
	void LoadGUI();

	int HitBoxCheck();

private:
	CU::GrowingArray<Card*> myCards;

	Instance myHandGUI;
};

