#include "BalancedBinaryTree.h"
#include "CharStringLink.h"
#include <iostream>
#include <fstream>
#include <string>
#include <io.h>
using namespace std;
void GetFileList(CharStringLink* inFileList, const char* inPath, const char* inFormat)
{
	char PathFormat[100];
	strcpy(PathFormat, inPath);
	strcat(PathFormat, "*");
	strcat(PathFormat, inFormat);

	struct _finddata_t fileinfo;
	intptr_t handle;
	if ((handle = _findfirst(PathFormat, &fileinfo)) == -1)
	{
		cout << "No file found!" << endl;
		system("pause");
		exit(0);
	}
	else
	{
		do
		{
			char inPathFile[100];
			strcpy(inPathFile, inPath);
			strcat(inPathFile, fileinfo.name);
			inFileList->add(inPathFile);
		} while (!(_findnext(handle, &fileinfo)));
		_findclose(handle);
	}
}
void LoadDict(BalancedBinaryTree* dict, char* path)
{
	string lineData;
	ifstream readDict(path);
	const int max_num = 275908, max_len = 40;
	char** temp = new char* [275908];
	memset(temp, 0, sizeof(char*) * max_num);
	for (int i = 0; i < max_num; i++)
	{
		temp[i] = new char[max_len];
		memset(temp[i], 0, sizeof(char) * max_len);
	}
	int i = 0;
	while (readDict.getline(temp[i], 40))
	{
		i++;
	}
	// TODO: 折半插入
	for (int i = 0; i < max_num; i++)
		delete[] temp[i];
	delete[] temp;
}
int main()
{
	// Load dictionary from the given file .dic
	char dictPath[] = ".\\dictionary\\mydict.dic";
	BalancedBinaryTree dict;
	LoadDict(&dict, dictPath);

	// Get all .txt file name
	char txtPathName[15] = ".\\input\\";
	char txtFormat[10] = ".txt";
	CharStringLink* txtFileList = new CharStringLink();
	GetFileList(txtFileList, txtPathName, txtFormat);
	
	// Test txtFileList
	BaseCharString* pTxtList = txtFileList->getBase()->next;
	bool adjust = false;
	while (pTxtList != NULL)
	{
		char txtNameTemp[40];
		pTxtList->data->toChar(txtNameTemp);
		char wordTemp[40];
		ifstream readTxt(txtNameTemp);
		while (readTxt.getline(wordTemp, 40))
		{
			// update documents infomation
		}

		pTxtList = pTxtList->next;
	}
}