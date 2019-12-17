#include "BalancedBinaryTree.h"



BalancedBinaryTree::BalancedBinaryTree()
{
	pBase = NULL;
}
PNode BalancedBinaryTree::CreateNode(char * c)
{
	PNode newNode = new word;
	newNode->w = CharString(c);

	newNode->wordID = -1;
	newNode->df = 0;
	newNode->occur = 0;
	newNode->article = NULL;

	newNode->balanceState = EH;
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;

	return newNode;
}
PNode BalancedBinaryTree::CreateNode(char * c, int wi, int df, int oc, doc* at)
{
	PNode newNode = new word;

	newNode->w = CharString(c);
	newNode->wordID = wi;
	newNode->df = df;
	newNode->occur = oc;
	newNode->article = at;

	newNode->balanceState = EH;
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;

	return newNode;
}
inline void FreeDocList(doc* head)
{
	doc* temp;
	while (head)
	{
		temp = head->next;
		delete head;
		head = temp;
	}
}
BalancedBinaryTree::~BalancedBinaryTree()
{

}
//ÓÒÐý Ë³Ê±ÕëÐý×ª
void BalancedBinaryTree::R_Rotate(PNode* node) {
	PNode tmp = (*node)->leftChild;
	(*node)->leftChild = tmp->rightChild;
	tmp->rightChild = (*node);
	(*node) = tmp;
}

//×óÐý£¬ÄæÊ±ÕëÐý×ª
void BalancedBinaryTree::L_Rotate(PNode* node) {
	PNode tmp = (*node)->rightChild;
	(*node)->rightChild = tmp->leftChild;
	tmp->leftChild = (*node);
	(*node) = tmp;
}

//×ó±ßÊ§ºâµ÷Õû
void BalancedBinaryTree::leftBalance(PNode* node) {
	PNode leftchild = (*node)->leftChild;
	PNode tmpRightChild = NULL;
	switch (leftchild->balanceState)
	{
	case LH:                                                                     //LLÐÍÊ§ºâ
		(*node)->balanceState = leftchild->balanceState = EH;
		R_Rotate(node);
		break;
	case RH:                                                                    //LRÐÍÊ§ºâ
		tmpRightChild = leftchild->rightChild;
		switch (tmpRightChild->balanceState)
		{
		case LH:
			(*node)->balanceState = RH;
			leftchild->balanceState = EH;
			break;
		case EH:
			(*node)->balanceState = leftchild->balanceState = EH;
			break;
		case RH:
			(*node)->balanceState = EH;
			leftchild->balanceState = LH;
			break;
		}
		tmpRightChild->balanceState = EH;
		L_Rotate(&(*node)->leftChild);
		R_Rotate(node);
		break;
	}
}

//ÓÒ±ßÊ§ºâµ÷Õû
void BalancedBinaryTree::rightBalance(PNode* node) {
	PNode rightchild = (*node)->rightChild;
	PNode tmpChild = NULL;
	switch (rightchild->balanceState)
	{
	case RH:                                                                          //RRÐÍÊ§ºâ
		(*node)->balanceState = rightchild->balanceState = EH;
		L_Rotate(node);
		break;
	case LH:                                                                         //RLÐÍÊ§ºâ
		tmpChild = rightchild->leftChild;
		switch (tmpChild->balanceState)
		{
		case LH:
			(*node)->balanceState = EH;
			rightchild->balanceState = RH;
			break;
		case EH:
			(*node)->balanceState = rightchild->balanceState = EH;
			break;
		case RH:
			(*node)->balanceState = EH;
			rightchild->balanceState = LH;
			break;
		}
		tmpChild->balanceState = EH;
		R_Rotate(&(*node)->rightChild);
		L_Rotate(node);
		break;
	}
}

//
bool BalancedBinaryTree::insertRecursion(PNode pTemp, char * c, bool * adjust)
{
	if (pTemp == NULL)
	{
		// TODO
		pTemp = CreateNode(c);
		*adjust = true;
		return true;
	}
	else if (pTemp->w == c)
	{
		*adjust = false;
		return false;
	}
	else if (pTemp->w > c)
	{
		// insert to left child
		if (!insertRecursion(pTemp->leftChild, c, adjust))
			return 0;
		if (*adjust)
		{
			switch (pTemp->balanceState)
			{
			case LH:
				leftBalance(&pTemp);
				*adjust = false;
				break;
			case RH:
				pTemp->balanceState = EH;
				*adjust = false;
				break;
			case EH:
				pTemp->balanceState = LH;
				*adjust = true;
				break;
			}
		}
	}
	else
	{
		// insert to right child
		if (!insertRecursion(pTemp->rightChild, c, adjust))
			return 0;
		if (*adjust)
		{
			switch (pTemp->balanceState)
			{
			case LH:
				pTemp->balanceState = EH;
				*adjust = false;
				break;
			case RH:
				rightBalance(&pTemp);
				*adjust = false;
				break;
			case EH:
				pTemp->balanceState = RH;
				*adjust = true;
				break;
			}
		}
	}
	return false;
}

//
void BalancedBinaryTree::InsertNode(char* c, bool* adjust)
{
	insertRecursion(pBase, c, adjust);
}