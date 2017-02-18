#include "stdafx.h"
#include "Game.h"
#include "CardGameState.h"
#include "../../Engine/Animation.h"

Game::Game() : myEngineInstance(nullptr)
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

	//UpdateCameraMovement();
	UpdateUtilities();

	return true;
}

void Game::Render()
{
	myEngineInstance->RenderDebugText("Debug Text", Vector2<float>(0,0), 0.6f);

	myStates.GetLast()->Render();

	myEngineInstance->PresentBackBuffer();
}



//Private methods

void Game::UpdateUtilities()
{
	Time::Update();
	InputManager::Update();
}

void Game::UpdateCameraMovement()
{
	Camera& cam = myEngineInstance->GetCamera();
	float deltaTime = Time::DeltaTime();
	float speed = 10.f;
	float rotationSpeed = 2.f;

	if (InputManager::Keyboard.IsKeyDown(DIK_LCONTROL))
	{
		speed *= 0.2f;
	}

	if (InputManager::Keyboard.IsKeyDown(DIK_S))
	{
		cam.MoveBack(speed, deltaTime);
	}
	if (InputManager::Keyboard.IsKeyDown(DIK_W))
	{
		cam.MoveForward(speed, deltaTime);
	}
	if (InputManager::Keyboard.IsKeyDown(DIK_D))
	{
		cam.MoveLeft(speed, deltaTime);
	}
	if (InputManager::Keyboard.IsKeyDown(DIK_A))
	{
		cam.MoveRight(speed, deltaTime);
	}


	float rotation = rotationSpeed * deltaTime;
	if (InputManager::Keyboard.IsKeyDown(DIK_UPARROW))
	{
		cam.RotateX(-rotation);
	}
	if (InputManager::Keyboard.IsKeyDown(DIK_DOWNARROW))
	{
		cam.RotateX(rotation);
	}
	if (InputManager::Keyboard.IsKeyDown(DIK_LEFTARROW))
	{
		cam.RotateY(-rotation);
	}
	if (InputManager::Keyboard.IsKeyDown(DIK_RIGHTARROW))
	{
		cam.RotateY(rotation);
	}
	if (InputManager::Keyboard.IsKeyDown(DIK_E))
	{
		cam.RotateZ(-rotation);
	}
	if (InputManager::Keyboard.IsKeyDown(DIK_Q))
	{
		cam.RotateZ(rotation);
	}

	if (InputManager::Keyboard.IsKeyDown(DIK_NUMPAD8))
	{
		cam.MoveUp(speed, deltaTime);
	}
	if (InputManager::Keyboard.IsKeyDown(DIK_NUMPAD2))
	{
		cam.MoveDown(speed, deltaTime);
	}
}