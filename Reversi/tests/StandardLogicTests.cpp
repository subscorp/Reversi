/******************************************
*Ori Hirshfeld
*201085776
*Amichai Wollin
*300582392
******************************************/

#include "gtest/gtest.h"
#include "../GameManager.h"

TEST(StandardLogicTest,IsPossibleTest)
{
    StandardLogic sl;
    Board b;
    EXPECT_EQ(false,sl.isPossible(1,1,'X',&b));
    EXPECT_EQ(false,sl.isPossible(2,2,'X',&b));
    EXPECT_EQ(false,sl.isPossible(1,2,'O',&b));
    EXPECT_EQ(false,sl.isPossible(3,1,'O',&b));
    EXPECT_EQ(false,sl.isPossible(4,1,'X',&b));
    EXPECT_EQ(true,sl.isPossible(5,6,'X',&b));
    EXPECT_EQ(true,sl.isPossible(4,3,'X',&b));
    EXPECT_EQ(true,sl.isPossible(3,4,'X',&b));
    EXPECT_EQ(true,sl.isPossible(4,6,'O',&b));
    EXPECT_EQ(true,sl.isPossible(3,5,'O',&b));
    EXPECT_EQ(true,sl.isPossible(5,3,'O',&b));
}

TEST(StandardLogicTest,MoveIsValidTest)
{
    StandardLogic stl;
    Board brd;
    EXPECT_EQ(false,stl.moveIsValid('X',"1X1",&brd));
    EXPECT_EQ(false,stl.moveIsValid('X',"ABC",&brd));
    EXPECT_EQ(false,stl.moveIsValid('X',"Def",&brd));
    EXPECT_EQ(false,stl.moveIsValid('X',"ju7876f",&brd));
    EXPECT_EQ(false,stl.moveIsValid('X',"12",&brd));
    EXPECT_EQ(false,stl.moveIsValid('X',"uiop",&brd));
    EXPECT_EQ(false,stl.moveIsValid('X',"mathematics",&brd));
    EXPECT_EQ(false,stl.moveIsValid('O',"los pollos hermanos",&brd));
    EXPECT_EQ(false,stl.moveIsValid('O',"one on one",&brd));
    EXPECT_EQ(false,stl.moveIsValid('O',"saymyname",&brd));
    EXPECT_EQ(false,stl.moveIsValid('O',"Deaf",&brd));
    EXPECT_EQ(false,stl.moveIsValid('O',"112",&brd));
    EXPECT_EQ(false,stl.moveIsValid('O',"5y6",&brd));
    EXPECT_EQ(true,stl.moveIsValid('O',"4O6",&brd));
    EXPECT_EQ(true,stl.moveIsValid('O',"5O3",&brd));
    EXPECT_EQ(true,stl.moveIsValid('X',"4X3",&brd));
    EXPECT_EQ(true,stl.moveIsValid('X',"5X6",&brd));
}
