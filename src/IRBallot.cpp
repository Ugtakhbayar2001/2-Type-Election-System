#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include "IRBallot.h"

using namespace std;


IRBallot::IRBallot(string ballotString) {
    stringstream iss(ballotString);
    string temp;
    while (iss.good()) {
        getline(iss, temp, ',');
        if (!temp.empty()){
            ballotInfo.push_back(stoi(temp));
        }
        else{
            ballotInfo.push_back(-1);
        }
    }     
};


void IRBallot::UpdateRank() {
    if (noMoreRanks == true) {
        return;
    }
    bool flag = false;
    currentRank++;
    for (auto iter = ballotInfo.begin(); iter != ballotInfo.end(); ++iter)
        if (*iter == currentRank) {
            flag = true;
            break;
        }
    if (flag == false) {
        noMoreRanks = true;
        currentRank = -1;
    }
}


int IRBallot::CurrentRank() {
    return(currentRank);
}


bool IRBallot::IsNoRanks() {
    return(noMoreRanks);
}


int IRBallot::forCandidate() {
    int index = 0;
    int indicatedCandidateIndex = -1;
    if (currentRank == -1)
        return(indicatedCandidateIndex);
    while (indicatedCandidateIndex == -1) {
        if (ballotInfo[index] == currentRank) {
            indicatedCandidateIndex = index;
            break;
        }
        index++;
    }
    return(indicatedCandidateIndex);
}
