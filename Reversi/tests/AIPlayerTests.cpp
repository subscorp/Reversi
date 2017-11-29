/******************************************
*Ori Hirshfeld
*201085776
*Amichai Wollin
*300582392
******************************************/

#include "gtest/gtest.h"
#include "../Board.h"
#include "../GameManager.h"

StandardLogic logic;
Board board;
AIPlayer player('O',&logic);

TEST(AIPlayerTest, CanDoMoveTest)
{
	//initially the AI player can make a move
	EXPECT_EQ(player.canDoMove(&board),1);

	//case where all pieces are O
	board.setCell('O',4,5);
	board.setCell('O',5,4);
	EXPECT_NE(player.canDoMove(&board),1);

	//case where all pieces are X
	board.setCell('X',4,5);
	board.setCell('X',5,4);
	board.setCell('X',4,4);
	board.setCell('X',5,5);
	EXPECT_NE(player.canDoMove(&board),1);

	//case where the board is full
	for(int i=1;i<board.getNumRows();i++)
			for(int j=1;j<board.getNumCols();j++)
				board.setCell('X',i,j);
	EXPECT_NE(player.canDoMove(&board),1);

	//case where the board is empty
	for(int i=1;i<board.getNumRows();i++)
				for(int j=1;j<board.getNumCols();j++)
					board.setCell(' ',i,j);
	EXPECT_NE(player.canDoMove(&board),1);
}


TEST(AIPlayerTest, MakeMoveTest)
{
	int* move = NULL;
	int moveX;
	int moveY;
	//initialize the board
	board.setCell('X',4,5);
	board.setCell('X',5,4);
	board.setCell('O',4,4);
	board.setCell('O',5,5);

	//x first 3 moves: 3,4 , 6,5 , 4,3
	board.setCell('X',3,4);
	board.flip(3,4,'X');
	move = player.makeMove(&board,move);
	moveX = move[0]; moveY = move[1];
	EXPECT_EQ(moveX,3);
	EXPECT_EQ(moveY,3);
	board.flip(3,3,'O');
	board.setCell('X',6,5);
	board.flip(6,5,'X');
	move = player.makeMove(&board,move);
	moveX = move[0]; moveY = move[1];
	EXPECT_EQ(moveX,6);
	EXPECT_EQ(moveY,6);
	board.flip(6,6,'O');
	board.setCell('X',4,3);
	board.flip(4,3,'X');
	move = player.makeMove(&board,move);
	moveX = move[0]; moveY = move[1];
	EXPECT_EQ(moveX,5);
	EXPECT_EQ(moveY,3);

	//re-initialize the board
	for(int i=1;i<board.getNumRows();i++)
		for(int j=1;j<board.getNumCols();j++)
			board.setCell(' ',i,j);
	board.setCell('X',4,5);
	board.setCell('X',5,4);
	board.setCell('O',4,4);
	board.setCell('O',5,5);

	//x first 3 moves: 5,6 , 6,3 , 8,4
	board.setCell('X',5,6);
	board.flip(5,6,'X');
	move = player.makeMove(&board,move);
	moveX = move[0]; moveY = move[1];
	EXPECT_EQ(moveX,6);
	EXPECT_EQ(moveY,4);
	board.flip(6,4,'O');
	board.setCell('X',6,3);
	board.flip(6,3,'X');
	move = player.makeMove(&board,move);
	moveX = move[0]; moveY = move[1];
	EXPECT_EQ(moveX,4);
	EXPECT_EQ(moveY,6);
	board.flip(6,6,'O');
	board.setCell('X',7,4);
	board.flip(7,4,'X');
	move = player.makeMove(&board,move);
	moveX = move[0]; moveY = move[1];
	EXPECT_EQ(moveX,8);
	EXPECT_EQ(moveY,4);
}






