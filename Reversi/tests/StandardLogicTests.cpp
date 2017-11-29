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
    b=Board();
    EXPECT_EQ(false,sl.isPossible(1,1,'X',&b));
    EXPECT_EQ(false,sl.isPossible(2,2,'X',&b));
    EXPECT_EQ(false,sl.isPossible(1,2,'O',&b));
    EXPECT_EQ(false,sl.isPossible(3,1,'O',&b));
    EXPECT_EQ(false,sl.isPossible(4,1,'X',&b));
}


