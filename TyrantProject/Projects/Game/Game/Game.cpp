#include "stdafx.h"
#include "Game.h"
#include "../../Engine/ModelLoader.h"
#include "CardFactory.h"

Instance cardTestInstance;
Instance test3;
Instance test2;
Instance test;
CU::GrowingArray<Instance*> instanser;
CU::GrowingArray<Instance*> instanser2;
CardFactory factory;

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

	Model* illu = ModelLoader::LoadRectangle3D(Vector2<float>(1.42f, 1.15f), eEffectType3D::Textured, "Data/Textures/Illustrations/Raider/Assault/RadioOfficer.jpg");
	test3.Init(illu, instanser2);
	test3.SetPosition({ -0.0f, 0.25f, 0 });
	instanser.Add(&test3);

	Model* cooldown = ModelLoader::LoadRectangle3D(Vector2<float>(0.2f, 0.3f), eEffectType3D::Textured, "Data/Textures/Icons/cooldownIcon.png");
	test2.Init(cooldown,instanser2);
	test2.SetPosition({ 0.6f,0.8f,-0.1f });
	instanser.Add(&test2); 


	Model* cardModel = ModelLoader::LoadRectangle3D(Vector2<float>(1.5f, 2.f), eEffectType3D::Card, "Data/Textures/CardCanvas/canvas.png", true);
	cardModel->AddTexture("HighlightTexture", "Data/Textures/CardCanvas/highlight.png");
	cardTestInstance.Init(cardModel,instanser);

	factory.LoadCards();
	CardData temp = factory.GetCard("Radio Officer");

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
	cardTestInstance.Render();
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