/**
 * @file CPLElection.h
 * @author Dheva Subramaniam subra231@umn.edu
 * @brief Header file for CPLElection class for use with the 2-Type Election System
 * @version 0.1
 * @date 2023-03-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef CPLELECTION_H
#define CPLELECTION_H

#include "Election.h"
#include "Party.h"
#include "CPLBallot.h"

#include <vector>
#include <stdio.h>
#include <string>
#include <iostream>

/**
 * @class CPLElection
 * @brief Class for use with processing the votes of a Closed Party List election
 */
class CPLElection : public Election {
public:
    /**
     * @brief Constructor for CPL election type class
     * 
     * @param electionFile A reference to a file stream connected to a file containing the ballots for the election
     * @param date A string containing the date for use with the audit filer
     */
    CPLElection(std::ifstream& electionFile, std::string date);
    
    /**
     * @brief Provides the structure for tabulating the results of a CPL type election
     * 
     */
    void RunElection();
    
    /**
     * @brief Will display key portions of information to the terminal following the processing of a CPL type election
     * 
     */
    void DisplayResults();

private:
    std::vector<Party> parties;         ///< Vector containing all of the party objects associated with an election
    int partiesTotal;                   ///< The total number of parties
    int seatsTotal;                     ///< The total number of seats up for assignment
    std::vector<CPLBallot> ballots;     ///< Vector containing all of the ballot objects associated with an election

    /**
     * @brief Redistributes the seats assigned to a given party to the next most popular parties
     * 
     * @param partyIndex Is the index of the party whose seats are being redistributed in the party vector 
     */
    void SeatRedistribution(int partyIndex);

    /**
     * @brief Read in the ballots from a CPL election file.
     * 
     */
    void ReadElectionFile();

    /**
     * @brief Tally the votes for each party based on read in ballots for a CPL election
     * 
     * @param partyVotesTotal A reference to an empty vector that will be altered to reflect the totals where each index corresponds to a party receiving votes for a CPLElection.
     */
    void CountBallots(vector<int>& partyVotesTotal);
};


#endif