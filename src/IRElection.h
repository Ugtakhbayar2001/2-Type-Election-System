/**
 * @file IRElection.h
 * @author Ugtakhbayar Battulga  (battu016@umn.edu)
 * @brief Header file for IRElection class for use with the 2-Type Election System
 * @version 0.1
 * @date 2023-03-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef IRELECTION_H
#define IRELECTION_H

#include <vector>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>

#include "Election.h"
#include "ElectionFactory.h"
#include "IRBallot.h"
#include "Candidate.h"
#include "AuditFiler.h"


/**
 * @class IRElection 
 * @brief Represents an Instant-Runoff Election
 */
class IRElection : public Election {
  public:
    /**
     * @brief Constructor for IRElection
     * @param electionFile The input stream containing the election data
     * @param date The date of the election
     */
    IRElection(std::ifstream& electionFile, std::string date);
    
    /**
     * @brief Runs the IRElection and determines the winner
     */
    void RunElection();
    
    /**
     * @brief Displays the election results
     * @param winIndex The index of the winning candidate
     */
    void DisplayResults();

  protected:   
    /**
     * @brief Counts the votes for each candidate
     * @param candidateVotesTotal The total number of votes for each candidate
     */
    void CountBallots(std::vector<int>& candidateVotesTotal);

  private:

    /**
     * @brief Reads the election file and initializes the candidates and ballots vectors
     * @param electionFile The input stream containing the election data
     */
    void ReadElectionFile();
    
    /**
     * @brief Redistributes the votes of the candidate with the fewest votes
     * @param lowestIndex The index of the candidate with the fewest votes
     */
    void RedistributeVotes(int lowestIndex);
    
    /**
     * @brief Checks if a candidate has a majority of the votes
     * @return The index of the candidate with a majority of the votes, or -1 if no candidate has a majority
     */
    int CheckMajority();
    
    int winIndex;
    std::vector<Candidate> candidates;      // Vector containing the candidates in the election
    int candidatesTotal;                    // Total number of candidates
    std::vector<IRBallot> ballots;          // Vector containing the ballots in the election
    int electionStage;                      // The current stage of the election
    int ballotsTotal;                      // The total number of ballots
};

#endif
