#pragma once
#include <d3d11.h>
#include "Schlaeger.h"
#include "Ball.h"



void InitGame();
bool UpdateScene();
void ResetGame();
void Set_Game_Over(bool tmpBool);

bat* Get_Schlaeger_1();
bat* Get_Schlaeger_2();
ball* Get_Ball();
ID3D11Buffer* Get_Referenced_Buffer1();
ID3D11Buffer* Get_Referenced_Buffer2();
ID3D11Buffer* Get_Referenced_Buffer3();
ID3D11Buffer* GET_cbSchlaeger1();
ID3D11Buffer* GET_cbSchlaeger2();
ID3D11Buffer* GET_cbBall();
