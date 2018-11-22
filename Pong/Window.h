#pragma once
#include <Windows.h>

void Create_Window(int width, int height, bool IsFullScreen, HINSTANCE hInstance, PWSTR pCmdLine, int nCmdShow);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HWND Get_Window_Handle();
int Get_Client_Width();
int Get_Client_Height();
bool Get_IsFullscreen();