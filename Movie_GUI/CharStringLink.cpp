#include "CharStringLink.h"

using namespace std;

CharStringLink::CharStringLink()
{
	pBase = new BaseCharString;
	pBase->data = NULL;
	pBase->next = NULL;
}

CharStringLink::CharStringLink(const CharStringLink& CSL)
{
	pBase = new BaseCharString;
	BaseCharString* p = pBase;
	BaseCharString* q = CSL.pBase->next;
	while (q != NULL)
	{
		BaseCharString* n = new BaseCharString;
		n->data = new CharString(*(CSL.pBase->data));
		n->next = NULL;

		p->next = n;
		p = p->next;
		
		q = q->next;
	}
}

CharStringLink::~CharStringLink()
{
	BaseCharString* p;
	while (pBase != NULL)
	{
		p = pBase->next;
		if (pBase->data != NULL)
			delete pBase->data;
		delete pBase;
		pBase = p;
	}
}

// Function: Add a CharString to this CharStringLink
// Parameters:
//  CS: the CharString needed to be added
void CharStringLink::add(const CharString& CS)
{
	BaseCharString* p = pBase;
	while (p->next != NULL)
	{
		p = p->next;
	}
	BaseCharString* n = new BaseCharString;
	n->data = new CharString(CS);
	n->next = NULL;
	p->next = n;
}

// Function: Add a character string to this CharStringLink
// Parameters:
//  CS: the pointer of the character string
void CharStringLink::add(const char* CS)
{
	BaseCharString* p = pBase;
	while (p->next != NULL)
	{
		p = p->next;
	}
	BaseCharString* n = new BaseCharString;
	n->data = new CharString(CS);
	n->next = NULL;
	p->next = n;
}

// Function: Remove the first item of the link
void CharStringLink::remove()
{
	BaseCharString* p = pBase->next;
	pBase->next = p->next;
	delete p;
}

// Function: Search the given Charstring in this link
// Parameters:
//  CS: the CharString need to ba searched
// Return: the position of "CS". If failing, return -1.
int CharStringLink::search(const CharString& CS)
{
	if (pBase->next != NULL)
		return -1;
	BaseCharString* p = pBase->next;
	int index = 0;
	while (p != NULL)
	{
		index++;
		if (isSameString(*(p->data), CS))
		{
			return index;
		}
		p = p->next;
	}
	return -1;
}

// Function: Save all the string in this link to a given file
// Parameters:
//  savePath: a pointer of a character string standing for saving path and file name
void CharStringLink::save(char* savePath)
{
	BaseCharString* p = pBase->next;
	ofstream out(savePath);
	char* temp = NULL;
	while (p != NULL)
	{
		temp = new char[p->data->len() + 1];
		p->data->toChar(temp);
		out << temp;
		if (p->next != NULL)
			out << endl;
		delete[] temp;
		p = p->next;
	}
}

// Function: Return the first BaseCharString pointer of this link
BaseCharString* CharStringLink::getBase() const
{
	return pBase;
}

// Function :Return the length of this link
int CharStringLink::getLength()
{
	int length = 0;
	BaseCharString* p = pBase;
	while (p->next != NULL)
	{
		length++;
		p = p->next;
	}
	return length;
}