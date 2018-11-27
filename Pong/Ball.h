#pragma once
#include <d3d11.h>
#include "Structures.h"
#include <DirectXMath.h>
#include "Renderer.h"
#include <time.h>
using namespace DirectX;

class ball
{
	D3D11_BUFFER_DESC ballBufferDesc = { };
	D3D11_BUFFER_DESC ballIndexBufferDesc = { };
	D3D11_SUBRESOURCE_DATA ballData = { };
	D3D11_SUBRESOURCE_DATA ballIndexData = { };

	Vertex Ball[9] =
	{
		//Westen
		XMFLOAT4(0.01f, 0.05f, 0.0f, 1.0f), XMFLOAT4(0.3f, 0.3f, 0.3f, 1),

		//Nordwest
		XMFLOAT4(0.02f, 0.09f, 0.0f, 1.0f), XMFLOAT4(0.3f, 0.3f, 0.3f, 1),
		
		//Norden
		XMFLOAT4(0.05f, 0.1f, 0.0f, 1.0f), XMFLOAT4(0.3f, 0.3f, 0.3f, 1),
		
		//Nordost
		XMFLOAT4(0.08f, 0.09f, 0.0f, 1.0f), XMFLOAT4(0.3f, 0.3f, 0.3f, 1),

		//Osten
		XMFLOAT4(0.09f, 0.05f, 0.0f, 1.0f), XMFLOAT4(0.3f, 0.3f, 0.3f, 1),

		//Südost
		XMFLOAT4(0.08f, 0.01f, 0.0f, 1.0f), XMFLOAT4(0.3f, 0.3f, 0.3f, 1),

		//Süden
		XMFLOAT4(0.05f, 0.0f, 0.0f, 1.0f), XMFLOAT4(0.3f, 0.3f, 0.3f, 1),

		//Südwest
		XMFLOAT4(0.02f, 0.01f, 0.0f, 1.0f), XMFLOAT4(0.3f, 0.3f, 0.3f, 1),

		//Mittelpunkt der Erde
		XMFLOAT4(0.05f, 0.05f, 0.0f, 1.0f), XMFLOAT4(0.3f, 0.3f, 0.3f, 1),
	};


	UINT ballIndex[24] =
	{
		0, 1, 8,
		1, 2, 8,
		2, 3, 8,
		3, 4, 8,
		4, 5, 8,
		5, 6, 8,
		6, 7, 8,
		7, 0, 8
	};

public:

	ID3D11Buffer* ballBuffer = nullptr;
	ID3D11Buffer* ballIndexBuffer = nullptr;

	//Position der Mitte des Schlägers
	float y;
	float x;
	XMFLOAT2 direction;
	float velocity;

	ball()
	{
		//Initializing the Coordinates
		y = 0;
		x = 0;
		
		srand(time(NULL));
		int i = (rand() % 360) - 180;//0° bis 179°
		int i2 = (rand() % 360) - 180;//0° bis 179°
		float j = 1.0f / i;
		float j2 = 1.0f / i2;

		//Betrag des 2D Vektors
		float betrag = sqrtf(j * j + j2 * j2);


		direction = { j / betrag, j2 / betrag };
		velocity = 0.001;

		//Create Vertex Buffer
		ballBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		ballBufferDesc.ByteWidth = sizeof(Vertex) * 9;
		ballBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		ballData.pSysMem = Ball;

		Get_Device()->CreateBuffer(&ballBufferDesc, &ballData, &ballBuffer);

		//Create Index Buffer
		ballIndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ballIndexBufferDesc.ByteWidth = sizeof(UINT) * 24;
		ballIndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		ballIndexData.pSysMem = ballIndex;

		Get_Device()->CreateBuffer(&ballIndexBufferDesc, &ballIndexData, &ballIndexBuffer);
	};

	~ball()
	{
		ballBuffer->Release();
		ballIndexBuffer->Release();
	};

	ID3D11Buffer* Get_ball_Buffer();
	ID3D11Buffer* Get_ball_Index_Buffer();
};