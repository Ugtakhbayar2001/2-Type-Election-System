#include <string>
#include <sstream>
#include <iostream>
#include "Candidate.h"

using namespace std;

Candidate::Candidate(string name) {
	candidateName = name;
}

void Candidate::SetVoteTotal(int total) {
	voteTotal = total;
	if (voteTotal == -1)
		isDropped = true;
}

bool Candidate::IsDropped(void) {
	return(isDropped);
}

int Candidate::GetVoteTotal(void) {
	return(voteTotal);
}

string Candidate::GetName(void) {
	return(candidateName);
}