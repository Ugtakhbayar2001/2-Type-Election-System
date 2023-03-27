/**
 * @file Party.h
 * @author Claire Maurus (mauru003@umn.edu)
 * @brief header file for Party Class for use with CPL Election, Stores information such as Party Name, Cadidate names, Seats awarded to a party and Votes awarded to a party.
 * @version 0.1
 * @date 2023-03-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef PARTY_H
#define PARTY_H

#include <String>
#include <vector>
#include <iostream>
#include <sstream>     
using namespace std;
class Party{
    vector<string> candidateCPL;    ///< Vector of containing list of cadidates running under partName
    string partyName;               ///< String containing the name of the Party the oject represents
    int voteTotal;                  ///< Integer storing the number of votes awarded to the Party
    int seatsAwarded;               ///< Integer representing the number of seats given to the Party

    public:
        /**
         * @brief Construct a new Party object 
         *        Initalizes voteTotal and seatsAwarded to 0.
         * 
         * @param cadidateInfo String is parsed and used to populate the CadidateCPL vector
         * @param name Used to set the partyName string
         */
        Party(string cadidateInfo, string name);
        /**
         * @brief Set the voteTotal for the object
         * 
         * @param total the new total number votes that are assicated with the Party object
         */
        void setVoteTotal(int total);
        /**
         * @brief Get the Vote Total from object
         * 
         * @return Integer value of total number of votes a party has currently assigned.
         */
        int getVoteTotal(void);
        /**
         * @brief Set the Seats for the Party object
         * 
         * @param seats used to set the internal varible seatsAwarded
         */
        void setSeats(int seats);
        /**
         * @brief Get the seatsAwarded from object
         * 
         * @return integer correlating to the seats awarded to the Party object
         */
        int getSeats(void);
        /**
         * @brief Get the Number of Candidates in the Party object
         * 
         * @return The integer value of the number of candidates contained in the candidateCPL vector 
         */
        int getCadidateNum(void);
        /**
         * @brief Get a Cadidate Name from object
         * 
         * @param index The index in the cadidateCPL vector the user wants a name for
         * @return The string of the candidate name
         */
        string getCadidateName(int index);
        /**
         * @brief Get Party Name from object
         * 
         * @return The string of the party's name
         */
        string getPartyName();  
};

#endif
