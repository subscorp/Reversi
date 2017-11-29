/******************************************
*Ori Hirshfeld
*201085776
*Amichai Wollin
*300582392
******************************************/

#include "Board.h"
#include <string>
#include <vector>
#include "helper.h"

using namespace std;

#pragma once
class Logic
{
public:
	//check if it is possible to put color on the current board at index i,j
	virtual bool isPossible(int x, int y, char color, Board *board) = 0;

	//prints the possible moves for color on the current board
	virtual void printPossibleMoves(char color, Board *board) = 0;

	//gets the possible moves for color on the current board according to the standard rules
	virtual void getPossibleMoves(char color, Board *board, vector<location> *possibleMoves) = 0;

	//checks if the move color chose to make is valid
	virtual bool moveIsValid(char color, string input, Board *board) = 0;
};

