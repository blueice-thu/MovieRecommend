#include "BalancedBinaryTree.h"
#include "CharStringLink.h"
#include "HelpFunc.h"
#include <iostream>
#include <fstream>
#include <string>
#include <io.h>
#include <windows.h>

using namespace std;
#define MAX_COMMAND 5

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
		//resultList->Print();
		//cout << endl;
		// Write result to outfile
		resultList->Write(result1File);
		delete resultList;
	}
	readQuery1.close();
	cout << "query 1 finished\n";


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

	char movieTitle[100];
	ifstream readInfo;
	while (readQuery2.getline(movieTitle, 50))
	{
		// Delete space
		int i = 0;
		while (movieTitle[i] != '\0' && movieTitle[i] != ' ')
			i++;
		while (i < 100)
		{
			movieTitle[i] = '\0';
			i++;
		}

		// Read a query
		BaseCharString* pInfoList = infoFileList->getBase()->next;
		char infoTitle[100] = { '\0' }; // the movie name
		char infoName[40] = { '\0' }; // the .info file name
		bool find = false;

		// Find movie in .info file
		while (pInfoList)
		{
			pInfoList->data->toChar(infoName);
			readInfo.open(infoName);
			readInfo.getline(infoTitle, 50);
			readInfo.close();

			// Delete space
			int i = 0;
			while (infoTitle[i] != '\0' && infoTitle[i] != ' ')
				i++;
			while (i < 100)
			{
				infoTitle[i] = '\0';
				i++;
			}

			// Find given aim movie
			bool same = true;
			if (movieTitle[0] != infoTitle[0] || movieTitle[1] != infoTitle[1])
				same = false;
			else
			{
				size_t len1 = strlen(movieTitle);
				size_t len2 = strlen(infoTitle);
				len1 = len1 <= len2 ? len1 : len2;
				for (size_t i = 0; i < len1; i++)
				{
					if (movieTitle[i] != infoTitle[i])
					{
						same = false;
						break;
					}
					else if (movieTitle[i] == ' ' || infoTitle[i] == ' ')
						break;
				}
			}
			if (same)
			{
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

				// Get movie name, skip the first one
				doc* pDoc = resultList->Head()->next;
				for (int i = 0; i < MAX_COMMAND; i++)
				{
					if (!pDoc)
						break;

					char path[100] = u8".\\input\\";

					char filename[100] = { '\0' };
					IdToInfo(pDoc->docID, filename);
					strcat(path, filename);

					readInfo.open(path);
					char moviename[100] = { '\0' };
					readInfo.getline(moviename, 100);
					writeResult2 << "(" << pDoc->docID << ","
						<< moviename << ") ";
					readInfo.close();
					pDoc = pDoc->next;
				}
				writeResult2 << endl;
				//cout << endl;
				find = true;
				break;
			}
			else
			{
				pInfoList = pInfoList->next;
			}
		}
		if (!find)
			writeResult2 << u8"该电影不在数据库中，无法推荐\n";
	}
	cout << "query 2 finished";

	readQuery2.close();
	writeResult2.close();

}