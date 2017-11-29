/******************************************
*Ori Hirshfeld
*201085776
******************************************/

#pragma once
#include "Board.h"
#include "StandardLogic.h"
#include "Player.h"
#include<string>

using namespace std;

class LocalPlayer: public Player
{
public:
	//default constructor and destructor for LocalPlayer
	LocalPlayer();
	~LocalPlayer();

	//constructor for LocalPlayer that takes color and logic as parameters
	LocalPlayer(char color, Logic *logic);

	//checks if the player can make a move on the current board
	bool canDoMove(Board *board);

	//let the player make a move
	int* makeMove(Board *board, int* move);
};


