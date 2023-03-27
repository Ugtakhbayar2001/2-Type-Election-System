#include <gtest/gtest.h>
#include "IRBallot.h"

IRBallot testBallot = IRBallot("1,3,2,4");
TEST(IRBallotTest, InitializationTest) {
	EXPECT_EQ(testBallot.CurrentRank(), 1);
	EXPECT_EQ(testBallot.forCandidate(), 0);
	EXPECT_EQ(testBallot.IsNoRanks(), false);
}
TEST(IRBallotTest, UpdateRankTest) {
	testBallot.UpdateRank();
	EXPECT_EQ(testBallot.CurrentRank(), 2);
	EXPECT_EQ(testBallot.forCandidate(), 2);
	EXPECT_EQ(testBallot.IsNoRanks(), false);
}
TEST(IRBallotTest, NoRanksTest) {
	testBallot.UpdateRank();
	testBallot.UpdateRank();
	testBallot.UpdateRank();
	EXPECT_EQ(testBallot.forCandidate(), -1);
	EXPECT_EQ(testBallot.CurrentRank(), -1);
	EXPECT_EQ(testBallot.IsNoRanks(), true);
}

IRBallot smallBallot = IRBallot("2,1");

TEST(IRBallotTest, fewCandidatesTest) {
	EXPECT_EQ(smallBallot.CurrentRank(), 1);
	EXPECT_EQ(smallBallot.forCandidate(), 1);
	EXPECT_EQ(smallBallot.IsNoRanks(), false);
	smallBallot.UpdateRank();
	EXPECT_EQ(smallBallot.CurrentRank(), 2);
	EXPECT_EQ(smallBallot.forCandidate(), 0);
	EXPECT_EQ(smallBallot.IsNoRanks(), false);
	smallBallot.UpdateRank();
	EXPECT_EQ(smallBallot.forCandidate(), -1);
	EXPECT_EQ(smallBallot.CurrentRank(), -1);
	EXPECT_EQ(smallBallot.IsNoRanks(), true);
}

IRBallot blanksBallot = IRBallot(",1,,");

TEST(IRBallotTest, blanksTest) {
	EXPECT_EQ(blanksBallot.CurrentRank(), 1);
	EXPECT_EQ(blanksBallot.forCandidate(), 1);
	EXPECT_EQ(blanksBallot.IsNoRanks(), false);
	blanksBallot.UpdateRank();
	EXPECT_EQ(blanksBallot.forCandidate(), -1);
	EXPECT_EQ(blanksBallot.CurrentRank(), -1);
	EXPECT_EQ(blanksBallot.IsNoRanks(), true);
}

IRBallot largeBallot = IRBallot("3,,1,,2,,,4,,");

TEST(IRBallotTest, manyCandidatesTest) {
	EXPECT_EQ(largeBallot.CurrentRank(), 1);
	EXPECT_EQ(largeBallot.forCandidate(), 2);
	EXPECT_EQ(largeBallot.IsNoRanks(), false);
	largeBallot.UpdateRank();
	EXPECT_EQ(largeBallot.CurrentRank(), 2);
	EXPECT_EQ(largeBallot.forCandidate(), 4);
	EXPECT_EQ(largeBallot.IsNoRanks(), false);
	largeBallot.UpdateRank();
	largeBallot.UpdateRank();
	largeBallot.UpdateRank();
	EXPECT_EQ(largeBallot.forCandidate(), -1);
	EXPECT_EQ(largeBallot.CurrentRank(), -1);
	EXPECT_EQ(largeBallot.IsNoRanks(), true);
}
