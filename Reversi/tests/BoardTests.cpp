/******************************************
*Ori Hirshfeld
*201085776
*Amichai Wollin
*300582392
******************************************/


#include "gtest/gtest.h"
#include "../Board.h"
#include <iostream>
using namespace std;

Board b;

//default constructor test
TEST(BoardTest, DefaultConstructorTest)
{
	EXPECT_EQ(b.getNumCols(),b.getNumRows());
	EXPECT_EQ(b.getNumCols(), 9);
	EXPECT_EQ(b.getCell(4,4),'O');
	EXPECT_EQ(b.getCell(5,5),'O');
	EXPECT_EQ(b.getCell(4,5),'X');
	EXPECT_EQ(b.getCell(5,4),'X');
	EXPECT_NE(b.getCell(6,6),'O');
	EXPECT_EQ(b.getCell(8,8),' ');
	EXPECT_EQ(b.isCellEmpty(1,1),1);
	EXPECT_EQ(b.isCellEmpty(4,4),0);
	EXPECT_EQ(b.getNumWhites(),b.getNumBlacks());
	EXPECT_EQ(b.getNumBlacks(),2);
}


//getters and setters test
TEST(BoardTest, SettersAndGettersTest)
{
	b.setCell('X',1,2);
	b.setCell('X',7,6);
	b.setCell('O',7,7);
	b.setCell('X',5,5);
	b.setNumRows(16);
	b.setNumCols(32);

	EXPECT_EQ(b.getCell(1,2),'X');
	EXPECT_EQ(b.getCell(1,2),'X');
	EXPECT_EQ(b.getCell(7,6),'X');
	EXPECT_EQ(b.getCell(7,7),'O');
	EXPECT_EQ(b.getCell(5,5),'X');
	EXPECT_EQ(b.getNumWhites(),2);
	EXPECT_EQ(b.getNumBlacks(),5);
	EXPECT_GT(b.getNumBlacks(), b.getNumWhites());
	EXPECT_EQ(b.getNumRows(),16);
	EXPECT_EQ(b.getNumCols(),32);
	EXPECT_LT(b.getNumRows(),b.getNumCols());
}

//test the case that the board is full
TEST(BoardTest, IsFullTest)
{
	EXPECT_NE(b.isFull(),1);

	b.setNumRows(9);
	b.setNumCols(9);
	for(int i=1;i<b.getNumRows();i++)
			for(int j=1;j<b.getNumCols();j++)
				b.setCell('X',i,j);

	EXPECT_EQ(b.isFull(),1);

}

//test flip
TEST(BoardTest, FlipTest)
{
	//working on a new board
	Board b2;

	//flip two at once, from left to right
	b2.setCell('O',5,6);
	b2.setCell('X',5,7);
	b2.flip(5,7,'X');
	EXPECT_EQ(b2.getCell(5,5),'X');
	EXPECT_EQ(b2.getCell(5,6),'X');

	//flip from up downwards
	b2.setCell('O',6,4);
	b2.flip(5,3,'O');
	EXPECT_EQ(b2.getCell(6,4),'O');

	//flip in diagonal
	b2.setCell('X',7,3);
	b2.flip(7,3,'X');
	EXPECT_EQ(b2.getCell(6,4),'X');
}



