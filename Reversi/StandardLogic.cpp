
#include <iostream>
#include "StandardLogic.h"
#include "helper.h"
#include<vector>
using namespace std;


StandardLogic::StandardLogic()
{
}


StandardLogic::~StandardLogic()
{
}

bool StandardLogic::isPossible(int x, int y, char color, Board *board)
{
	char turnColor = (color == 'X') ? 'X' : 'O';
	char opponentColor = (color == 'X') ? 'O' : 'X';
	int i;

	if (!board->isCellEmpty(x, y)) return false; // we cannot place a pawn if there is allready a pawn in that cell

	/* now we want to check if the player of color 'color' can place a pawn in this cell
	we will check each direction to see if there is a squence of opposite color pawns in this direction,
	and if so , we will then check if after that sequence there is again the color of our current player.
	- if we will find a direction that will satisfy the above conditions then this means that this cell is valid for our current player to put his pawn on. */

	//CHECK NORTH
	i = 1;
	if (((x - i) >= 0)) // make sure we are not at the top border
		if (opponentColor == board->getCell(x - i, y))
		{ // there is indeed an opponent pawn in the cell above, possibly more then 1 , there can be a sequence
		  // now we will check if after this squence of opponents' pawns there is a pawn of our own color
			i++;
			while (!((x - i)<0)) {
				if (!board->isCellEmpty(x - i, y))
					if (turnColor == board->getCell(x - i, y)) // we have found our own Pawn after a series of opponents' pawns in the north direction. so this cell is legit for us.
						return true;
					else i++; // next tile to the north also has an opponents pawn in it, we keep climbing top in search for our own color.
				else i = board->getNumRows(); // if we reached the border
			}
		}

	//CHECK NORTH EAST
	i = 1;
	if (!((x - i)<0) && !((y + i)>board->getNumCols() - 1))
		if (opponentColor == board->getCell(x - i, y + i))
		{ //  there is an opponent tile in the north east of this tile
			i++;
			while (!((x - i)<0) && !((y + i)>board->getNumCols() - 1)) {
				if (!board->isCellEmpty(x - i, y + i))
					if (turnColor == board->getCell(x - i, y + i))
						return true;
					else i++;
				else i = board->getNumRows();
			}
		}

	//CHECK EAST
	i = 1;
	if (!((y + i)>board->getNumCols() - 1))
		if (opponentColor == board->getCell(x, y + i))
		{//  there is an opponent tile in the north of this tile
			i++;
			while (!((y + i)>board->getNumCols() - 1)) {
				if (!board->isCellEmpty(x, y + i))
					if (turnColor == board->getCell(x, y + i))
						return true;
					else i++;
				else i = board->getNumCols();
			}
		}

	//CHECK SOUTH EAST
	i = 1;
	if (!((x + i)>board->getNumRows() - 1) && !((y + i)>board->getNumCols() - 1))
		if (opponentColor == board->getCell(x + i, y + i))
		{//  there is an opponent tile in the south east of this tile
			i++;
			while (!((x + i)>board->getNumRows() - 1) && !((y + i)>board->getNumRows() - 1))
			{
				if (!board->isCellEmpty(x + i, y + i))
					if (turnColor == board->getCell(x + i, y + i))
						return true;
					else i++;
				else i = board->getNumRows();
			}
		}



	//CHECK SOUTH
	i = 1;
	if (!((x + i)>board->getNumRows() - 1))
		if (opponentColor == board->getCell(x + i, y))
		{//  there is an opponent tile in the south of this tile
			i++;
			while (!((x + i)>board->getNumRows() - 1)) {
				if (!board->isCellEmpty(x + i, y))
					if (turnColor == board->getCell(x + i, y))
						return true;
					else i++;
				else i = board->getNumRows();
			}
		}

	//CHECK SOUTH WEST
	i = 1;
	if (!((x + i)>board->getNumRows() - 1) && !((y - i)<0))
		if (opponentColor == board->getCell(x + i, y - i))
		{//  there is an opponent tile in the south west of this tile
			i++;
			while (!((x + i)>board->getNumRows() - 1) && !((y - i)<0)) {
				if (!board->isCellEmpty(x + i, y - i))
					if (turnColor == board->getCell(x + i, y - i))
						return true;
					else i++;
				else i = board->getNumRows();
			}
		}

	//CHECK WEST
	i = 1;
	if (!((y - i)<0))
		if (opponentColor == board->getCell(x, y - i))
		{ //  there is an opponent tile in the west of this tile
			i++;
			while (!((y - i)<0)) {
				if (!board->isCellEmpty(x, y - i))
					if (turnColor == board->getCell(x, y - i))
						return true;
					else i++;
				else i = board->getNumRows();
			}
		}

	//CHECK NORTH WEST
	i = 1;
	if (!((x - i)<0) && !((y - i)<0))
		if (opponentColor == board->getCell(x - i, y - i))
		{//  there is an opponent tile in the north west of this tile
			i++;
			while (!((x - i)<0) && !((y - i)<0)) {
				if (!board->isCellEmpty(x - i, y - i))
					if (turnColor == board->getCell(x - i, y - i))
						return true;
					else i++;
				else i = board->getNumRows();
			}
		}

	return false;
}


void StandardLogic::printPossibleMoves(char color, Board *board)
{
	for (int i = 1; i<board->getNumRows(); i++)
		for (int j = 1; j < board->getNumCols(); j++)
		{
			if (StandardLogic::isPossible(i, j, color, board))
				cout << "(" << i << "," << j << ")  ";
		}
	cout << endl;
}

void StandardLogic::getPossibleMoves(char color, Board *board, vector<location> *possibleMoves)
{
	location possibleMove;
	for (int i = 1; i<board->getNumRows(); i++)
		for (int j = 1; j < board->getNumCols(); j++)
		{
			if (StandardLogic::isPossible(i, j, color, board))
			{
				possibleMove.x = i;
				possibleMove.y = j;
				possibleMoves->push_back(possibleMove);
			}
		}
}

bool StandardLogic::moveIsValid(char color, string input, Board *board)
{
	if (input.length() != 3)
		return false;
	int i = (int)input[0] - 48;
	int j = (int)input[2] - 48;
	if (!(i > 0 && i < 9 && j > 0 && j < 9))
		return false;
	if (StandardLogic::isPossible(i, j, color, board))
		return true;
	else
		return false;
}
