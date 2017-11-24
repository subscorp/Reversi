/******************************************
*Ori Hirshfeld
*201085776
******************************************/

#include "Board.h"
#include<string>

using namespace std;

#pragma once
class Logic
{
public:
	//check if it is possible to put color on the current board at index i,j
	virtual bool isPossible(int x, int y, char color, Board *board) = 0;

	//prints the possible moves for color on the current board
	virtual void printPossibleMoves(char color, Board *board) = 0;

	//checks if the move color chose to make is valid
	virtual bool moveIsValid(char color, string input, Board *board) = 0;
};

