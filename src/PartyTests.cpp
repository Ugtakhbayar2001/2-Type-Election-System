/**
 * @file CPLBallotTest.cpp
 * @author Claire Maurus mauru003@umn.edu
 * @brief CPP file for google test framework testing file to test the Party class
 * @version 0.1
 * @date 2023-03-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "gtest\gtest.h"
#include "Party.h"

//Test Case: Party_01
TEST (VoteTotalTest, StdPartyNoVotes){
    Party testing1("Candidate A, Candidate B, Candidate C", "Party A"); //makes new
    Party testing2("A, B, C, D, E, G", "Testing");

    EXPECT_EQ (0, testing1.getVoteTotal());
    EXPECT_EQ (0, testing2.getVoteTotal());
}

//Test Case: Party_01
TEST (VoteTotalTest, StdPartyWithVotes){
    Party testing1("Candidate A, Cadidate B, Cadidate C", "Party A"); //makes new
    Party testing2("A, B, C, D, E, G", "Testing");

    testing1.setVoteTotal(10);
    testing2.setVoteTotal(700000);

    EXPECT_EQ (10, testing1.getVoteTotal());
    EXPECT_EQ (700000, testing2.getVoteTotal());

    testing1.setVoteTotal(9999);
    testing2.setVoteTotal(8);

    EXPECT_EQ (9999, testing1.getVoteTotal());
    EXPECT_EQ (8, testing2.getVoteTotal());
}

//Test Case: Party_02
TEST (SeatTotalTest, StdPartyNoSeats){
    Party testing1("Candidate A, Candidate B, Candidate C", "Party A"); //makes new
    Party testing2("A, B, C, D, E, G", "Testing");

    EXPECT_EQ (0, testing1.getSeats());
    EXPECT_EQ (0, testing2.getSeats());
}

//Test Case: Party_02
TEST (SeatTotalTest, StdPartyWithSeats){
    Party testing1("Candidate A, Candidate B, Candidate C", "Party A"); //makes new
    Party testing2("A, B, C, D, E, G", "Testing");

    testing1.setSeats(18);
    testing2.setSeats(1200);

    EXPECT_EQ (18, testing1.getSeats());
    EXPECT_EQ (1200, testing2.getSeats());

    testing1.setSeats(9999);
    testing2.setSeats(1);

    EXPECT_EQ (9999, testing1.getSeats());
    EXPECT_EQ (1, testing2.getSeats());
}

//Test Case: Party_03
TEST (CadidateNameTest, getCandNameInRange){
    Party testing1("Candidate A, Candidate B, Candidate C", "Party A"); //makes new
    Party testing2("A, B, C, D, E, G", "Testing");

    EXPECT_EQ("Candidate A", testing1.getCadidateName(0));
    EXPECT_EQ("Candidate B", testing1.getCadidateName(1));
    EXPECT_EQ("Candidate C", testing1.getCadidateName(2));

    EXPECT_EQ("A", testing2.getCadidateName(0));
    EXPECT_EQ("B", testing2.getCadidateName(1));
    EXPECT_EQ("C", testing2.getCadidateName(2));
    EXPECT_EQ("D", testing2.getCadidateName(3));
    EXPECT_EQ("E", testing2.getCadidateName(4));
    EXPECT_EQ("G", testing2.getCadidateName(5));
}

//Test Case: Party_03
TEST (CadidateNameTest, getCandNameOutRange){
    Party testing1("Candidate A, Candidate B, Candidate C", "Party A"); //makes new

    EXPECT_EQ("Out of Candidates", testing1.getCadidateName(-1));
    EXPECT_EQ("Out of Candidates", testing1.getCadidateName(-7));
    EXPECT_EQ("Out of Candidates", testing1.getCadidateName(3));
}

//Test Case: Party_04
TEST (CadidateNumTest, stdTest){
    Party testing1("Candidate A, Candidate B, Candidate C", "Party A"); //makes new
    Party testing2("A, B, C, D, E, G", "Testing");

   EXPECT_EQ(3, testing1.getCadidateNum());
   EXPECT_EQ(6, testing2.getCadidateNum());
}

//Test Case: Party_05
TEST (GetPartyName, getterTesting){
    Party testing1("Candidate A, Candidate B", "News"); //makes new
    Party testing2("A, B, C, D, E, G", "Testing");

    EXPECT_EQ("News", testing1.getPartyName());
    EXPECT_EQ("Testing", testing2.getPartyName());
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
