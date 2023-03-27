/**
 * @file CPLBallot.h
 * @author Claire Maurus (mauru003@umn.edu)
 * @brief Header file for CPLBallot Class for use with CPL Election, reprsents a ballot and the vote on the ballot
 * @version 0.1
 * @date 2023-03-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef CPLBALLOT_H
#define CPLBALLOT_H

#include <string>
using namespace std;

/**
 * @class CPLBallot
 * @brief Represents a single ballot from a CPL election
 * 
 */

class CPLBallot{
    int indicatedPartyIndex = -1; ///< Integer containing index value that corresponds to a party assicated with that index initally -1

    public:
        /**
         * @brief Construct a new CPLBallot object, parsing the ballot string to find position of vote
         * 
         * 
         * @param ballot A string in Comma Deliniated form, Ex: ,1,,, 
         */
        CPLBallot(string ballot);    
        /**
         * @brief Gets which candidate was voted for on the Ballot for the CPL election
         * 
         * @return indicatedPartyIndex infomation stored in the object
         */
        int forParty(void);
};

#endif
