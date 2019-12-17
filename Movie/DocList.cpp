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
doc * DocList::CreateDoc(int id, int t = 0)
{
	doc* d = new doc;
	d->docID = id;
	d->times = t;
	d->next = NULL;
	return d;
}
bool DocList::Add(int id)
{
	if (head == NULL)
	{
		head = CreateDoc(id, 1);
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
				pDoc->next = CreateDoc(id, 1);
				break;
			}
		}
	}
	return true;
}
bool DocList::Add(doc * node)
{
	if (!node)
		return false;
	int id = node->docID;
	if (head == NULL)
	{
		head = CreateDoc(id, node->times);
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
				return false;
			}
			if (pDoc->next != NULL)
			{
				pDoc = pDoc->next;
			}
			else
			{
				// a new doc
				pDoc->next = CreateDoc(id, node->times);
				break;
			}
		}
	}
	return true;
}
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
doc * DocList::Edit(int id, int newDocID)
{
	doc* p = Search(id);
	if (p)
		p->docID = newDocID;
	return p;
}
doc * DocList::Head()
{
	return head;
}
void DocList::Write(char * file, bool print)
{
	ofstream out(file, ios::app);
	doc* temp = head;
	while (temp)
	{
		out << "(" << temp->docID << "," << temp->times << ")";
		if (print)
			cout << "(" << temp->docID << "," << temp->times << ")";
		temp = temp->next;
		if (temp)
		{
			out << " ";
			if (print)
				cout << " ";
		}
	}
	out << "\n";
	out.close();
}