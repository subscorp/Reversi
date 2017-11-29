/******************************************
*Ori Hirshfeld
*201085776
*Amichai Wollin
*300582392
******************************************/

#include <iostream>
using namespace std;
#include "Board.h"

Board::Board()
{
	numRows = 9;
	numCols = 9;
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			boardArr[i][j] = ' ';
		}
	}
	boardArr[3][3] = 'O'; boardArr[4][4] = 'O';
	boardArr[3][4] = 'X'; boardArr[4][3] = 'X';
	numBlacks = 2; numWhites = 2;
}

Board::Board(int numRows, int numCols)
{

}

int Board::getNumCols() const
{
	return numCols;
}

void Board::setNumCols(int numCols)
{
	this->numCols = numCols;
}

int Board::getNumRows() const
{
	return numRows;
}

void Board::setNumRows(int numRows)
{
	this->numRows = numRows;
}

void Board::printBoard() const
{
	cout << "Current board:" << endl << endl;
	cout << ' ';
	for (int i = 1; i < numRows; i++)
	{
		cout << '|' << i;
	}
	cout << '|' << endl;
	cout << "------------------" << endl;
	for (int i = 0; i < numRows - 1; i++)
	{
		cout << i + 1;
		for (int j = 0; j < numCols; j++)
		{
			cout << '|' << boardArr[i][j];
		}
		cout << endl;
		cout << "------------------" << endl;
	}
}

void Board::setCell(char color, int i, int j)
{

	if (color == 'X' && boardArr[i-1][j-1] == ' ')
	{
		numBlacks++;
	}
	else if (color == 'X' && boardArr[i - 1][j - 1] == 'O')
	{
		numBlacks++;
		numWhites--;
	}
	else if(color == 'O' && boardArr[i-1][j-1] == ' ')
	{
		numWhites++;
	}
	else if (color == 'O' && boardArr[i - 1][j - 1] == 'X')
	{
		numWhites++;
		numBlacks--;
	}
	boardArr[i - 1][j - 1] = color;
}

char Board::getCell(int i, int j)
{
	return boardArr[i-1][j-1];
}

int Board::getNumWhites()
{
	return numWhites;
}

int Board::getNumBlacks()
{
	return numBlacks;
}

bool Board::isFull()
{
	return ((numWhites + numBlacks) == 64);
}

bool Board::isCellEmpty(int i, int j)
{
	return (boardArr[i - 1][j - 1] == ' ');
}


//this function gets the place in which we placed a pawn and checks all the directions in order to flip pawns
void Board::flip(int x, int y, char color)
{
	char turnColor = (color == 'X') ? 'X' : 'O';
	char opponentColor = (color == 'X') ? 'O' : 'X';
	int i;
	bool validFlipDirection;

	//CHECK NORTH
	validFlipDirection = false;

	if (x - 1 > 0)
	{
		if (getCell(x - 1, y) == opponentColor)
		{
			i = 2;
			while (x - i > 0)
			{
				if (getCell(x - i, y) == ' ')
				{
					validFlipDirection = false;
					break;
				}
				if (getCell(x - i, y) == turnColor)
				{
					validFlipDirection = true;
					break;
				}
				i++;
			}
			if (validFlipDirection)
			{
				i = 1;
				while (getCell(x - i, y) == opponentColor)
				{
					setCell(turnColor, x - i, y);
					i++;
				}
			}
		}
	}
	//CHECK NORTH EAST
	validFlipDirection = false;
	if (x - 1 > 0 && y + 1 < numCols)
	{
		if (getCell(x - 1, y + 1) == opponentColor)
		{
			i = 2;
			while (x - i > 0 && y + i < numCols)
			{
				if (getCell(x - i, y + i) == ' ')
				{
					validFlipDirection = false;
					break;
				}
				if (getCell(x - i, y + i) == turnColor)
				{
					validFlipDirection = true;
					break;
				}
				i++;
			}
			if (validFlipDirection)
			{
				i = 1;
				while (getCell(x - i, y + i) == opponentColor)
				{
					setCell(turnColor, x - i, y + i);
					i++;
				}
			}
		}
	}

	//CHECK EAST
	validFlipDirection = false;
	if (y + 1 < numCols)
	{
		if (getCell(x, y + 1) == opponentColor)
		{
			i = 2;
			while (y + i < numCols)
			{
				if (getCell(x, y + i) == ' ')
				{
					validFlipDirection = false;
					break;
				}
				if (getCell(x, y + i) == turnColor)
				{
					validFlipDirection = true;
					break;
				}
				i++;
			}
			if (validFlipDirection)
			{
				i = 1;
				while (getCell(x, y + i) == opponentColor)
				{
					setCell(turnColor, x, y + i);
					i++;
				}
			}
		}
	}

	//CHECK SOUTH EAST
	validFlipDirection = false;
	if (x + 1 < numRows && y + 1 < numCols)
	{
		if (getCell(x + 1, y + 1) == opponentColor)
		{
			i = 2;
			while (x + i < numRows && y + i < numCols)
			{
				if (getCell(x + i, y + i) == ' ')
				{
					validFlipDirection = false;
					break;
				}
				if (getCell(x + i, y + i) == turnColor)
				{
					validFlipDirection = true;
					break;
				}
				i++;
			}
			if (validFlipDirection)
			{
				i = 1;
				while (getCell(x + i, y + i) == opponentColor)
				{
					setCell(turnColor, x + i, y + i);
					i++;
				}
			}
		}
	}

	//CHECK SOUTH
	validFlipDirection = false;
	if (x + 1 < numRows)
	{
		if (getCell(x + 1, y) == opponentColor)
		{
			i = 2;
			while (x + i < numRows)
			{
				if (getCell(x + i, y) == ' ')
				{
					validFlipDirection = false;
					break;
				}
				if (getCell(x + i, y) == turnColor)
				{
					validFlipDirection = true;
					break;
				}
				i++;
			}
			if (validFlipDirection)
			{
				i = 1;
				while (getCell(x + i, y) == opponentColor)
				{
					setCell(turnColor, x + i, y);
					i++;
				}
			}
		}
	}
	//CHECK SOUTH WEST
	validFlipDirection = false;
	if (x + 1 < numRows && y - 1 > 0)
	{
		if (getCell(x + 1, y - 1) == opponentColor)
		{
			i = 2;
			while (x + i < numRows && y - i > 0)
			{
				if (getCell(x + i, y - i) == ' ')
				{
					validFlipDirection = false;
					break;
				}
				if (getCell(x + i, y - i) == turnColor)
				{
					validFlipDirection = true;
					break;
				}
				i++;
			}
			if (validFlipDirection)
			{
				i = 1;
				while (getCell(x + i, y - i) == opponentColor)
				{
					setCell(turnColor, x + i, y - i);
					i++;
				}
			}
		}
	}
	//CHECK WEST
	validFlipDirection = false;
	if (y - 1 > 0)
	{
		if (getCell(x, y - 1) == opponentColor)
		{
			i = 2;
			while (y - i > 0)
			{
				if (getCell(x, y - i) == ' ')
				{
					validFlipDirection = false;
					break;
				}
				if (getCell(x, y - i) == turnColor)
				{
					validFlipDirection = true;
					break;
				}
				i++;
			}
			if (validFlipDirection)
			{
				i = 1;
				while (getCell(x, y - i) == opponentColor)
				{
					setCell(turnColor, x, y - i);
					i++;
				}
			}
		}
	}
	//CHECK NORTH WEST
	validFlipDirection = false;
	if (x - 1 > 0 && y - 1 > 0)
	{
		if (getCell(x - 1, y - 1) == opponentColor)
		{
			i = 2;
			while (x - i > 0 && y - i > 0)
			{
				if (getCell(x - i, y - i) == ' ')
				{
					validFlipDirection = false;
					break;
				}
				if (getCell(x - i, y - i) == turnColor)
				{
					validFlipDirection = true;
					break;
				}
				i++;
			}
			if (validFlipDirection)
			{
				i = 1;
				while (getCell(x - i, y - i) == opponentColor)
				{
					setCell(turnColor, x - i, y - i);
					i++;
				}
			}
		}
	}
}

