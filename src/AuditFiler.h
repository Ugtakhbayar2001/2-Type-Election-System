/**
 * @file AuditFiler.h
 * @author CLaire Maurus mauru003@umn.edu
 * @brief Header file for AuditFiler Class for use with the 2-Type Election System, used to create and fill a file with election information
 * @version 0.1
 * @date 2023-03-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef AUTIDFILER_H
#define AUTIDFILER_H
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "stdio.h"

using namespace std;

class AuditFiler{
    string date;                        ///<date passed in from main in MMDDYYYY form
    string electionType;                ///<"CPL" For Closed Party List OR "IR" for Instant Runoff
    vector<string> electionInformation; ///<Contains all the info for the Audit File
    ofstream auditFile;                 ///<Pointer to the audit file
    
    private:
         /**
         * @brief Create a File object in the current directory with the name MMDDYYYY<electionType>.txt, Called at beginning of WriteToFile()
         * 
         */
        void CreateFile();
        /**
         * @brief Closes the auditFile called at the end of WriteToFie()
         * 
         */
        void CloseFile();

    public:
        /**
         * @brief Construct a new Audit Filer object
         * 
         * @param Date Used to set date string and should be in the form MMDDYYY
         * @param ElectionType Used to set the electionType string, either CPL or IR
         */
        AuditFiler(string Date, string ElectionType);
        /**
         * @brief Write the contents of the electionInformation vector to the auditFile
         * contains calls to CreateFile() and CloseFile()
         * 
         */
        void WriteToFile();
        /**
         * @brief Adds information to electionInformation vector, pushing info onto the vector
         * 
         * @param info Information passes in from outside the class
         */
        void AddElectionInfo(string info);
};
#endif
