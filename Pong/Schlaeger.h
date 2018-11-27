#pragma once
#include "Structures.h"
#include "Renderer.h"
#include <d3d11.h>

class bat 
{
	D3D11_BUFFER_DESC schlaegerBufferDesc = { };
	D3D11_BUFFER_DESC schlaegerIndexBufferDesc = { };
	D3D11_SUBRESOURCE_DATA schlaegerData = { };
	D3D11_SUBRESOURCE_DATA schlaegerIndexData = { };

	Vertex Schlaeger[4] =
	{
		XMFLOAT4(0.0f, 0.3f, 0.0f, 1.0f), XMFLOAT4(0.3f, 0.3f, 0.3f, 1),
		XMFLOAT4(0.05f, 0.3f, 0.0f, 1.0f), XMFLOAT4(0.3f, 0.3f, 0.3f, 1),
		XMFLOAT4(0.05f, 0.0f, 0.0f, 1.0f), XMFLOAT4(0.3f, 0.3f, 0.3f, 1),
		XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f), XMFLOAT4(0.3f, 0.3f, 0.3f, 1),
	};

	
	UINT SchlaegerIndex[6] =
	{
		0, 1, 3,
		1, 2, 3,
	};

public:

	ID3D11Buffer* schlaegerBuffer = nullptr;
	ID3D11Buffer* schlaegerIndexBuffer = nullptr;

	//Position der Mitte des Schlägers
	float y;

	bat()
	{
		//Initializing the Coordinates
		y = 0;

		//Create Vertex Buffer
		schlaegerBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		schlaegerBufferDesc.ByteWidth = sizeof(Vertex) * 4;
		schlaegerBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		schlaegerData.pSysMem = Schlaeger;

		Get_Device()->CreateBuffer(&schlaegerBufferDesc, &schlaegerData, &schlaegerBuffer);

		//Create Index Buffer
		schlaegerIndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		schlaegerIndexBufferDesc.ByteWidth = sizeof(UINT) * 6;
		schlaegerIndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		schlaegerIndexData.pSysMem = SchlaegerIndex;

		Get_Device()->CreateBuffer(&schlaegerIndexBufferDesc, &schlaegerIndexData, &schlaegerIndexBuffer);
	};

	~bat()
	{
		schlaegerBuffer->Release();
		schlaegerIndexBuffer->Release();
	};

	ID3D11Buffer* Get_Schlaeger_Buffer();
	ID3D11Buffer* Get_Schlaeger_Index_Buffer();

};

