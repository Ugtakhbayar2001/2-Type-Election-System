/**
 * @file ElectionFactory.cpp
 * @author Dheva Subramaniam subra231@umn.edu
 * @brief Source file for ElectionFactory Class for use with the 2-Type Election System
 * @version 0.1
 * @date 2023-03-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "ElectionFactory.h"

#include "IRElection.h"
#include "CPLElection.h"


Election* ElectionFactory::CreateElection(std::string type, std::string date, std::ifstream& electionFile) {
    if (type.compare("IR") == 0) {                                  // if the indicated type is IR, creates an IRElection 
        return new IRElection(electionFile, date);
    } else if (type.compare("CPL") == 0) {                          // if the indicated type is CPL, creates a CPLElection 
        return new CPLElection(electionFile, date);
    } else {                                                        // if any other type is read from the file, will throw an error
        throw runtime_error("Error: Invalid election type- \"" +
                                type + "\" is not supported");
    }
}
