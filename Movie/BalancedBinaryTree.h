#pragma once
#include "CharString.h"
#include "DocList.h"
enum BalanceFactor { EH, LH, RH };

typedef struct word
{
	char* w;
	int df;		// The number of articles word occuring
	int occur;	// The total times of word occuring
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
	PNode CreateNode(char * c);
	PNode CreateNode(char * c, int df, int oc, doc* at);
	doc* CreateDoc(int id);
	bool InsertNode(char* c, bool* adjust);
	PNode SearchNode(char* c);
	void UpdateNode(char* c, int newDocID);
	void RemoveNode(char* c);
	void EditNode();
private:
	void R_Rotate(PNode* node);
	void L_Rotate(PNode* node);
	void leftBalance(PNode* node);
	void rightBalance(PNode* node);
	bool insertRecursion(PNode& pTemp, char* c, bool* adjust);
	PNode searchRecursion(PNode pTemp, char* c);
	PNode pBase;
};

