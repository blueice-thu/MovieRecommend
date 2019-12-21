#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

// Character String class
class CharString
{
public:
	CharString();
	CharString(const char* s);
	CharString(const CharString& C);
	~CharString();
	int len() const;
	int indexOf(const char* s) const; // Find a given string in this stirng
	CharString substring(int left, int right) const; // Get a part of this string of a given position
	void concat(const CharString& C); // Concatenate this string and another string
	void assign(const char* s); // Make this string equal to the given string
	CharString& operator = (const char* s);
	void print() const;
	friend bool isSameString(const CharString& CS1, const CharString& CS2);
	friend bool operator==(const CharString& CS1, const CharString& CS2);
	friend bool operator>(const CharString& CS1, const CharString& CS2);
	void toChar(char* re);
	char operator[](int nIndex);
private:
	char* pBase;
	int length;
};
