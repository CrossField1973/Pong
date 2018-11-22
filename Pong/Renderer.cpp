#include "Renderer.h"
#include "Window.h"
#include <d3d11.h>

D3D_FEATURE_LEVEL featureLevel[4] =
{
	D3D_FEATURE_LEVEL_11_0,
	D3D_FEATURE_LEVEL_10_1,
	D3D_FEATURE_LEVEL_10_0,
	D3D_FEATURE_LEVEL_9_1,
};
D3D_FEATURE_LEVEL currentFeatureLevel = { };

//Create Device Context and Swapchain
DXGI_SWAP_CHAIN_DESC swapChainDesc = { };
IDXGISwapChain* swapChain = nullptr;
ID3D11Device* device = nullptr;
ID3D11DeviceContext* context = nullptr;

//Create Render Target View
ID3D11RenderTargetView* renderTargetView = nullptr;
ID3D11Texture2D* backBuffer = nullptr;

//Create Depht Stencil Buffer
D3D11_TEXTURE2D_DESC depthStencilDesc = { };
ID3D11Texture2D* depthStencilBuffer = nullptr;
ID3D11DepthStencilView* depthStencilView = nullptr;

//Create View Port
D3D11_VIEWPORT vp = { };

void InitD3D11(HWND hwnd)
{
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.Height = Get_Client_Height();
	swapChainDesc.BufferDesc.Width = Get_Client_Width();
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.OutputWindow = hwnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Windowed = !Get_IsFullscreen();
	swapChainDesc.Flags = 0;

	D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, featureLevel, 4, D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, nullptr, &context);

	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));
	device->CreateRenderTargetView(backBuffer, 0, &renderTargetView);
	backBuffer->Release();

	depthStencilDesc.Width = Get_Client_Width();
	depthStencilDesc.Height = Get_Client_Height();
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	device->CreateTexture2D(&depthStencilDesc, 0, &depthStencilBuffer);
	device->CreateDepthStencilView(depthStencilBuffer, 0, &depthStencilView);

	context->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	vp.Width = static_cast<float>(Get_Client_Width());
	vp.Height = static_cast<float>(Get_Client_Height());
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	context->RSSetViewports(1, &vp);
}

void CleanUp()
{
	//Release all COM Objects
	if (swapChain != NULL)
	{
		swapChain->Release();
	}

	if (context != NULL)
	{
		context->Release();
	}

	if (device != NULL)
	{
		device->Release();
	}

	if (renderTargetView != NULL)
	{
		renderTargetView->Release();
	}

	if (backBuffer != NULL)
	{
		backBuffer->Release();
	}

	if (depthStencilBuffer != NULL)
	{
		depthStencilBuffer->Release();
	}

	if (depthStencilView != NULL)
	{
		depthStencilView->Release();
	}
}

ID3D11Device * Get_Device()
{
	return device;
}

ID3D11DeviceContext * Get_Context()
{
	return context;
}

IDXGISwapChain * Get_SwapChain()
{
	return swapChain;
}

ID3D11RenderTargetView * Get_RenderTargetView()
{
	return renderTargetView;
}
