#include "Input.h"
#include "Window.h"
#include "GameState.h"


void InitDirectInput(HINSTANCE hInstance)
{
	DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&DirectInput, NULL);

	DirectInput->CreateDevice(GUID_SysKeyboard, &DIKeyboard, NULL);

	DIKeyboard->SetDataFormat(&c_dfDIKeyboard);
	DIKeyboard->SetCooperativeLevel(Get_Window_Handle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
}

void DetectInput()
{
	BYTE keyboardState[256];

	DIKeyboard->Acquire();

	DIKeyboard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);

	//Physics Player 1
	if (keyboardState[DIK_W] & 0x80)
	{
		Get_Schlaeger_2()->y += 0.001;

		if (Get_Schlaeger_2()->y + 0.15 >= 1)
		{
			Get_Schlaeger_2()->y = 1 - 0.15;
		}
	}

	if (keyboardState[DIK_S] & 0x80)
	{
		Get_Schlaeger_2()->y += -0.001;

		if (Get_Schlaeger_2()->y - 0.15 <= -1)
		{
			Get_Schlaeger_2()->y = -1 + 0.15;
		}
	}

	//Physics Player 2
	if (keyboardState[DIK_UP] & 0x80)
	{
	    Get_Schlaeger_1()->y += 0.001;

		if (Get_Schlaeger_1()->y + 0.15 >= 1)
		{
			Get_Schlaeger_1()->y = 1 - 0.15;
		}
	}

	if (keyboardState[DIK_DOWN] & 0x80)
	{
		Get_Schlaeger_1()->y += -0.001;

		if (Get_Schlaeger_1()->y -0.15 <= -1)
		{
			Get_Schlaeger_1()->y = -1 + 0.15;
		}
	}
}

void ReleaseInput()
{
	DIKeyboard->Unacquire();
	DIKeyboard->Release();
	DirectInput->Release();
}
