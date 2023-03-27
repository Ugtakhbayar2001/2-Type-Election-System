/**
 * @file Candidate.h
 * @author Mark Jokinen (jokin010@umn.edu)
 * @brief Header file for Candidate class for use with IR Election, represents a candidate and the votes assigned to them
 * @version 0.1
 * @date 2023-03-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <string>

using namespace std;

/**
* @class Candidate
*
* @brief Represents a candidate in an Instant Runoff election
*/

class Candidate {
    bool isDropped = false;
    string candidateName;
    int voteTotal = 0;

public:
    /**
    * @brief Constructor for Candidate class.
    *
    * @param name is the string candidateName will be set to
    */
    Candidate(string name);

    /**
    * @brief Used to set the candidate's vote count.  Setting to -1 drops the candidate
    *
    * @param total is the value the candidate's vote count is set to
    */
    void SetVoteTotal(int total);

    /**
    * @brief Used to check whether or not a candidate has been dropped
    *
    * @return isDropped is a boolean flag indicating the dropped status
    */
    bool IsDropped(void);

    /**
    * @brief Used to get the candidate's vote count
    *
    * @return voteTotal is the number of votes a candidate has
    */
    int GetVoteTotal(void);

    /**
    * @brief Used to get the candidate's name
    *
    * @return candidateName is the candidate's name
    */
    string GetName(void);
};

#endif
