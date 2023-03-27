#include <gtest/gtest.h>
#include "Candidate.h"

Candidate testCandidate = Candidate("name");
TEST(CandidateTest, InitializationTest) {
	EXPECT_EQ(testCandidate.GetVoteTotal(), 0);
	EXPECT_EQ(testCandidate.GetName(), "name");
	EXPECT_EQ(testCandidate.IsDropped(), false);
}

TEST(CandidateTest, SetVoteTest) {
	testCandidate.SetVoteTotal(10);
	EXPECT_EQ(testCandidate.GetVoteTotal(), 10);
	EXPECT_EQ(testCandidate.IsDropped(), false);
	testCandidate.SetVoteTotal(0);
	EXPECT_EQ(testCandidate.GetVoteTotal(), 0);
	EXPECT_EQ(testCandidate.IsDropped(), false);
}

TEST(CandidateTest, DropTest) {
	testCandidate.SetVoteTotal(-1);
	EXPECT_EQ(testCandidate.GetVoteTotal(), -1);
	EXPECT_EQ(testCandidate.IsDropped(), true);
}