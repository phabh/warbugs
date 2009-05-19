#include "CCenarioList.h"

CCenarioList::CCenarioList(void)
{
	_first = new SCenarioElemento();
	_size = 0;
}
CCenarioList::CCenarioList(CCenario *Cenario)
{
	_first = new SCenarioElemento();
	_first->valor = Cenario;
	_first->next = NULL;
	_first->prev = NULL;
	_size = 1;
}
bool CCenarioList::isEmpty()
{
	return(_size == 0);
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
		_size = 1;
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
		_size = _size + 1;
		temp = NULL;
		delete temp;
	}
	nodo = NULL;
	delete nodo;
}
CCenario *CCenarioList::removeCenarioByPosition(int pos)
{
	SCenarioElemento *temp = _first;
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
CCenario *CCenarioList::removeCenario(int ID)
{
	SCenarioElemento *temp = _first;
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
/*CCenario *CCenarioList::removeCenario(CCenario *Cenario)
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
}*/
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
CCenario *CCenarioList::getElementAt(int index)
{
	SCenarioElemento *temp = _first;
	index = index - 1;
	while(index > 0)
	{
		temp = temp->next;
		index = index - 1;
	}
	return(temp->valor);
}
bool CCenarioList::haveCenario(int ID)
{
	SCenarioElemento *temp = _first;
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

void CCenarioList::update()
{
	for(int i = 0; i < size(); i=i+1)
	{
		getElementAt(i)->update();
	}
}