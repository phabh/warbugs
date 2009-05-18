#include "CBolsaList.h"

CBolsaList::CBolsaList(void)
{
	_first = NULL;
	_size = 0;
}
CBolsaList::CBolsaList(CBolsa *bolsa)
{
	_first->valor = bolsa;
	_first->next = NULL;
	_first->prev = NULL;
	_size = 1;
}
bool CBolsaList::isEmpty()
{
	return(_first == NULL);
}
int CBolsaList::size()
{
	return(_size);
}
void CBolsaList::addBag(CBolsa *bolsa)
{
	SBagElemento *nodo = new SBagElemento();
	nodo->valor = bolsa;
	nodo->next = NULL;
	nodo->prev = NULL;
	if(isEmpty())
	{
		_first = nodo;
		_size = 1;
	}
	else
	{
		SBagElemento *temp = _first;
		while(temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = nodo;
		nodo->prev = temp;
		_size = _size + 1;
		temp = NULL;
		delete temp;
	}
	nodo = NULL;
	delete nodo;
}
CBolsa *CBolsaList::removeBolsaByPosition(int pos)
{
	SBagElemento *temp = _first;
	if(pos < size())
	{
		while(pos > 0)
		{
			temp = temp->next;
			pos = pos -1;
		}
		if(temp->prev != NULL)
		{
			(temp->prev)->next = temp->next;
			_size = _size - 1;
			return(temp->valor);
		}
		else
		{
			_first = temp->next;
			_first->next = (temp->next)->next;
			_first->prev = NULL;
			_size = _size - 1;
			return(temp->valor);
		}

		if(temp->next != NULL)
		{
			(temp->next)->prev = temp->prev;
			_size = _size - 1;
			return(temp->valor);
		}
		else
		{
			(temp->prev)->next = NULL;
			_size = _size - 1;
			return(temp->valor);
		}
	}
	else
	{
		return(NULL);
	}
}
CBolsa *CBolsaList::removeBolsa(int ID)
{
	SBagElemento *temp = _first;
	while(temp->next != NULL)
	{
		if((temp->valor)->getID() == ID)
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
			_size = _size - 1;
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
/*CBolsa *CBolsaList::removeBolsa(CBolsa *bolsa)
{
	SBagElemento *temp = _first;
	while(temp->next != NULL)
	{
		if(temp->valor == bolsa)
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
}*/
CBolsa *CBolsaList::getBolsa(int IDbolsa)
{
	SBagElemento *temp = _first;
	while(temp->next != NULL)
	{
		if((temp->valor)->getID() == IDbolsa)
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
CBolsa *CBolsaList::getElementAt(int index)
{
	SBagElemento *temp = _first;
	index = index - 1;
	while(index > 0)
	{
		temp = temp->next;
		index = index - 1;
	}
	return(temp->valor);
}
bool CBolsaList::haveBolsa(CBolsa *bolsa)
{
	SBagElemento *temp = _first;
	while(temp->next != NULL)
	{
		if(temp->valor == bolsa)
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
