#include "CharStringLink.h"
#include "BalancedBinaryTree.h"
#include <iostream>
#include <fstream>
#include <string>
#include <io.h>
#include <windows.h>

using namespace std;

// Function: transform a file name of .info to be one of .txt
// e.g. c = "567.info" ====> c = "567.txt"
void InfoToTxt(char* c);

// Function: transform a file name of .txt to be one of .info
// e.g. c = "567.txt" ====> c = "567.info"
void TxtToInfo(char* c);

// Function: transform a integer to be a file name of .info
// e.g. id = 5, str = "" ====> id = 5, str = "5.info"
void IdToInfo(int id, char* str);

// Function: transform a string to be a integer
// e.g. c = "pre567.info" ====> return 567
int CharToInt(char* c);

// Function: 
// 1. Get all file names whose format is "inFormat" in "inPath"
// 2. Save names in "inFileList"
// 3. Generate output file names whose formats are "outFormat" in "outPath"
// 4. Save names in "outFileList"
void GetFileList(CharStringLink* inFileList, const char* inPath, const char* inFormat);

// Function: add all words of .dict file into a BalancedBinaryTree in specifical order
// Order: [0, 1, 2, 3, 4, ..., 18, 19]
// e.g. loop 0: [9]
//		loop 1: [4, 14]
//		loop 2: [2, 6, 11, 16]
//		loop 3: [1, 3, 5, 7, 10, 12, 15, 17]
//		loop 4: [8, 13, 18]
//		loop 5: [19]
// The reason is explained in detail in my report.
void LoadDict(BalancedBinaryTree* dict, char* path);