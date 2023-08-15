# 2 Type Election System
Team 8: Claire, Dheva, Mark, Ugta <br />
CSCI 5801 Spring 2023 Waterfall & Scrum Project

This project handles two types of provided election results CSV files: 
- IR: Instant Runoff
- CPL: Close Party List

## To Run the Code:
Various Make File Commands:
- `make build` this generates an executable file named 2-TypeElection.exe
- `make allTests` this generates a test executable for all test cpps (all files following the <*Tests.cpp> naming convention)
- `make <classname>Tests` This generates a single test executable for the tests belonging to <classname> (uses the <classname>Tests.cpp file)
- `make cleanOutputs` this removes all *.txt files generated from tests or executables
- `make clean` this removes all object files and executables in the directory

These should be executed in the same directory as where all the .cpp and .h files exist.

### Running the Program
1. After you call `make build` make sure that the election result csv file is in the same directory as the system files. 
2. Run the Program from the command line in the terminal:
   - Linux/Mac: `./2-TypeElection <file name>`
   - Windows: `.\2-TypeElection.exe <file name>`
  File Name refers to the CSV election input file. 
 3. If you did not provide a command line arg then the terminal will prompt you to enter a file name.
 4. System will prompt you to enter a date in MMDDYYYY format
  
 ### Important Note
 If there already exists a file in the directory with the name MMDDYYYY<Election_Type>.txt with Election_Type being the election type of the file provided to the system, that existing file will be truncated on this version of the program. We suggest moving an audit file from the current working directory after it has been generated to avoid any loss of data.
 
 To access the project's Doxygen main page and gain insights into its overall structure, navigate to the "documentation/html" directory and launch the "index.html" file in your preferred browser.
