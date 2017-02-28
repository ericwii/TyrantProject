#include "stdafx.h"
#include "CardHand.h"
#include "Card.h"

Vector2<float> canvasSize(1.5f, 2.0f);

Vector2<float> mousePosition;

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

	//mousePosition = InputManager::Mouse.GetWindowPosition(Engine::GetInstance()->GetWindowHandle());
	//mousePosition /= Engine::GetInstance()->GetResolution();
	//
	//string temp;
	//temp += "X: ";
	//temp += mousePosition.x;
	//temp += " Y: ";
	//temp += mousePosition.y;
	//Engine::GetInstance()->RenderDebugText(temp, {-1.f,-1.f}, 0.5f);
	//
	//Engine::GetInstance()->RenderDebugText("M", mousePosition);

	//Vector3<float> lastPosition = myCards[0]->GetPosition();
	//lastPosition.x = mousePosition.x * 5.f;
	//lastPosition.y = mousePosition.y * 5.f;
	//myCards[0]->SetPosition(lastPosition);
}

CU::GrowingArray<Card*>& CCardHand::GetCards()
{
	return myCards;
}

Card * CCardHand::ChooseCardToPlay()
{
	int hitIndex = HitBoxCheck();

	if (hitIndex >= 0)
	{
		return myCards[hitIndex];
	}
	return nullptr;
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
	

	
	//for (int i = 0; i < myCards.Size(); i++)
	//{
	//	//mousePosition = myCards[i]->GetPosition();
	//	//rectangle = myCards[i]->GetPosition() * Engine::GetInstance()->GetCamera().GetProjection();
	//	////Vector2<float> temp = canvasSize * Engine::GetInstance()->GetCamera().GetProjection();
	//	//rectangle.z = canvasSize.x;
	//	//rectangle.w = canvasSize.y;
	//
	//	if (Collision::PointVsAABB(mousePosition,rectangle) == true)
	//	{
	//		return i;
	//	}
	//}
	return 0;
}
