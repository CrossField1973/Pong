#include "SetupGame.h"
#include "Schlaeger.h"
#include "Ball.h"

void InitGame()
{
	bat schlaeger1;	
	bat schlaeger2;

	UINT Stride;
	UINT Offset;

	Get_Context()->IASetVertexBuffers(0, 1, &schlaeger1.Get_Schlaeger_Bufffer, &Stride, &Offset);
	Get_Context()->IASetVertexBuffers(1, 1, &schlaeger2.Get_Schlaeger_Bufffer, &Stride, &Offset);

	Get_Context()->IASetIndexBuffer(&schlaeger1.Get_Schlaeger_Index_Buffer, DXGI_FORMAT_R16_UINT, Offset);
	Get_Context()->IASetIndexBuffer(&schlaeger1.Get_Schlaeger_Index_Buffer, DXGI_FORMAT_R16_UINT, Offset);

	Get_Context()->IASetInputLayout();//
	Get_Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
}
