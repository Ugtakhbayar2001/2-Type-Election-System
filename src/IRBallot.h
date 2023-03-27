/**
 * @file IRBallot.h
 * @author Mark Jokinen (jokin010@umn.edu)
 * @brief Header file for IRBallot class for use with IR Election, represents a ballot and the votes on it
 * @version 0.1
 * @date 2023-03-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef IRBALLOT_H
#define IRBALLOT_H

#include <string>
#include <vector>
using namespace std;

/**
* @class IRBallot
* @brief Represents a ballot in an Instant Runoff election
*/

class IRBallot {
    vector<int> ballotInfo;
    int currentRank = 1;
    bool noMoreRanks = false;

public:
    /**
    * @brief Constructor for IRBallot class.
    *
    * Takes in an Instant Runoff Ballot in the form of a string and formats it into the vector ballotInfo
    *
    * @param ballotString is the IR ballot used to create the object
    */
    IRBallot(string ballotString);

    /**
    * @brief Used to update which candidate an IR ballot is being counted for
    *
    * After the currently chosen candidate is dropped, Increments the rank, then checks if there is a candidate assigned that rank.  If there is not, marks the ballot as having no more ranks.
    *
    * @return currentRank if the ballot has already run out of candidates, returns '-1' to indicate this.
    */
    void UpdateRank(void);

    /**
    * @brief Used to check the current ranked candidate the ballot is being counted for
    *
    * @return currentRank is the rank of candidate who the ballot is currently counted for
    */
    int CurrentRank(void);

    /**
    * @brief Used to check if ballot has run out of candidates to be counted for
    *
    * @return noMoreRanks is a flag indicating whether or not every candidate with a ranking on the ballot has been dropped
    */
    bool IsNoRanks(void);

    /**
    * @brief Used to identify the candidate the ballot is currently counted for
    *
    * @return indicatedCandidateIndex is the index corresponding to the candidate who the ballot is currently counted for,
    * who corresponds to the currentRank
    */
    int forCandidate(void);
};

#endif