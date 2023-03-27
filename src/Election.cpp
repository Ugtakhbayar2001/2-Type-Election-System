/**
 * @file Election.cpp
 * @author Dheva Subramaniam subra231@umn.edu
 * @brief Source file for Election Class for use with the 2-Type Election System
 * @version 0.1
 * @date 2023-03-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "Election.h"

#include <random>
#include <time.h>

int Election::TieBreaker(std::vector<int> options) {
        srand(time(NULL));                              // seeds the pseudorandom number generator with the system time
        int returnIndex = rand() % options.size();     // selects a random number between 0 (inclusive) and the size of the options vector (exclusive)
        return options.at(returnIndex);                 // returns the integer stored at that index
}

void Election::WriteResultsToFile() {
        auditFiler.WriteToFile();                       // calls AuditFiler's write function to write stored information to an audit file
}

Election::Election(std::string electionType, std::ifstream &electionFile, std::string date, int ballotTotal)
                        : auditFiler(date, electionType), electionFile(electionFile) {          // initializes the AuditFiler object and file stream reference
        this->ballotsTotal = ballotTotal;
}