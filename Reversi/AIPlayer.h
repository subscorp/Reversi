/******************************************
*Ori Hirshfeld
*201085776
******************************************/

#pragma once
#include "Board.h"
#include "StandardLogic.h"
#include "Player.h"
#include<string>

#ifndef AIPLAYER_H_
#define AIPLAYER_H_

class AIPlayer: public Player
{
public:
	AIPlayer();
	AIPlayer(char color, Logic *logic);
	virtual ~AIPlayer();


	//checks if the player can make a move on the current board
	bool canDoMove(Board *board);

	//let the player make a move
	void makeMove(Board *board, int* move);
};

#endif /* AIPLAYER_H_ */
