/******************************************
*Ori Hirshfeld
*201085776
*Amichai Wollin
*300582392
******************************************/

#pragma once
#include "Board.h"
#include "StandardLogic.h"
#include "Player.h"
#include "Client.h"
#include <stdlib.h>
#include<string>

using namespace std;

class RemotePlayer: public Player
{
public:
	//default constructor and destructor for LocalPlayer
	RemotePlayer();
	~RemotePlayer();

	//constructor for LocalPlayer that takes color and logic as parameters
	RemotePlayer(char color, Logic *logic, Client *client);

	//let the player make a move
	int* makeMove(Board *board, int* move);

private:
	Client *client;
};
