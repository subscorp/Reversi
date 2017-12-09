/******************************************
*Ori Hirshfeld
*201085776
*Amichai Wollin
*300582392
******************************************/

#include "Player.h"
#include "Logic.h"


Player::Player()
{
}

void Player::setColor(char color)
{
	this->color = color;
}

bool Player::canDoMove(Board *board)
{
	for (int i = 1; i<board->getNumRows(); i++)
			for (int j = 1; j < board->getNumCols(); j++)
			{
				if (logic->isPossible(i, j, color, board))
					return true;
			}
	return false;
}



