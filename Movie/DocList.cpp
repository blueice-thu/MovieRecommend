#include "DocList.h"



DocList::DocList()
{

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
doc * DocList::CreateDoc(int id)
{
	doc* d = new doc;
	d->docID = id;
	d->times = 1;
	d->next = NULL;
	return d;
}
bool DocList::Add(int id)
{
	if (head == NULL)
	{
		head = CreateDoc(id);
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
				pDoc->next = CreateDoc(id);
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