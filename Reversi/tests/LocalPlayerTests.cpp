/******************************************
*Ori Hirshfeld
*201085776
*Amichai Wollin
*300582392
******************************************/

#include "gtest/gtest.h"
#include "../Board.h"
#include "../GameManager.h"

StandardLogic standardLogic;
Board board2;
LocalPlayer localPlayer('X',&standardLogic);

TEST(LocalPlayerTest, CanDoMoveTest)
{
	//initially the LocalPlayer player can make a move
	EXPECT_EQ(localPlayer.canDoMove(&board2),1);

	//case where all pieces are X
	board2.setCell('X',4,4);
	board2.setCell('X',5,5);
	EXPECT_NE(localPlayer.canDoMove(&board2),1);

	//case where all pieces are O
	board2.setCell('O',4,5);
	board2.setCell('O',5,4);
	board2.setCell('O',4,4);
	board2.setCell('O',5,5);
	EXPECT_NE(localPlayer.canDoMove(&board2),1);

	//case where the board is full
	for(int i=1;i<board2.getNumRows();i++)
			for(int j=1;j<board2.getNumCols();j++)
				board2.setCell('O',i,j);
	EXPECT_NE(localPlayer.canDoMove(&board2),1);

	//case where the board is empty
	for(int i=1;i<board2.getNumRows();i++)
				for(int j=1;j<board2.getNumCols();j++)
					board2.setCell(' ',i,j);
	EXPECT_NE(localPlayer.canDoMove(&board2),1);
}

