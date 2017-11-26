/******************************************
*Ori Hirshfeld
*201085776
******************************************/

#include <iostream>
#include "AIPlayer.h"
#include "helper.h"
#include <vector>
using namespace std;


AIPlayer::AIPlayer()
{
	// TODO Auto-generated constructor stub

}

AIPlayer::AIPlayer(char color, Logic *logic)
{
	this->color = color;
	this->logic = logic;
}

AIPlayer::~AIPlayer()
{
	// TODO Auto-generated destructor stub
}

//checks if the player can make a move on the current board
bool AIPlayer::canDoMove(Board *board)
{
	for (int i = 1; i<board->getNumRows(); i++)
		for (int j = 1; j < board->getNumCols(); j++)
		{
			if (logic->isPossible(i, j, color, board))
				return true;
		}
	return false;
}

//let the player make a move
void AIPlayer::makeMove(Board *board, int* move)
{
	int numMovesO;
	int numMovesX;
	int score;
	int max, min;
	int minIndex;
	Board boardCopy = *board;
	Board boardCopy2;

	//cout << "testing boardCopy by placing something at 7,7 " << endl;
	//boardCopy.setCell('X',7,7);
	//boardCopy.printBoard();
	//numBlacks = boardCopy.getNumBlacks();
	//numWhites = boardCopy.getNumWhites();
	//cout <<"boardCopy stats: numBlacks is " << numBlacks << " numWhites is " << numWhites <<endl;
	//cout << "checking if board has changed: " << endl;
	//board->printBoard();
	//numBlacks = board->getNumBlacks();
	//numWhites = board->getNumWhites();
	//cout <<"original board stats: numBlacks is " << numBlacks << " numWhites is " << numWhites <<endl;
	//cout << "after check" << endl;

	//logic->getPossibleMoves(color, board, &possibleMoves);
	if (canDoMove(board))
	{
		logic->getPossibleMoves(color, board, &possibleMoves);
		numMovesO = possibleMoves.size();

		for(int i=0; i<numMovesO;i++)
		{
			possibleMoves.clear();
			logic->getPossibleMoves(color, board, &possibleMoves);

			cout << "checking state for possibleMove " << i << ":" << endl;
			boardCopy.setCell('O',possibleMoves[i].x,possibleMoves[i].y);
			boardCopy.flip(possibleMoves[i].x,possibleMoves[i].y,'O');
			boardCopy.printBoard();
			possibleMoves.clear();
			logic->getPossibleMoves('X',&boardCopy,&possibleMoves);
			numMovesX = possibleMoves.size();
			cout << "possible moves for X given this move are: " << endl;
			for(int j=0;j<numMovesX;j++)
			{
				boardCopy2 = boardCopy;
				cout << possibleMoves[j].x << " " << possibleMoves[j].y << endl;
				boardCopy2.setCell('X',possibleMoves[j].x, possibleMoves[j].y);
				boardCopy2.flip(possibleMoves[j].x, possibleMoves[j].y,'X');
				score = boardCopy2.getNumBlacks() - boardCopy2.getNumWhites();
				if(j == 0)
					max = score;

				if(score > max)
					max = score;
				cout << "current max: " << max << endl;

			}
			if(numMovesX == 0)
			{
				max = boardCopy.getNumBlacks() - boardCopy.getNumWhites();
			}
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
			cout << " current min: " << min << endl;
			//boardCopy.printBoard();
			//score = boardCopy.getNumWhites() - boardCopy.getNumBlacks();
			//cout << "the score is: " << score << endl;
			boardCopy = *board;
			//if(score > max)
			//{
				//max = score;
				//maxIndex = i;
			//}
		}
		possibleMoves.clear();
		logic->getPossibleMoves(color, board, &possibleMoves);

		//temp commands
		move[0] = possibleMoves[minIndex].x;
		move[1] = possibleMoves[minIndex].y;
		cout << "AI choices are: ";
		logic->printPossibleMoves(color,board);
		cout << "AI played " << '(' <<possibleMoves[minIndex].x
				<<',' <<possibleMoves[minIndex].y << ')' << endl;
		possibleMoves.clear();
	}
	else
	{
		cout << "no moves available for " << color << endl << endl;
		move[0] = 0;
		move[1] = 0;
	}

}
