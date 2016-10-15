#include <Windows.h>
#include <fstream>
#include <time.h>
#include <algorithm> 

#include "../../CommonUtilities/Vector4.h"
#include "../../Engine/Engine.h"
#include "../../Game/Game/Game.h"
#include "../../Time/Time.h"

Game* globalGamePointer(nullptr);

WORD globalClientWidth = 0;
WORD globalClientHeight = 0;
bool globalIsResizing = false;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_ACTIVATE:

		if (globalGamePointer != NULL)
		{
			if (LOWORD(wParam) == WA_INACTIVE)
			{
				if (globalGamePointer != nullptr)
				{
					globalGamePointer->Pause();
				}
			}
			else
			{
				if (globalGamePointer != nullptr)
				{
					globalGamePointer->UnPause();
				}
			}
		}
		return 0;

	case WM_SIZE:
		// Save the new client area dimensions.
		globalClientWidth = LOWORD(lParam);
		globalClientHeight = HIWORD(lParam);
		{
			if (wParam == SIZE_MINIMIZED)
			{
				if (globalGamePointer != NULL)
				{
					globalGamePointer->Pause();
				}

			}
			else if (wParam == SIZE_MAXIMIZED)
			{
				if (globalGamePointer != NULL)
				{
					globalGamePointer->UnPause();
					globalGamePointer->OnResize(globalClientWidth, globalClientHeight);
				}
			}
			else if (wParam == SIZE_RESTORED)
			{
				// Restoring from minimized state?
				if (globalIsResizing)
				{
					// If user is dragging the resize bars, we do not resize 
					// the buffers here because as the user continuously 
					// drags the resize bars, a stream of WM_SIZE messages are
					// sent to the window, and it would be pointless (and slow)
					// to resize for each WM_SIZE message received from dragging
					// the resize bars.  So instead, we reset after the user is 
					// done resizing the window and releases the resize bars, which 
					// sends a WM_EXITSIZEMOVE message.
				}
				else // API call such as SetWindowPos or mSwapChain->SetFullscreenState.
				{
					if (globalGamePointer != NULL)
					{
						globalGamePointer->UnPause();
						globalGamePointer->OnResize(globalClientWidth, globalClientHeight);
					}

				}
			}
		}
		break;

	case WM_ENTERSIZEMOVE:
		globalGamePointer->Pause();
		globalIsResizing = true;
		break;
		// WM_EXITSIZEMOVE is sent when the user releases the resize bars.
		// Here we reset everything based on the new window dimensions.
	case WM_EXITSIZEMOVE:
		globalGamePointer->UnPause();
		globalIsResizing = false;
		globalGamePointer->OnResize(globalClientWidth, globalClientHeight);
		break;


	default:
		return DefWindowProcA(hWnd, message, wParam, lParam);
	}

	return 0;
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR aCmndLine, int)
{
	aCmndLine;
	MSG windowsMessage;

	Game game;
	game.Init(WndProc);
	globalGamePointer = &game;

	for (;;)
	{
		// check for messages
		if (PeekMessageA(&windowsMessage, NULL, 0, 0, PM_REMOVE))
		{
			// handle or dispatch messages
			if (windowsMessage.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&windowsMessage);
			DispatchMessageA(&windowsMessage);
		}
		else
		{
			if (game.Update() == false)
			{
				break;
			}
			else game.Render();
		}
	}

	return 0;
}