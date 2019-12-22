#pragma once
#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

// A node of DocList
typedef struct doc
{
	int docID;
	int times;
	int multiWord;	// How many key words appear
	struct doc* next;
}doc;

class DocList
{
public:
	DocList();
	~DocList();
	doc * CreateDoc(int id, int t, int mul);
	bool Add(int id);
	bool Add(doc* node);
	bool Remove(int id);
	doc* Search(int id);
	doc* Edit(int id, int newDocID);
	doc* Head();
	void Write(char* file);
	void Sort();
	void Print();
private:
	doc* head;
};
