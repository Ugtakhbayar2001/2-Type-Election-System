/**
 * @file Party.cpp
 * @author CLaire Maurus (mauru003@umn.edu)
 * @brief CPP file for the Class Party used for CPL election, Stores information such as Party Name, Cadidate names, Seats awarded to a party and Votes awarded to a party.
 * @version 0.1
 * @date 2023-03-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <String>
#include <vector>
#include <iostream>
#include <sstream>      
#include "Party.h"

using namespace std;

Party::Party(string cadidateInfo, string name){
            voteTotal=0;            //inialized to zero since they start a 0 votes   
            seatsAwarded=0;         //initalised to zero since the hae not ben given any seats to begin with
            partyName=name;

            stringstream strstream(cadidateInfo);    //this creates a stream to be treated like a file stream
            while(strstream.good()){                //make sure there is not issues or at end of string
                string tempStr;
                getline(strstream, tempStr, ',');   //get the first string before the comma
                candidateCPL.push_back(tempStr);
            }
}

void Party::setVoteTotal(int total){            //Set the Votes for the Party Object
    voteTotal=total;
    return;
}

int Party::getVoteTotal(){                      //Get the Vote assigned to the Party Object
    return (voteTotal);
}

void Party::setSeats(int seats){                //Set the seats assigned to a party Object
    seatsAwarded=seats;
    return;
}

int Party::getSeats(){                          //Get the seats currently set to the Party Object
    return(seatsAwarded);
}

int Party::getCadidateNum(){
    return(candidateCPL.size());
}

string Party::getCadidateName(int index){       //Takes in an integer and returns the Candidate names stored at that index in the Cadidate vector class attribute
    if(index>=getCadidateNum() || index<0){     //if the index is larger than the cadidates listed for the party then return Out of Cadidate String
        return "Out of Candidates";
    }
    return(candidateCPL.at(index));
}

string Party::getPartyName(){                   //Get the partyName Attribute from the object set my the constructor
    return(partyName);
}
