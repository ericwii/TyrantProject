#include "stdafx.h"
#include "CardHand.h"
#include "Card.h"

Vector2<float> canvasSize(1.5f, 2.0f);

CCardHand::CCardHand()
{
	myCards.Allocate(4);
	
	LoadGUI();
}


CCardHand::~CCardHand()
{
}

void CCardHand::Render()
{
	//render gui
	myHandGUI.Render();

	for (int i = 0; i < myCards.Size(); i++)
	{
		myCards[i]->Render();
	}

	Vector2<float> mousePosition;

	mousePosition = InputManager::Mouse.GetWindowPosition(Engine::GetInstance()->GetWindowHandle());
	mousePosition.x /= Engine::GetInstance()->GetResolution().x;
	mousePosition.y /= Engine::GetInstance()->GetResolution().y;
	//mousePosition = (mousePosition * 2) - 1;

	string temp;
	temp += "X: ";
	temp += mousePosition.x;
	temp += " Y: ";
	temp += mousePosition.y;
	Engine::GetInstance()->RenderDebugText(temp, {0,0}, 0.5f);

	Engine::GetInstance()->RenderDebugText("M", mousePosition);
}

CU::GrowingArray<Card*>& CCardHand::GetCards()
{
	return myCards;
}

Card * CCardHand::ChooseCardToPlay()
{
	return myCards[HitBoxCheck()];
}

void CCardHand::LoadGUI()
{
	Model* GUI = ModelLoader::LoadRectangle(Vector2<float>(6.f, 3.f), eEffectType::Textured, "Data/Textures/yourHand.png");
	myHandGUI.Init(GUI);
	myHandGUI.SetPosition(Vector2<float>(1.8f, 0.2f));
}

int CCardHand::HitBoxCheck()
{
	Vector4<float> rectangle;
	Vector2<float> mousePosition;
	
	for (int i = 0; i < myCards.Size(); i++)
	{
		mousePosition = myCards[i]->GetPosition();
		rectangle = myCards[i]->GetPosition()/5;
		rectangle.z = canvasSize.x;
		rectangle.w = canvasSize.y;

		mousePosition = InputManager::Mouse.GetWindowPosition(Engine::GetInstance()->GetWindowHandle());
		mousePosition.x /= Engine::GetInstance()->GetResolution().x;
		mousePosition.y /= Engine::GetInstance()->GetResolution().y;
		mousePosition = (mousePosition * 2) - 1;

		if (Collision::PointVsAABB(mousePosition,rectangle) == true)
		{
			return i;
		}
	}
	return 0;
}
