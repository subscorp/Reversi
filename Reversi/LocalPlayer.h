
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

	//let the player make a move
	int* makeMove(Board *board, int* move);
};


