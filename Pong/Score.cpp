#include "Score.h"

int scoreLeft = 0;
int scoreRight = 0;


void Set_Score(string winner)
{
	if (winner == "left")
	{
		scoreLeft++;
	}

	if (winner == "right")
	{
		scoreRight++;
	}
}

int CheckScore(string player)
{
	if (player == "left")
	{
		return scoreLeft;
	}
	if (player == "right")
	{
		return scoreRight;
	}
}
