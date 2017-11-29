/******************************************
*Ori Hirshfeld
*201085776
*Amichai Wollin
*300582392
******************************************/

#pragma once
class Board
{
public:
	//default constructor for our board
	Board();

	//constructor with parameters for possible later use
	Board(int numRows, int numCols);

	//this function prints the board
	void printBoard() const;

	//puts color in cell i,j
	void setCell(char color, int i, int j);

	//return the color in cell i,j
	char getCell(int i, int j);

	//retutrns number of white and black pawns
	int  getNumWhites();
	int  getNumBlacks();

	//checks if the board is full
	bool isFull();

	//check if a cell at index i,j is empty
	bool isCellEmpty(int i, int j);

	//flips the color in cells according to the rules of reversi after a move done by the player
	void flip(int x, int y, char color);

	//getters and setters for possible later use
	int getNumCols() const;
	void setNumCols(int numCols);
	int getNumRows() const;
	void setNumRows(int numRows);
private:
	char boardArr[9][9];
	int numRows;
	int numCols;
	int numBlacks;
	int numWhites;
};
