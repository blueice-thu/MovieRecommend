#pragma once

#include "CharString.h"
#include <iostream>
#include <malloc.h>
#include <fstream>

using namespace std;

typedef struct BaseCharString
{
	CharString* data;
	BaseCharString* next;
}BaseCharString;

// Character String Link class
class CharStringLink
{
public:
	CharStringLink();
	CharStringLink(const CharStringLink& CSL);
	~CharStringLink();
	void add(const CharString& CS);
	void add(const char* CS);
	void remove(); // Remove the first item of the link
	int search(const CharString& CS);
	BaseCharString* getBase() const; // Search the given Charstring in this link
	void save(char* savePath); // Save all the string in this link to a given file
	int getLength();
private:
	BaseCharString* pBase;
};
