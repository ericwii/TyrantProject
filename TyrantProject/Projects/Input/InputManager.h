#pragma once

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>

#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

enum eMouseButton
{
	LEFTBUTTON = 0,
	RIGHTBUTTON = 1,
	SCROLLBUTTON = 2
};

class InputManager
{
	class MouseInput
	{
		friend class InputManager;

	public:
		MouseInput();
		~MouseInput();

		bool IsButtonDown(const eMouseButton aButton);
		bool IsButtonUp(const eMouseButton aButton);

		bool WasButtonJustPressed(const eMouseButton aButton);
		bool WasButtonJustReleased(const eMouseButton aButton);

		bool IsAnyButtonDown();
		bool WasAnyButtonJustPressed();

		long GetDeltaX() const;
		long GetDeltaY() const;
		long GetScrollDelta() const;

		Vector2<long> GetDeltaVector();
		Vector2<float> GetWindowPosition(HWND aWindowHandle, Vector2<float> aResolution);
		Vector2<float> GetPosition();

	private:
		void Update();

		LPDIRECTINPUTDEVICE8 myMousePointer;
		DIMOUSESTATE myMouseState;
		BYTE myButtonsLastStates[3];
	};

	class KeyboardInput
	{
		friend class InputManager;

	public:
		KeyboardInput();
		~KeyboardInput();

		bool IsKeyDown(short aKey);
		bool WasKeyJustPressed(short aKey);
		bool WasKeyJustReleased(short aKey);

		bool IsAnyKeyDown();
		bool WasAnyKeyJustPressed();

	private:
		LPDIRECTINPUTDEVICE8 myKeyboardPointer;
		BYTE myKeyboardBuffer[256];
		BYTE myKeysLastStates[256];
		HRESULT myKeyboardStateResult;
	};

public:
	/*Initializes the mouse and keyboard devices*/
	static void Initialize();

	/*Updates the states of all input devices*/
	static void Update();

	static MouseInput Mouse;
	static KeyboardInput Keyboard;

private:
	InputManager();
	~InputManager();

	static InputManager* myInstance;
	LPDIRECTINPUT8 myDirectInputPointer; //direct input interface
	bool myIsInitialized;
};