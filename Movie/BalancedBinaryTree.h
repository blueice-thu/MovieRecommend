#pragma once
#include "CharString.h"
enum BalanceFactor { EH, LH, RH };
typedef struct doc
{
	int docID;
	int times;
	struct doc* next;
};
typedef struct word
{
	CharString w;
	int wordID;
	int df;// The number of articles word occuring
	int occur;// The total times of word occuring
	doc* article;

	BalanceFactor balanceState;
	struct word *leftChild, *rightChild;
}*PNode;
// https://blog.csdn.net/xwm1993/article/details/80405430
class BalancedBinaryTree
{
public:
	BalancedBinaryTree();
	~BalancedBinaryTree();
	PNode CreateNode(char* c);
	void Insert(char* c);
private:
	PNode pBase;
};

