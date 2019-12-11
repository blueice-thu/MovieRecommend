#include "CharString.h"

using namespace std;

CharString::CharString()
{
	this->pBase = NULL;
	this->length = 0;
}

CharString::CharString(const char* s)
{
	int lenS = 0;
	while (s[lenS] != NULL)
		lenS++;
	this->length = lenS;
	this->pBase = new char[length + 1];

	for (int i = 0; i < lenS; i++)
	{
		this->pBase[i] = s[i];
	}

	this->pBase[lenS] = NULL;
}

CharString::CharString(const CharString& C)
{
	this->length = C.length;
	this->pBase = new char[this->length + 1];

	for (int i = 0; i < this->length; i++)
		this->pBase[i] = C.pBase[i];

	this->pBase[this->length] = NULL;
}

CharString::~CharString()
{
	if (pBase != NULL)
	{
		delete[] pBase;
	}
}
int CharString::len() const
{
	return this->length;
}

// Function: Find a given string in this stirng.
// Parameters:
//  s: the string needed to search
// Return: the index of "s". If failing, return -1.
int CharString::indexOf(const char* s) const
{
	if (s == NULL || pBase == NULL)
		return -1;
	int lenS = 0;
	while (s[lenS] != NULL)
		lenS++;
	if (lenS > length)
		return -1;

	for (int i = 0; i < length - lenS + 1; i++)
	{
		int j;
		for (j = 0; j < lenS && i + j < length; j++)
		{
			if (s[j] != pBase[i + j])
				break;
		}
		if (j == lenS)
			return i;
	}
	return -1;
}

// Function: Get a part of this string of a given position.
// Parameters:
//  left: the start index of string (included)
//  right: the end index of string (Not included)
// Return: a CharString of this string with index from left to right.
CharString CharString::substring(int left, int right) const
{
	CharString result;
	if (right >= length)
		right = length;
	result.length = right - left;
	if (result.length <= 0)
	{
		cout << "No Sub!" << endl;
		system("pause");
		exit(0);
	}
	result.pBase = new char[result.length + 1];
	for (int i = 0; i < result.length; i++)
	{
		result.pBase[i] = (this->pBase + left)[i];
	}
	result.pBase[result.length] = NULL;
	return result;
}

// Function: Concatenate this string and another string.
// Parameters:
//  C: another CharString need to be added
void CharString::concat(const CharString& C)
{
	char* result = new char[this->length + C.length + 1];
	int i = 0;
	if (this->length > 0)
	{
		for (i = 0; i < this->length; i++)
			result[i] = this->pBase[i];
	}
	this->length = this->length + C.length;
	if (C.length > 0)
	{
		for (int j = i; j < this->length + C.length; j++)
		{
			result[j] = C.pBase[j - i];
		}
	}
	result[this->length] = NULL;
	if (pBase != NULL)
		delete[] pBase;
	pBase = result;
}

// Function: Make this string equal to the given string
// Parameters:
//  s: the given string
void CharString::assign(const char* s)
{
	if (s == NULL || s[0] == NULL)
	{
		cout << "A string is EMPTY!" << endl;
		return;
	}
	int lenS = 0;
	if (this->pBase != NULL)
	{
		delete[](this->pBase);
		this->pBase = NULL;
		this->length = 0;
	}
	while (s[lenS] != NULL)
	{
		lenS++;
	}
	this->pBase = new char[lenS + 1];
	this->length = lenS;
	for (int i = 0; i < lenS; i++)
		this->pBase[i] = s[i];
	this->pBase[lenS] = NULL;
}

// Function: Make this string equal to the given string
// Parameters:
//  s: the given string
CharString& CharString::operator = (const char* s)
{
	this->assign(s);
	return *this;
}
void CharString::print() const
{
	if (this->pBase != NULL)
	{
		for (int i = 0; i < this->length; i++)
			cout << this->pBase[i];
	}
}

// Function: Judge if the two CharString is equal
bool isSameString(const CharString& CS1, const CharString& CS2)
{
	if (CS1.length != CS2.length)
		return false;
	int i = 0;
	while (i < CS1.length)
	{
		if (CS1.pBase[i] != CS2.pBase[i])
			return false;
		i++;
	}
	return true;
}

// Function: Create a same character string and make "re" equal to its pointer
// Parameters:
//  re: the pointer needed to point the new string
void CharString::toChar(char* re)
{
	memset(re, 0, (this->length + 1) * sizeof(char));
	strcpy(re, pBase);
	re[this->length] = NULL;
}
