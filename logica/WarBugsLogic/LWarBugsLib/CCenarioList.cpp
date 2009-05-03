#include "CCenarioList.h"

CCenarioList::CCenarioList(void)
{
	_first = NULL;
	_size = 0;
}
CCenarioList::CCenarioList(CCenario *Cenario)
{
	_first->valor = Cenario;
	_first->next = NULL;
	_first->prev = NULL;
	_size = 1;
}
bool CCenarioList::isEmpty()
{
	return(_first == NULL);
}
int CCenarioList::size()
{
	return(_size);
}
void CCenarioList::addCenario(CCenario *Cenario)
{
	SCenarioElemento *nodo = new SCenarioElemento();
	nodo->valor = Cenario;
	nodo->next = NULL;
	nodo->prev = NULL;
	if(isEmpty())
	{
		_first = nodo;
	}
	else
	{
		SCenarioElemento *temp = _first;
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
/*CCenario *CCenarioList::removeCenario(int posCenario)
{
	SCenarioElemento *temp = _first;
	posCenario = posCenario - 1;
	while(posCenario > 0)
	{
		temp = temp->next;
		posCenario = posCenario -1;
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
	return(temp->Cenario);
}*/
CCenario *CCenarioList::removeCenario(int IDCenario)
{
	SCenarioElemento *temp = _first;
	while(temp->next != NULL)
	{
		if((temp->valor)->getID() == IDCenario)
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
CCenario *CCenarioList::removeCenario(CCenario *Cenario)
{
	SCenarioElemento *temp = _first;
	while(temp->next != NULL)
	{
		if(temp->valor == Cenario)
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
CCenario *CCenarioList::getCenario(int IDCenario)
{
	SCenarioElemento *temp = _first;
	while(temp->next != NULL)
	{
		if((temp->valor)->getID() == IDCenario)
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
bool CCenarioList::haveCenario(CCenario *Cenario)
{
	SCenarioElemento *temp = _first;
	while(temp->next != NULL)
	{
		if(temp->valor == Cenario)
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

