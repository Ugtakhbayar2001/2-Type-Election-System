/**
 * @file ElectionFactory.h
 * @author Dheva Subramaniam subra231@umn.edu
 * @brief Header file for ElectionFactory Class for use with the 2-Type Election System
 * @version 0.1
 * @date 2023-03-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef ELECTION_FACTORY
#define ELECTION_FACTORY

#include "Election.h"
#include "string"
#include <iostream>

/**
 * @class ElectionFactory
 * @brief Given the type of election, creates and returns proper derived election handler as a parent reference
 */
class ElectionFactory {
public:
    /**
     * @brief Static method that creates and returns a reference to an object to process an election
     * 
     * @param type Indicates which type of election should be created
     * @param date Stored for record purposes and to instantiate an AuditFiler member
     * @param electionFile Will be read by the object to store the ballots
     * @return Election pointer to derived election type class
     */
    static Election* CreateElection(std::string type, std::string date, std::ifstream& electionFile);
};

#endif