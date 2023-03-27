/**
 * @file CPLBallot.cpp
 * @author Claire Maurus (mauru003@umn.edu)
 * @brief CPP file for the Class CPLBallot used for CPL election, represents a ballot from a CPL election and that position of vote to be mapped to a party
 * @version 0.1
 * @date 2023-03-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <string>
#include "CPLBallot.h"

using namespace std; 
CPLBallot::CPLBallot(string ballot){
            int index = 0;
            while(indicatedPartyIndex==-1){     //Loops through comma deliniated list looking for the 1
                if(ballot[index] == '1'){       //Save location of the 1 to class attribute
                    indicatedPartyIndex = index;
                    break;
                }
                index++;
            }
        };

int CPLBallot::forParty(){          
    return(indicatedPartyIndex);    //Returns the index(0...n) that coresponds to a party in the CPL election 
}