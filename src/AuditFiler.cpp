/**
 * @file AuditFiler.cpp
 * @author Claire Maurus mauru003@umn.edu
 * @brief CPP file for AuditFiler Class for use with the 2-Type Election System, used to create and fill a file with election information
 * @version 0.1
 * @date 2023-03-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "stdio.h"
#include "AuditFiler.h"

using namespace std;

AuditFiler::AuditFiler(string Date, string ElectionType){
            date = Date;
            electionType = ElectionType;
}

void AuditFiler::CreateFile(){          //file will be named mmddyyyy<ElectionType>.txt
    //create the file in the current directory
    string fileName = date + electionType + ".txt";
    
    auditFile.open(fileName);   
    if(!auditFile.is_open()){ cout<<"Failed to create/open " + fileName;} //safety check that file opened or that given file name was valid
    return;
}

void AuditFiler::CloseFile(){       //Closes the File opened in the createFile()
    auditFile.close();
            if(auditFile.fail()){cout<<"File Failed to Close Correctly";}           //Safety Check that File Closes      
    return;                                                                         //If File Failed to open it will fail to close and continue
}

void AuditFiler::WriteToFile(){
    //write info about the election to the file
    CreateFile();

    for(int i=0; i <electionInformation.size(); i++){   //for each item in the election info vector 
        auditFile << electionInformation[i] << endl;    //Add it to the audit file in vector order and a new line
        if(auditFile.bad()){
            cout<<"Failure to write the following info to the audit file: "+ electionInformation[i];
        }
    }

    CloseFile();
    return;
}

void AuditFiler::AddElectionInfo(string info){
    //add info to the vector about the election this will be used to populate the file later
    electionInformation.push_back(info);
    return;
}
