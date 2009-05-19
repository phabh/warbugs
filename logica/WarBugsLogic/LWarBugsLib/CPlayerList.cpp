#include "CPlayerList.h"

CPlayerList::CPlayerList(void)
{
	_first = new SPlayerElemento();
	_size = 0;
}
CPlayerList::CPlayerList(CJogador *Jogador)
{
	_first = new SPlayerElemento();
	_first->valor = Jogador;
	_first->next = NULL;
	_first->prev = NULL;
	_size = 1;
}
bool CPlayerList::isEmpty()
{
	return(_size == 0);
}
int CPlayerList::size()
{
	return(_size);
}
void CPlayerList::addJogador(CJogador *Jogador)
{
	SPlayerElemento *nodo = new SPlayerElemento();
	nodo->valor = Jogador;
	nodo->next = NULL;
	nodo->prev = NULL;
	if(isEmpty())
	{
		_first = nodo;
		_size = 1;
	}
	else
	{
		SPlayerElemento *temp = _first;
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
CJogador *CPlayerList::removeJogadorByPosition(int pos)
{
	SPlayerElemento *temp = _first;
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
CJogador *CPlayerList::removeJogador(int ID)
{
	SPlayerElemento *temp = _first;
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
/*CJogador *CPlayerList::removeJogador(CJogador *Jogador)
{
	SPlayerElemento *temp = _first;
	while(temp->next != NULL)
	{
		if(temp->valor == Jogador)
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
CJogador *CPlayerList::getJogador(int IDJogador)
{
	SPlayerElemento *temp = _first;
	while(temp->next != NULL)
	{
		if((temp->valor)->getID() == IDJogador)
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
CJogador *CPlayerList::getElementAt(int index)
{
	SPlayerElemento *temp = _first;
	index = index - 1;
	while(index > 0)
	{
		temp = temp->next;
		index = index - 1;
	}
	return(temp->valor);
}
bool CPlayerList::haveJogador(CJogador *Jogador)
{
	SPlayerElemento *temp = _first;
	while(temp->next != NULL)
	{
		if(temp->valor == Jogador)
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
