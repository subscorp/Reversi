/******************************************
*Ori Hirshfeld
*201085776
*Amichai Wollin
*300582392
******************************************/

#include <iostream>
using namespace std;
#include "LocalPlayer.h"

LocalPlayer::LocalPlayer()
{
}

LocalPlayer::LocalPlayer(char color, Logic *logic)
{
	this->color = color;
	this->logic = logic;
}

LocalPlayer::~LocalPlayer()
{
}


bool LocalPlayer::canDoMove(Board *board)
{
	for (int i = 1; i<board->getNumRows(); i++)
		for (int j = 1; j < board->getNumCols(); j++)
		{
			if (logic->isPossible(i, j, color, board))
				return true;
		}
	return false;
}


int* LocalPlayer:: makeMove(Board *board, int* move)
{
	string input;
	if (canDoMove(board))
	{
		cout << color << ": it's your move." << endl;
		do {
			cout << "your possible moves: ";
			logic->printPossibleMoves(color, board);
			cout << "please insert move in the form \"row col\" and press enter" << endl;
			cout << endl;
			std::getline(std::cin, input);
		} while (!logic->moveIsValid(color, input, board));
		move[0] = (int)input[0] - 48;
		move[1] = (int)input[2] - 48;
	}
	else
	{
		cout << "no moves available for " << color << endl << endl;
		move[0] = 0;
		move[1] = 0;
	}
	//only for debuging
	return move;
}

