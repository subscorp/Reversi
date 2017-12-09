/******************************************
*Ori Hirshfeld
*201085776
*Amichai Wollin
*300582392
******************************************/

#include <iostream>
#include "AIPlayer.h"
#include "helper.h"
#include <vector>
using namespace std;


AIPlayer::AIPlayer()
{

}

AIPlayer::AIPlayer(char color, Logic *logic)
{
	this->color = color;
	this->logic = logic;
}

AIPlayer::~AIPlayer()
{

}

//let the AI player make a move
int* AIPlayer::makeMove(Board *board, int* move)
{
	int numMovesO;
	int numMovesX;
	int score;
	int max, min;
	int minIndex;
	Board boardCopy = *board;
	Board boardCopy2;

	//checks if the AI can make a move
	if (canDoMove(board))
	{
		//gets the possible moves for the AI
		logic->getPossibleMoves(color, board, &possibleMoves);
		numMovesO = possibleMoves.size();

		/*
		 * we perform each move in memory using copy constructors and give a score
		 * according to the instructions by checking every move X can make after the move
		 * performed by the AI
		 */
		for(int i=0; i<numMovesO;i++)
		{
			/*
			 * first we perform the move of the AI and save the state of the board
			 * in boardCopy
			 */
			possibleMoves.clear();
			logic->getPossibleMoves(color, board, &possibleMoves);
			boardCopy.setCell('O',possibleMoves[i].x,possibleMoves[i].y);
			boardCopy.flip(possibleMoves[i].x,possibleMoves[i].y,'O');

			/*
			 * now we use the vector possible moves for getting the possible moves
			 * of X on boardCopy
			 */
			possibleMoves.clear();
			logic->getPossibleMoves('X',&boardCopy,&possibleMoves);

			//checking each possible move X can do and computing the score
			numMovesX = possibleMoves.size();
			for(int j=0;j<numMovesX;j++)
			{
				//here we use another copy constructor to save the state of boardCopy
				boardCopy2 = boardCopy;
				boardCopy2.setCell('X',possibleMoves[j].x, possibleMoves[j].y);
				boardCopy2.flip(possibleMoves[j].x, possibleMoves[j].y,'X');

				//computing the score
				score = boardCopy2.getNumBlacks() - boardCopy2.getNumWhites();
				if(j == 0)
					max = score;

				if(score > max)
					max = score;

			}

			//handling the case that X has no moves after O moved
			if(numMovesX == 0)
			{
				max = boardCopy.getNumBlacks() - boardCopy.getNumWhites();
			}

			//more commands to compute the score according to the instructions
			if(i == 0)
			{
				min = max;
				minIndex = 0;
			}

			if(max < min)
			{
				min = max;
				minIndex = i;
			}

			//reseting boardCopy for the next possible move of the AI
			boardCopy = *board;
		}

		//finally we insert the move computed above into our move array
		possibleMoves.clear();
		logic->getPossibleMoves(color, board, &possibleMoves);
		move[0] = possibleMoves[minIndex].x;
		move[1] = possibleMoves[minIndex].y;

		//displaying the possible moves of the AI and the move the AI played
		cout << "O possible moves: ";
		logic->printPossibleMoves(color,board);
		cout << "O played " << '(' <<possibleMoves[minIndex].x
				<<',' <<possibleMoves[minIndex].y << ')' << endl;
		possibleMoves.clear();
	}

	//handles the case were the AI has no moves available
	else
	{
		cout << "no moves available for " << color << endl << endl;
		move[0] = 0;
		move[1] = 0;
	}

	//return the move, mostly for unit testing and debug
	return move;
}
