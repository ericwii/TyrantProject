#include "stdafx.h"
#include "Game.h"
#include "../../Engine/ModelLoader.h"
#include "Card.h"

Card testCard;

CU::GrowingArray<Instance*> instanser;
CU::GrowingArray<Instance*> instanser2;

Game::Game() : myEngineInstance(nullptr)
{
}

Game::~Game()
{
}



bool Game::Init(WNDPROC aWindowProc)
{
	instanser.Allocate(10);
	instanser2.Allocate(10);
	Engine::Start(aWindowProc, WindowSetupInfo(eWindowMode::Windowed));
	myEngineInstance = Engine::GetInstance();
	myEngineInstance->GetCamera().SetPosition(Vector3<float>(0, 0, -2.1f));

	InputManager::Initialize();

	testCard.LoadFromXMl("Data/XML files/test.xml");

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
	UpdateCameraMovement();

	UpdateUtilities();
	return true;
}

void Game::Render()
{
	testCard.Render();
	myEngineInstance->RenderDebugText("Debug Text", Vector2<float>(0,0), 0.6f);

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
	float speed = 3.f;

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


	float rotation = 0.5f * deltaTime;
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
}