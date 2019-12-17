#pragma once
#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

typedef struct doc
{
	int docID;
	int times;
	struct doc* next;
}doc;

class DocList
{
public:
	DocList();
	~DocList();
	doc * CreateDoc(int id, int t);
	bool Add(int id);
	bool Add(doc* node);
	bool Remove(int id);
	doc* Search(int id);
	doc* Edit(int id, int newDocID);
	doc* Head();
	void Write(char* file, bool print = true);
private:
	doc* head;
};
