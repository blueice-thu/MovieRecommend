#include "DocList.h"

DocList::DocList()
{
	head = NULL;
}

DocList::~DocList()
{
	doc* temp;
	while (head)
	{
		temp = head->next;
		delete head;
		head = temp;
	}
}

// Function: create a DocList node
//		default: an empty node
doc * DocList::CreateDoc(int id, int t = 0, int mul = 0)
{
	doc* d = new doc;
	d->docID = id;
	d->times = t;
	d->multiWord = mul;
	d->next = NULL;
	return d;
}

// Function: add a node by id
bool DocList::Add(int id)
{
	if (head == NULL)
	{
		head = CreateDoc(id, 1, 1);
	}
	else
	{
		doc* pDoc = head;
		while (pDoc)
		{
			if (pDoc->docID == id)
			{
				// add doc to existing one
				pDoc->times++;
				return false;
			}
			if (pDoc->next != NULL)
			{
				pDoc = pDoc->next;
			}
			else
			{
				// a new doc
				pDoc->next = CreateDoc(id, 1, 1);
				break;
			}
		}
	}
	return true;
}

// Function: add a node by node
bool DocList::Add(doc * node)
{
	if (!node)
		return false;
	int id = node->docID;
	if (head == NULL)
	{
		head = CreateDoc(id, node->times, node->multiWord);
	}
	else
	{
		doc* pDoc = head;
		while (pDoc)
		{
			if (pDoc->docID == id)
			{
				// add doc to existing one
				pDoc->times += node->times;
				pDoc->multiWord++;
				return false;
			}
			if (pDoc->next != NULL)
			{
				pDoc = pDoc->next;
			}
			else
			{
				// a new doc
				pDoc->next = CreateDoc(id, node->times, node->multiWord);
				break;
			}
		}
	}
	return true;
}

// Function: Search a node by id
doc* DocList::Search(int id)
{
	doc* temp = head;
	while (temp)
	{
		if (temp->docID == id)
			return temp;
		temp = temp->next;
	}
	return NULL;
}

// Function: remove a node
bool DocList::Remove(int id)
{
	if (!head)
		return false;

	doc* temp = head;
	if (head->docID == id)
	{
		head = head->next;
		delete temp;
		return true;
	}
	
	while (temp->next)
	{
		if (temp->next->docID == id)
		{
			doc* toDel = temp->next;
			temp->next = temp->next->next;
			delete toDel;
			return true;
		}
		temp = temp->next;
	}

	return false;
}

// Function: edit a node
doc * DocList::Edit(int id, int newDocID)
{
	doc* p = Search(id);
	if (p)
		p->docID = newDocID;
	return p;
}

// Function: return the head point of the doc list
doc * DocList::Head()
{
	return head;
}

// Funtion: write the DocList to special path
void DocList::Write(char * file)
{
	ofstream out(file, ios::app);
	doc* temp = head;
	while (temp)
	{
		out << "(" << temp->docID << "," << temp->times << ")";
		temp = temp->next;
		if (temp)
		{
			out << " ";
		}
	}
	out << "\n";
	out.close();
}

// Function: swap two nodes (node 1 and node 2)
void swapNode(doc* node0)
{
	if (node0 == NULL || node0->next == NULL || node0->next->next == NULL)
		return;
	doc* node1 = node0->next;
	doc* node2 = node1->next;
	doc* node3 = node2->next;
	node0->next = node2;
	node1->next = node3;
	node2->next = node1;
}

// Function: sort the list by multiWord (first) and times (second)
void DocList::Sort()
{
	if (head == NULL || head->next == NULL)
		return;

	int len = 0;
	doc* temp = head;
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	temp = head;
	int lastChange = len - 2;

	doc* pre_head = new doc;

	doc* temp_head = new doc;
	temp_head->docID = head->docID;
	temp_head->multiWord = head->multiWord;
	temp_head->times = head->times;
	temp_head->next = head->next;

	pre_head->next = temp_head;
	while (lastChange != 0)
	{
		int max_step = lastChange;
		lastChange = 0;
		doc* new_head = pre_head;
		for (int i = 0; i < max_step; i++)
		{
			if (new_head->next->next == NULL)
				break;
			if (new_head->next->multiWord < new_head->next->next->multiWord)
			{
				swapNode(new_head);
				lastChange = i;
			}
			else if (new_head->next->multiWord == new_head->next->next->multiWord && new_head->next->times < new_head->next->next->times)
			{
				swapNode(new_head);
				lastChange = i;
			}
			new_head = new_head->next;
		}
	}
	delete head;
	head = pre_head->next;
	delete pre_head;
}

// Function: print the doc list
void DocList::Print()
{
	doc* temp = head;
	int i = 0;
	while (temp)
	{
		cout << "(" << i
			<< ", docID: " << temp->docID
			<< ", multi: " << temp->multiWord
			<< ", times: " << temp->times
			<< ")";
		temp = temp->next;
		cout << endl;
	}
}