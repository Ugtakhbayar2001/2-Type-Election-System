/**
 * @file CPLElection.cpp
 * @author Dheva Subramaniam subra231@umn.edu
 * @brief Source file for CPLElection class for use with the 2-Type Election System
 * @version 0.1
 * @date 2023-03-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "CPLElection.h"

#include <fstream>
#include <sstream>
#include <iomanip>

CPLElection::CPLElection(std::ifstream& electionFile, std::string date) : Election("CPL", electionFile, date) {     // input gets passed to the super constructor and the ballots are read from the file
    ReadElectionFile();
}

void CPLElection::RunElection() {
    std::vector<int> partiesVoteTotals(partiesTotal, 0);                                                                        // vector of votes received by each party
    std::vector<int> partiesVoteRemainders(partiesTotal, 0);                                                                    // vector of remainder votes (votes left over after dividing their totals by the quota)
    int awardedSeatsTotal = 0;

    auditFiler.AddElectionInfo("Counting ballots:");                                                                            // lets the auditfiler know that ballots are being counted
    CountBallots(partiesVoteTotals);                                                                                            // counts the ballots and stores in partiesVoteTotals vector

    int quota = ballotsTotal / seatsTotal;                                                                                      // quota is used to determine the bulk of assigned seats, each party receives a seat for as many times as they are able to match the quota
    auditFiler.AddElectionInfo("Quota determined to be: " + std::to_string(quota));

    for (int i = 0; i < partiesTotal; i++) {                                                                                    // assigns bothe the corresponding vote totals and remainders for each party using the logic described above
        int votesForParty = partiesVoteTotals.at(i);
        int awardSeats = (votesForParty / quota);

        parties.at(i).setVoteTotal(votesForParty);
        parties.at(i).setSeats(awardSeats);
        awardedSeatsTotal += awardSeats;
        partiesVoteRemainders.at(i) = votesForParty % quota;

        auditFiler.AddElectionInfo("Party \"" + parties.at(i).getPartyName() + "\" | Seats assigned using quota: " + std::to_string(awardSeats));
    }

    int partyToAward = -1;
    while (awardedSeatsTotal < seatsTotal) {                                        // loop runs as long as there are still chairs left to assign
        std::vector<int> options;
        int max_elem = -1;
        for (int i = 0; i < partiesTotal; i++) {
            int voteRemainder = partiesVoteRemainders.at(i);
            if (voteRemainder > max_elem) {                                         // if a vote remainder is the largest found so far, will clear option list and push into list of options to chose from when determining the party with the most remainder votes
                options.clear();
                options.push_back(i);
                max_elem = voteRemainder;
            } else if (voteRemainder == max_elem) {                                 // if equal to the largest found so far, but not greater, will add to option list without clearing
                options.push_back(i);
            }
        }

        if (options.size() > 1) {                                                   // if there's more than one option, uses tie breaker to choose one randomly as the party to recieve a chair
            std::string tieMessage = "Tie during seat allocation between";
            for (int i = 0; i < options.size() - 1; i++) {
                tieMessage += (" " + parties.at(options.at(i)).getPartyName());
            }
            tieMessage += (" and " + parties.at(options.back()).getPartyName());
            auditFiler.AddElectionInfo(tieMessage);
            partyToAward = TieBreaker(options);
        } else {
            partyToAward = options.front();
        }

        parties.at(partyToAward).setSeats(parties.at(partyToAward).getSeats() + 1);     // increments seat count of party by one
        partiesVoteRemainders.at(partyToAward) = 0;
        awardedSeatsTotal += 1;
        std::string additionalSeatMessgae = "Awarded remainder seat to \"" + parties.at(partyToAward).getPartyName() + "\"";
        auditFiler.AddElectionInfo(additionalSeatMessgae);
    }

    for (int i = 0; i < partiesTotal; i++) {                                        // check each party to see if there are too many seats assigned to any, if so will redistribute the extras
        if (parties.at(i).getCadidateNum() < parties.at(i).getSeats()) {
            SeatRedistribution(i);
        }
    }

    auditFiler.AddElectionInfo("Candidates receiving seats:");
    for (int i = 0; i < partiesTotal; i++) {
        string candidateSeatString;
        int partyReceivedSeats = parties.at(i).getSeats();
        candidateSeatString += parties.at(i).getPartyName() + ":";
        if (partyReceivedSeats == 0) {
            candidateSeatString += " None";
        } else {
            for (int j = 0; j < partyReceivedSeats; j++) {
                candidateSeatString += " " + parties.at(i).getCadidateName(j);
            }
        }

        auditFiler.AddElectionInfo(candidateSeatString);
    } 
}

void CPLElection::DisplayResults() {
    std::cout << "Election type: CPL" << std::endl;                                 // print election type
    std::cout << "Number of seats: " << seatsTotal << std::endl;                    // print # of seats total
    std::cout << "Number of ballots cast: " << ballotsTotal << std::endl;           // print # of ballots
    std::cout << "Party results: " << std::endl;

    for (int i = 0; i < partiesTotal; i++) {
        int partyReceivedVotes = parties.at(i).getVoteTotal();
        int partyReceivedSeats = parties.at(i).getSeats();
        std::cout << parties.at(i).getPartyName() << ": " << std::endl;
        std::cout << "Number of votes: " << partyReceivedVotes << " (" << fixed << setprecision(2) << 100 * ((double)partyReceivedVotes / (double)ballotsTotal) << "%)" << std::endl;     // print # of received votes and pertange of votes received for each party
        std::cout << "Number of seats: " << partyReceivedSeats << " (" << fixed << setprecision(2) << 100 * ((double)partyReceivedSeats / (double)seatsTotal) << "%)" << std::endl;       // print # of received votes and pertange of seats received for each party
    }

    std::cout << "Candidates receiving seats:" << std::endl;                        // print the candidates being awarded seats based on how many seats their party got
    for (int i = 0; i < partiesTotal; i++) {
        int partyReceivedSeats = parties.at(i).getSeats();
        std::cout << parties.at(i).getPartyName() << ":";
        if (partyReceivedSeats == 0) {
            std::cout << " None" << std::endl;
        } else {
            for (int j = 0; j < partyReceivedSeats; j++) {
                std::cout << " " << parties.at(i).getCadidateName(j);
            }
            std::cout << std::endl;
        }
    } 
}

void CPLElection::ReadElectionFile() {
    auditFiler.AddElectionInfo("CPLElection");          // document election type

    string strPartiesTotal;                             // get number of parties
    if (!getline(electionFile, strPartiesTotal)) {
        throw runtime_error("Error: Unable to read number of parties from file.");
    }  
    auditFiler.AddElectionInfo("Number of Parties: " + strPartiesTotal);        // document number of parties
    partiesTotal = stoi(strPartiesTotal);

    string partiesLine;                                 // get the names of parties being voted on
    if (!getline(electionFile, partiesLine)) {
        throw runtime_error("Error: Unable to read party names from file.");
    }

    std::vector<std::string> partyNames;                          // convert comma separated string containing party names into vector
    std::string partyName;
    stringstream partyNamesStream(partiesLine);
    while (getline(partyNamesStream, partyName, ',')) {
        if (partyName[0] == ' ') {
            partyName.erase(0, 1);
        }
        partyNames.push_back(partyName);
    }

    for (int i = 0; i < partyNames.size(); i++) {
        std::string candidateNames;                     // get names of candidates for each party
        if (!getline(electionFile, candidateNames)) {
            throw runtime_error("Error: Unable to read candidate names from file.");
        }
        for (int i = 0; i < candidateNames.size(); i++) {
            if (candidateNames[i] == ' ') {
              candidateNames.erase(i, 1);  
            }
        }
        auditFiler.AddElectionInfo(partyNames.at(i) + ": " + candidateNames);   // document party name and candidates

        parties.push_back(Party(candidateNames, partyNames.at(i)));             // store party information
    }

    string strSeatsTotal;                               // get number of seats being voted for
    if(!getline(electionFile, strSeatsTotal)) {
        throw runtime_error("Error: Unable to read number of seats from file.");
    }
    auditFiler.AddElectionInfo("Number of seats: " + strSeatsTotal);
    seatsTotal = stoi(strSeatsTotal);

    string strBallotsTotal;                             // get number of seats being voted for
    if(!getline(electionFile, strBallotsTotal)) {
        throw runtime_error("Error: Unable to read number of ballots from file.");
    }
    auditFiler.AddElectionInfo("Number of ballots: " + strBallotsTotal);
    ballotsTotal = stoi(strBallotsTotal);

    for(int i = 0; i < ballotsTotal; i++) {
        string strBallotInfo;                           // get number of seats being voted for
        if(!getline(electionFile, strBallotInfo)) {
            throw runtime_error("Error: Unable to read ballot " + (i+1));
        }
        ballots.push_back(CPLBallot(strBallotInfo));    // store ballot information

        auditFiler.AddElectionInfo("Ballot ID: " + to_string(i+1) + " Ballot Info: " + strBallotInfo);      // document ballot information
    }

    electionFile.close();      // close file stream since it will no longer be needed
}

void CPLElection::CountBallots(vector<int>& partyVotesTotal) {
    for (int i = 0; i < ballotsTotal; i++) {
        int votedFor = ballots.at(i).forParty();        // gets the corresponding party index that the ballot was for
        partyVotesTotal.at(votedFor) += 1;              // increments the total for the indicated party

        auditFiler.AddElectionInfo("Party \"" + parties.at(votedFor).getPartyName() + "\" received ballot number " + std::to_string(i + 1));     // documents which party the vote was assigned to
    }
}

void CPLElection::SeatRedistribution(int partyIndex) {
    int redistributeSeats = parties.at(partyIndex).getSeats() - parties.at(partyIndex).getCadidateNum();                // gets number of seats to be redistributed
    int partyToReallocateTo = -1;

    string reallocationFromMessage =    "Party \"" + parties.at(partyIndex).getPartyName() + "\" has " +
                                        to_string(parties.at(partyIndex).getSeats()) + " seat(s) but only " +
                                        to_string(parties.at(partyIndex).getCadidateNum()) + " candidate(s)- redistributing " +
                                        to_string(redistributeSeats) + " seat(s)";

    auditFiler.AddElectionInfo(reallocationFromMessage);

    while (redistributeSeats > 0) {
        std::vector<int> options;
        int max_elem = -1;
        for (int i = 0; i < partiesTotal; i++) {                                                                        // gets the party (or parties if there's a tie) with the next highest votes and with still open seats
            int voteTotal = parties.at(i).getVoteTotal();
            if ((voteTotal > max_elem) && (parties.at(i).getSeats() < parties.at(i).getCadidateNum())) {
                options.clear();
                options.push_back(i);
                max_elem = voteTotal;
            } else if ((voteTotal == max_elem) && (parties.at(i).getSeats() < parties.at(i).getCadidateNum())) {
                options.push_back(i);
            }
        }
        if (options.size() > 1) {                                                                                       // if more than one option, uses tie breaker to select one randomly
            std::string tieMessage = "Tie during seat reallocation between";
            for (int i = 0; i < options.size() - 1; i++) {
                tieMessage += (" " + parties.at(options.at(i)).getPartyName());
            }
            tieMessage += (" and " + parties.at(options.back()).getPartyName());
            auditFiler.AddElectionInfo(tieMessage);

            partyToReallocateTo = TieBreaker(options);
        } else {
            partyToReallocateTo = options.front();
        }

        string reallocationToMessage =    "Party \"" + parties.at(partyToReallocateTo).getPartyName() + "\" given one seat from \"" +
                                            parties.at(partyIndex).getPartyName() + "\"";

        parties.at(partyIndex).setSeats(parties.at(partyIndex).getSeats() - redistributeSeats);
        auditFiler.AddElectionInfo(reallocationToMessage);
        parties.at(partyToReallocateTo).setSeats(parties.at(partyToReallocateTo).getSeats() + 1);
        redistributeSeats -= 1;
    }
}