#include "stdafx.h"
#include "InputManager.h"

#define KEYDOWN(name,key) (name[key] & 0x80) 

InputManager::MouseInput InputManager::Mouse;
InputManager::KeyboardInput InputManager::Keyboard;
InputManager* InputManager::myInstance = nullptr;

/* Mouse */

InputManager::MouseInput::MouseInput()
{
}

InputManager::MouseInput::~MouseInput()
{
}


void InputManager::MouseInput::Update()
{
	myMousePointer->Acquire();

	for (int i = 0; i < 3; ++i)
	{
		myButtonsLastStates[i] = myMouseState.rgbButtons[i];
	}

	myMousePointer->GetDeviceState(sizeof(DIMOUSESTATE), &myMouseState);
}

bool InputManager::MouseInput::IsButtonDown(const eMouseButton aButton)
{
	return !!(KEYDOWN(myMouseState.rgbButtons, aButton));
}

bool InputManager::MouseInput::IsButtonUp(const eMouseButton aButton)
{
	return !(KEYDOWN(myMouseState.rgbButtons, aButton));
}

bool InputManager::MouseInput::WasButtonJustPressed(const eMouseButton aButton)
{
	if (myButtonsLastStates[aButton] != myMouseState.rgbButtons[aButton])
	{
		return !!(KEYDOWN(myMouseState.rgbButtons, aButton));
	}

	return false;
}

bool InputManager::MouseInput::WasButtonJustReleased(const eMouseButton aButton)
{
	if (myButtonsLastStates[aButton] != myMouseState.rgbButtons[aButton])
	{
		return !(KEYDOWN(myMouseState.rgbButtons, aButton));
	}

	return false;
}

bool InputManager::MouseInput::IsAnyButtonDown()
{
	for (int i = 0; i < 3; ++i)
	{
		if (KEYDOWN(myMouseState.rgbButtons, i))
		{
			return true;
		}
	}
	return false;
}

bool InputManager::MouseInput::WasAnyButtonJustPressed()
{
	for (int i = 0; i < 3; ++i)
	{
		if (WasButtonJustPressed(eMouseButton(i)))
		{
			return true;
		}
	}
	return false;
}

long InputManager::MouseInput::GetDeltaX() const
{
	return myMouseState.lX;
}

long InputManager::MouseInput::GetDeltaY() const
{
	return myMouseState.lY;
}

long InputManager::MouseInput::GetScrollDelta() const
{
	return (myMouseState.lZ / 120);
}

Vector2<long> InputManager::MouseInput::GetDeltaVector()
{
	return Vector2<long>(myMouseState.lX, myMouseState.lY);
}

const Vector2<float> mouseOffset(0.013f, 0.08f);
Vector2<float> InputManager::MouseInput::GetWindowPosition(HWND aWindowHandle, Vector2<float> aResolution)
{
	DEBUG_ASSERT(aWindowHandle != NULL, "Cannot get mouse position from a null window handle");

	RECT screenPosition = { 0, 0 };
	GetWindowRect(aWindowHandle, &screenPosition);
	
	POINT cursorPoint;
	GetCursorPos(&cursorPoint);
	
	float mouse_X = static_cast<float>((cursorPoint.x - screenPosition.left)) / aResolution.x;
	float mouse_Y = static_cast<float>((cursorPoint.y - screenPosition.top)) / aResolution.y;

	return Vector2<float>(mouse_X * 2.f - 1.f, mouse_Y * 2.f - 1.f) - mouseOffset;
}

Vector2<float> InputManager::MouseInput::GetPosition()
{
	POINT cursorPoint;
	GetCursorPos(&cursorPoint);
	return Vector2<float>(static_cast<float>(cursorPoint.x), static_cast<float>(cursorPoint.y));
}








/* Keyboard */

InputManager::KeyboardInput::KeyboardInput()
{
}

InputManager::KeyboardInput::~KeyboardInput()
{
}

bool InputManager::KeyboardInput::IsKeyDown(short aKey)
{
	DEBUG_ASSERT(aKey >= 0, "Key code cannot be smaller than 0");

	if (KEYDOWN(myKeyboardBuffer, aKey))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool InputManager::KeyboardInput::WasKeyJustPressed(short aKey)
{
	DEBUG_ASSERT(aKey >= 0, "Key code cannot be smaller than 0");

	if (myKeysLastStates[aKey] != myKeyboardBuffer[aKey])
	{
		if (KEYDOWN(myKeyboardBuffer, aKey))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}

bool InputManager::KeyboardInput::WasKeyJustReleased(short aKey)
{
	DEBUG_ASSERT(aKey >= 0, "Key code cannot be smaller than 0");

	if (myKeysLastStates[aKey] != myKeyboardBuffer[aKey])
	{
		if (KEYDOWN(myKeyboardBuffer, aKey))
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	return false;
}

//Kan finnas en bättre lösning en 1 for-sats
bool InputManager::KeyboardInput::IsAnyKeyDown()
{
	for (short i = 0; i < 255; ++i)
	{
		if (IsKeyDown(i))
		{
			return true;
		}
	}
	return false;
} 

bool InputManager::KeyboardInput::WasAnyKeyJustPressed()
{
	for (short i = 0; i < 255; ++i)
	{
		if (WasKeyJustPressed(i))
		{
			return true;
		}
	}
	return false;
}








/* InputManager */

InputManager::InputManager()
{
	//Create the DirectInput Connection
	DirectInput8Create(GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&myDirectInputPointer,
		NULL);

	if (myDirectInputPointer == nullptr)
	{
		OutputDebugStringA("\nDirectInput Connection Failed!");
		return;
	}
	else
	{
		OutputDebugStringA("\nDirectInput Connection Sucessfull!\n");
	}

	myIsInitialized = false;
}

InputManager::~InputManager()
{
	Keyboard.myKeyboardPointer->Release();
	Mouse.myMousePointer->Release();
	myDirectInputPointer->Release();
}


void InputManager::Initialize()
{
	if (myInstance == nullptr)
	{
		myInstance = new InputManager();
		myInstance->myIsInitialized = true;

		myInstance->myDirectInputPointer->CreateDevice(GUID_SysKeyboard, &Keyboard.myKeyboardPointer, NULL);

		myInstance->myDirectInputPointer->CreateDevice(GUID_SysMouse, &Mouse.myMousePointer, NULL);

		//Setting up the keyboard
		Keyboard.myKeyboardPointer->SetDataFormat(&c_dfDIKeyboard);
		Keyboard.myKeyboardPointer->SetCooperativeLevel(0, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

		//Setting up the mouse
		Mouse.myMousePointer->SetDataFormat(&c_dfDIMouse);
		Mouse.myMousePointer->SetCooperativeLevel(0, DISCL_NONEXCLUSIVE);
	}
}

void InputManager::Update()
{
	DEBUG_ASSERT(myInstance->myIsInitialized, "Input wrapper is not initialized");

	Keyboard.myKeyboardPointer->Acquire();

	for (int i = 0; i < 255; i++)
	{
		Keyboard.myKeysLastStates[i] = Keyboard.myKeyboardBuffer[i];
	}
	
	Keyboard.myKeyboardStateResult = Keyboard.myKeyboardPointer->GetDeviceState(sizeof(Keyboard.myKeyboardBuffer), &Keyboard.myKeyboardBuffer);
	
	Mouse.Update();

	//Keyboard is not connected
	if (Keyboard.myKeyboardStateResult != S_OK)
	{
		Keyboard.myKeyboardPointer->Acquire();
	}
}