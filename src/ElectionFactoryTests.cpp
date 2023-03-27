/**
 * @file CPLElection.cpp
 * @author Dheva Subramaniam subra231@umn.edu
 * @brief Source file containing tests for the ElectionFactory class
 * @version 0.1
 * @date 2023-03-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "gtest/gtest.h"
#include "ElectionFactory.h"
#include "CPLElection.h"
#include "IRElection.h"

#include <iostream>

TEST(ElectionFactoryTests, CreateIRElection) {                                                          // TestID: ElectionFactory_01
    ifstream testElectionFile ("../testing/IRElectionTest_General.csv", std::ifstream::in);
    testElectionFile.ignore(256, '\n');

    Election* testElection = ElectionFactory::CreateElection("IR", "01012001", testElectionFile);
    IRElection* cplElection = dynamic_cast<IRElection *>(testElection);
    EXPECT_NE(nullptr, cplElection);
}

TEST(ElectionFactoryTests, CreateCPLElection) {                                                         // TestID: ElectionFactory_02
    ifstream testElectionFile ("../testing/CPLElectionTest_General.csv", std::ifstream::in);
    testElectionFile.ignore(256, '\n');

    Election* testElection = ElectionFactory::CreateElection("CPL", "01012001", testElectionFile);
    CPLElection* cplElection = dynamic_cast<CPLElection *>(testElection);
    EXPECT_NE(nullptr, cplElection);
}

TEST(ElectionFactoryTests, InvalidTypeCreation) {                                                       // TestID: ElectionFactory_03
    ifstream testElectionFile;

    try {
        ElectionFactory::CreateElection("INV", "01012001", testElectionFile);
        FAIL();
    } catch (runtime_error e) {
        EXPECT_STREQ("Error: Invalid election type- \"INV\" is not supported", e.what());
    }
}

int main(int argc, char **argv) {

    std::cout << "test" << std::endl;
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}