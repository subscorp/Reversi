/******************************************
*Ori Hirshfeld
*201085776
*Amichai Wollin
*300582392
******************************************/

#include "gtest/gtest.h"
#include "../Board.h"
#include "../GameManager.h"

StandardLogic logic3;
Board board3;

//we test on AIPlayer but it works the same for any type of player
AIPlayer Aiplayer('O',&logic3);

TEST(PlayerTest, CanDoMoveTest)
{
	//initially the AI player can make a move
	EXPECT_EQ(Aiplayer.canDoMove(&board3),1);

	//case where all pieces are O
	board3.setCell('O',4,5);
	board3.setCell('O',5,4);
	EXPECT_NE(Aiplayer.canDoMove(&board3),1);

	//case where all pieces are X
	board3.setCell('X',4,5);
	board3.setCell('X',5,4);
	board3.setCell('X',4,4);
	board3.setCell('X',5,5);
	EXPECT_NE(Aiplayer.canDoMove(&board3),1);

	//case where the board is full
	for(int i=1;i<board3.getNumRows();i++)
			for(int j=1;j<board3.getNumCols();j++)
				board3.setCell('X',i,j);
	EXPECT_NE(Aiplayer.canDoMove(&board3),1);

	//case where the board is empty
	for(int i=1;i<board3.getNumRows();i++)
				for(int j=1;j<board3.getNumCols();j++)
					board3.setCell(' ',i,j);
	EXPECT_NE(Aiplayer.canDoMove(&board3),1);
}



