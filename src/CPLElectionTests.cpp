/**
 * @file CPLElection.cpp
 * @author Dheva Subramaniam subra231@umn.edu
 * @brief Source file containing tests for the CPLElection class
 * @version 0.1
 * @date 2023-03-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "gtest/gtest.h"
#include "CPLElection.h"

#include <iostream>
#include <string>

TEST(CPLElectionTests, ReadElectionAndDisplayResults_Basic) {                                 // TestID: CPLElection_01
    ifstream testElectionFile ("../testing/CPLElectionTest_Basic.csv", std::ifstream::in);
    testElectionFile.ignore(256, '\n');

    CPLElection testElection = CPLElection(testElectionFile, "05012001");
    EXPECT_EQ(testElectionFile.is_open(), false);
    
    testing::internal::CaptureStdout();
    testElection.DisplayResults();
    
    string expectedOut =    "Election type: CPL\n"
                            "Number of seats: 3\n"
                            "Number of ballots cast: 8\n"
                            "Party results: \n"
                            "PartyA: \n"
                            "Number of votes: 0 (0.00%)\n"
                            "Number of seats: 0 (0.00%)\n"
                            "PartyB: \n"
                            "Number of votes: 0 (0.00%)\n"
                            "Number of seats: 0 (0.00%)\n"
                            "PartyC: \n"
                            "Number of votes: 0 (0.00%)\n"
                            "Number of seats: 0 (0.00%)\n"
                            "PartyD: \n"
                            "Number of votes: 0 (0.00%)\n"
                            "Number of seats: 0 (0.00%)\n"
                            "PartyE: \n"
                            "Number of votes: 0 (0.00%)\n"
                            "Number of seats: 0 (0.00%)\n"
                            "Candidates receiving seats:\n"
                            "PartyA: None\n"
                            "PartyB: None\n"
                            "PartyC: None\n"
                            "PartyD: None\n"
                            "PartyE: None\n";
    
    EXPECT_EQ(testing::internal::GetCapturedStdout(), expectedOut);
}

TEST(CPLElectionTests, ReadElectionAndWriteResults_Basic) {                                   // TestID: CPLElection_02
    ifstream testElectionFile ("../testing/CPLElectionTest_Basic.csv", std::ifstream::in);
    testElectionFile.ignore(256, '\n');

    CPLElection testElection = CPLElection(testElectionFile, "05022001");
    testElection.WriteResultsToFile();

    EXPECT_EQ(testElectionFile.is_open(), false);
    string expectedOut =    "CPLElection\n"
                            "Number of Parties: 5\n"
                            "PartyA: A,B,C,D\n"
                            "PartyB: E,F,G\n"
                            "PartyC: H,I,J,K,L\n"
                            "PartyD: M,N\n"
                            "PartyE: O\n"
                            "Number of seats: 3\n"
                            "Number of ballots: 8\n"
                            "Ballot ID: 1 Ballot Info: 1,,,,\n"
                            "Ballot ID: 2 Ballot Info: ,,1,,\n"
                            "Ballot ID: 3 Ballot Info: ,,,1,\n"
                            "Ballot ID: 4 Ballot Info: ,,1,,\n"
                            "Ballot ID: 5 Ballot Info: ,,1,,\n"
                            "Ballot ID: 6 Ballot Info: ,,,,1\n"
                            "Ballot ID: 7 Ballot Info: ,,,,1\n"
                            "Ballot ID: 8 Ballot Info: ,,,1,\n";
    
    ifstream actualOutRead ("05022001CPL.txt");
    stringstream actualOut;
    actualOut << actualOutRead.rdbuf();
    
    EXPECT_EQ(actualOut.str(), expectedOut);
}

TEST(CPLElectionTests, RunElectionandDisplayTest_Basic) {                                     // TestID: CPLElection_03
    ifstream testElectionFile ("../testing/CPLElectionTest_Basic.csv", std::ifstream::in);
    testElectionFile.ignore(256, '\n');

    CPLElection testElection = CPLElection(testElectionFile, "05032001");
    testElection.RunElection();
    EXPECT_EQ(testElectionFile.is_open(), false);
    
    testing::internal::CaptureStdout();
    testElection.DisplayResults();
    
    string expectedOut =    "Election type: CPL\n"
                            "Number of seats: 3\n"
                            "Number of ballots cast: 8\n"
                            "Party results: \n"
                            "PartyA: \n"
                            "Number of votes: 1 (12.50%)\n"
                            "Number of seats: 0 (0.00%)\n"
                            "PartyB: \n"
                            "Number of votes: 0 (0.00%)\n"
                            "Number of seats: 0 (0.00%)\n"
                            "PartyC: \n"
                            "Number of votes: 3 (37.50%)\n"
                            "Number of seats: 1 (33.33%)\n"
                            "PartyD: \n"
                            "Number of votes: 2 (25.00%)\n"
                            "Number of seats: 1 (33.33%)\n"
                            "PartyE: \n"
                            "Number of votes: 2 (25.00%)\n"
                            "Number of seats: 1 (33.33%)\n"
                            "Candidates receiving seats:\n"
                            "PartyA: None\n"
                            "PartyB: None\n"
                            "PartyC: H\n"
                            "PartyD: M\n"
                            "PartyE: O\n";
    
    EXPECT_EQ(testing::internal::GetCapturedStdout(), expectedOut);
}

TEST(CPLElectionTests, RunElectionandWriteTest_Basic) {                                       // TestID: CPLElection_04
    ifstream testElectionFile ("../testing/CPLElectionTest_Basic.csv", std::ifstream::in);
    testElectionFile.ignore(256, '\n');

    CPLElection testElection = CPLElection(testElectionFile, "05042001");
    testElection.RunElection();
    testElection.WriteResultsToFile();

    EXPECT_EQ(testElectionFile.is_open(), false);
    string expectedOut =    "CPLElection\n"
                            "Number of Parties: 5\n"
                            "PartyA: A,B,C,D\n"
                            "PartyB: E,F,G\n"
                            "PartyC: H,I,J,K,L\n"
                            "PartyD: M,N\n"
                            "PartyE: O\n"
                            "Number of seats: 3\n"
                            "Number of ballots: 8\n"
                            "Ballot ID: 1 Ballot Info: 1,,,,\n"
                            "Ballot ID: 2 Ballot Info: ,,1,,\n"
                            "Ballot ID: 3 Ballot Info: ,,,1,\n"
                            "Ballot ID: 4 Ballot Info: ,,1,,\n"
                            "Ballot ID: 5 Ballot Info: ,,1,,\n"
                            "Ballot ID: 6 Ballot Info: ,,,,1\n"
                            "Ballot ID: 7 Ballot Info: ,,,,1\n"
                            "Ballot ID: 8 Ballot Info: ,,,1,\n"
                            "Counting ballots:\n"
                            "Party \"PartyA\" received ballot number 1\n"
                            "Party \"PartyC\" received ballot number 2\n"
                            "Party \"PartyD\" received ballot number 3\n"
                            "Party \"PartyC\" received ballot number 4\n"
                            "Party \"PartyC\" received ballot number 5\n"
                            "Party \"PartyE\" received ballot number 6\n"
                            "Party \"PartyE\" received ballot number 7\n"
                            "Party \"PartyD\" received ballot number 8\n"
                            "Quota determined to be: 2\n"
                            "Party \"PartyA\" | Seats assigned using quota: 0\n"
                            "Party \"PartyB\" | Seats assigned using quota: 0\n"
                            "Party \"PartyC\" | Seats assigned using quota: 1\n"
                            "Party \"PartyD\" | Seats assigned using quota: 1\n"
                            "Party \"PartyE\" | Seats assigned using quota: 1\n"
                            "Candidates receiving seats:\n"
                            "PartyA: None\n"
                            "PartyB: None\n"
                            "PartyC: H\n"
                            "PartyD: M\n"
                            "PartyE: O\n";
    
    ifstream actualOutRead ("05042001CPL.txt");
    stringstream actualOut;
    actualOut << actualOutRead.rdbuf();
    
    EXPECT_EQ(actualOut.str(), expectedOut);
}

TEST(CPLElectionTests, RunElectionandDisplayTest_RemainderAllocation) {                         // TestID: CPLElection_05
    ifstream testElectionFile ("../testing/CPLElectionTest_RemainderAllocation.csv", std::ifstream::in);
    testElectionFile.ignore(256, '\n');

    CPLElection testElection = CPLElection(testElectionFile, "05052001");
    testElection.RunElection();
    EXPECT_EQ(testElectionFile.is_open(), false);
    
    testing::internal::CaptureStdout();
    testElection.DisplayResults();
    
    string expectedOut =    "Election type: CPL\n"
                            "Number of seats: 7\n"
                            "Number of ballots cast: 21\n"
                            "Party results: \n"
                            "PartyA: \n"
                            "Number of votes: 12 (57.14%)\n"
                            "Number of seats: 4 (57.14%)\n"
                            "PartyB: \n"
                            "Number of votes: 8 (38.10%)\n"
                            "Number of seats: 3 (42.86%)\n"
                            "PartyC: \n"
                            "Number of votes: 1 (4.76%)\n"
                            "Number of seats: 0 (0.00%)\n"
                            "Candidates receiving seats:\n"
                            "PartyA: A B C D\n"
                            "PartyB: E F G\n"
                            "PartyC: None\n";
    
    EXPECT_EQ(testing::internal::GetCapturedStdout(), expectedOut);
}

TEST(CPLElectionTests, RunElectionandWriteTest_RemainderAllocation) {                           // TestID: CPLElection_06
    ifstream testElectionFile ("../testing/CPLElectionTest_RemainderAllocation.csv", std::ifstream::in);
    testElectionFile.ignore(256, '\n');

    CPLElection testElection = CPLElection(testElectionFile, "05062001");
    testElection.RunElection();
    testElection.WriteResultsToFile();

    EXPECT_EQ(testElectionFile.is_open(), false);
    string expectedOut =    "CPLElection\n"
                            "Number of Parties: 3\n"
                            "PartyA: A,B,C,D\n"
                            "PartyB: E,F,G\n"
                            "PartyC: H,I\n"
                            "Number of seats: 7\n"
                            "Number of ballots: 21\n"
                            "Ballot ID: 1 Ballot Info: 1,,\n"
                            "Ballot ID: 2 Ballot Info: 1,,\n"
                            "Ballot ID: 3 Ballot Info: 1,,\n"
                            "Ballot ID: 4 Ballot Info: 1,,\n"
                            "Ballot ID: 5 Ballot Info: 1,,\n"
                            "Ballot ID: 6 Ballot Info: 1,,\n"
                            "Ballot ID: 7 Ballot Info: 1,,\n"
                            "Ballot ID: 8 Ballot Info: 1,,\n"
                            "Ballot ID: 9 Ballot Info: 1,,\n"
                            "Ballot ID: 10 Ballot Info: 1,,\n"
                            "Ballot ID: 11 Ballot Info: 1,,\n"
                            "Ballot ID: 12 Ballot Info: 1,,\n"
                            "Ballot ID: 13 Ballot Info: ,1,\n"
                            "Ballot ID: 14 Ballot Info: ,1,\n"
                            "Ballot ID: 15 Ballot Info: ,1,\n"
                            "Ballot ID: 16 Ballot Info: ,1,\n"
                            "Ballot ID: 17 Ballot Info: ,1,\n"
                            "Ballot ID: 18 Ballot Info: ,1,\n"
                            "Ballot ID: 19 Ballot Info: ,1,\n"
                            "Ballot ID: 20 Ballot Info: ,1,\n"
                            "Ballot ID: 21 Ballot Info: ,,1\n"
                            "Counting ballots:\n"
                            "Party \"PartyA\" received ballot number 1\n"
                            "Party \"PartyA\" received ballot number 2\n"
                            "Party \"PartyA\" received ballot number 3\n"
                            "Party \"PartyA\" received ballot number 4\n"
                            "Party \"PartyA\" received ballot number 5\n"
                            "Party \"PartyA\" received ballot number 6\n"
                            "Party \"PartyA\" received ballot number 7\n"
                            "Party \"PartyA\" received ballot number 8\n"
                            "Party \"PartyA\" received ballot number 9\n"
                            "Party \"PartyA\" received ballot number 10\n"
                            "Party \"PartyA\" received ballot number 11\n"
                            "Party \"PartyA\" received ballot number 12\n"
                            "Party \"PartyB\" received ballot number 13\n"
                            "Party \"PartyB\" received ballot number 14\n"
                            "Party \"PartyB\" received ballot number 15\n"
                            "Party \"PartyB\" received ballot number 16\n"
                            "Party \"PartyB\" received ballot number 17\n"
                            "Party \"PartyB\" received ballot number 18\n"
                            "Party \"PartyB\" received ballot number 19\n"
                            "Party \"PartyB\" received ballot number 20\n"
                            "Party \"PartyC\" received ballot number 21\n"
                            "Quota determined to be: 3\n"
                            "Party \"PartyA\" | Seats assigned using quota: 4\n"
                            "Party \"PartyB\" | Seats assigned using quota: 2\n"
                            "Party \"PartyC\" | Seats assigned using quota: 0\n"
                            "Awarded remainder seat to \"PartyB\"\n"
                            "Candidates receiving seats:\n"
                            "PartyA: A B C D\n"
                            "PartyB: E F G\n"
                            "PartyC: None\n";
    
    ifstream actualOutRead ("05062001CPL.txt");
    stringstream actualOut;
    actualOut << actualOutRead.rdbuf();
    
    EXPECT_EQ(actualOut.str(), expectedOut);
}

TEST(CPLElectionTests, RunElectionandDisplayTest_TieDuringRemainder) {                          // TestID: CPLElection_07
    ifstream testElectionFile ("../testing/CPLElectionTest_TieDuringRemainder.csv", std::ifstream::in);
    testElectionFile.ignore(256, '\n');

    CPLElection testElection = CPLElection(testElectionFile, "05072001");
    testElection.RunElection();
    EXPECT_EQ(testElectionFile.is_open(), false);
    
    testing::internal::CaptureStdout();
    testElection.DisplayResults();
    
    string expectedOutDefinite =    "Election type: CPL\n"
                            "Number of seats: 6\n"
                            "Number of ballots cast: 12\n"
                            "Party results: \n"
                            "PartyA: \n"
                            "Number of votes: 6 (50.00%)\n"
                            "Number of seats: 3 (50.00%)\n"
                            "PartyB: \n"
                            "Number of votes: 4 (33.33%)\n"
                            "Number of seats: 2 (33.33%)\n";

    string expectedOutOption1 = "PartyC: \n"
                            "Number of votes: 1 (8.33%)\n"
                            "Number of seats: 1 (16.67%)\n"
                            "PartyD: \n"
                            "Number of votes: 1 (8.33%)\n"
                            "Number of seats: 0 (0.00%)\n"
                            "Candidates receiving seats:\n"
                            "PartyA: A B C\n"
                            "PartyB: E F\n"
                            "PartyC: H\n"
                            "PartyD: None\n";

    string expectedOutOption2 = "PartyC: \n"
                            "Number of votes: 1 (8.33%)\n"
                            "Number of seats: 0 (0.00%)\n"
                            "PartyD: \n"
                            "Number of votes: 1 (8.33%)\n"
                            "Number of seats: 1 (16.67%)\n"
                            "Candidates receiving seats:\n"
                            "PartyA: A B C\n"
                            "PartyB: E F\n"
                            "PartyC: None\n"
                            "PartyD: J\n";
    
    string actualOut = testing::internal::GetCapturedStdout();
    size_t splitter;
    splitter = actualOut.find("PartyC: \n");
    string actualOutDefinite = actualOut.substr(0,splitter);
    string actualOutOption = actualOut.substr(splitter, string::npos);

    EXPECT_EQ(actualOutDefinite, expectedOutDefinite);

    EXPECT_PRED3(
        [](string actual, string option1, string option2) {return actual.compare(option1) == 0 || actual.compare(option2) == 0;}, 
        actualOutOption, expectedOutOption1, expectedOutOption2);
}

TEST(CPLElectionTests, RunElectionandWriteTest_TieDuringRemainder) {                            // TestID: CPLElection_08
    ifstream testElectionFile ("../testing/CPLElectionTest_TieDuringRemainder.csv", std::ifstream::in);
    testElectionFile.ignore(256, '\n');

    CPLElection testElection = CPLElection(testElectionFile, "05082001");
    testElection.RunElection();
    testElection.WriteResultsToFile();

    EXPECT_EQ(testElectionFile.is_open(), false);
    string expectedOutDefinite =    "CPLElection\n"
                            "Number of Parties: 4\n"
                            "PartyA: A,B,C,D\n"
                            "PartyB: E,F,G\n"
                            "PartyC: H,I\n"
                            "PartyD: J,K\n"
                            "Number of seats: 6\n"
                            "Number of ballots: 12\n"
                            "Ballot ID: 1 Ballot Info: 1,,,\n"
                            "Ballot ID: 2 Ballot Info: 1,,,\n"
                            "Ballot ID: 3 Ballot Info: 1,,,\n"
                            "Ballot ID: 4 Ballot Info: 1,,,\n"
                            "Ballot ID: 5 Ballot Info: 1,,,\n"
                            "Ballot ID: 6 Ballot Info: 1,,,\n"
                            "Ballot ID: 7 Ballot Info: ,1,,\n"
                            "Ballot ID: 8 Ballot Info: ,1,,\n"
                            "Ballot ID: 9 Ballot Info: ,1,,\n"
                            "Ballot ID: 10 Ballot Info: ,1,,\n"
                            "Ballot ID: 11 Ballot Info: ,,1,\n"
                            "Ballot ID: 12 Ballot Info: ,,,1\n"
                            "Counting ballots:\n"
                            "Party \"PartyA\" received ballot number 1\n"
                            "Party \"PartyA\" received ballot number 2\n"
                            "Party \"PartyA\" received ballot number 3\n"
                            "Party \"PartyA\" received ballot number 4\n"
                            "Party \"PartyA\" received ballot number 5\n"
                            "Party \"PartyA\" received ballot number 6\n"
                            "Party \"PartyB\" received ballot number 7\n"
                            "Party \"PartyB\" received ballot number 8\n"
                            "Party \"PartyB\" received ballot number 9\n"
                            "Party \"PartyB\" received ballot number 10\n"
                            "Party \"PartyC\" received ballot number 11\n"
                            "Party \"PartyD\" received ballot number 12\n"
                            "Quota determined to be: 2\n"
                            "Party \"PartyA\" | Seats assigned using quota: 3\n"
                            "Party \"PartyB\" | Seats assigned using quota: 2\n"
                            "Party \"PartyC\" | Seats assigned using quota: 0\n"
                            "Party \"PartyD\" | Seats assigned using quota: 0\n"
                            "Tie during seat allocation between PartyC and PartyD\n";

    string expectedOutOption1 = "Awarded remainder seat to \"PartyC\"\n"
                            "Candidates receiving seats:\n"
                            "PartyA: A B C\n"
                            "PartyB: E F\n"
                            "PartyC: H\n"
                            "PartyD: None\n";

    string expectedOutOption2 = "Awarded remainder seat to \"PartyD\"\n"
                            "Candidates receiving seats:\n"
                            "PartyA: A B C\n"
                            "PartyB: E F\n"
                            "PartyC: None\n"
                            "PartyD: J\n";
    
    ifstream actualOutRead ("05082001CPL.txt");
    stringstream actualOut;
    actualOut << actualOutRead.rdbuf();
    string actualOutStr = actualOut.str();

    size_t splitter;
    splitter = actualOutStr.find("Awarded");
    string actualOutDefinite = actualOutStr.substr(0,splitter);
    string actualOutOption = actualOutStr.substr(splitter, string::npos);

    EXPECT_EQ(actualOutDefinite, expectedOutDefinite);
    
    EXPECT_PRED3(
        [](string actual, string option1, string option2) {return actual.compare(option1) == 0 || actual.compare(option2) == 0;}, 
        actualOutOption, expectedOutOption1, expectedOutOption2);
}

TEST(CPLElectionTests, RunElectionandDisplayTest_SeatRedistribution) {                          // TestID: CPLElection_09
    ifstream testElectionFile ("../testing/CPLElectionTest_SeatRedistribution.csv", std::ifstream::in);
    testElectionFile.ignore(256, '\n');

    CPLElection testElection = CPLElection(testElectionFile, "05092001");
    testElection.RunElection();
    EXPECT_EQ(testElectionFile.is_open(), false);
    
    testing::internal::CaptureStdout();
    testElection.DisplayResults();
    
    string expectedOut =    "Election type: CPL\n"
                            "Number of seats: 8\n"
                            "Number of ballots cast: 17\n"
                            "Party results: \n"
                            "PartyA: \n"
                            "Number of votes: 8 (47.06%)\n"
                            "Number of seats: 3 (37.50%)\n"
                            "PartyB: \n"
                            "Number of votes: 7 (41.18%)\n"
                            "Number of seats: 4 (50.00%)\n"
                            "PartyC: \n"
                            "Number of votes: 2 (11.76%)\n"
                            "Number of seats: 1 (12.50%)\n"
                            "Candidates receiving seats:\n"
                            "PartyA: A B C\n"
                            "PartyB: D E F G\n"
                            "PartyC: H\n";
    
    EXPECT_EQ(testing::internal::GetCapturedStdout(), expectedOut);
}

TEST(CPLElectionTests, RunElectionandWriteTest_SeatRedistribution) {                            // TestID: CPLElection_10
    ifstream testElectionFile ("../testing/CPLElectionTest_SeatRedistribution.csv", std::ifstream::in);
    testElectionFile.ignore(256, '\n');

    CPLElection testElection = CPLElection(testElectionFile, "05102001");
    testElection.RunElection();
    testElection.WriteResultsToFile();

    EXPECT_EQ(testElectionFile.is_open(), false);
    string expectedOut =    "CPLElection\n"
                            "Number of Parties: 3\n"
                            "PartyA: A,B,C\n"
                            "PartyB: D,E,F,G\n"
                            "PartyC: H,I\n"
                            "Number of seats: 8\n"
                            "Number of ballots: 17\n"
                            "Ballot ID: 1 Ballot Info: 1,,\n"
                            "Ballot ID: 2 Ballot Info: 1,,\n"
                            "Ballot ID: 3 Ballot Info: 1,,\n"
                            "Ballot ID: 4 Ballot Info: 1,,\n"
                            "Ballot ID: 5 Ballot Info: 1,,\n"
                            "Ballot ID: 6 Ballot Info: 1,,\n"
                            "Ballot ID: 7 Ballot Info: 1,,\n"
                            "Ballot ID: 8 Ballot Info: 1,,\n"
                            "Ballot ID: 9 Ballot Info: ,1,\n"
                            "Ballot ID: 10 Ballot Info: ,1,\n"
                            "Ballot ID: 11 Ballot Info: ,1,\n"
                            "Ballot ID: 12 Ballot Info: ,1,\n"
                            "Ballot ID: 13 Ballot Info: ,1,\n"
                            "Ballot ID: 14 Ballot Info: ,1,\n"
                            "Ballot ID: 15 Ballot Info: ,1,\n"
                            "Ballot ID: 16 Ballot Info: ,,1\n"
                            "Ballot ID: 17 Ballot Info: ,,1\n"
                            "Counting ballots:\n"
                            "Party \"PartyA\" received ballot number 1\n"
                            "Party \"PartyA\" received ballot number 2\n"
                            "Party \"PartyA\" received ballot number 3\n"
                            "Party \"PartyA\" received ballot number 4\n"
                            "Party \"PartyA\" received ballot number 5\n"
                            "Party \"PartyA\" received ballot number 6\n"
                            "Party \"PartyA\" received ballot number 7\n"
                            "Party \"PartyA\" received ballot number 8\n"
                            "Party \"PartyB\" received ballot number 9\n"
                            "Party \"PartyB\" received ballot number 10\n"
                            "Party \"PartyB\" received ballot number 11\n"
                            "Party \"PartyB\" received ballot number 12\n"
                            "Party \"PartyB\" received ballot number 13\n"
                            "Party \"PartyB\" received ballot number 14\n"
                            "Party \"PartyB\" received ballot number 15\n"
                            "Party \"PartyC\" received ballot number 16\n"
                            "Party \"PartyC\" received ballot number 17\n"
                            "Quota determined to be: 2\n"
                            "Party \"PartyA\" | Seats assigned using quota: 4\n"
                            "Party \"PartyB\" | Seats assigned using quota: 3\n"
                            "Party \"PartyC\" | Seats assigned using quota: 1\n"
                            "Party \"PartyA\" has 4 seat(s) but only 3 candidate(s)- redistributing 1 seat(s)\n"
                            "Party \"PartyB\" given one seat from \"PartyA\"\n"
                            "Candidates receiving seats:\n"
                            "PartyA: A B C\n"
                            "PartyB: D E F G\n"
                            "PartyC: H\n";
    
    ifstream actualOutRead ("05102001CPL.txt");
    stringstream actualOut;
    actualOut << actualOutRead.rdbuf();
    
    EXPECT_EQ(actualOut.str(), expectedOut);
}

TEST(CPLElectionTests, RunElectionandDisplayTest_TieDuringSeatRedistribution) {                 // TestID: CPLElection_11
    ifstream testElectionFile ("../testing/CPLElectionTest_TieDuringSeatRedistribution.csv", std::ifstream::in);
    testElectionFile.ignore(256, '\n');

    CPLElection testElection = CPLElection(testElectionFile, "05112001");
    testElection.RunElection();
    EXPECT_EQ(testElectionFile.is_open(), false);
    
    testing::internal::CaptureStdout();
    testElection.DisplayResults();
    
    string expectedOutDefinite =    "Election type: CPL\n"
                            "Number of seats: 3\n"
                            "Number of ballots cast: 3\n"
                            "Party results: \n"
                            "PartyA: \n"
                            "Number of votes: 3 (100.00%)\n"
                            "Number of seats: 2 (66.67%)\n";

    string expectedOutOption1 = "PartyB: \n"
                            "Number of votes: 0 (0.00%)\n"
                            "Number of seats: 1 (33.33%)\n"
                            "PartyC: \n"
                            "Number of votes: 0 (0.00%)\n"
                            "Number of seats: 0 (0.00%)\n"
                            "PartyD: \n"
                            "Number of votes: 0 (0.00%)\n"
                            "Number of seats: 0 (0.00%)\n"
                            "Candidates receiving seats:\n"
                            "PartyA: A B\n"
                            "PartyB: C\n"
                            "PartyC: None\n"
                            "PartyD: None\n";

    string expectedOutOption2 = "PartyB: \n"
                            "Number of votes: 0 (0.00%)\n"
                            "Number of seats: 0 (0.00%)\n"
                            "PartyC: \n"
                            "Number of votes: 0 (0.00%)\n"
                            "Number of seats: 1 (33.33%)\n"
                            "PartyD: \n"
                            "Number of votes: 0 (0.00%)\n"
                            "Number of seats: 0 (0.00%)\n"
                            "Candidates receiving seats:\n"
                            "PartyA: A B\n"
                            "PartyB: None\n"
                            "PartyC: E\n"
                            "PartyD: None\n";

    string expectedOutOption3 = "PartyB: \n"
                            "Number of votes: 0 (0.00%)\n"
                            "Number of seats: 0 (0.00%)\n"
                            "PartyC: \n"
                            "Number of votes: 0 (0.00%)\n"
                            "Number of seats: 0 (0.00%)\n"
                            "PartyD: \n"
                            "Number of votes: 0 (0.00%)\n"
                            "Number of seats: 1 (33.33%)\n"
                            "Candidates receiving seats:\n"
                            "PartyA: A B\n"
                            "PartyB: None\n"
                            "PartyC: None\n"
                            "PartyD: F\n";
    
    string actualOut = testing::internal::GetCapturedStdout();
    size_t splitter;
    splitter = actualOut.find("PartyB: \n");
    string actualOutDefinite = actualOut.substr(0,splitter);
    string actualOutOption = actualOut.substr(splitter, string::npos);

    EXPECT_EQ(actualOutDefinite, expectedOutDefinite);

    EXPECT_PRED4(
        [](string actual, string option1, string option2, string option3) {return actual.compare(option1) == 0 || actual.compare(option2) == 0 || actual.compare(option3) == 0;}, 
        actualOutOption, expectedOutOption1, expectedOutOption2, expectedOutOption3);
}

TEST(CPLElectionTests, RunElectionandWriteTest_TieDuringSeatRedistribution) {                   // TestID: CPLElection_12
    ifstream testElectionFile ("../testing/CPLElectionTest_TieDuringSeatRedistribution.csv", std::ifstream::in);
    testElectionFile.ignore(256, '\n');

    CPLElection testElection = CPLElection(testElectionFile, "05122001");
    testElection.RunElection();
    testElection.WriteResultsToFile();

    EXPECT_EQ(testElectionFile.is_open(), false);
    string expectedOutDefinite =    "CPLElection\n"
                            "Number of Parties: 4\n"
                            "PartyA: A,B\n"
                            "PartyB: C,D\n"
                            "PartyC: E\n"
                            "PartyD: F\n"
                            "Number of seats: 3\n"
                            "Number of ballots: 3\n"
                            "Ballot ID: 1 Ballot Info: 1,,,\n"
                            "Ballot ID: 2 Ballot Info: 1,,,\n"
                            "Ballot ID: 3 Ballot Info: 1,,,\n"
                            "Counting ballots:\n"
                            "Party \"PartyA\" received ballot number 1\n"
                            "Party \"PartyA\" received ballot number 2\n"
                            "Party \"PartyA\" received ballot number 3\n"
                            "Quota determined to be: 1\n"
                            "Party \"PartyA\" | Seats assigned using quota: 3\n"
                            "Party \"PartyB\" | Seats assigned using quota: 0\n"
                            "Party \"PartyC\" | Seats assigned using quota: 0\n"
                            "Party \"PartyD\" | Seats assigned using quota: 0\n";

    string expectedOutOption1 = "Party \"PartyA\" has 3 seat(s) but only 2 candidate(s)- redistributing 1 seat(s)\n"
                                "Tie during seat reallocation between PartyB PartyC and PartyD\n"
                                "Party \"PartyB\" given one seat from \"PartyA\"\n"
                                "Candidates receiving seats:\n"
                                "PartyA: A B\n"
                                "PartyB: C\n"
                                "PartyC: None\n"
                                "PartyD: None\n";

    string expectedOutOption2 = "Party \"PartyA\" has 3 seat(s) but only 2 candidate(s)- redistributing 1 seat(s)\n"
                                "Tie during seat reallocation between PartyB PartyC and PartyD\n"
                                "Party \"PartyC\" given one seat from \"PartyA\"\n"
                                "Candidates receiving seats:\n"
                                "PartyA: A B\n"
                                "PartyB: None\n"
                                "PartyC: E\n"
                                "PartyD: None\n";

    string expectedOutOption3 = "Party \"PartyA\" has 3 seat(s) but only 2 candidate(s)- redistributing 1 seat(s)\n"
                                "Tie during seat reallocation between PartyB PartyC and PartyD\n"
                                "Party \"PartyD\" given one seat from \"PartyA\"\n"
                                "Candidates receiving seats:\n"
                                "PartyA: A B\n"
                                "PartyB: None\n"
                                "PartyC: None\n"
                                "PartyD: F\n";    
    
    ifstream actualOutRead ("05122001CPL.txt");
    stringstream actualOut;
    actualOut << actualOutRead.rdbuf();
    string actualOutStr = actualOut.str();

    size_t splitter;
    splitter = actualOutStr.find("Party \"PartyA\" has");
    string actualOutDefinite = actualOutStr.substr(0,splitter);
    string actualOutOption = actualOutStr.substr(splitter, string::npos);

    EXPECT_EQ(actualOutDefinite, expectedOutDefinite);
    
    EXPECT_PRED4(
        [](string actual, string option1, string option2, string option3) {return actual.compare(option1) == 0 || actual.compare(option2) == 0 || actual.compare(option3) == 0;}, 
        actualOutOption, expectedOutOption1, expectedOutOption2, expectedOutOption3);
}

TEST(CPLElectionTests, RunElectionandDisplayTest_Single) {                                     // TestID: CPLElection_13
    ifstream testElectionFile ("../testing/CPLElectionTest_Single.csv", std::ifstream::in);
    testElectionFile.ignore(256, '\n');

    CPLElection testElection = CPLElection(testElectionFile, "05132001");
    testElection.RunElection();
    EXPECT_EQ(testElectionFile.is_open(), false);
    
    testing::internal::CaptureStdout();
    testElection.DisplayResults();
    
    string expectedOut =    "Election type: CPL\n"
                            "Number of seats: 1\n"
                            "Number of ballots cast: 1\n"
                            "Party results: \n"
                            "PartyA: \n"
                            "Number of votes: 1 (100.00%)\n"
                            "Number of seats: 1 (100.00%)\n"
                            "Candidates receiving seats:\n"
                            "PartyA: A\n";
    
    EXPECT_EQ(testing::internal::GetCapturedStdout(), expectedOut);
}

TEST(CPLElectionTests, RunElectionandWriteTest_Single) {                                       // TestID: CPLElection_14
    ifstream testElectionFile ("../testing/CPLElectionTest_Single.csv", std::ifstream::in);
    testElectionFile.ignore(256, '\n');

    CPLElection testElection = CPLElection(testElectionFile, "05142001");
    testElection.RunElection();
    testElection.WriteResultsToFile();

    EXPECT_EQ(testElectionFile.is_open(), false);
    string expectedOut =    "CPLElection\n"
                            "Number of Parties: 1\n"
                            "PartyA: A\n"
                            "Number of seats: 1\n"
                            "Number of ballots: 1\n"
                            "Ballot ID: 1 Ballot Info: 1\n"
                            "Counting ballots:\n"
                            "Party \"PartyA\" received ballot number 1\n"
                            "Quota determined to be: 1\n"
                            "Party \"PartyA\" | Seats assigned using quota: 1\n"
                            "Candidates receiving seats:\n"
                            "PartyA: A\n";
    
    ifstream actualOutRead ("05142001CPL.txt");
    stringstream actualOut;
    actualOut << actualOutRead.rdbuf();
    
    EXPECT_EQ(actualOut.str(), expectedOut);
}

int main(int argc, char **argv) {

    std::cout << "test" << std::endl;
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}