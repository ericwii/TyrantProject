#include "stdafx.h"
#include "CardHand.h"
#include "Card.h"

Vector2<float> canvasSize(1.5f, 2.0f);
Vector2<float> handStartPosition(0.1f, 0.1f);
float cardOffset = 1.8f;



CardHand::CardHand()
{
	LoadGUI();
}


CardHand::~CardHand()
{
}

void CardHand::AddCard(Card* aCard)
{
	aCard->SetOrientation(CU::Matrix44<float>::CreateRotateAroundY(PI * 2));
	myCards.Add(aCard);

	Vector2<float> position = handStartPosition;
	for (int i = 0; i < myCards.Size(); ++i)
	{
		position.x = handStartPosition.x + cardOffset* i;
		myCards[i]->SetPosition(position);
	}
}

void CardHand::RemoveCard(Card* aCard)
{
	myCards.RemoveNonCyclic(aCard);

	Vector2<float> position = handStartPosition;
	for (int i = 0; i < myCards.Size(); ++i)
	{
		position.x = handStartPosition.x + cardOffset* i;
		myCards[i]->SetPosition(position);
	}
}

void CardHand::Render()
{
	//render gui
	myHandGUI.Render();

	for (int i = 0; i < myCards.Size(); ++i)
	{
		myCards[i]->Render();
	}

	//Hitbox2D currentHitbox(0, 0, 0.2f, 0.4f);
	//Vector2<float> hitboxOffset(0.1f, 0.24f);
	//Camera camera = Engine::GetInstance()->GetCamera();
	//for (int i = 0; i < myCards.Size(); ++i)
	//{
	//	currentHitbox.SetPosition(camera.ToScreenPosition(myCards[i]->GetPosition()) - hitboxOffset);
	//	Engine::GetInstance()->RenderDebugHitbox2D(currentHitbox);
	//}
}


bool CardHand::ChooseCardToPlay(Card*& chosenCard)
{
	if (InputManager::Mouse.WasButtonJustPressed(eMouseButton::LEFTBUTTON))
	{
		int hitIndex = HitBoxCheck();
		if (hitIndex >= 0)
		{
			chosenCard = myCards[hitIndex];
			return true;
		}
	}

	return false;
}

void CardHand::LoadGUI()
{
	Model* GUI = ModelLoader::LoadRectangle(Vector2<float>(6.f, 3.f), eEffectType::Textured, "Data/Textures/yourHand.png");
	myHandGUI.Init(GUI);
	myHandGUI.SetPosition(Vector2<float>(1.8f, 0.2f));
}

int CardHand::HitBoxCheck()
{
	Vector2<float> mousePosition = InputManager::Mouse.GetWindowPosition(Engine::GetInstance()->GetWindowHandle(), Engine::GetInstance()->GetResolution());
	Camera camera = Engine::GetInstance()->GetCamera();

	Hitbox2D currentHitbox(0, 0, 0.2f, 0.4f);
	Vector2<float> hitboxOffset(0.1f, 0.24f);
	for (int i = 0; i < myCards.Size(); i++)
	{
		currentHitbox.SetPosition(camera.ToScreenPosition(myCards[i]->GetPosition()) - hitboxOffset);
	
		if (currentHitbox.Inside(mousePosition))
		{
			return i;
		}
	}

	return -1;
}
