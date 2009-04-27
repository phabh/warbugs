#include "CBolsa.h"

CBolsa::CBolsa(void)
{
	_first = NULL;
	_next = NULL;
	_size = 0;
}
CBolsa::CBolsa(CBolsa * base)
{
	_item = base->getFirst();
	_next = base->getNext();
	_size = base->size();
}
CBolsa::CBolsa(CItem *item)
{
	_item = item;
	_next = NULL;
}
CItem *CBolsa::getThis()
{
	return(_item);
}
CBolsa *CBolsa::getNext()
{
	return(_next);
}
void CBolsa::setThis(CItem *item)
{
	_item = first;
}
void CBolsa::setNext(CBolsa *next)
{
	_next = next;
}
bool CBolsa::isEmpty()
{
	return(_first == NULL);
}
int CBolsa::size()
{
	return(_size);
}
void CBolsa::addItem(CItem *item)
{
	CBolsa *temp = new CBolsa(item);
	if(isEmpty())
	{
		this = temp;
		_next = NULL;
		_size = _size + 1;
	}
	else
	{
		CBolsa *temp2 = this;
		while(temp2->getNext() == NULL)
		{
			temp2 = temp2->getNext();
		}
		temp2->setNext(temp);

		temp2 = NULL;
		delete temp2;
	}
	temp = NULL;
	delete temp;
}
CItem *CBolsa::removeItem(int IDItem)
{
}
CItem *CBolsa::getItem(intIDItem)
{
}
