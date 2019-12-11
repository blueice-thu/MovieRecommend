#include "Stack.h"
#include <malloc.h>
#include <iostream>

using namespace std;

#define MAX_STACK_SIZE 1024 // the maximal size of the stack

Stack::Stack()
{
	this->pBase = (char*)malloc(MAX_STACK_SIZE * sizeof(char));
	this->pTop = this->pBase;
	this->size = MAX_STACK_SIZE;
	this->length = 0;
}

Stack::~Stack()
{
	if (this->pBase != NULL)
		free(pBase);
}

// Function: Judge if the stack is empty
bool Stack::empty()
{
	if (this->pBase == this->pTop)
		return true;
	else
		return false;
}

// Function: Judge if the stack is full
bool Stack::full()
{
	if (this->pTop - this->pBase >= this->size)
		return true;
	else
		return false;
}

// Function: Push a character into the stack
void Stack::push(char e)
{
	if (this->full())
	{
		cout << "Stack Over Flow!" << endl;
		exit(0);
	}
	*(this->pTop) = e;
	(this->pTop)++;
	this->length++;
}

// Function: Pop out the top character of the stack
void Stack::pop()
{
	if (this->empty())
	{
		cout << endl << "Empty Stack!" << endl;
		exit(0);
	}
	(this->pTop)--;
	this->length--;
}

// Function: Return the top character of the stack
char Stack::top()
{
	if (this->empty())
	{
		printf("\nEmpty Stack!\n");
		exit(0);
	}
	return(*(this->pTop - 1));
}

// Function: Return the length of the stack
int Stack::len()
{
	return this->length;
}
