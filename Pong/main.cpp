#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include "Window.h"
#include "Renderer.h"
#include "GameState.h"
#include "Input.h"

//Als Beispiel eingesetzte Werte
bool IsFullScreen = false;
int ClientWidth = 800;
int ClientHeight = 600;



int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	Create_Window(ClientWidth, ClientHeight, IsFullScreen, hInstance, pCmdLine, nCmdShow);

	InitD3D11(Get_Window_Handle());

	ShowWindow(Get_Window_Handle(), nCmdShow);

	InitGame();

	InitDirectInput(hInstance);

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
		float grey[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
		Get_Context()->ClearRenderTargetView(Get_RenderTargetView(), grey);
		Get_Context()->ClearDepthStencilView(Get_DepthStencilView(), D3D11_CLEAR_DEPTH | D3D10_CLEAR_STENCIL, 1.0f, 0);
		DetectInput();
		if (UpdateScene() == false)
		{
			break;
		}

		Get_SwapChain()->Present(0, 0);
	}

	ReleaseInput();
	CleanUp();
	return 0;
}
