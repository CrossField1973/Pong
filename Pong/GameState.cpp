#include "GameState.h"
#include "Schlaeger.h"
#include "Renderer.h"
#include "Ball.h"
#include <DirectXMath.h>
#include <d3d11.h>
#include "Physics.h"

bool gameOver = false;

struct cbBat
{
	XMMATRIX Transformation;
};


ID3D11Buffer* referencedBuffer1 = nullptr;
ID3D11Buffer* referencedBuffer2 = nullptr;
ID3D11Buffer* referencedBuffer3 = nullptr;

ID3D11Buffer* cbSchlaeger1 = nullptr;
ID3D11Buffer* cbSchlaeger2 = nullptr;
ID3D11Buffer* cbBall = nullptr;

cbBat cBuffer1 = { };
cbBat cBuffer2 = { };
cbBat cBall = { };

bat* pSchlaeger1;
bat* pSchlaeger2;
ball* pBall;

void InitGame()
{
	Set_Shaders();

	Set_Input_Layout();

	Get_Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//Create Constant Buffer
	D3D11_BUFFER_DESC cbSchlaeger1_Desc = { };
	
	cbSchlaeger1_Desc.Usage = D3D11_USAGE_DEFAULT;
	cbSchlaeger1_Desc.ByteWidth = sizeof(cbBat);
	cbSchlaeger1_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	Get_Device()->CreateBuffer(&cbSchlaeger1_Desc, NULL, &cbSchlaeger1);


	D3D11_BUFFER_DESC cbSchlaeger2_Desc = { };

	cbSchlaeger2_Desc.Usage = D3D11_USAGE_DEFAULT;
	cbSchlaeger2_Desc.ByteWidth = sizeof(cbBat);
	cbSchlaeger2_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	Get_Device()->CreateBuffer(&cbSchlaeger2_Desc, NULL, &cbSchlaeger2);


	D3D11_BUFFER_DESC cbBall_Desc = { };

	cbBall_Desc.Usage = D3D11_USAGE_DEFAULT;
	cbBall_Desc.ByteWidth = sizeof(cbBat);
	cbBall_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	Get_Device()->CreateBuffer(&cbBall_Desc, NULL, &cbBall);


	//Initialize Constant Buffer
	XMMATRIX World1 = XMMatrixTranslation(0.8f - 0.025f, -0.15f, 0.0f);
	XMMATRIX World2 = XMMatrixTranslation(-0.8f - 0.025f, -0.15f, 0.0f);
	XMMATRIX World3 = XMMatrixTranslation(-0.05f, -0.05f, 0.0f);

	cBuffer1.Transformation = XMMatrixTranspose(World1);
	cBuffer2.Transformation = XMMatrixTranspose(World2);
	cBall.Transformation = XMMatrixTranspose(World3);

	/*Get_Context()->UpdateSubresource(cbSchlaeger1, 0, NULL, &cBuffer1, 0, 0);
	Get_Context()->UpdateSubresource(cbSchlaeger2, 0, NULL, &cBuffer2, 0, 0);

	Get_Context()->VSSetConstantBuffers(0, 1, &cbSchlaeger1);
	Get_Context()->VSSetConstantBuffers(1, 1, &cbSchlaeger2);*/
}


bool UpdateScene()
{

	static bat schlaeger1;
	static bat schlaeger2;
	static ball balli;

	pSchlaeger1 = &schlaeger1;
	pSchlaeger2 = &schlaeger2;
	pBall = &balli;


	UINT Stride = sizeof(Vertex);
	UINT Offset = 0;

	referencedBuffer1 = schlaeger1.Get_Schlaeger_Buffer();
	referencedBuffer2 = schlaeger1.Get_Schlaeger_Buffer();
	referencedBuffer3 = balli.Get_ball_Buffer();

	CheckBall(&balli);

	XMMATRIX World1 = XMMatrixTranslation(0.8f - 0.025f, -0.15f + Get_Schlaeger_1()->y, 0.0f);
	XMMATRIX World2 = XMMatrixTranslation(-0.8f - 0.025f, -0.15f + Get_Schlaeger_2()->y, 0.0f);
	XMMATRIX World3 = XMMatrixTranslation(-0.05f + balli.x, -0.05f + balli.y, 0.0f);


	cBuffer1.Transformation = XMMatrixTranspose(World1);
	cBuffer2.Transformation = XMMatrixTranspose(World2);
	cBall.Transformation = XMMatrixTranspose(World3);

	//Draw Schlaeger1
	Get_Context()->IASetVertexBuffers(0, 1, &referencedBuffer1, &Stride, &Offset);
	Get_Context()->IASetIndexBuffer(Get_Schlaeger_1()->Get_Schlaeger_Index_Buffer(), DXGI_FORMAT_R32_UINT, 0);
	Get_Context()->UpdateSubresource(cbSchlaeger1, 0, NULL, &cBuffer1, 0, 0);
	Get_Context()->VSSetConstantBuffers(0, 1, &cbSchlaeger1);

	Get_Context()->DrawIndexed(6, 0, 0);

	//Draw Schlaeger2
	Get_Context()->IASetVertexBuffers(0, 1, &referencedBuffer2, &Stride, &Offset);
	Get_Context()->IASetIndexBuffer(Get_Schlaeger_2()->Get_Schlaeger_Index_Buffer(), DXGI_FORMAT_R32_UINT, 0);
	Get_Context()->UpdateSubresource(cbSchlaeger2, 0, NULL, &cBuffer2, 0, 0);
	Get_Context()->VSSetConstantBuffers(0, 1, &cbSchlaeger2);

	Get_Context()->DrawIndexed(6, 0, 0);

	//Draw Balli
	Get_Context()->IASetVertexBuffers(0, 1, &referencedBuffer3, &Stride, &Offset);
	Get_Context()->IASetIndexBuffer(Get_Ball()->Get_ball_Index_Buffer(), DXGI_FORMAT_R32_UINT, 0);
	Get_Context()->UpdateSubresource(cbBall, 0, NULL, &cBall, 0, 0);
	Get_Context()->VSSetConstantBuffers(0, 1, &cbBall);

	Get_Context()->DrawIndexed(24, 0, 0);

	return !gameOver;
}

void ResetGame()
{
	//Reset Ball Position and Direction
	Get_Ball()->x = 0;
	Get_Ball()->y = 0;

	srand(time(NULL));
	int i = (rand() % 360) - 180;//0° bis 179°
	int i2 = (rand() % 360) - 180;//0° bis 179°
	float j = 1.0f / i;
	float j2 = 1.0f / i2;

	//Betrag des 2D Vektors
	float betrag = sqrtf(j * j + j2 * j2);


	Get_Ball()->direction = { j / betrag, j2 / betrag };

	//Reset Bat Position
	Get_Schlaeger_1()->y = 0;
	Get_Schlaeger_2()->y = 0;

}

void Set_Game_Over(bool tmpBool)
{
	gameOver = tmpBool;
}

bat * Get_Schlaeger_1()
{
	return pSchlaeger1;
}

bat * Get_Schlaeger_2()
{
	return pSchlaeger2;
}

ball * Get_Ball()
{
	return pBall;
}

ID3D11Buffer * Get_Referenced_Buffer1()
{
	return referencedBuffer1;
}

ID3D11Buffer * Get_Referenced_Buffer2()
{
	return referencedBuffer2;
}

ID3D11Buffer * Get_Referenced_Buffer3()
{
	return referencedBuffer3;
}

ID3D11Buffer * GET_cbSchlaeger1()
{
	return cbSchlaeger1;
}

ID3D11Buffer * GET_cbSchlaeger2()
{
	return cbSchlaeger2;
}

ID3D11Buffer * GET_cbBall()
{
	return cbBall;
}
