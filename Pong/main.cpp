#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include "Window.h"
#include "Renderer.h"
#include "SetupGame.h"

//Als Beispiel eingesetzte Werte
bool IsFullScreen = false;
int ClientWidth = 800;
int ClientHeight = 600;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	Create_Window(ClientWidth, ClientHeight, IsFullScreen, hInstance, pCmdLine, nCmdShow);

	InitD3D11(Get_Window_Handle());



	ShowWindow(Get_Window_Handle(), nCmdShow);

	// Run the message loop.

	MSG msg = { };
	while (TRUE)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (msg.message == WM_QUIT)
		{
			break;
		}
		//Where the real fun starts
		float black[4] = { 0, 0, 0, 1, };
		Get_Context()->ClearRenderTargetView(Get_RenderTargetView(), black);
		Get_SwapChain()->Present(0, 0);
	}

	CleanUp();
	return 0;
}

