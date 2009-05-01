#include "CBolsaList.h"

CBolsaList::CBolsaList(void)
{
	_first = NULL;
	_size = 0;
}
CBolsaList::CBolsaList(CBolsa *bolsa)
{
	_first->bolsa = bolsa;
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
void CBolsaList::addBolsa(CBolsa *bolsa)
{
	SBagElemento *nodo = new SBagElemento();
	nodo->bolsa = bolsa;
	nodo->next = NULL;
	nodo->prev = NULL;
	if(isEmpty())
	{
		_first = nodo;
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
		temp = NULL;
		delete temp;
	}
	nodo = NULL;
	delete nodo;
}
/*CBolsa *CBolsaList::removebolsa(int posbolsa)
{
	SBagElemento *temp = _first;
	posbolsa = posbolsa - 1;
	while(posbolsa > 0)
	{
		temp = temp->next;
		posbolsa = posbolsa -1;
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
	return(temp->bolsa);
}*/
CBolsa *CBolsaList::removeBolsa(int IDbolsa)
{
	SBagElemento *temp = _first;
	while(temp->next != NULL)
	{
		if((temp->bolsa)->getID() == IDbolsa)
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
			return(temp->bolsa);
		}
	}
	temp = NULL;
	delete temp;
	return(NULL);
}
CBolsa *CBolsaList::removeBolsa(CBolsa *bolsa)
{
	SBagElemento *temp = _first;
	while(temp->next != NULL)
	{
		if(temp->bolsa == bolsa)
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
			return(temp->bolsa);
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
CBolsa *CBolsaList::getBolsa(int IDbolsa)
{
	SBagElemento *temp = _first;
	while(temp->next != NULL)
	{
		if((temp->bolsa)->getID() == IDbolsa)
		{
			return(temp->bolsa);
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
bool CBolsaList::haveBolsa(CBolsa *bolsa)
{
	SBagElemento *temp = _first;
	while(temp->next != NULL)
	{
		if(temp->bolsa == bolsa)
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
