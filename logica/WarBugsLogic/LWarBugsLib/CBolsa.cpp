#include "CBolsa.h"

CBolsa::CBolsa(void)
{
	_first = NULL;
	_size = 0;
}
CBolsa::CBolsa(CItem *item)
{
	_first->valor = item;
	_first->next = NULL;
	_first->prev = NULL;
	_size = 1;
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
	SElemento *nodo = new SElemento();
	nodo->valor = item;
	nodo->next = NULL;
	nodo->prev = NULL;
	if(isEmpty())
	{
		_first = nodo;
	}
	else
	{
		SElemento *temp = _first;
		while(temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = nodo;
		nodo->prev = temp;
		temp = NULL;
		delete temp;
	}
	nodo = NULL;
	delete nodo;
}
CItem *CBolsa::removeItemByPosition(int posItem)
{
	SElemento *temp = _first;
	posItem = posItem - 1;
	while(posItem > 0)
	{
		temp = temp->next;
		posItem = posItem -1;
	}
	if(temp->prev != NULL)
	{
		(temp->prev)->next = temp->next;
		return(temp->valor);
	}
	else
	{
		_first = temp->next;
		_first->next = (temp->next)->next;
		_first->prev = NULL;
		return(temp->valor);
	}

	if(temp->next != NULL)
	{
		(temp->next)->prev = temp->prev;
		return(temp->valor);
	}
	else
	{
		(temp->prev)->next = NULL;
		return(temp->valor);
	}
}
CItem *CBolsa::removeItem(int IDItem)
{
	SElemento *temp = _first;
	while(temp->next != NULL)
	{
		if((temp->valor)->getID() == IDItem)
		{
			if(temp->prev != NULL)
				(temp->prev)->next = temp->next;
			else
			{
				_first = temp->next;
				_first->next = (temp->next)->next;
				_first->prev = NULL;
			}

			if(temp->next != NULL)
				(temp->next)->prev = temp->prev;
			else
			{
				(temp->prev)->next = NULL;
			}
			return(temp->valor);
		}
	}
	temp = NULL;
	delete temp;
	return(NULL);
}
CItem *CBolsa::removeItem(CItem *item)
{
	SElemento *temp = _first;
	while(temp->next != NULL)
	{
		if(temp->valor == item)
		{
			if(temp->prev != NULL)
				(temp->prev)->next = temp->next;
			else
			{
				_first = temp->next;
				_first->next = (temp->next)->next;
				_first->prev = NULL;
			}

			if(temp->next != NULL)
				(temp->next)->prev = temp->prev;
			else
			{
				(temp->prev)->next = NULL;
			}
			return(temp->valor);
		}
		else
		{
			temp = temp->next;
		}
	}
	temp = NULL;
	delete temp;
	return(NULL);
}
CItem *CBolsa::getItem(int IDItem)
{
	SElemento *temp = _first;
	while(temp->next != NULL)
	{
		if((temp->valor)->getID() == IDItem)
		{
			return(temp->valor);
		}
		else
		{
			temp = temp->next;
		}
	}
	temp = NULL;
	delete temp;
	return(NULL);
}
bool CBolsa::haveItem(CItem *item)
{
	SElemento *temp = _first;
	while(temp->next != NULL)
	{
		if(temp->valor == item)
		{
			temp = NULL;
			delete temp;
			return(true);
		}
		else
		{
			temp = temp->next;
		}
	}
	temp = NULL;
	delete temp;
	return(false);
}
