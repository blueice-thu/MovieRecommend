#include "HelpFunc.h"
#include <QDebug>

void InfoToTxt(char* c)
{
	int i = 0;
	while (!(c[i] >= '0' && c[i] <= '9'))
		i++;
	while (c[i] >= '0' && c[i] <= '9')
		i++;
	// c[i] = point
	c[++i] = 't'; c[++i] = 'x'; c[++i] = 't';
	c[++i] = '\0';
}
void TxtToInfo(char* c)
{
	int i = 0;
	while (!(c[i] >= '0' && c[i] <= '9'))
		i++;
	while (c[i] >= '0' && c[i] <= '9')
		i++;
	// c[i] = point
	c[++i] = 'i'; c[++i] = 'n'; c[++i] = 'f'; c[++i] = '0';
	c[++i] = '\0';
}
void IdToInfo(int id, char* str)
{
	_itoa(id, str, 10);
	int i = 0;
	while (str[i] != '\0')
		i++;
	str[i++] = '.'; str[i++] = 'i'; str[i++] = 'n'; str[i++] = 'f'; str[i++] = 'o';
	str[i++] = '\0';
}
int CharToInt(char* c)
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
    char PathFormat[100] = {'\0'};
    strcpy(PathFormat, inPath);
    strcat(PathFormat, "*");
    strcat(PathFormat, inFormat);

	struct _finddata_t fileinfo;
    intptr_t handle = _findfirst(PathFormat, &fileinfo);
    if (handle == -1)
	{
        qDebug() << "No file found!" << endl;
		exit(0);
	}
	else
	{
		do
		{
            char inPathFile[100] = {'\0'};
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
	char** temp = new char*[max_num];
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
	//cout << "dict num: " << max_num << endl;
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
