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
#include <string>
#include <vector>
#include "helper.h"
using namespace std;

#ifndef AIPLAYER_H_
#define AIPLAYER_H_

class AIPlayer: public Player
{
public:
	AIPlayer();
	AIPlayer(char color, Logic *logic);
	virtual ~AIPlayer();

	//let the player make a move
	int* makeMove(Board *board, int* move);
private:
	vector<location> possibleMoves;

};

#endif /* AIPLAYER_H_ */
