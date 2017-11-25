/******************************************
*Ori Hirshfeld
*201085776
******************************************/

#include <iostream>
#include "AIPlayer.h"
#include "helper.h"
#include <vector>
using namespace std;


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

	logic->getPossibleMoves(color, board, &possibleMoves);
	if (canDoMove(board))
	{
		//temp commands
		move[0] = possibleMoves[1].x;
		move[1] = possibleMoves[1].y;
		cout << "AI choices are: ";
		logic->printPossibleMoves(color,board);
		cout << "AI played " << '(' <<possibleMoves[1].x
				<<',' <<possibleMoves[1].y << ')' << endl;
		possibleMoves.clear();
	}
	else
	{
		cout << "no moves available for " << color << endl << endl;
		move[0] = 0;
		move[1] = 0;
	}

}
