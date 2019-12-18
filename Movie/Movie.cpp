#include "BalancedBinaryTree.h"
#include "CharStringLink.h"
#include <iostream>
#include <fstream>
#include <string>
#include <io.h>
#include <windows.h>

using namespace std;
void InfoToTxt(char* c)
{
	int i = 0;
	while (c[i] >= '0' && c[i] <= '9')
		i++;
	// c[i] = point
	c[++i] = 't'; c[++i] = 'x'; c[++i] = 't';
	c[++i] = '\0';
}
void InfoToTxt(char* c)
{
	int i = 0;
	while (c[i] >= '0' && c[i] <= '9')
		i++;
	// c[i] = point
	c[++i] = 'i'; c[++i] = 'n'; c[++i] = 'f'; c[++i] = '0';
	c[++i] = '\0';
}
inline int CharToInt(char* c)
{
	int result = 0;
	int i = 0;
	while (!(c[i] >= '0' && c[i] <= '9'))
		i++;
	while (c[i] >= '0' && c[i] <= '9')
	{
		result = result * 10 + c[i] - '0';
		i++;
	}
	return result;
}

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
	const int max_len = 50;
	char** temp = new char* [max_num];
	memset(temp, 0, sizeof(char*) * max_num);
	for (int i = 0; i < max_num; i++)
	{
		temp[i] = new char[max_len];
		memset(temp[i], 0, sizeof(char) * max_len);
	}
	max_num = 0;
	while (readDict.getline(temp[max_num], 50))
	{
		//cout << temp[max_num] << ",";
		max_num++;
	}
	cout << "dict num: " << max_num << endl;
	readDict.close();
	// 折半插入
	bool adjust = false;
	//for (int i = 0; i < max_num; i++)
	//	dict->InsertNode(temp[i], &adjust);
	int usedLength = 1;
	int* nextIndex = new int[usedLength];
	memset(nextIndex, 0, sizeof(int) * usedLength);
	nextIndex[0] = (0 + max_num) / 2;
	int success = 0;
	while (success < max_num)
	{
		int* nextIndexTemp = new int[usedLength * 2];
		memset(nextIndexTemp, 0, sizeof(int) * usedLength * 2);
		int k = 0;
		// 一边插入，一边更新下一个待插入序列
		for (int i = 0; i < usedLength; i++)
		{
			if (dict->InsertNode(temp[nextIndex[i]], &adjust))
				success++;
			//cout << temp[nextIndex[i]] << ", ";
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

}

int main()
{
	system("chcp 65001");

	// Load dictionary from the given file .dic
	char dictPath[] = ".\\dictionary\\mydict.dic";
	BalancedBinaryTree* dict = new BalancedBinaryTree();
	LoadDict(dict, dictPath);
	cout << "Load dictionary from the given file .dic" << endl;
	
	// Get all .txt file name
	char txtPathName[15] = u8".\\input\\";
	char txtFormat[10] = u8".txt";
	CharStringLink* txtFileList = new CharStringLink();
	GetFileList(txtFileList, txtPathName, txtFormat);
	cout << "Get all .txt file name" << endl;
	
	// Build document list
	BaseCharString* pTxtList = txtFileList->getBase()->next;
	while (pTxtList != NULL)
	{
		char txtNameTemp[40];
		pTxtList->data->toChar(txtNameTemp);
		int docID = CharToInt(txtNameTemp);
		char wordTemp[40];
		ifstream readTxt(txtNameTemp);
		while (readTxt.getline(wordTemp, 40))
		{
			dict->UpdateNode(wordTemp, docID);
		}
		readTxt.close();
		pTxtList = pTxtList->next;
	}
	cout << "Build document list" << endl;

	// Deal with query1.txt
	char query1File[] = "query1.txt";
	char result1File[] = "result1.txt";
	ifstream readQuery1(query1File);
	// Clear out file
	ofstream writeResult1(result1File);
	writeResult1.close();

	char sentTemp[100];
	while (readQuery1.getline(sentTemp, 100))
	{
		// Read a line
		int lenSent = strlen(sentTemp);
		DocList* resultList = new DocList();
		for (int i = 0; i < lenSent; i++)
		{
			while (sentTemp[i] == ' ')
				i++;
			if (i >= lenSent)
				break;
			// Read a word
			char aWord[50] = { '\0' };
			int end = i + 1;
			while (end < lenSent && sentTemp[end] != ' ')
				end++; // The position of space
			for (int j = 0; i + j < end; j++)
			{
				aWord[j] = sentTemp[i + j];
			}
			i = end;

			// Get document list of aWord
			PNode re = dict->SearchNode(aWord);
			doc* reDoc = NULL;
			if (re)
				reDoc = re->article->Head();
			while (reDoc)
			{
				resultList->Add(reDoc);
				reDoc = reDoc->next;
			}
		}
		resultList->Sort();
		resultList->Print();
		cout << endl;
		// Write result to outfile
		resultList->Write(result1File);
		delete resultList;
	}
	readQuery1.close();

	//exit(0);

	// Deal with query2.txt
	char query2File[] = "query2.txt";
	char result2File[] = "result2.txt";
	ifstream readQuery2(query2File);
	ofstream writeResult2(result2File);

	// Get all .info file name
	char infoPathName[15] = u8".\\input\\";
	char infoFormat[10] = u8".info";
	CharStringLink* infoFileList = new CharStringLink();
	GetFileList(infoFileList, infoPathName, infoFormat);
	cout << "Get all .info file name" << endl;

	char movieTitle[50];
	ifstream readInfo;
	while (readQuery2.getline(movieTitle, 50))
	{
		// Read a query
		BaseCharString* pInfoList = infoFileList->getBase()->next;
		char infoTitle[50] = { '\0' }; // the movie name
		char infoName[40] = { '\0' }; // the .info name
		bool find = false;
		while (pInfoList)
		{
			// Find movie in .info file
			pInfoList->data->toChar(infoName);
			readInfo.open(infoName);
			readInfo.getline(infoTitle, 50);
			readInfo.close();

			if (strcmp(movieTitle, infoTitle) == 0)
			{
				// Find aim movie
				InfoToTxt(infoName);
				ifstream readTxt(infoName);
				DocList* resultList = new DocList();
				char txtTemp[50] = { '\0' };
				while (readTxt.getline(txtTemp, 50))
				{
					PNode re = dict->SearchNode(txtTemp);
					doc* reDoc = NULL;
					if (re)
						reDoc = re->article->Head();
					while (reDoc)
					{
						resultList->Add(reDoc);
						reDoc = reDoc->next;
					}
				}
				resultList->Sort();
				resultList->Print();
				cout << endl;
				// TODO
				find = true;
				break;
			}
		}
		if (!find)
			writeResult2 << "该电影不在数据库中，无法推荐 ";
	}

	readQuery2.close();
	writeResult2.close();

}