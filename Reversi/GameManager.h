/******************************************
*Ori Hirshfeld
*201085776
*Amichai Wollin
*300582392
******************************************/

#pragma once
#include "Board.h"
#include "LocalPlayer.h"
#include "AIPlayer.h"
#include "Logic.h"
class GameManager
{
public:
	//default constructor and destructor for gameManager
	GameManager();
	GameManager(Logic *logic, Player *player1, Player *player2);
	~GameManager();

	//announce the winner
	void announceWinner(Board *board);

	//this function contains the main loop of the game and runs the game
	void runGame();

private:
	Player *playerX;
	Player *playerO;
	Board board;
	Logic *gameLogic;
	char currentTurn;
	bool gameOver;
};
