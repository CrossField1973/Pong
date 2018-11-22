#include "Window.h"
#include <Windows.h>

HWND wHWND = { };

int Client_Width;
int Client_Height;
bool IsFullscreen;

int Get_Client_Width()
{
	return Client_Width;
}

int Get_Client_Height()
{
	return Client_Height;
}

bool Get_IsFullscreen()
{
	return IsFullscreen;
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hwnd, &ps);
	}
	return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);


}

HWND Get_Window_Handle()
{
	return wHWND;
}

void Create_Window(int width, int height, bool IsFullScreen, HINSTANCE hInstance, PWSTR pCmdLine, int nCmdShow)
{
	Client_Width = width;
	Client_Height = height;
	IsFullscreen = IsFullScreen;

	//Adjust Window Size
	RECT rect = { 0, 0, width, height };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, NULL);

	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

	// Register the window class.
	const wchar_t CLASS_NAME[] = L"Sample Window Class";

	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = (LPSTR)CLASS_NAME;

	RegisterClass(&wc);

	// Create the window.

	wHWND = CreateWindowEx(
		0,                              // Optional window styles.
		(LPSTR)CLASS_NAME,                     // Window class
		(LPSTR)L"Learn to Program Windows",    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, width, height,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);
}
