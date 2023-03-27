/**
 * @file IRElection.cpp
 * @author Ugtakhbayar Battulga  (battu016@umn.edu)
 * @brief Source file for IRElection class for use with the 2-Type Election System
 * @version 0.1
 * @date 2023-03-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <vector>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "Election.h"
#include "IRElection.h"
#include "ElectionFactory.h"
#include "IRBallot.h"
#include "Candidate.h"
#include "AuditFiler.h"

using namespace std;

IRElection::IRElection(std::ifstream& electionFile, std::string date): Election("IR", electionFile, date) {
    ReadElectionFile();
    winIndex = -1;
}

void IRElection::RunElection() {
    // Create a vector to store the total number of votes for each candidate, initialized to 0
    vector<int> candidateVotesTotal(candidatesTotal, 0);

    auditFiler.AddElectionInfo("Counting Ballots");

    // Count the ballots to determine the initial vote totals for each candidate
    CountBallots(candidateVotesTotal);

    // Set the vote total for each candidate
    for (int i = 0; i < candidatesTotal; i++) {
        candidates.at(i).SetVoteTotal(candidateVotesTotal.at(i));
    }
    

    int winner = -1;
    int candsLeft = candidatesTotal;

    // Loop until a winner is found or all candidates are dropped
    while (winner == -1) {
        
        // Check for a majority winner
        winner = CheckMajority();

        // If a majority winner is found, add information about the election and the winner to the audit file
        if (winner != -1) {
            auditFiler.AddElectionInfo("Majority Found in first round");
            winIndex = winner;
            auditFiler.AddElectionInfo("Winner is: " + candidates.at(winner).GetName() + " with " + to_string(candidates.at(winner).GetVoteTotal()) + " Votes");
        }

        // If no majority winner is found and there are more than 2 candidates remaining, 
        // drop the candidate(s) with the lowest number of votes
        if (winner == -1 && candsLeft > 2) {
            auditFiler.AddElectionInfo("No Majority Found with more than 2 Candidates remaining");

            // Find the candidate(s) with the lowest number of votes
            vector<int> lowestIndices;
            int lowestTotal = INT_MAX;
            for (int i = 0; i < candidatesTotal; i++) {
                if (!candidates.at(i).IsDropped() && candidates.at(i).GetVoteTotal() == lowestTotal) {
                    lowestIndices.push_back(i);
                } else if (!candidates.at(i).IsDropped() && candidates.at(i).GetVoteTotal() < lowestTotal) {
                    lowestTotal = candidates.at(i).GetVoteTotal();
                    lowestIndices.clear();
                    lowestIndices.push_back(i);
                }
            }

            // If there is only one candidate with the lowest number of votes, 
            // drop that candidate and redistribute their votes
            if (lowestIndices.size() == 1) {
                candidates.at(lowestIndices.at(0)).SetVoteTotal(-1);
                auditFiler.AddElectionInfo("Dropped Candidate Name: " + candidates.at(lowestIndices.at(0)).GetName());
                auditFiler.AddElectionInfo("Redistribute Votes");
                RedistributeVotes(lowestIndices.at(0));
                candsLeft--;

                // Count the ballots again and update the vote totals for each candidate
                fill(candidateVotesTotal.begin(), candidateVotesTotal.end(),0);
                CountBallots(candidateVotesTotal);
                for (int i = 0; i < candidatesTotal; i++) {
                    candidates.at(i).SetVoteTotal(candidateVotesTotal.at(i));
                }                
            // If there are multiple candidates with the lowest number of votes, 
            // break the tie and drop the candidate
            } else if (lowestIndices.size() > 1) {

                auditFiler.AddElectionInfo("Tie Has Occurred");

                // Determine which candidate to drop using a tie-breaker algorithm
                int tieLoser = TieBreaker(lowestIndices);
                candidates.at(tieLoser).SetVoteTotal(-1);
                auditFiler.AddElectionInfo("Candidate dropped based of tieLoser: " + candidates.at(tieLoser).GetName());
                auditFiler.AddElectionInfo("Redistribute Votes");
                RedistributeVotes(tieLoser);
                candsLeft--;
                fill(candidateVotesTotal.begin(), candidateVotesTotal.end(),0);
                CountBallots(candidateVotesTotal);
                for (int i = 0; i < candidatesTotal; i++) {
                    candidates.at(i).SetVoteTotal(candidateVotesTotal.at(i));
                }                
            }
        // If there is no clear winner and there are two candidates remaining, 
        // the election moves to a popularity contest.
        } else if (winner == -1) {
            auditFiler.AddElectionInfo("Remaining 2 Candidates with no majority move to popularity");

            // Determine which candidate has the most votes.
            int indexOfMostVotes = 0;
            bool multiple = false;
            for (int i = 1; i < candidatesTotal; i++) {
                if (candidates.at(i).GetVoteTotal() > candidates.at(indexOfMostVotes).GetVoteTotal()) {
                    indexOfMostVotes = i;
                    multiple = false;
                } else if (candidates.at(i).GetVoteTotal() == candidates.at(indexOfMostVotes).GetVoteTotal()) {
                    multiple = true;
                }
            }
            winIndex = indexOfMostVotes;

            // If there is a tie, use the TieBreaker function to determine the winner.
            if (multiple) {
                vector<int> options;
                for (int i = 0; i < candidatesTotal; i++) {
                    if (candidates.at(i).GetVoteTotal() == candidates.at(indexOfMostVotes).GetVoteTotal()) {
                        options.push_back(i);
                    }
                }
                winner = TieBreaker(options);
                winIndex = winner;
                auditFiler.AddElectionInfo("Tie Has Occurred and after TieBreaker " + candidates.at(winner).GetName() + " has won with " + to_string(candidates.at(winner).GetVoteTotal()) + " Votes");
            } else {
                // Otherwise, the candidate with the most votes is declared the winner.
                winner = indexOfMostVotes;
                auditFiler.AddElectionInfo("Winner is: " + candidates.at(winner).GetName() + " with " + to_string(candidates.at(winner).GetVoteTotal()) + " Votes");
            }
        }
    }
}


void IRElection::DisplayResults() {
    cout << "Election type: IR" << endl;
    cout << "Number of candidates: " << candidatesTotal << endl;
    cout << "Number of ballots cast: " << ballotsTotal << endl;
    cout << "IR Election results in last round: " << endl;
    
    // Calculate percentage for votes
    float percentage;

    for (int i = 0; i < candidatesTotal; i++) {
        percentage = (float)candidates.at(i).GetVoteTotal() / ballotsTotal * 100;
        cout << "Number of votes for candidate number " << i+1 << ": " 
             << candidates.at(i).GetVoteTotal() << " (" << fixed << setprecision(2) 
             << percentage << "%)" << endl;
    }
    
    // Print winner
    if (winIndex == -1) {
        cout << "Winner: None" << endl;
    }
    else {
        cout << "Winner: " << candidates.at(winIndex).GetName() << endl;
    }
}

void IRElection::ReadElectionFile() {
    // Call auditFiler.AddElectionInfo
    auditFiler.AddElectionInfo("IRElection");

    // Read the number of candidates
    string strCandidatesTotal;
    if (!getline(electionFile, strCandidatesTotal)) {
        throw runtime_error("Error: Unable to read number of candidates from file.");
    }  
    auditFiler.AddElectionInfo("Number of Candidates: " + strCandidatesTotal);

    // Convert the number of candidates from string to int
    candidatesTotal = stoi(strCandidatesTotal);

    // Read the candidate names
    string candidatesLine;
    if (!getline(electionFile, candidatesLine)) {
        throw runtime_error("Error: Unable to read candidate names from file.");
    }    
    vector<string> candidateNames;
    stringstream ss(candidatesLine);
    string candidateName;
    while (getline(ss, candidateName, ',')) {
        if (candidateName[0] == ' ') {
            candidateName.erase(0, 1);
        }
        candidateNames.push_back(candidateName);
    }
    for (int i = 0; i < candidatesTotal; i++) {
        auditFiler.AddElectionInfo("Candidate " + to_string(i+1) + ": " + candidateNames.at(i));
        candidates.push_back(Candidate(candidateNames.at(i)));
    }

    // Read the number of ballots
    string strBallotsTotal;
    if(!getline(electionFile, strBallotsTotal)) {
        throw runtime_error("Error: Unable to read number of ballots from file.");
    }
    auditFiler.AddElectionInfo("Number of ballots: " + strBallotsTotal);

    // Convert variable strBallotsTotal(string) to int and assign to ballotsTotal
    ballotsTotal = stoi(strBallotsTotal);

    for(int i = 0; i < ballotsTotal; i++) {

        // Read a line from the input file into a local variable bInfo
        string bInfo;
        if (!getline(electionFile, bInfo)) {
            throw runtime_error("Error: Unable to read ballot information from file.");
        }

        // Create an instance of IRBallot(bInfo)
        ballots.push_back(IRBallot(bInfo));

        // Call auditFiler.AddElectionInfo(“Ballot ID:” + index + “Ballot Info:” + bInfo)
        auditFiler.AddElectionInfo("Ballot ID: " + to_string(i+1) + " Ballot Info: " + bInfo);
    }    
    electionFile.close();
}

void IRElection::CountBallots(vector<int>& candidateVotesTotal) {
    for (int i = 0; i < ballots.size(); i++) {
        IRBallot ballot = ballots.at(i);

        // check if the current rank is valid
        if (ballot.CurrentRank() != -1) {

            // get the index of the candidate from the ballot
            int candidateIndex = ballot.forCandidate();

            // increment the candidate's vote count
            candidateVotesTotal.at(candidateIndex) += 1;
            auditFiler.AddElectionInfo("Ballot #" + to_string(i+1) + " went to Candidate #" + to_string(candidateIndex+1));
        }
    }
    
    for (int i = 0;i < candidates.size(); i++) {
        auditFiler.AddElectionInfo("Candidate #" + to_string(i+1) + " received " + to_string(candidateVotesTotal.at(i)) + " vote(s)");
    }
}
//change so that it checks if the updated rank is a candidate that is still in the election
void IRElection::RedistributeVotes(int lowestIndex) {

    for (int i=0; i<ballotsTotal; i++) {
        // check if the ballot was cast for the candidate with the least votes
        if (ballots.at(i).forCandidate() == lowestIndex) {
            // update the rank of the candidate on the ballot
            ballots.at(i).UpdateRank();
            //checks if the candidate at the updated rank is dropped
            while (ballots.at(i).forCandidate() != -1 && candidates.at(ballots.at(i).forCandidate()).IsDropped()) {
               ballots.at(i).UpdateRank(); 
            }
        }
    }
}
 // check majority by comparing the votes to the total number of initial ballots
int IRElection::CheckMajority() {
    for (int i= 0; i < candidatesTotal; i++) {
        if (candidates.at(i).GetVoteTotal() / ballotsTotal > 0.5) {
            return i;
        }
    }
    return -1;
}