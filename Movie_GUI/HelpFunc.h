#include "CharStringLink.h"
#include "BalancedBinaryTree.h"
#include <iostream>
#include <fstream>
#include <string>
#include <io.h>
#include <windows.h>

using namespace std;

void InfoToTxt(char* c);
void TxtToInfo(char* c);
void IdToInfo(int id, char* str);
int CharToInt(char* c);
void GetFileList(CharStringLink* inFileList, const char* inPath, const char* inFormat);
void LoadDict(BalancedBinaryTree* dict, char* path);