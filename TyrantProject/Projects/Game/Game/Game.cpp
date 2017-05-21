#include "stdafx.h"
#include "Game.h"
#include "CardGameState.h"
#include "../../Engine/Animation.h"

Game::Game() : myEngineInstance(nullptr), myShowFrameRate(false)
{
}

Game::~Game()
{
}



bool Game::Init(WNDPROC aWindowProc)
{
	Engine::Start(aWindowProc, WindowSetupInfo(eWindowMode::Windowed));
	myEngineInstance = Engine::GetInstance();
	myEngineInstance->GetCamera().SetPosition(Vector3<float>(0, 0, -5.f));

	InputManager::Initialize();
	CardFactory::Create();
	CardFactory::GetInstance().LoadCards();

	myStates.Allocate(3);
	myStates.Add(new CardGameState());
	myStates.GetLast()->OnEnter();

	//AnimationData data
	//{
	//	"Data/Textures/animation_test.png",
	//	30,
	//	5,
	//	60.f,
	//	true
	//};
	//
	//testAnimation.Init(data, Vector3<float>(), Vector2<float>(1.f, 1.5f));
	//testAnimation.Play();

	return true;
}

bool Game::Destroy()
{
	return true;
}




void Game::OnResize(const int aWidth, const int aHeight)
{
	DEBUG_ASSERT(myEngineInstance != nullptr, "Can't resize screen when engine is not initialized");
	myEngineInstance->ResizeScreen(aWidth, aHeight);
}

void Game::Pause()
{

}

void Game::UnPause()
{

}


bool Game::Update()
{
	myStates.GetLast()->Update();

	if (myShowFrameRate)
	{
		myFpsCounter.AddFrame(Time::DeltaTime());
	}
	UpdateDebugInput();
	UpdateUtilities();

	return true;
}

void Game::Render()
{
	myStates.GetLast()->Render();

	if (myShowFrameRate)
	{
		myFpsCounter.RenderFrameRate();
	}
	myEngineInstance->PresentBackBuffer();
}



//Private methods

void Game::UpdateUtilities()
{
	Time::Update();
	InputManager::Update();
}

void Game::UpdateDebugInput()
{
	if (InputManager::Keyboard.WasKeyJustPressed(DIK_F1))
	{
		Time::SetTimeScale(1.f);
	}
	else if (InputManager::Keyboard.WasKeyJustPressed(DIK_F2))
	{
		Time::SetTimeScale(2.f);
	}
	else if (InputManager::Keyboard.WasKeyJustPressed(DIK_F3))
	{
		Time::SetTimeScale(3.f);
	}
	else if (InputManager::Keyboard.WasKeyJustPressed(DIK_F4))
	{
		Time::SetTimeScale(4.f);
	}

	if (InputManager::Keyboard.WasKeyJustPressed(DIK_F9))
	{
		Time::SetTimeScale(0.5f);
	}
	else if (InputManager::Keyboard.WasKeyJustPressed(DIK_F10))
	{
		Time::SetTimeScale(0.25f);
	}
	else if (InputManager::Keyboard.WasKeyJustPressed(DIK_F11))
	{
		Time::SetTimeScale(0.12f);
	}
	else if (InputManager::Keyboard.WasKeyJustPressed(DIK_F12))
	{
		Time::SetTimeScale(0.06f);
	}



	if (InputManager::Keyboard.WasKeyJustPressed(DIK_F5))
	{
		myShowFrameRate = !myShowFrameRate;
	}
}