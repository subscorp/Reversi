/******************************************
*Ori Hirshfeld
*201085776
******************************************/

#pragma once
#include "Board.h"
#include "Logic.h"
#include<string>

using namespace std;

class StandardLogic: public Logic
{
public:
	//default constructor and destructor for StandardLogic
	StandardLogic();
	~StandardLogic();

	//check if it is possible to put color on the current board at index i,j according to standard rules
	bool isPossible(int x, int y, char color, Board *board);

	//prints the possible moves for color on the current board according to standard rules
	void printPossibleMoves(char color, Board *board);

	//checks if the move color chose to make is valid according to standard rules
	bool moveIsValid(char color, string input, Board *board);
};

