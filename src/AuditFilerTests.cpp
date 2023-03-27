/**
 * @file AuditFilerTest.cpp
 * @author Claire Maurus maurus
 * @brief Testing File used for all the unit test cases in the AuditFile class
 * @version 0.1
 * @date 2023-03-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "gtest\gtest.h"
#include "AuditFiler.h"

#include <fstream>
#include <iostream>
#include "stdio.h"

using namespace std;

//Test Case AuditFiler_01
TEST(FileCreate, fileCreatingTest){
    AuditFiler test1("MMDDYYYY", "Election_Type");
    test1.WriteToFile();
}

//Test Case AuditFiler_02
TEST (AddingingInfo, addinginforNewFile){
    AuditFiler test1("MMDDYYYY", "IR");
    test1.AddElectionInfo("News");
    test1.WriteToFile();

    AuditFiler test2("MMDDYYYY", "CPL");
    test2.AddElectionInfo("Testing Info");
    test2.AddElectionInfo("Testing Info 2");
    test2.WriteToFile();

    //open two files and expected and they should match or do it manually

}

//Test Case AuditFiler_03
TEST (ExistingFiles, existingFileSameName){
    //file named MMDDYYYPreExisting1.txt and MMDDYYPreExisting2.txt will be in same directory with information
    AuditFiler existingTest1("MMDDYYYY", "PreExisting1");   //add nothing to and write to file
    AuditFiler existingTest2("MMDDYYYY", "PreExisting2");   //add info to existing file

    existingTest1.WriteToFile();

    existingTest2.AddElectionInfo("New information to add");
    existingTest2.WriteToFile();

}

//Test Case AuditFiler_04
TEST (FileNamesTest, forbiddenChar){
    AuditFiler test1("?", "@");       //File Name should be MMDDYYYElectionTest.txt
    test1.AddElectionInfo("News");
    test1.WriteToFile();
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
