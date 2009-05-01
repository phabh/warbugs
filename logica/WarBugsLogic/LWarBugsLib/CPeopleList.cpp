#include "CPeopleList.h"

CPeopleList::CPeopleList(void)
{
	_first = NULL;
	_size = 0;
}
CPeopleList::CPeopleList(CPersonagem *personagem)
{
	_first->personagem = personagem;
	_first->next = NULL;
	_first->prev = NULL;
	_size = 1;
}
bool CPeopleList::isEmpty()
{
	return(_first == NULL);
}
int CPeopleList::size()
{
	return(_size);
}
void CPeopleList::addPersonagem(CPersonagem *personagem)
{
	_size = _size + 1;
	SCharElemento *nodo = new SCharElemento();
	nodo->personagem = personagem;
	nodo->next = NULL;
	nodo->prev = NULL;
	if(isEmpty())
	{
		_first = nodo;
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
		temp = NULL;
		delete temp;
	}
	nodo = NULL;
	delete nodo;
}
CPersonagem *CPeopleList::removePersonagem(int IDpersonagem)
{
	SCharElemento *temp = _first;
	while(temp->next != NULL)
	{
		if((temp->personagem)->getID() == IDpersonagem)
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
			return(temp->personagem);
		}
		temp = temp->next;
	}
	temp = NULL;
	delete temp;
	return (NULL);
}
CPersonagem *CPeopleList::removePersonagem(CPersonagem *personagem)
{
	SCharElemento *temp = _first;
	while(temp->next != NULL)
	{
		if(temp->personagem == personagem)
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
			return(temp->personagem);
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
CPersonagem *CPeopleList::getPersonagem(int IDpersonagem)
{
	SCharElemento *temp = _first;
	while(temp->next != NULL)
	{
		if((temp->personagem)->getID())
		{
			return(temp->personagem);
		}
		else
		{
			temp = temp->next;
		}
	}
	return(NULL);
}
bool CPeopleList::havePersonagem(CPersonagem *personagem)
{
	SCharElemento *temp = _first;
	while(temp->next != NULL)
	{
		if(temp->personagem == personagem)
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

