#include "BalancedBinaryTree.h"



BalancedBinaryTree::BalancedBinaryTree()
{
	pBase = NULL;
}
PNode BalancedBinaryTree::CreateNode(char * c)
{
	PNode newNode = new word;
	newNode->w = CharString(c);

	//newNode->wordID = -1;
	newNode->df = 0;
	newNode->occur = 0;
	newNode->article = NULL;

	newNode->balanceState = EH;
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;

	return newNode;
}
PNode BalancedBinaryTree::CreateNode(char * c, int df, int oc, doc* at)
{
	PNode newNode = new word;

	newNode->w = CharString(c);
	newNode->df = df;
	newNode->occur = oc;
	newNode->article = at;

	newNode->balanceState = EH;
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;

	return newNode;
}
doc * BalancedBinaryTree::CreateDoc(int id, int t)
{
	doc* d = new doc;
	d->docID = id;
	d->times = t;
	d->next = NULL;
	return d;
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
//右旋 顺时针旋转
void BalancedBinaryTree::R_Rotate(PNode* node)
{
	cout << "R_Rotate" << endl;
	PNode tmp = (*node)->leftChild;
	(*node)->leftChild = tmp->rightChild;
	tmp->rightChild = (*node);
	(*node) = tmp;
}

//左旋，逆时针旋转
void BalancedBinaryTree::L_Rotate(PNode* node)
{
	cout << "L_Rotate" << endl;
	PNode tmp = (*node)->rightChild;
	(*node)->rightChild = tmp->leftChild;
	tmp->leftChild = (*node);
	(*node) = tmp;
}

//左边失衡调整
void BalancedBinaryTree::leftBalance(PNode* node) {
	PNode leftchild = (*node)->leftChild;
	PNode tmpRightChild = NULL;
	switch (leftchild->balanceState)
	{
	case LH:                                                                     //LL型失衡
		(*node)->balanceState = leftchild->balanceState = EH;
		R_Rotate(node);
		break;
	case RH:                                                                    //LR型失衡
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

//右边失衡调整
void BalancedBinaryTree::rightBalance(PNode* node) {
	PNode rightchild = (*node)->rightChild;
	PNode tmpChild = NULL;
	switch (rightchild->balanceState)
	{
	case RH:                                                                          //RR型失衡
		(*node)->balanceState = rightchild->balanceState = EH;
		L_Rotate(node);
		break;
	case LH:                                                                         //RL型失衡
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
			return false;
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
			return false;
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
	return true;
}

//
bool BalancedBinaryTree::InsertNode(char* c, bool* adjust)
{
	return insertRecursion(pBase, c, adjust);
}
PNode BalancedBinaryTree::searchRecursion(PNode pTemp, char * c)
{
	if (!pTemp)
		return NULL;
	if (isSameString(pTemp->w, c))
	{
		return pBase;
	}
	else if (pTemp->w > CharString(c) && pTemp->leftChild)
	{
		return searchRecursion(pTemp->leftChild, c);
	}
	else if (!(pTemp->w > CharString(c)) && pTemp->rightChild)
	{
		return searchRecursion(pTemp->rightChild, c);
	}
	else
		return NULL;
}
//
PNode BalancedBinaryTree::SearchNode(char * c)
{
	return searchRecursion(pBase, c);
}

// 
void BalancedBinaryTree::UpdateNode(char * c, int newDocID)
{
	PNode node = SearchNode(c);
	if (node == NULL)
		return;
	node->occur++;
	if (node->article == NULL)
	{
		node->article = CreateDoc(newDocID, 1);
		node->df++;
	}
	else
	{
		doc* pDoc = node->article;
		while (pDoc)
		{
			if (pDoc->docID == newDocID)
			{
				// add doc to existing one
				pDoc->times++;
				break;
			}
			if (pDoc->next != NULL)
			{
				pDoc = pDoc->next;
			}
			else
			{
				// a new doc
				pDoc->next = CreateDoc(newDocID, 1);
				break;
			}
		}
	}
}