#pragma once

using namespace std;

// Stack class
class Stack
{
public:
	Stack();
	~Stack();
	bool empty();
	bool full();
	void push(char e);
	void pop();
	char top();
	int len();
private:
	int size;
	int length;
	char* pTop, *pBase;
};