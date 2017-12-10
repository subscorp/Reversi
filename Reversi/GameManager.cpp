/******************************************
*Ori Hirshfeld
*201085776
*Amichai Wollin
*300582392
******************************************/

#include <iostream>
using namespace std;
#include "GameManager.h"
#include "Board.h"


GameManager::GameManager()
{
	currentTurn = 'X';
	gameOver = false;
	gameLogic = new StandardLogic();
	playerX = new  LocalPlayer('X', gameLogic);
	playerO = new LocalPlayer('O', gameLogic);
}
GameManager::GameManager(Logic *logic, Player *player1, Player *player2)
{
	currentTurn = 'X';
	gameOver = false;
	gameLogic = logic;
	if (player1->getColor() == 'X') {
		playerX = player1;
		playerO = player2;
	}
	else {
		playerX = player2;
		playerO = player1;
	}
}

GameManager::~GameManager()
{
	delete[] playerX;
	delete[] playerO;
	delete[] gameLogic;
}

void GameManager::runGame()
{
	int* move = new int[2];
	move[0] = 1;
	move[1] = 1;
	bool xCanMove;
	bool oCanMove;

	// THIS IS THE GAME LOOP
	while (!gameOver)
	{

		// Print the game board
		board.printBoard();

		// Let playerX play, if it's his turn
		if (currentTurn == 'X')
		{
			playerX->makeMove(&board, move);

			//according to the check we do inside makeMove
			if (move[0] != 0 && move[1] != 0)
			{
				xCanMove = true;
				int i = move[0];
				int j = move[1];
				board.setCell(currentTurn, i, j);
				board.flip(i, j, currentTurn);
				cout << endl;
			}
			else
				xCanMove = false;

			currentTurn = 'O';
		}

		// Let playerO play, if it's his turn
		else
		{
			playerO->makeMove(&board, move);

			//according to the check we do inside makeMove
			if (move[0] != 0 && move[1] != 0)
			{
				oCanMove = true;
				int i = move[0];
				int j = move[1];
				board.setCell(currentTurn, i, j);
				board.flip(i, j, currentTurn);
				cout << endl;
			}
			else
				oCanMove = false;

			currentTurn = 'X';
		}
		if (board.isFull() || (!xCanMove && !oCanMove))
			gameOver = true;
	}
	delete[] move;
	board.printBoard();
	cout << endl;
	announceWinner(&board);
}


void GameManager::announceWinner(Board *board)
{
	char winner = ' ';
	if (board->getNumBlacks() > board->getNumWhites())
	{
		winner = 'X';
	}
	else if (board->getNumBlacks() < board->getNumWhites())
	{
		winner = 'O';
	}
	else
		winner = 'T';
	cout << "X score is: " << board->getNumBlacks() << endl;
	cout << "O score is: " << board->getNumWhites() << endl;
	if (winner != 'T')
		cout << "the winner is: " << winner << '!' << endl;
	else
		cout << "it's a tie!" << endl;
}
