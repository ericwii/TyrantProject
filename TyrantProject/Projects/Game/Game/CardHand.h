#pragma once
#include "GUIWindow.h"

class Card;

class CardHand
{
public:
	CardHand();
	~CardHand();

	void Init(bool aIsUser);
	
	void AddCard(Card* aCard);
	void RemoveCard(Card* aCard);
	bool ChooseCardToPlay(Card*& chosenCard);

	void SetActive(bool active);
	inline bool HasCards();
	inline CU::VectorOnStack<Card*, 3>& GetCards();

private:
	void UpdateDrag(Vector2<float>& aMousePosition);

	GUIWindow myHandGUI;
	CU::VectorOnStack<Card*,3> myCards;
	Hitbox2D myDragHitbox;
	Vector2<float> myDragOffset;
	Vector2<float> myGUIPos;
	bool myPlayerIsUser;
};


inline bool CardHand::HasCards()
{
	return myCards.Size() > 0;
}

inline CU::VectorOnStack<Card*, 3>& CardHand::GetCards()
{
	return myCards;
}