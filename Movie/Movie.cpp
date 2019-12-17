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
	int max_num = 275908;
	const int max_len = 40;
	char** temp = new char* [275908];
	memset(temp, 0, sizeof(char*) * max_num);
	for (int i = 0; i < max_num; i++)
	{
		temp[i] = new char[max_len];
		memset(temp[i], 0, sizeof(char) * max_len);
	}
	max_num = 0;
	while (readDict.getline(temp[max_num], 40))
	{
		max_num++;
	}
	// TODO: 折半插入
	bool adjust = false;

	//bool* mark = new bool[max_num];
	//memset(mark, 0, sizeof(bool) * max_num);
	int usedLength = 1;
	int* nextIndex = new int[usedLength];
	memset(nextIndex, 0, sizeof(int) * usedLength);
	nextIndex[0] = (0 + max_num) / 2;
	bool success = true;
	while (success)
	{
		success = false;
		int* nextIndexTemp = new int[usedLength * 2];
		memset(nextIndexTemp, 0, sizeof(int) * usedLength * 2);
		int k = 0;
		// 一边插入，一边更新下一个待插入序列
		for (int i = 0; i < usedLength; i++)
		{
			if (dict->InsertNode(temp[nextIndex[i]], &adjust))
				success = true;
			if (i == 0 && i == usedLength - 1)
			{
				nextIndexTemp[k++] = nextIndex[0] / 2;
				nextIndexTemp[k++] = (nextIndex[0] + max_num) / 2;
			}
			else if (i == usedLength - 1 && i != 0)
			{
				nextIndexTemp[k++] = (nextIndex[i] + max_num) / 2;
			}
			else
			{
				if (i == 0)
				{
					nextIndexTemp[k++] = nextIndex[0] / 2;
					if (usedLength == 1)
						break;
				}
				int mid = (nextIndex[i] + nextIndex[i + 1] + 1) / 2;
				nextIndexTemp[k++] = (nextIndex[i] + mid) / 2;
				nextIndexTemp[k++] = (mid + nextIndex[i + 1]) / 2;
			}
		}
		delete[] nextIndex;
		nextIndex = nextIndexTemp;
		usedLength *= 2;
	}
	
	for (int i = 0; i < max_num; i++)
		delete[] temp[i];
	delete[] temp;
	//delete[] mark;
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