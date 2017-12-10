/******************************************
*Ori Hirshfeld
*201085776
*Amichai Wollin
*300582392
******************************************/

#include "Board.h"
#include "StandardLogic.h"
#include "Logic.h"
#pragma once
class Player
{
public:
	//default constructor for Player
	Player();

	//set the color of player
	void setColor(char color);

	//checks if the player can make a move on the current board
	bool canDoMove(Board *board);

	//let the player make a move
	virtual int* makeMove(Board *board, int* move) = 0;

	char getColor() { return color; }
	//virtual void connectToServer() = 0;
	//virtual int sendExercise(int arg1, char op, int arg2) = 0;
protected:
	char color;
	Logic *logic;
};

