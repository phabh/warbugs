
#include "CBuffList.h"

CBuffList::CBuffList(void)
{
	_first = new SBuffElemento();
	_size = 0;
}
CBuffList::CBuffList(CBuff *Buff)
{
	_first = new SBuffElemento();
	_first->valor = Buff;
	_first->next = NULL;
	_first->prev = NULL;
	_size = 1;
}
bool CBuffList::isEmpty()
{
	return(_size == 0);
}
int CBuffList::size()
{
	return(_size);
}
void CBuffList::addBuff(CBuff *Buff)
{
	SBuffElemento *nodo = new SBuffElemento();
	nodo->valor = Buff;
	nodo->next = NULL;
	nodo->prev = NULL;
	if(isEmpty())
	{
		_first = nodo;
		_size = 1;
	}
	else
	{
		SBuffElemento *temp = _first;
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
CBuff *CBuffList::removeBuffByPosition(int pos)
{
	SBuffElemento *temp = _first;
	if(pos < size())
	{
		while(pos > 0)
		{
			temp = temp->next;
			pos = pos -1;
		}
		//Se for o primeiro
		if(temp->prev == NULL)
		{
			_first = temp->next;
			temp->next = NULL;
			_size = _size - 1;
			return(temp->valor);
		}
		//Se for o último
		else if(temp->next == NULL)
		{
			(temp->prev)->next = NULL;
			temp->prev = NULL;
			_size = _size - 1;
			return(temp->valor);
		}
		else
		{
			(temp->prev)->next = temp->next;
			(temp->next)->prev = temp->prev;
			temp->next = NULL;
			temp->prev = NULL;
			_size = _size - 1;
			return(temp->valor);
		}
	}
	else
	{
		return(NULL);
	}
}
CBuff *CBuffList::removeBuff(int ID)
{
	SBuffElemento *temp = _first;
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
CBuff *CBuffList::removeBuff(CBuff *Buff)
{
	SBuffElemento *temp = _first;
	while(temp->next != NULL)
	{
		if((temp->valor)->getTipo() == Buff->getTipo())
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
CBuff *CBuffList::getBuff(int IDBuff)
{
	SBuffElemento *temp = _first;
	while(temp->next != NULL)
	{
		if((temp->valor)->getID() == IDBuff)
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
CBuff *CBuffList::getBuff(CBuff *buff)
{
	SBuffElemento *temp = _first;
	while(temp->next != NULL)
	{
		if((temp->valor)->getID() == buff->getTipo())
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
CBuff *CBuffList::getElementAt(int index)
{
	SBuffElemento *temp = _first;
	index = index - 1;
	while(index > 0)
	{
		temp = temp->next;
		index = index - 1;
	}
	return(temp->valor);
}
bool CBuffList::haveBuff(CBuff *Buff)
{
	SBuffElemento *temp = _first;
	while(temp->next != NULL)
	{
		if(temp->valor->getTipo() == Buff->getTipo())
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

void CBuffList::executeBuffs(CPersonagem *jogador, CBuffList *lista)
{
	SBuffElemento *temp = _first;
	while(temp->next != NULL)
	{
		temp->valor->execute(jogador, lista);
	}
}
