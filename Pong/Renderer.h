#pragma once
#include <Windows.h>
#include <d3d11.h>

void InitD3D11(HWND hwnd);
void Set_Shaders();
void Set_Input_Layout();
void CleanUp();
ID3D11Device* Get_Device();
ID3D11DeviceContext* Get_Context();
ID3D11RenderTargetView* Get_RenderTargetView();
ID3D11DepthStencilView* Get_DepthStencilView();
IDXGISwapChain* Get_SwapChain();