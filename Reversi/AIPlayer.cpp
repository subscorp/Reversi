/******************************************
*Ori Hirshfeld
*201085776
******************************************/

#include <iostream>
using namespace std;
#include "AIPlayer.h"

AIPlayer::AIPlayer()
{
	// TODO Auto-generated constructor stub

}

AIPlayer::AIPlayer(char color, Logic *logic)
{
	this->color = color;
	this->logic = logic;
}

AIPlayer::~AIPlayer()
{
	// TODO Auto-generated destructor stub
}

//checks if the player can make a move on the current board
bool AIPlayer::canDoMove(Board *board)
{
	for (int i = 1; i<board->getNumRows(); i++)
		for (int j = 1; j < board->getNumCols(); j++)
		{
			if (logic->isPossible(i, j, color, board))
				return true;
		}
	return false;
}

//let the player make a move
void AIPlayer::makeMove(Board *board, int* move)
{
	if (canDoMove(board))
	{
		cout << "AI moved..." << endl;

		//temp commands
		move[0] = 0;
		move[1] = 0;
	}
	else
	{
		cout << "no moves available for " << color << endl << endl;
		move[0] = 0;
		move[1] = 0;
	}

}
