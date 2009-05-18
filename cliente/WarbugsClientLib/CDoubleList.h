#pragma once

#include <iostream>
using namespace std;

template<class A>
struct SCelula
{
    A *valor;
	int id;
    SCelula *next;
    SCelula *prev;
};

template<class T>
class CDoubleList
{
private:
   SCelula<T> *_first;
   int _size;
public:
   CDoubleList();
   
   int size();
   bool isEmpty();
   
   void addElement(T *element, int ID);
   T *removeElement(int ID);
   T *getElement(int ID);
   
   void addElementAt(T *element, int pos);
   T *removeElementAt(int pos);
   T *getElementAt(int pos);
};

//Construtor
template<class T>CDoubleList<T>::CDoubleList()
{
    _first = new SCelula<T>();
    _size = 0;
}

//Retorna o tamanho da lista
template<class T>int CDoubleList<T>::size()
{
    return(_size);
}

//Retorna true se a lista estiver vazia, caso contrário retorna false
template<class T>bool CDoubleList<T>::isEmpty()
{
    return(_size == 0);
}

//Adiciona um elemento ao fim da lista
template<class T>void CDoubleList<T>::addElement(T *element, int ID)
{
    if(isEmpty())
    {
        _first->valor = element;
        _first->next = NULL;
        _first->prev = NULL;
		_first->id = ID;
        _size = 1;
    }
    else
    {
        SCelula<T> *temp = _first;
        SCelula<T> *temp2 = new SCelula<T>();
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp2->valor = element;
        temp2->prev = temp;
        temp2->next = NULL;
		temp2->id = ID;
        temp->next = temp2;
        
        _size = _size + 1;
        temp = NULL;
        temp2 = NULL;
        delete temp;
        delete temp2;
    }
}

//Remove o elemento indicado da lista. No pior caso percorre toda a lista
template<class T>T *CDoubleList<T>::removeElement(int ID)
{
	SCelula<T> *temp = _first;
	while(temp->next != NULL)
	{
		if(temp->id == ID)
		{
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
			temp = temp->next;
		}
	}
	temp = NULL;
	delete temp;
	return(NULL);
}
template<class T>T *CDoubleList<T>::getElement(int ID)
{
	SCelula<T> *temp = _first;
	while(temp->next != NULL)
	{
		if(temp->id == ID)
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
//Adiciona um elemento na posição pos. Caso pos seja maior que size()-1, adiciona o elemento ao fim da lista
template<class T>void CDoubleList<T>::addElementAt(T *element, int pos)
{
    if((isEmpty()) || (pos >= size()-1))
    {
        addElement(element);
        return;
    }
    else
    {
		if(pos > 0)
		{
			SCelula<T> *temp = _first;
			SCelula<T> *temp2 = new SCelula<T>();   
			while(pos > 0)
			{
				temp = temp->next;
				pos = pos - 1;
			}
			temp2->valor = element;
			temp2->next = temp;
			temp2->prev = temp->prev;
			(temp->prev)->next = temp2;
			temp->prev = temp2;
        
			_size = _size + 1;
			temp = NULL;
			temp2 = NULL;
			delete temp;
			delete temp2;
		}
		else
		{
			SCelula<T> *temp = new SCelula<T>();
			temp->valor = element;
			temp->next = _first;
			temp->prev = NULL;
			_first->prev = temp;
			_first = temp;
			_size = _size + 1;
			temp = NULL;
			delete temp;
		}
        return;
    }
}

//Remove o elemento na posição pos e retorna seu valor
template<class T>T *CDoubleList<T>::removeElementAt(int pos)
{
	SCelula<T> *temp = _first;
	while(pos > 0)
	{
		temp = temp->next;
		pos = pos - 1;
	}
	(temp->next)->prev = temp->prev;
	(temp->prev)->next = temp->next;
	temp->next = NULL;
	temp->prev = NULL;
	T *value = (temp->valor);
	_size = _size - 1;
	temp = NULL;
	delete temp;
	return(value);
}
//Retorna o valor do elemento na posição dada. Alterações posteriores ao apontador retornado, NÃO alterarão o elemento na lista 
template<class T>T *CDoubleList<T>::getElementAt(int pos)
{
	SCelula<T> *temp = _first;
	while(pos > 0)
	{
		temp = temp->next;
		pos = pos - 1;
	}
	T *value = (temp->valor);
	return(value);
}
