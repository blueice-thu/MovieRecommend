#include "BalancedBinaryTree.h"

BalancedBinaryTree::BalancedBinaryTree()
{
	pBase = NULL;
}

PNode BalancedBinaryTree::CreateNode(char * c)
{
	PNode newNode = new word;
	newNode->w = new char[50];
	memset(newNode->w, 0, sizeof(char) * 50);
	strcpy(newNode->w, c);
	
	newNode->df = 0;
	newNode->occur = 0;
	newNode->article = new DocList();

	newNode->balanceState = EH;
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;

	return newNode;
}

PNode BalancedBinaryTree::CreateNode(char * c, int df, int oc, doc* at)
{
	PNode newNode = new word;

	newNode->w = new char[50];
	memset(newNode->w, 0, sizeof(char) * 50);
	strcpy(newNode->w, c);

	newNode->df = df;
	newNode->occur = oc;
	newNode->article->Add(at->docID);

	newNode->balanceState = EH;
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;

	return newNode;
}

BalancedBinaryTree::~BalancedBinaryTree()
{
	ClearTree(pBase);
	pBase = NULL;
}

// Function: delete tree by preorder traversal
void BalancedBinaryTree::ClearTree(PNode root)
{
	if (root)
	{
		ClearTree(root->leftChild);
		ClearTree(root->rightChild);
		if (root->w)
			delete[] root->w;
		if (root->article)
			delete root->article;
		delete root;
	}
}

// Function: right-handed rotation
void BalancedBinaryTree::R_Rotate(PNode* node)
{
	PNode tmp = (*node)->leftChild;
	(*node)->leftChild = tmp->rightChild;
	tmp->rightChild = (*node);
	(*node) = tmp;
}

// Function: left-handed rotation
void BalancedBinaryTree::L_Rotate(PNode* node)
{
	PNode tmp = (*node)->rightChild;
	(*node)->rightChild = tmp->leftChild;
	tmp->leftChild = (*node);
	(*node) = tmp;
}

// Left imbalance adjustment
void BalancedBinaryTree::leftBalance(PNode* node)
{
	PNode leftchild = (*node)->leftChild;
	PNode tmpRightChild = NULL;
	switch (leftchild->balanceState)
	{
	case LH:                                                                     // LL
		(*node)->balanceState = leftchild->balanceState = EH;
		R_Rotate(node);
		break;
	case RH:                                                                    // LR
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

// Right imbalance adjustment
void BalancedBinaryTree::rightBalance(PNode* node)
{
	PNode rightchild = (*node)->rightChild;
	PNode tmpChild = NULL;
	switch (rightchild->balanceState)
	{
	case RH:                                                                          // RR
		(*node)->balanceState = rightchild->balanceState = EH;
		L_Rotate(node);
		break;
	case LH:                                                                         // RL
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

// Function: insert a string by Recursion and adjust
bool BalancedBinaryTree::insertRecursion(PNode& pTemp, char * c, bool * adjust)
{
	if (pTemp == NULL)
	{
		// Insert success
		pTemp = CreateNode(c);
		*adjust = true;
		return true;
	}
	int diff = strcmp(pTemp->w, c);
	if (diff == 0)
	{
		*adjust = false;
		return false;
	}
	else if (diff > 0)
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

// Function: insert a string into the tree
//		if the string exists, return false
bool BalancedBinaryTree::InsertNode(char* c, bool* adjust)
{
	return insertRecursion(pBase, c, adjust);
}

// Function: search a string by Recursion
PNode BalancedBinaryTree::searchRecursion(PNode pTemp, char * c)
{
	if (!pTemp)
		return NULL;
	int diff = strcmp(pTemp->w, c);
	if (diff == 0)
	{
		return pTemp;
	}
	else if (diff > 0 && pTemp->leftChild)
	{
		return searchRecursion(pTemp->leftChild, c);
	}
	else if (diff < 0 && pTemp->rightChild)
	{
		return searchRecursion(pTemp->rightChild, c);
	}
	else
		return NULL;
}
// Function: search a string in the tree
//		if the string doesn't exist, return NULL
PNode BalancedBinaryTree::SearchNode(char * c)
{
	return searchRecursion(pBase, c);
}

// Function: add a new doc node to a tree node
void BalancedBinaryTree::UpdateNode(char * c, int newDocID)
{
	PNode node = SearchNode(c);
	if (node == NULL)
		return;
	node->occur++;
	if (node->article->Add(newDocID))
		node->df++;
	node->occur++;
}

// Function: remove a node
bool BalancedBinaryTree::RemoveNode(PNode &root, char* c, bool &shorter)
{
	if (root == NULL) {
		return false;
	}
	int diff = strcmp(root->w, c);
	if (diff == 0)
	{
		PNode tmp = NULL;
		if (root->leftChild == NULL)
		{
			tmp = root;
			root = root->rightChild;
			delete tmp;
			shorter = true;
		}
		else if (root->rightChild == NULL)
		{
			tmp = root;
			root = root->leftChild;
			delete tmp;
			shorter = true;
		}
		else
		{
			tmp = root->leftChild;
			while (tmp->rightChild) {
				tmp = tmp->rightChild;
			}
			if (root->w)
				delete[](root->w);
			strcpy(root->w, c);
			RemoveNode(root->leftChild, tmp->w, shorter);
		}
	}
	else if (diff > 0)
	{
		if (!RemoveNode(root->leftChild, c, shorter))
		{
			return false;
		}
		if (shorter)
		{
			switch (root->balanceState)
			{
			case LH:
				root->balanceState = EH;
				shorter = true;
				break;
			case RH:
				rightBalance(&root);
				if (root->rightChild->balanceState == EH)
					shorter = false;
				else
					shorter = true;
				break;
			case EH:
				root->balanceState = RH;
				shorter = false;
				break;
			}
		}
	}
	else
	{
		if (!RemoveNode(root->rightChild, c, shorter)) {
			return false;
		}
		if (shorter) {
			switch (root->balanceState)
			{
			case LH:
				leftBalance(&root);
				if (root->leftChild->balanceState == EH)
					shorter = false;
				else
					shorter = true;
				break;
			case EH:
				root->balanceState = LH;
				shorter = false;
				break;
			case RH:
				root->balanceState = EH;
				shorter = true;
				break;
			}
		}
	}
	return true;
}

// Function: edit a node
void BalancedBinaryTree::EditNode(char* c, int newdf, int newoccur)
{
	PNode node = SearchNode(c);
	if (node == NULL)
		return;
	if (newdf >= 0)
		node->df = newdf;
	if (newoccur >= 0)
		node->df = newoccur;
}