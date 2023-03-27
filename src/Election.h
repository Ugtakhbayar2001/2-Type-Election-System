/**
 * @file Election.h
 * @author Dheva Subramaniam subra231@umn.edu
 * @brief Header file for Election Class for use with the 2-Type Election System
 * @version 0.1
 * @date 2023-03-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef ELECTION_H
#define ELECTION_H

#include "AuditFiler.h"
#include <vector>
#include <string>
#include <iostream>

/**
 * @class Election
 * @brief Abstract class that contains shared aspects of CPL and IR election derived classes
 */
class Election {
private:
    /**
     * @brief Tally the votes for each candidate based on read in ballots. This will be overrun by derived classes to account for differences in ballot structure.
     * 
     * @param entityVotesTotal A reference to an empty vector that will be altered to reflect the totals where each index corresponds to an entity receiving votes.
     */
    virtual void CountBallots(std::vector<int>& entityVotesTotal)=0;

    /**
     * @brief Read in the ballots from an election file. This will be overrun by derived classes to account for differences in file structure.
     * 
     */
    virtual void ReadElectionFile()=0;

protected:
    int ballotsTotal;               ///< The total number of ballots received
    AuditFiler auditFiler;          ///< AuditFiler object used to document information about the election as it is processed
    std::ifstream& electionFile;     ///< A reference to the election file being tabulated

    /**
     * @brief Given a vector of options to choose from, will randomly select one and return the result.
     * 
     * @param options A vector containing possible options to be selected from.
     * @param return Integer selected from the vector of options
     */
    int TieBreaker(std::vector<int> options);

public:
    /**
     * @brief Abstract constructor for derived classes to use to initialize inherited members.
     * 
     * @param electionType A vector containing possible options to be selected from
     * @param electionFile A file stream reference pointing to the election file containing the ballots for an election.
     * @param date A string representing the date of the election. Used to initialize the auditFiler member.
     * @param ballotTotal Integer representing the number of ballots being processed. Will default to zero and be updated once the election file has been read in.
     */
    Election(std::string electionType, std::ifstream& electionFile, std::string date, int ballotTotal=0);
    
    /**
     * @brief Provides the structure for tabulating the results of an election. Will be overrun by derived classes to account for different in election types.
     * 
     */
    virtual void RunElection()=0;
    
    /**
     * @brief Will display key portions of information to the terminal following the processing of an election
     * 
     */
    virtual void DisplayResults()=0;

    /**
     * @brief Write accumulated audit information to an audit file.
     */
    void WriteResultsToFile();
};

#endif