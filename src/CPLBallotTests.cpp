/**
 * @file CPLBallotTest.cpp
 * @author Claire Maurus mauru003@umn.edu
 * @brief CPP file for google test framework testing file to test the CPLBallot class
 * @version 0.1
 * @date 2023-03-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "gtest\gtest.h"
#include "CPLBallot.h"

//TestCase: CPLBallot_01
TEST (ForPartyTest, getterTest){
    CPLBallot testing1("1,,,,");
    CPLBallot testing2(",1,,,");
    CPLBallot testing3(",,,,1,,");
    CPLBallot testing4(",,,,,1");

    EXPECT_EQ(0, testing1.forParty());
    EXPECT_EQ(1, testing2.forParty());
    EXPECT_EQ(4, testing3.forParty());
    EXPECT_EQ(5, testing4.forParty());
}
//TestCase: CPLBallot_01
TEST(ForPartyTest, edgeCase){
    CPLBallot testing("1");

    EXPECT_EQ(0, testing.forParty());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
