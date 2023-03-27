/**
 * @file main.cpp
 * @author Dheva Subramaniam subra231@umn.edu
 * @brief Source file for main class for 2-Type Election System
 * @version 0.1
 * @date 2023-03-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ElectionFactory.h"
#include "Election.h"

#include <string>
#include <iostream>

/**
* @brief Main function for the 2-Type Election System
* 
* @param argc   Integer representing the number of command line arguments that were provided upon starting the program
* @param argv   Stores any provided command line arguments provided upon starting the program
*/
int main(int argc, char* argv[]) {
    std::string fileName;                                                                                   // gets file name, either via command argument or by prompting user for it
    if (argc < 2) {
        std::cout << "No file name detected. Please input file name: ";
        std::cin >> fileName;
    } else {
        fileName = argv[1];
    }

    std::ifstream electionFile (fileName, std::ifstream::in);                                               // creates file reading object
    while (electionFile.fail()) {
        std::cout << "Unable to open file, please enter name again: ";
        std::cin >> fileName;
        electionFile.open(fileName, std::ifstream::in);                                           // tries to reopen using new input
    }

    std::string date;                                                                                       // asks user for the date
    std::cout << "Please input the date in the form of MMDDYYYY: ";
    std::cin >> date;

    std::string electionType;                                                                               // reads election type
    if (!getline(electionFile, electionType)) {
        throw runtime_error("Error: Unable to read election type from file.");
    }
    
    Election* electionProcessor = ElectionFactory::CreateElection(electionType, date, electionFile);        // uses election type to create an appropriate election derived class

    electionProcessor->RunElection();                                                                       // processes election data

    electionProcessor->DisplayResults();                                                                    // prints key info related to result of ran election

    electionProcessor->WriteResultsToFile();                                                                // writes the results to an audit file

    delete electionProcessor;                                                                               // election is created dynamically so is manually freed to avoid memory leaks
}