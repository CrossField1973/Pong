#pragma once
#include <dinput.h>

IDirectInputDevice8* DIKeyboard;
LPDIRECTINPUT8 DirectInput;

void InitDirectInput(HINSTANCE hInstance);
void DetectInput();
void ReleaseInput();