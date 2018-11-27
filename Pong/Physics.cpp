#include "Physics.h"
#include "GameState.h"
#include "Score.h"

void CheckBall(ball * balli)
{

	//Left Boundary 
	if (balli->x - 0.05 <= -1)
	{
		Set_Score("right");

		if (CheckScore("right") == 3)
		{
			Set_Game_Over(true);
		}

		ResetGame();
	}

	//Right Boundary
	if (balli->x + 0.05 >= 1)
	{
		Set_Score("left");
		
		if (CheckScore("left") == 3)
		{
			Set_Game_Over(true);
		}

		ResetGame();
	}

	//Top Boundary
	if (balli->y + 0.05 >= 1)
	{
		balli->direction.y = -balli->direction.y;
	}

	//Bottom Boundary
	if (balli->y - 0.05 <= -1)
	{
		balli->direction.y = -balli->direction.y;
	}

	//Schlaeger1
	if(balli->y <= (Get_Schlaeger_1()->y + 0.15) && balli->y >= (Get_Schlaeger_1()->y - 0.15) && balli->x >= 0.75 && balli->x <= 0.85)
	{
		balli->direction.x = -balli->direction.x;
		/*balli->direction.y = -balli->direction.y;*/
	}

	//Schlaeger2 
	if (balli->y <= (Get_Schlaeger_2()->y + 0.15) && balli->y >= (Get_Schlaeger_2()->y - 0.15) && balli->x <= -0.75 && balli->x >= -0.85)
	{
		balli->direction.x = -balli->direction.x;
		/*balli->direction.y = -balli->direction.y;*/
	}

	balli->x += balli->direction.x * balli->velocity;
	balli->y += balli->direction.y * balli->velocity;

}


