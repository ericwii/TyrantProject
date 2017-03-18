#pragma once


class Card;


class CardHand
{
public:
	CardHand();
	~CardHand();
	
	void AddCard(Card* aCard);
	void RemoveCard(Card* aCard);
	void Render();


	bool ChooseCardToPlay(Card*& chosenCard);

	inline bool HasCards();
	inline CU::VectorOnStack<Card*, 3>& GetCards();

private:
	void LoadGUI();
	int HitBoxCheck();

	CU::VectorOnStack<Card*,3> myCards;
	Instance myHandGUI;
};


inline bool CardHand::HasCards()
{
	return myCards.Size() > 0;
}

inline CU::VectorOnStack<Card*, 3>& CardHand::GetCards()
{
	return myCards;
}