#pragma once
#include "Structures.h"
#include "Renderer.h"
#include <d3d11.h>

class bat 
{
	ID3D11Buffer* schlaegerBuffer = nullptr;
	ID3D11Buffer* schlaegerIndexBuffer = nullptr;
	D3D11_BUFFER_DESC schlaegerBufferDesc = { };
	D3D11_BUFFER_DESC schlaegerIndexBufferDesc = { };
	D3D11_SUBRESOURCE_DATA schlaegerData = { };
	D3D11_SUBRESOURCE_DATA schlaegerIndexData = { };

	Vertex Schlaeger[4] =
	{
		XMFLOAT4(0, 3, 0, 1), XMFLOAT4(1, 1, 1, 1),
		XMFLOAT4(1, 3, 0, 1), XMFLOAT4(1, 1, 1, 1),
		XMFLOAT4(1, 0, 0, 1), XMFLOAT4(1, 1, 1, 1),
		XMFLOAT4(1, 0, 0, 1), XMFLOAT4(1, 1, 1, 1),
	};

	
	UINT SchlaegerIndex[] =
	{
		0, 1, 3,
		1, 2, 3,
	};

public:
	bat()
	{
		//Create Vertex Buffer
		schlaegerBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		schlaegerBufferDesc.ByteWidth = sizeof(Vertex) * 4;
		schlaegerBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		schlaegerData.pSysMem = Schlaeger;

		Get_Device()->CreateBuffer(&schlaegerBufferDesc, &schlaegerData, &schlaegerBuffer);

		//Create Index Buffer
		schlaegerIndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		schlaegerIndexBufferDesc.ByteWidth = sizeof(Vertex) * 4;
		schlaegerIndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		schlaegerIndexData.pSysMem = SchlaegerIndex;

		Get_Device()->CreateBuffer(&schlaegerIndexBufferDesc, &schlaegerIndexData, &schlaegerIndexBuffer);
	};

	~bat()
	{
		schlaegerBuffer->Release();
		schlaegerIndexBuffer->Release();
	};

	ID3D11Buffer* Get_Schlaeger_Bufffer();
	ID3D11Buffer* Get_Schlaeger_Index_Buffer();

};

