#include "CPlayerList.h"

CPlayerList::CPlayerList(void)
{
	_first = NULL;
	_size = 0;
}
CPlayerList::CPlayerList(CJogador *Jogador)
{
	_first->valor = Jogador;
	_first->next = NULL;
	_first->prev = NULL;
	_size = 1;
}
bool CPlayerList::isEmpty()
{
	return(_first == NULL);
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
		temp = NULL;
		delete temp;
	}
	nodo = NULL;
	delete nodo;
}
CJogador *CPlayerList::removeJogadorByPosition(int posJogador)
{
	SPlayerElemento *temp = _first;
	posJogador = posJogador - 1;
	while(posJogador > 0)
	{
		temp = temp->next;
		posJogador = posJogador -1;
	}
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
CJogador *CPlayerList::removeJogador(int IDJogador)
{
	SPlayerElemento *temp = _first;
	while(temp->next != NULL)
	{
		if((temp->valor)->getID() == IDJogador)
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
CJogador *CPlayerList::removeJogador(CJogador *Jogador)
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
}
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
