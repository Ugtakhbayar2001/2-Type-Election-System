/**
 * @file IRElectionTests.cpp
 * @author Ugtakhbayar Battulga  (battu016@umn.edu)
 * @brief unit testing file that uses the google test framework
 * @version 0.1
 * @date 2023-03-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../src/Election.h"
#include "../src/IRElection.h"
#include "../src/Candidate.h"
#include "../src/IRBallot.h"
#include "../src/AuditFiler.h"
#include "gtest/gtest.h"
#include <fstream>

// IRElection_01
TEST(IRElectionTests, ReadElectionAndDisplayResults_Majority) {
    ifstream testElectionFile ("../testing/IRElectionTests_Majority.csv", std::ifstream::in);
    testElectionFile.ignore(256, '\n');

    IRElection testElection = IRElection(testElectionFile, "02222001");
    EXPECT_EQ(testElectionFile.is_open(), false);

    testing::internal::CaptureStdout();
    testElection.DisplayResults();

    std::string expectedResults = 
      "Election type: IR\n"
      "Number of candidates: 5\n"
      "Number of ballots cast: 8\n"
      "IR Election results in last round: \n"
      "Number of votes for candidate number 1: 0 (0.00%)\n"
      "Number of votes for candidate number 2: 0 (0.00%)\n"
      "Number of votes for candidate number 3: 0 (0.00%)\n"
      "Number of votes for candidate number 4: 0 (0.00%)\n"
      "Number of votes for candidate number 5: 0 (0.00%)\n"
      "Winner: None\n";

    EXPECT_EQ(testing::internal::GetCapturedStdout(), expectedResults);
}

// IRElection_02
TEST(IRElectionTests, ReadElectionAndWriteResults_Majority) { 
    ifstream testElectionFile ("../testing/IRElectionTests_Majority.csv", std::ifstream::in);
    testElectionFile.ignore(256, '\n');

    IRElection testElection = IRElection(testElectionFile, "02222002");
    testElection.WriteResultsToFile();

    EXPECT_EQ(testElectionFile.is_open(), false);
    string expectedOut =    
      "IRElection\n"
      "Number of Candidates: 5\n"
      "Candidate 1: A\n"
      "Candidate 2: B\n"
      "Candidate 3: C\n"
      "Candidate 4: D\n"
      "Candidate 5: E\n"
      "Number of ballots: 8\n"
      "Ballot ID: 1 Ballot Info: 1,3,4,2,5\n"
      "Ballot ID: 2 Ballot Info: ,2,1,,3\n"
      "Ballot ID: 3 Ballot Info: 2,3,,1,\n"
      "Ballot ID: 4 Ballot Info: 4,3,1,2,\n"
      "Ballot ID: 5 Ballot Info: 3,4,1,5,2\n"
      "Ballot ID: 6 Ballot Info: ,,,2,1\n"
      "Ballot ID: 7 Ballot Info: ,,,,1\n"
      "Ballot ID: 8 Ballot Info: ,3,2,1,\n";
    
    ifstream actualOutRead ("02222002IR.txt");
    stringstream actualOut;
    actualOut << actualOutRead.rdbuf();
    
    EXPECT_EQ(actualOut.str(), expectedOut);
    remove("../src/02222002IR.txt");
}

// IRElection_03
TEST(IRElectionTests, ConstructorAndReadElection_Single) { 
    ifstream testElectionFile ("../testing/IRElectionTests_Single.csv", std::ifstream::in);
    testElectionFile.ignore(256, '\n');

    IRElection testElection = IRElection(testElectionFile, "02222003");

    testing::internal::CaptureStdout();
    testElection.DisplayResults();

    std::string expectedResults = 
      "Election type: IR\n"
      "Number of candidates: 1\n"
      "Number of ballots cast: 3\n"
      "IR Election results in last round: \n"
      "Number of votes for candidate number 1: 0 (0.00%)\n"
      "Winner: None\n";

    EXPECT_EQ(testing::internal::GetCapturedStdout(), expectedResults);
}

// IRElection_04
TEST(IRElectionTests, ConstructorAndWriteResults_Single) { 
    ifstream testElectionFile ("../testing/IRElectionTests_Single.csv", std::ifstream::in);
    testElectionFile.ignore(256, '\n');

    IRElection testElection = IRElection(testElectionFile, "02222004");
    testElection.WriteResultsToFile();

    EXPECT_EQ(testElectionFile.is_open(), false);
    string expectedOut =    
      "IRElection\n"
      "Number of Candidates: 1\n"
      "Candidate 1: A\n"
      "Number of ballots: 3\n"
      "Ballot ID: 1 Ballot Info: 1\n"
      "Ballot ID: 2 Ballot Info: 1\n"
      "Ballot ID: 3 Ballot Info: 1\n";
    
    ifstream actualOutRead ("02222004IR.txt");
    stringstream actualOut;
    actualOut << actualOutRead.rdbuf();
    
    EXPECT_EQ(actualOut.str(), expectedOut);
    remove("../src/02222004IR.txt");
}

// IRElection_05
TEST(IRElectionTests, DisplayResultsAndRunElection_Single) { 
    ifstream testElectionFile ("../testing/IRElectionTests_Single.csv", std::ifstream::in);
    testElectionFile.ignore(256, '\n');

    IRElection testElection = IRElection(testElectionFile, "02222005");
    testElection.RunElection();

    testing::internal::CaptureStdout();
    testElection.DisplayResults();

    std::string expectedResults = 
      "Election type: IR\n"
      "Number of candidates: 1\n"
      "Number of ballots cast: 3\n"
      "IR Election results in last round: \n"
      "Number of votes for candidate number 1: 3 (100.00%)\n"
      "Winner: A\n";

    EXPECT_EQ(testing::internal::GetCapturedStdout(), expectedResults);
}

// IRElection_06
TEST(IRElectionTests, WriteResultsAndRunElection_Single) { 
    ifstream testElectionFile ("../testing/IRElectionTests_Single.csv", std::ifstream::in);
    testElectionFile.ignore(256, '\n');

    IRElection testElection = IRElection(testElectionFile, "02222006");
    testElection.RunElection();
    testElection.WriteResultsToFile();

    std::string expectedOut =    
      "IRElection\n"
      "Number of Candidates: 1\n"
      "Candidate 1: A\n"
      "Number of ballots: 3\n"
      "Ballot ID: 1 Ballot Info: 1\n"
      "Ballot ID: 2 Ballot Info: 1\n"
      "Ballot ID: 3 Ballot Info: 1\n"
      "Counting Ballots\n"
      "Ballot #1 went to Candidate #1\n"
      "Ballot #2 went to Candidate #1\n"
      "Ballot #3 went to Candidate #1\n"
      "Candidate #1 received 3 vote(s)\n"
      "Majority Found in first round\n"
      "Winner is: A with 3 Votes\n";

    ifstream actualOutRead ("02222006IR.txt");
    stringstream actualOut;
    actualOut << actualOutRead.rdbuf();
    
    EXPECT_EQ(actualOut.str(), expectedOut);
    remove("02222006IR.txt");
}


// IRElection_07
TEST(IRElectionTests, DisplayResultsAndRunElection_Majority) { 
    ifstream testElectionFile ("../testing/IRElectionTests_Majority.csv", std::ifstream::in);
    testElectionFile.ignore(256, '\n');

    IRElection testElection = IRElection(testElectionFile, "02222007");
    testElection.RunElection();

    testing::internal::CaptureStdout();
    testElection.DisplayResults();

    std::string expectedResults = 
      "Election type: IR\n"
      "Number of candidates: 5\n"
      "Number of ballots cast: 8\n"
      "IR Election results in last round: \n"
      "Number of votes for candidate number 1: 0 (0.00%)\n"
      "Number of votes for candidate number 2: 0 (0.00%)\n"
      "Number of votes for candidate number 3: 3 (37.50%)\n"
      "Number of votes for candidate number 4: 4 (50.00%)\n"
      "Number of votes for candidate number 5: 0 (0.00%)\n"
      "Winner: D\n";

    EXPECT_EQ(testing::internal::GetCapturedStdout(), expectedResults);
}

// IRElection_08
TEST(IRElectionTests, WriteResultsAndRunElection_Majority) { 
    ifstream testElectionFile ("../testing/IRElectionTests_Majority.csv", std::ifstream::in);
    testElectionFile.ignore(256, '\n');

    IRElection testElection = IRElection(testElectionFile, "02222008");
    testElection.RunElection();
    testElection.WriteResultsToFile();

    EXPECT_EQ(testElectionFile.is_open(), false);
    std::string expectedOut =    
      "IRElection\n"
      "Number of Candidates: 5\n"
      "Candidate 1: A\n"
      "Candidate 2: B\n"
      "Candidate 3: C\n"
      "Candidate 4: D\n"
      "Candidate 5: E\n"
      "Number of ballots: 8\n"
      "Ballot ID: 1 Ballot Info: 1,3,4,2,5\n"
      "Ballot ID: 2 Ballot Info: ,2,1,,3\n"
      "Ballot ID: 3 Ballot Info: 2,3,,1,\n"
      "Ballot ID: 4 Ballot Info: 4,3,1,2,\n"
      "Ballot ID: 5 Ballot Info: 3,4,1,5,2\n"
      "Ballot ID: 6 Ballot Info: ,,,2,1\n"
      "Ballot ID: 7 Ballot Info: ,,,,1\n"
      "Ballot ID: 8 Ballot Info: ,3,2,1,\n"
      "Counting Ballots\n"
      "Ballot #1 went to Candidate #1\n"
      "Ballot #2 went to Candidate #3\n"
      "Ballot #3 went to Candidate #4\n"
      "Ballot #4 went to Candidate #3\n"
      "Ballot #5 went to Candidate #3\n"
      "Ballot #6 went to Candidate #5\n"
      "Ballot #7 went to Candidate #5\n"
      "Ballot #8 went to Candidate #4\n"
      "Candidate #1 received 1 vote(s)\n"
      "Candidate #2 received 0 vote(s)\n"
      "Candidate #3 received 3 vote(s)\n"
      "Candidate #4 received 2 vote(s)\n"
      "Candidate #5 received 2 vote(s)\n"
      "No Majority Found with more than 2 Candidates remaining\n"
      "Dropped Candidate Name: B\n"
      "Redistribute Votes\n"
      "Ballot #1 went to Candidate #1\n"
      "Ballot #2 went to Candidate #3\n"
      "Ballot #3 went to Candidate #4\n"
      "Ballot #4 went to Candidate #3\n"
      "Ballot #5 went to Candidate #3\n"
      "Ballot #6 went to Candidate #5\n"
      "Ballot #7 went to Candidate #5\n"
      "Ballot #8 went to Candidate #4\n"
      "Candidate #1 received 1 vote(s)\n"
      "Candidate #2 received 0 vote(s)\n"
      "Candidate #3 received 3 vote(s)\n"
      "Candidate #4 received 2 vote(s)\n"
      "Candidate #5 received 2 vote(s)\n"
      "No Majority Found with more than 2 Candidates remaining\n"
      "Dropped Candidate Name: A\n"
      "Redistribute Votes\n"
      "Ballot #1 went to Candidate #4\n"
      "Ballot #2 went to Candidate #3\n"
      "Ballot #3 went to Candidate #4\n"
      "Ballot #4 went to Candidate #3\n"
      "Ballot #5 went to Candidate #3\n"
      "Ballot #6 went to Candidate #5\n"
      "Ballot #7 went to Candidate #5\n"
      "Ballot #8 went to Candidate #4\n"
      "Candidate #1 received 0 vote(s)\n"
      "Candidate #2 received 0 vote(s)\n"
      "Candidate #3 received 3 vote(s)\n"
      "Candidate #4 received 3 vote(s)\n"
      "Candidate #5 received 2 vote(s)\n"
      "No Majority Found with more than 2 Candidates remaining\n"
      "Dropped Candidate Name: E\n"
      "Redistribute Votes\n"
      "Ballot #1 went to Candidate #4\n"
      "Ballot #2 went to Candidate #3\n"
      "Ballot #3 went to Candidate #4\n"
      "Ballot #4 went to Candidate #3\n"
      "Ballot #5 went to Candidate #3\n"
      "Ballot #6 went to Candidate #4\n"
      "Ballot #8 went to Candidate #4\n"
      "Candidate #1 received 0 vote(s)\n"
      "Candidate #2 received 0 vote(s)\n"
      "Candidate #3 received 3 vote(s)\n"
      "Candidate #4 received 4 vote(s)\n"
      "Candidate #5 received 0 vote(s)\n"
      "Remaining 2 Candidates with no majority move to popularity\n"
      "Winner is: D with 4 Votes\n";

    ifstream actualOutRead ("02222008IR.txt");
    stringstream actualOut;
    actualOut << actualOutRead.rdbuf();
    
    EXPECT_EQ(actualOut.str(), expectedOut);
    remove("02222008IR.txt");
}

// IRElection_09
TEST(IRElectionTests, DisplayResultsAndRunElection_DropTie) { 
    ifstream testElectionFile ("../testing/IRElectionTests_DropTie.csv", std::ifstream::in);
    testElectionFile.ignore(256, '\n');

    IRElection testElection = IRElection(testElectionFile, "02222009");
    testElection.RunElection();

    std::string expectedResults = 
      "Election type: IR\n"
      "Number of candidates: 5\n"
      "Number of ballots cast: 12\n"
      "IR Election results in last round: \n";
    
    testing::internal::CaptureStdout();
    testElection.DisplayResults();
    std::string actual = testing::internal::GetCapturedStdout();
    if(actual == 
      "Election type: IR\n"
      "Number of candidates: 5\n"
      "Number of ballots cast: 12\n"
      "IR Election results in last round: \n"
      "Number of votes for candidate number 1: 0 (0.00%)\n"
      "Number of votes for candidate number 2: 3 (25.00%)\n"
      "Number of votes for candidate number 3: 0 (0.00%)\n"
      "Number of votes for candidate number 4: 8 (66.67%)\n"
      "Number of votes for candidate number 5: 0 (0.00%)\n"
      "Winner: D\n"
      ) {
        expectedResults += 
      "Number of votes for candidate number 1: 0 (0.00%)\n"
      "Number of votes for candidate number 2: 3 (25.00%)\n"
      "Number of votes for candidate number 3: 0 (0.00%)\n"
      "Number of votes for candidate number 4: 8 (66.67%)\n"
      "Number of votes for candidate number 5: 0 (0.00%)\n"
      "Winner: D\n";
      } else if(actual == 
      "Election type: IR\n"
      "Number of candidates: 5\n"
      "Number of ballots cast: 12\n"
      "IR Election results in last round: \n"
      "Number of votes for candidate number 1: 5 (41.67%)\n"
      "Number of votes for candidate number 2: 0 (0.00%)\n"
      "Number of votes for candidate number 3: 0 (0.00%)\n"
      "Number of votes for candidate number 4: 6 (50.00%)\n"
      "Number of votes for candidate number 5: 0 (0.00%)\n"
      "Winner: D\n"
      ) {
        expectedResults += 
      "Number of votes for candidate number 1: 5 (41.67%)\n"
      "Number of votes for candidate number 2: 0 (0.00%)\n"
      "Number of votes for candidate number 3: 0 (0.00%)\n"
      "Number of votes for candidate number 4: 6 (50.00%)\n"
      "Number of votes for candidate number 5: 0 (0.00%)\n"
      "Winner: D\n";
      }
      
    EXPECT_EQ(actual, expectedResults);
}

// IRElection_10
TEST(IRElectionTests, WriteResultsAndRunElection_DropTie) { 
    ifstream testElectionFile ("../testing/IRElectionTests_DropTie.csv", std::ifstream::in);
    testElectionFile.ignore(256, '\n');

    IRElection testElection = IRElection(testElectionFile, "02222010");
    testElection.RunElection();
    testElection.WriteResultsToFile();

    std::string expectedOut =    
      "IRElection\n"
      "Number of Candidates: 5\n"
      "Candidate 1: A\n"
      "Candidate 2: B\n"
      "Candidate 3: C\n"
      "Candidate 4: D\n"
      "Candidate 5: E\n"
      "Number of ballots: 12\n"
      "Ballot ID: 1 Ballot Info: 1,,3,2,\n"
      "Ballot ID: 2 Ballot Info: ,,1,2,3\n"
      "Ballot ID: 3 Ballot Info: 2,1,,3,4\n"
      "Ballot ID: 4 Ballot Info: ,2,,1,\n"
      "Ballot ID: 5 Ballot Info: 1,,,,\n"
      "Ballot ID: 6 Ballot Info: 2,1,,,\n"
      "Ballot ID: 7 Ballot Info: 4,3,,1,2\n"
      "Ballot ID: 8 Ballot Info: 1,,3,4,2\n"
      "Ballot ID: 9 Ballot Info: ,,1,2,\n"
      "Ballot ID: 10 Ballot Info: 3,4,5,2,1\n"
      "Ballot ID: 11 Ballot Info: 3,2,5,1,4\n"
      "Ballot ID: 12 Ballot Info: ,1,3,,2\n"
      "Counting Ballots\n"
      "Ballot #1 went to Candidate #1\n"
      "Ballot #2 went to Candidate #3\n"
      "Ballot #3 went to Candidate #2\n"
      "Ballot #4 went to Candidate #4\n"
      "Ballot #5 went to Candidate #1\n"
      "Ballot #6 went to Candidate #2\n"
      "Ballot #7 went to Candidate #4\n"
      "Ballot #8 went to Candidate #1\n"
      "Ballot #9 went to Candidate #3\n"
      "Ballot #10 went to Candidate #5\n"
      "Ballot #11 went to Candidate #4\n"
      "Ballot #12 went to Candidate #2\n"
      "Candidate #1 received 3 vote(s)\n"
      "Candidate #2 received 3 vote(s)\n"
      "Candidate #3 received 2 vote(s)\n"
      "Candidate #4 received 3 vote(s)\n"
      "Candidate #5 received 1 vote(s)\n"
      "No Majority Found with more than 2 Candidates remaining\n"
      "Dropped Candidate Name: E\n"
      "Redistribute Votes\n"
      "Ballot #1 went to Candidate #1\n"
      "Ballot #2 went to Candidate #3\n"
      "Ballot #3 went to Candidate #2\n"
      "Ballot #4 went to Candidate #4\n"
      "Ballot #5 went to Candidate #1\n"
      "Ballot #6 went to Candidate #2\n"
      "Ballot #7 went to Candidate #4\n"
      "Ballot #8 went to Candidate #1\n"
      "Ballot #9 went to Candidate #3\n"
      "Ballot #10 went to Candidate #4\n"
      "Ballot #11 went to Candidate #4\n"
      "Ballot #12 went to Candidate #2\n"
      "Candidate #1 received 3 vote(s)\n"
      "Candidate #2 received 3 vote(s)\n"
      "Candidate #3 received 2 vote(s)\n"
      "Candidate #4 received 4 vote(s)\n"
      "Candidate #5 received 0 vote(s)\n"
      "No Majority Found with more than 2 Candidates remaining\n"
      "Dropped Candidate Name: C\n"
      "Redistribute Votes\n"
      "Ballot #1 went to Candidate #1\n"
      "Ballot #2 went to Candidate #4\n"
      "Ballot #3 went to Candidate #2\n"
      "Ballot #4 went to Candidate #4\n"
      "Ballot #5 went to Candidate #1\n"
      "Ballot #6 went to Candidate #2\n"
      "Ballot #7 went to Candidate #4\n"
      "Ballot #8 went to Candidate #1\n"
      "Ballot #9 went to Candidate #4\n"
      "Ballot #10 went to Candidate #4\n"
      "Ballot #11 went to Candidate #4\n"
      "Ballot #12 went to Candidate #2\n"
      "Candidate #1 received 3 vote(s)\n"
      "Candidate #2 received 3 vote(s)\n"
      "Candidate #3 received 0 vote(s)\n"
      "Candidate #4 received 6 vote(s)\n"
      "Candidate #5 received 0 vote(s)\n"
      "No Majority Found with more than 2 Candidates remaining\n"
      "Tie Has Occurred\n"
      "Candidate dropped based of tieLoser: B\n"
      "Redistribute Votes\n"
      "Ballot #1 went to Candidate #1\n"
      "Ballot #2 went to Candidate #4\n"
      "Ballot #3 went to Candidate #1\n"
      "Ballot #4 went to Candidate #4\n"
      "Ballot #5 went to Candidate #1\n"
      "Ballot #6 went to Candidate #1\n"
      "Ballot #7 went to Candidate #4\n"
      "Ballot #8 went to Candidate #1\n"
      "Ballot #9 went to Candidate #4\n"
      "Ballot #10 went to Candidate #4\n"
      "Ballot #11 went to Candidate #4\n"
      "Candidate #1 received 5 vote(s)\n"
      "Candidate #2 received 0 vote(s)\n"
      "Candidate #3 received 0 vote(s)\n"
      "Candidate #4 received 6 vote(s)\n"
      "Candidate #5 received 0 vote(s)\n"
      "Remaining 2 Candidates with no majority move to popularity\n"
      "Winner is: D with 6 Votes\n";
    
    std::string expectedOut1 = 
      "IRElection\n"
      "Number of Candidates: 5\n"
      "Candidate 1: A\n"
      "Candidate 2: B\n"
      "Candidate 3: C\n"
      "Candidate 4: D\n"
      "Candidate 5: E\n"
      "Number of ballots: 12\n"
      "Ballot ID: 1 Ballot Info: 1,,3,2,\n"
      "Ballot ID: 2 Ballot Info: ,,1,2,3\n"
      "Ballot ID: 3 Ballot Info: 2,1,,3,4\n"
      "Ballot ID: 4 Ballot Info: ,2,,1,\n"
      "Ballot ID: 5 Ballot Info: 1,,,,\n"
      "Ballot ID: 6 Ballot Info: 2,1,,,\n"
      "Ballot ID: 7 Ballot Info: 4,3,,1,2\n"
      "Ballot ID: 8 Ballot Info: 1,,3,4,2\n"
      "Ballot ID: 9 Ballot Info: ,,1,2,\n"
      "Ballot ID: 10 Ballot Info: 3,4,5,2,1\n"
      "Ballot ID: 11 Ballot Info: 3,2,5,1,4\n"
      "Ballot ID: 12 Ballot Info: ,1,3,,2\n"
      "Counting Ballots\n"
      "Ballot #1 went to Candidate #1\n"
      "Ballot #2 went to Candidate #3\n"
      "Ballot #3 went to Candidate #2\n"
      "Ballot #4 went to Candidate #4\n"
      "Ballot #5 went to Candidate #1\n"
      "Ballot #6 went to Candidate #2\n"
      "Ballot #7 went to Candidate #4\n"
      "Ballot #8 went to Candidate #1\n"
      "Ballot #9 went to Candidate #3\n"
      "Ballot #10 went to Candidate #5\n"
      "Ballot #11 went to Candidate #4\n"
      "Ballot #12 went to Candidate #2\n"
      "Candidate #1 received 3 vote(s)\n"
      "Candidate #2 received 3 vote(s)\n"
      "Candidate #3 received 2 vote(s)\n"
      "Candidate #4 received 3 vote(s)\n"
      "Candidate #5 received 1 vote(s)\n"
      "No Majority Found with more than 2 Candidates remaining\n"
      "Dropped Candidate Name: E\n"
      "Redistribute Votes\n"
      "Ballot #1 went to Candidate #1\n"
      "Ballot #2 went to Candidate #3\n"
      "Ballot #3 went to Candidate #2\n"
      "Ballot #4 went to Candidate #4\n"
      "Ballot #5 went to Candidate #1\n"
      "Ballot #6 went to Candidate #2\n"
      "Ballot #7 went to Candidate #4\n"
      "Ballot #8 went to Candidate #1\n"
      "Ballot #9 went to Candidate #3\n"
      "Ballot #10 went to Candidate #4\n"
      "Ballot #11 went to Candidate #4\n"
      "Ballot #12 went to Candidate #2\n"
      "Candidate #1 received 3 vote(s)\n"
      "Candidate #2 received 3 vote(s)\n"
      "Candidate #3 received 2 vote(s)\n"
      "Candidate #4 received 4 vote(s)\n"
      "Candidate #5 received 0 vote(s)\n"
      "No Majority Found with more than 2 Candidates remaining\n"
      "Dropped Candidate Name: C\n"
      "Redistribute Votes\n"
      "Ballot #1 went to Candidate #1\n"
      "Ballot #2 went to Candidate #4\n"
      "Ballot #3 went to Candidate #2\n"
      "Ballot #4 went to Candidate #4\n"
      "Ballot #5 went to Candidate #1\n"
      "Ballot #6 went to Candidate #2\n"
      "Ballot #7 went to Candidate #4\n"
      "Ballot #8 went to Candidate #1\n"
      "Ballot #9 went to Candidate #4\n"
      "Ballot #10 went to Candidate #4\n"
      "Ballot #11 went to Candidate #4\n"
      "Ballot #12 went to Candidate #2\n"
      "Candidate #1 received 3 vote(s)\n"
      "Candidate #2 received 3 vote(s)\n"
      "Candidate #3 received 0 vote(s)\n"
      "Candidate #4 received 6 vote(s)\n"
      "Candidate #5 received 0 vote(s)\n"
      "No Majority Found with more than 2 Candidates remaining\n"
      "Tie Has Occurred\n"
      "Candidate dropped based of tieLoser: A\n"
      "Redistribute Votes\n"
      "Ballot #1 went to Candidate #4\n"
      "Ballot #2 went to Candidate #4\n"
      "Ballot #3 went to Candidate #2\n"
      "Ballot #4 went to Candidate #4\n"
      "Ballot #6 went to Candidate #2\n"
      "Ballot #7 went to Candidate #4\n"
      "Ballot #8 went to Candidate #4\n"
      "Ballot #9 went to Candidate #4\n"
      "Ballot #10 went to Candidate #4\n"
      "Ballot #11 went to Candidate #4\n"
      "Ballot #12 went to Candidate #2\n"
      "Candidate #1 received 0 vote(s)\n"
      "Candidate #2 received 3 vote(s)\n"
      "Candidate #3 received 0 vote(s)\n"
      "Candidate #4 received 8 vote(s)\n"
      "Candidate #5 received 0 vote(s)\n"
      "Remaining 2 Candidates with no majority move to popularity\n"
      "Winner is: D with 8 Votes\n";    

    ifstream actualOutRead ("02222010IR.txt");
    stringstream actualOut;
    actualOut << actualOutRead.rdbuf(); 

    bool testPassed = false;
    if (actualOut.str() == expectedOut || actualOut.str()== expectedOut1) {
        testPassed = true;
    }

    EXPECT_TRUE(testPassed);
    remove("02222010IR.txt");
}

// IRElection_11
TEST(IRElectionTests, DisplayResultsAndRunElection_WinnerTie) { 
    ifstream testElectionFile ("../testing/IRElectionTests_WinnerTie.csv", std::ifstream::in);
    testElectionFile.ignore(256, '\n');

    IRElection testElection = IRElection(testElectionFile, "02222011");
    testElection.RunElection();

    std::string expectedResults = 
      "Election type: IR\n"
      "Number of candidates: 5\n"
      "Number of ballots cast: 15\n"
      "IR Election results in last round: \n";
    
    testing::internal::CaptureStdout();
    testElection.DisplayResults();
    std::string actual = testing::internal::GetCapturedStdout();
    if(actual == 
      "Election type: IR\n"
      "Number of candidates: 5\n"
      "Number of ballots cast: 15\n"
      "IR Election results in last round: \n"
      "Number of votes for candidate number 1: 0 (0.00%)\n"
      "Number of votes for candidate number 2: 0 (0.00%)\n"
      "Number of votes for candidate number 3: 7 (46.67%)\n"
      "Number of votes for candidate number 4: 0 (0.00%)\n"
      "Number of votes for candidate number 5: 7 (46.67%)\n"
      "Winner: C\n"
      ) {
        expectedResults += 
      "Number of votes for candidate number 1: 0 (0.00%)\n"
      "Number of votes for candidate number 2: 0 (0.00%)\n"
      "Number of votes for candidate number 3: 7 (46.67%)\n"
      "Number of votes for candidate number 4: 0 (0.00%)\n"
      "Number of votes for candidate number 5: 7 (46.67%)\n"
      "Winner: C\n";
      } else if(actual == 
      "Election type: IR\n"
      "Number of candidates: 5\n"
      "Number of ballots cast: 15\n"
      "IR Election results in last round: \n"
      "Number of votes for candidate number 1: 0 (0.00%)\n"
      "Number of votes for candidate number 2: 0 (0.00%)\n"
      "Number of votes for candidate number 3: 7 (46.67%)\n"
      "Number of votes for candidate number 4: 0 (0.00%)\n"
      "Number of votes for candidate number 5: 7 (46.67%)\n"
      "Winner: E\n"
      ) {
        expectedResults += 
      "Number of votes for candidate number 1: 0 (0.00%)\n"
      "Number of votes for candidate number 2: 0 (0.00%)\n"
      "Number of votes for candidate number 3: 7 (46.67%)\n"
      "Number of votes for candidate number 4: 0 (0.00%)\n"
      "Number of votes for candidate number 5: 7 (46.67%)\n"
      "Winner: E\n";
      }
      
    EXPECT_EQ(actual, expectedResults);
}

// IRElection_12
TEST(IRElectionTests, WriteResultsAndRunElection_WinnerTie) { 
    ifstream testElectionFile ("../testing/IRElectionTests_WinnerTie.csv", std::ifstream::in);
    testElectionFile.ignore(256, '\n');

    IRElection testElection = IRElection(testElectionFile, "02222012");
    testElection.RunElection();
    testElection.WriteResultsToFile();

    EXPECT_EQ(testElectionFile.is_open(), false);
    std::string expectedOut =    
      "IRElection\n"
      "Number of Candidates: 5\n"
      "Candidate 1: A\n"
      "Candidate 2: B\n"
      "Candidate 3: C\n"
      "Candidate 4: D\n"
      "Candidate 5: E\n"
      "Number of ballots: 15\n"
      "Ballot ID: 1 Ballot Info: 1,,,,2\n"
      "Ballot ID: 2 Ballot Info: 1,,,,2\n"
      "Ballot ID: 3 Ballot Info: 1,,,,\n"
      "Ballot ID: 4 Ballot Info: ,1,,,2\n"
      "Ballot ID: 5 Ballot Info: ,1,2,,\n"
      "Ballot ID: 6 Ballot Info: ,,1,,\n"
      "Ballot ID: 7 Ballot Info: ,,1,,\n"
      "Ballot ID: 8 Ballot Info: ,,1,,\n"
      "Ballot ID: 9 Ballot Info: ,,1,,\n"
      "Ballot ID: 10 Ballot Info: ,,1,,\n"
      "Ballot ID: 11 Ballot Info: ,,2,1,\n"
      "Ballot ID: 12 Ballot Info: ,,,,1\n"
      "Ballot ID: 13 Ballot Info: ,,,,1\n"
      "Ballot ID: 14 Ballot Info: ,,,,1\n"
      "Ballot ID: 15 Ballot Info: ,,,,1\n"
      "Counting Ballots\n"
      "Ballot #1 went to Candidate #1\n"
      "Ballot #2 went to Candidate #1\n"
      "Ballot #3 went to Candidate #1\n"
      "Ballot #4 went to Candidate #2\n"
      "Ballot #5 went to Candidate #2\n"
      "Ballot #6 went to Candidate #3\n"
      "Ballot #7 went to Candidate #3\n"
      "Ballot #8 went to Candidate #3\n"
      "Ballot #9 went to Candidate #3\n"
      "Ballot #10 went to Candidate #3\n"
      "Ballot #11 went to Candidate #4\n"
      "Ballot #12 went to Candidate #5\n"
      "Ballot #13 went to Candidate #5\n"
      "Ballot #14 went to Candidate #5\n"
      "Ballot #15 went to Candidate #5\n"
      "Candidate #1 received 3 vote(s)\n"
      "Candidate #2 received 2 vote(s)\n"
      "Candidate #3 received 5 vote(s)\n"
      "Candidate #4 received 1 vote(s)\n"
      "Candidate #5 received 4 vote(s)\n"
      "No Majority Found with more than 2 Candidates remaining\n"
      "Dropped Candidate Name: D\n"
      "Redistribute Votes\n"
      "Ballot #1 went to Candidate #1\n"
      "Ballot #2 went to Candidate #1\n"
      "Ballot #3 went to Candidate #1\n"
      "Ballot #4 went to Candidate #2\n"
      "Ballot #5 went to Candidate #2\n"
      "Ballot #6 went to Candidate #3\n"
      "Ballot #7 went to Candidate #3\n"
      "Ballot #8 went to Candidate #3\n"
      "Ballot #9 went to Candidate #3\n"
      "Ballot #10 went to Candidate #3\n"
      "Ballot #11 went to Candidate #3\n"
      "Ballot #12 went to Candidate #5\n"
      "Ballot #13 went to Candidate #5\n"
      "Ballot #14 went to Candidate #5\n"
      "Ballot #15 went to Candidate #5\n"
      "Candidate #1 received 3 vote(s)\n"
      "Candidate #2 received 2 vote(s)\n"
      "Candidate #3 received 6 vote(s)\n"
      "Candidate #4 received 0 vote(s)\n"
      "Candidate #5 received 4 vote(s)\n"
      "No Majority Found with more than 2 Candidates remaining\n"
      "Dropped Candidate Name: B\n"
      "Redistribute Votes\n"
      "Ballot #1 went to Candidate #1\n"
      "Ballot #2 went to Candidate #1\n"
      "Ballot #3 went to Candidate #1\n"
      "Ballot #4 went to Candidate #5\n"
      "Ballot #5 went to Candidate #3\n"
      "Ballot #6 went to Candidate #3\n"
      "Ballot #7 went to Candidate #3\n"
      "Ballot #8 went to Candidate #3\n"
      "Ballot #9 went to Candidate #3\n"
      "Ballot #10 went to Candidate #3\n"
      "Ballot #11 went to Candidate #3\n"
      "Ballot #12 went to Candidate #5\n"
      "Ballot #13 went to Candidate #5\n"
      "Ballot #14 went to Candidate #5\n"
      "Ballot #15 went to Candidate #5\n"
      "Candidate #1 received 3 vote(s)\n"
      "Candidate #2 received 0 vote(s)\n"
      "Candidate #3 received 7 vote(s)\n"
      "Candidate #4 received 0 vote(s)\n"
      "Candidate #5 received 5 vote(s)\n"
      "No Majority Found with more than 2 Candidates remaining\n"
      "Dropped Candidate Name: A\n"
      "Redistribute Votes\n"
      "Ballot #1 went to Candidate #5\n"
      "Ballot #2 went to Candidate #5\n"
      "Ballot #4 went to Candidate #5\n"
      "Ballot #5 went to Candidate #3\n"
      "Ballot #6 went to Candidate #3\n"
      "Ballot #7 went to Candidate #3\n"
      "Ballot #8 went to Candidate #3\n"
      "Ballot #9 went to Candidate #3\n"
      "Ballot #10 went to Candidate #3\n"
      "Ballot #11 went to Candidate #3\n"
      "Ballot #12 went to Candidate #5\n"
      "Ballot #13 went to Candidate #5\n"
      "Ballot #14 went to Candidate #5\n"
      "Ballot #15 went to Candidate #5\n"
      "Candidate #1 received 0 vote(s)\n"
      "Candidate #2 received 0 vote(s)\n"
      "Candidate #3 received 7 vote(s)\n"
      "Candidate #4 received 0 vote(s)\n"
      "Candidate #5 received 7 vote(s)\n"
      "Remaining 2 Candidates with no majority move to popularity\n"
      "Tie Has Occurred and after TieBreaker C has won with 7 Votes\n";
    
    std::string expectedOut1 = 
      "IRElection\n"
      "Number of Candidates: 5\n"
      "Candidate 1: A\n"
      "Candidate 2: B\n"
      "Candidate 3: C\n"
      "Candidate 4: D\n"
      "Candidate 5: E\n"
      "Number of ballots: 15\n"
      "Ballot ID: 1 Ballot Info: 1,,,,2\n"
      "Ballot ID: 2 Ballot Info: 1,,,,2\n"
      "Ballot ID: 3 Ballot Info: 1,,,,\n"
      "Ballot ID: 4 Ballot Info: ,1,,,2\n"
      "Ballot ID: 5 Ballot Info: ,1,2,,\n"
      "Ballot ID: 6 Ballot Info: ,,1,,\n"
      "Ballot ID: 7 Ballot Info: ,,1,,\n"
      "Ballot ID: 8 Ballot Info: ,,1,,\n"
      "Ballot ID: 9 Ballot Info: ,,1,,\n"
      "Ballot ID: 10 Ballot Info: ,,1,,\n"
      "Ballot ID: 11 Ballot Info: ,,2,1,\n"
      "Ballot ID: 12 Ballot Info: ,,,,1\n"
      "Ballot ID: 13 Ballot Info: ,,,,1\n"
      "Ballot ID: 14 Ballot Info: ,,,,1\n"
      "Ballot ID: 15 Ballot Info: ,,,,1\n"
      "Counting Ballots\n"
      "Ballot #1 went to Candidate #1\n"
      "Ballot #2 went to Candidate #1\n"
      "Ballot #3 went to Candidate #1\n"
      "Ballot #4 went to Candidate #2\n"
      "Ballot #5 went to Candidate #2\n"
      "Ballot #6 went to Candidate #3\n"
      "Ballot #7 went to Candidate #3\n"
      "Ballot #8 went to Candidate #3\n"
      "Ballot #9 went to Candidate #3\n"
      "Ballot #10 went to Candidate #3\n"
      "Ballot #11 went to Candidate #4\n"
      "Ballot #12 went to Candidate #5\n"
      "Ballot #13 went to Candidate #5\n"
      "Ballot #14 went to Candidate #5\n"
      "Ballot #15 went to Candidate #5\n"
      "Candidate #1 received 3 vote(s)\n"
      "Candidate #2 received 2 vote(s)\n"
      "Candidate #3 received 5 vote(s)\n"
      "Candidate #4 received 1 vote(s)\n"
      "Candidate #5 received 4 vote(s)\n"
      "No Majority Found with more than 2 Candidates remaining\n"
      "Dropped Candidate Name: D\n"
      "Redistribute Votes\n"
      "Ballot #1 went to Candidate #1\n"
      "Ballot #2 went to Candidate #1\n"
      "Ballot #3 went to Candidate #1\n"
      "Ballot #4 went to Candidate #2\n"
      "Ballot #5 went to Candidate #2\n"
      "Ballot #6 went to Candidate #3\n"
      "Ballot #7 went to Candidate #3\n"
      "Ballot #8 went to Candidate #3\n"
      "Ballot #9 went to Candidate #3\n"
      "Ballot #10 went to Candidate #3\n"
      "Ballot #11 went to Candidate #3\n"
      "Ballot #12 went to Candidate #5\n"
      "Ballot #13 went to Candidate #5\n"
      "Ballot #14 went to Candidate #5\n"
      "Ballot #15 went to Candidate #5\n"
      "Candidate #1 received 3 vote(s)\n"
      "Candidate #2 received 2 vote(s)\n"
      "Candidate #3 received 6 vote(s)\n"
      "Candidate #4 received 0 vote(s)\n"
      "Candidate #5 received 4 vote(s)\n"
      "No Majority Found with more than 2 Candidates remaining\n"
      "Dropped Candidate Name: B\n"
      "Redistribute Votes\n"
      "Ballot #1 went to Candidate #1\n"
      "Ballot #2 went to Candidate #1\n"
      "Ballot #3 went to Candidate #1\n"
      "Ballot #4 went to Candidate #5\n"
      "Ballot #5 went to Candidate #3\n"
      "Ballot #6 went to Candidate #3\n"
      "Ballot #7 went to Candidate #3\n"
      "Ballot #8 went to Candidate #3\n"
      "Ballot #9 went to Candidate #3\n"
      "Ballot #10 went to Candidate #3\n"
      "Ballot #11 went to Candidate #3\n"
      "Ballot #12 went to Candidate #5\n"
      "Ballot #13 went to Candidate #5\n"
      "Ballot #14 went to Candidate #5\n"
      "Ballot #15 went to Candidate #5\n"
      "Candidate #1 received 3 vote(s)\n"
      "Candidate #2 received 0 vote(s)\n"
      "Candidate #3 received 7 vote(s)\n"
      "Candidate #4 received 0 vote(s)\n"
      "Candidate #5 received 5 vote(s)\n"
      "No Majority Found with more than 2 Candidates remaining\n"
      "Dropped Candidate Name: A\n"
      "Redistribute Votes\n"
      "Ballot #1 went to Candidate #5\n"
      "Ballot #2 went to Candidate #5\n"
      "Ballot #4 went to Candidate #5\n"
      "Ballot #5 went to Candidate #3\n"
      "Ballot #6 went to Candidate #3\n"
      "Ballot #7 went to Candidate #3\n"
      "Ballot #8 went to Candidate #3\n"
      "Ballot #9 went to Candidate #3\n"
      "Ballot #10 went to Candidate #3\n"
      "Ballot #11 went to Candidate #3\n"
      "Ballot #12 went to Candidate #5\n"
      "Ballot #13 went to Candidate #5\n"
      "Ballot #14 went to Candidate #5\n"
      "Ballot #15 went to Candidate #5\n"
      "Candidate #1 received 0 vote(s)\n"
      "Candidate #2 received 0 vote(s)\n"
      "Candidate #3 received 7 vote(s)\n"
      "Candidate #4 received 0 vote(s)\n"
      "Candidate #5 received 7 vote(s)\n"
      "Remaining 2 Candidates with no majority move to popularity\n"
      "Tie Has Occurred and after TieBreaker E has won with 7 Votes\n";

    ifstream actualOutRead ("02222012IR.txt");
    stringstream actualOut;
    actualOut << actualOutRead.rdbuf(); 

    bool testPassed = false;
    if (actualOut.str() == expectedOut || actualOut.str()== expectedOut1) {
        testPassed = true;
    }

    EXPECT_TRUE(testPassed);
    remove("02222012IR.txt");
}

// IRElection_13
TEST(IRElectionTests, DisplayResultsAndRunElection_WinnerAndDropTie) { 
    ifstream testElectionFile ("../testing/IRElectionTests_WinnerAndDropTie.csv", std::ifstream::in);
    testElectionFile.ignore(256, '\n');

    IRElection testElection = IRElection(testElectionFile, "02222013");
    testElection.RunElection();

    std::string expectedResults = 
      "Election type: IR\n"
      "Number of candidates: 5\n"
      "Number of ballots cast: 15\n"
      "IR Election results in last round: \n";
    
    testing::internal::CaptureStdout();
    testElection.DisplayResults();
    std::string actual = testing::internal::GetCapturedStdout();
    if(actual == 
      "Election type: IR\n"
      "Number of candidates: 5\n"
      "Number of ballots cast: 15\n"
      "IR Election results in last round: \n"
      "Number of votes for candidate number 1: 0 (0.00%)\n"
      "Number of votes for candidate number 2: 0 (0.00%)\n"
      "Number of votes for candidate number 3: 7 (46.67%)\n"
      "Number of votes for candidate number 4: 0 (0.00%)\n"
      "Number of votes for candidate number 5: 7 (46.67%)\n"
      "Winner: C\n"
      ) {
        expectedResults += 
      "Number of votes for candidate number 1: 0 (0.00%)\n"
      "Number of votes for candidate number 2: 0 (0.00%)\n"
      "Number of votes for candidate number 3: 7 (46.67%)\n"
      "Number of votes for candidate number 4: 0 (0.00%)\n"
      "Number of votes for candidate number 5: 7 (46.67%)\n"
      "Winner: C\n";
      } else if(actual == 
      "Election type: IR\n"
      "Number of candidates: 5\n"
      "Number of ballots cast: 15\n"
      "IR Election results in last round: \n"
      "Number of votes for candidate number 1: 0 (0.00%)\n"
      "Number of votes for candidate number 2: 0 (0.00%)\n"
      "Number of votes for candidate number 3: 7 (46.67%)\n"
      "Number of votes for candidate number 4: 0 (0.00%)\n"
      "Number of votes for candidate number 5: 7 (46.67%)\n"
      "Winner: E\n"
      ) {
        expectedResults += 
      "Number of votes for candidate number 1: 0 (0.00%)\n"
      "Number of votes for candidate number 2: 0 (0.00%)\n"
      "Number of votes for candidate number 3: 7 (46.67%)\n"
      "Number of votes for candidate number 4: 0 (0.00%)\n"
      "Number of votes for candidate number 5: 7 (46.67%)\n"
      "Winner: E\n";
      } else if(actual == 
      "Election type: IR\n"
      "Number of candidates: 5\n"
      "Number of ballots cast: 15\n"
      "IR Election results in last round: \n"
      "Number of votes for candidate number 1: 7 (46.67%)\n"
      "Number of votes for candidate number 2: 0 (0.00%)\n"
      "Number of votes for candidate number 3: 7 (46.67%)\n"
      "Number of votes for candidate number 4: 0 (0.00%)\n"
      "Number of votes for candidate number 5: 0 (0.00%)\n"
      "Winner: A\n"
      ) {
        expectedResults += 
      "Number of votes for candidate number 1: 7 (46.67%)\n"
      "Number of votes for candidate number 2: 0 (0.00%)\n"
      "Number of votes for candidate number 3: 7 (46.67%)\n"
      "Number of votes for candidate number 4: 0 (0.00%)\n"
      "Number of votes for candidate number 5: 0 (0.00%)\n"
      "Winner: A\n";
      } else if(actual == 
      "Election type: IR\n"
      "Number of candidates: 5\n"
      "Number of ballots cast: 15\n"
      "IR Election results in last round: \n"
      "Number of votes for candidate number 1: 7 (46.67%)\n"
      "Number of votes for candidate number 2: 0 (0.00%)\n"
      "Number of votes for candidate number 3: 7 (46.67%)\n"
      "Number of votes for candidate number 4: 0 (0.00%)\n"
      "Number of votes for candidate number 5: 0 (0.00%)\n"
      "Winner: C\n"
      ) {
        expectedResults += 
      "Number of votes for candidate number 1: 7 (46.67%)\n"
      "Number of votes for candidate number 2: 0 (0.00%)\n"
      "Number of votes for candidate number 3: 7 (46.67%)\n"
      "Number of votes for candidate number 4: 0 (0.00%)\n"
      "Number of votes for candidate number 5: 0 (0.00%)\n"
      "Winner: C\n";
      }
      
    EXPECT_EQ(actual, expectedResults);
}

// TieBreakerAlgorithm
TEST(IRElectionTests, RandomnessTieBreakerAlgortihm) { 
  int A = 0;
  int B = 0;

  //The algorithm use in TieBreaker 
  srand(time(NULL)); 
  bool fair = false;
  for (int i=0; i< 10000; i++) {
    vector<int> options(2, 0);
    int returnIndex = rand() % options.size();
    if (returnIndex == 0){
      A++;
    } else if (returnIndex == 1) {
      B++;
    }
  }

  if (A > 400 && A < 600) {
    fair = true;
  }

  EXPECT_EQ(fair, true);

}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}