#pragma once
#include <iostream>
#include <string.h>
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
	doc * CreateDoc(int id);
	bool Add(int id);
	bool Remove(int id);
	doc* Search(int id);
	doc* Edit(int id, int newDocID);
private:
	doc* head;
};
