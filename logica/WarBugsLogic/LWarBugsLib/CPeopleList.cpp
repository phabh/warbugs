#include "CPeopleList.h"

CPeopleList::CPeopleList(void)
{
	_first = new SCharElemento();
	_size = 0;
}
CPeopleList::CPeopleList(CPersonagem *personagem)
{
	_first = new SCharElemento();
	_first->valor = personagem;
	_first->next = NULL;
	_first->prev = NULL;
	_size = 1;
}
bool CPeopleList::isEmpty()
{
	return(_size == 0);
}
int CPeopleList::size()
{
	return(_size);
}
void CPeopleList::addPersonagem(CPersonagem *personagem)
{
	SCharElemento *nodo = new SCharElemento();
	nodo->valor = personagem;
	nodo->next = NULL;
	nodo->prev = NULL;
	if(isEmpty())
	{
		_first = nodo;
		_size = 1;
	}
	else
	{
		SCharElemento *temp = _first;
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
CPersonagem *CPeopleList::removePersonagemByPosition(int pos)
{
	SCharElemento *temp = _first;
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
CPersonagem *CPeopleList::removePersonagem(int ID)
{
	SCharElemento *temp = _first;
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
/*CPersonagem *CPeopleList::removePersonagem(CPersonagem *personagem)
{
	SCharElemento *temp = _first;
	while(temp->next != NULL)
	{
		if(temp->valor == personagem)
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
}*/
CPersonagem *CPeopleList::getPersonagem(int IDpersonagem)
{
	SCharElemento *temp = _first;
	while(temp->next != NULL)
	{
		if((temp->valor)->getID())
		{
			return(temp->valor);
		}
		else
		{
			temp = temp->next;
		}
	}
	return(NULL);
}
CPersonagem *CPeopleList::getElementAt(int index)
{
	SCharElemento *temp = _first;
	index = index - 1;
	while(index > 0)
	{
		temp = temp->next;
		index = index - 1;
	}
	return(temp->valor);
}
bool CPeopleList::havePersonagem(int ID)
{
	SCharElemento *temp = _first;
	while(temp->next != NULL)
	{
		if(temp->valor->getID() == ID)
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

