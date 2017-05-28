#include "stdafx.h"
#include "CardHand.h"
#include "Card.h"

Vector2<float> canvasHitboxSize(0.795f, 0.59f);
Vector3<float> cardStartPos(-1.8f, -0.15f, 0);
Vector2<float> dragHitboxOffset(-0.396f, -0.38f);
Vector2<float> dragHitboxSize(0.795f, 0.1f);
Vector2<float> projectionOffset(7.5, -5.f);
float cardOffset = 1.8f;
Camera* camera;



CardHand::CardHand()
{ }

CardHand::~CardHand()
{ }


void CardHand::Init(bool aIsUser)
{
	myPlayerIsUser = aIsUser;

	if (aIsUser == true)
	{
		Instance guiCanvas(ModelLoader::LoadRectangle(Vector2<float>(6.f, 3.f), eEffectType::Textured, "Data/Textures/playerHand.png"));
		myHandGUI.Init(guiCanvas, 1, 1);
		myHandGUI.SetPosition(Vector3<float>(1.8f, 0.2f));
		myHandGUI.SetHitbox(Hitbox2D(Vector2<float>(-0.157f, -0.335f), canvasHitboxSize));

		camera = &Engine::GetInstance()->GetCamera();

		Vector2<float> guiPos = camera->ToScreenPosition(myHandGUI.GetPosition());
		myDragHitbox.SetPosition(camera->ToScreenPosition(myHandGUI.GetPosition()) + dragHitboxOffset);
		myDragHitbox.SetSize(dragHitboxSize);
	}
}

void CardHand::AddCard(Card* aCard)
{
	if (myPlayerIsUser == true)
	{
		myHandGUI.AddChild(&aCard->GetInstance());

		aCard->SetOrientation(CU::Matrix44<float>::CreateRotateAroundY(PI * 2));
		aCard->SetPosition(myHandGUI.GetPosition() + Vector3<float>(cardStartPos.x + cardOffset * myCards.Size(), cardStartPos.y, cardStartPos.z));

		aCard->SetPopupHitbox();
	}

	myCards.Add(aCard);
}

void CardHand::RemoveCard(Card* aCard)
{
	myCards.RemoveNonCyclic(aCard);
	aCard->GetPopup().SetHitboxLayer(0);

	if (myPlayerIsUser == true)
	{
		myHandGUI.RemoveChild(&aCard->GetInstance());
		for (int i = 0; i < myCards.Size(); ++i)
		{
			myCards[i]->SetPosition(myHandGUI.GetPosition() + Vector3<float>(cardStartPos.x + cardOffset * i, cardStartPos.y, cardStartPos.z));
			myCards[i]->SetPopupHitbox();
			myCards[i]->GetPopup().SetHitboxLayer(0);
		}
	}
}

bool CardHand::ChooseCardToPlay(Card*& chosenCard)
{
	if (InputManager::Mouse.IsButtonDown(eMouseButton::LEFTBUTTON))
	{
		Vector2<float> mousePosition = InputManager::Mouse.GetWindowPosition(Engine::GetInstance()->GetWindowHandle(), Engine::GetInstance()->GetResolution());

		if (InputManager::Mouse.WasButtonJustPressed(eMouseButton::LEFTBUTTON))
		{
			for (int i = 0; i < myCards.Size(); ++i)
			{
				if (myCards[i]->GetPopup().GetHitbox().Inside(mousePosition))
				{
					chosenCard = myCards[i];
					return true;
				}
			}
			if (myDragHitbox.Inside(mousePosition))
			{
				myGUIPos = camera->ToScreenPosition(myHandGUI.GetPosition());
				myGUIPos.y *= -1.f;
				myDragOffset = (myGUIPos - mousePosition) * projectionOffset;
			}
		}
		else if (myDragOffset.Length2() > 0)
		{
			UpdateDrag(mousePosition);
		}
	}
	else
	{
		myDragOffset.x = 0;
		myDragOffset.y = 0;
	}
	
	return false;
}

void CardHand::SetActive(bool active)
{
	if (myPlayerIsUser == true)
	{
		myHandGUI.SetActive(active);
		for (int i = 0; i < myCards.Size(); ++i)
		{
			myCards[i]->GetPopup().SetActive(active);
			myCards[i]->GetPopup().SetHitboxLayer(2);
		}
	}
}


//Private Methods

Vector2<float> dragPosition;
void CardHand::UpdateDrag(Vector2<float>& aMousePosition)
{
	dragPosition = aMousePosition * projectionOffset + myDragOffset;
	dragPosition.x = MAX(MIN(dragPosition.x, 4.5f), -4.5f);
	dragPosition.y = MAX(MIN(dragPosition.y, 3.5f), -3.5f);

	myHandGUI.SetPosition(dragPosition);

	myGUIPos = camera->ToScreenPosition(myHandGUI.GetPosition());
	myGUIPos.y *= -1.f;
	myGUIPos.y += myDragHitbox.height * 0.8f;
	myDragHitbox.SetPosition(myGUIPos + dragHitboxOffset);


	myHandGUI.SetHitbox(Hitbox2D(myGUIPos + dragHitboxOffset, canvasHitboxSize));
	for (int i = 0; i < myCards.Size(); ++i)
	{
		myCards[i]->SetPopupHitbox();
	}
}