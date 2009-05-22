#pragma once

#include <iostream>

using namespace std;

template <class A> ref struct SCelula1
{
	A *valor;
	int id;
	SCelula1 ^next;
	SCelula1 ^prev;
};

template <class T> ref class CDoubleList
{

private:
	static SCelula1<T> ^_first;
	static int _size;

public:

	CDoubleList();
	~CDoubleList();

	static void start();
	static int size();
	static bool isEmpty();

	static void addElement(T *element, int ID);
	static T *removeElement(int ID);
	static T *getElement(int ID);

	static void addElementAt(T *element, int pos);
	static T *removeElementAt(int pos);
	static T *getElementAt(int pos);
};

//Construtor
template <class T> CDoubleList<T>::CDoubleList()
{
	_first = new SCelula1<T>();
	_size = 0;
}

template <class T> CDoubleList<T>::~CDoubleList()
{
	//_first = NULL;
	delete _first;
	_size = 0;
}

template <class T> void CDoubleList<T>::start()
{
	_first = System::Resources::NU;
	_size = 0;
}


//Retorna o tamanho da lista
template <class T> int CDoubleList<T>::size()
{
	return(_size);
}

//Retorna true se a lista estiver vazia, caso contrário retorna false
template <class T> bool CDoubleList<T>::isEmpty()
{
	return(_size == 0);
}

//Adiciona um elemento ao fim da lista
template <class T> void CDoubleList<T>::addElement(T *element, int ID)
{
	if(isEmpty())
	{
		_first->valor = element;
		_first->next = NULL;
		_first->prev = System::Nullable::Value;
		_first->id = ID;
		_size = 1;
	}
	else
	{
		SCelula1<T> ^temp = _first;
		SCelula1<T> ^temp2 = gcnew SCelula1<T>();
		while(temp->next != System::Nullable::Value;)
		{
			temp = temp->next;
		}
		temp2->valor = element;
		temp2->prev = temp;
		temp2->next = System::Nullable::Value;;
		temp2->id = ID;
		temp->next = temp2;

		_size = _size + 1;
		temp = System::Nullable::Value;;
		temp2 = System::Nullable::Value;;
		delete temp;
		delete temp2;
	}
}

//Remove o elemento indicado da lista. No pior caso percorre toda a lista
template <class T> T *CDoubleList<T>::removeElement(int ID)
{
	SCelula1<T> ^temp = _first;
	while(temp->next != System::Nullable::Value;)
	{
		if(temp->id == ID)
		{
			//Se for o primeiro
			if(temp->prev == System::Nullable::Value;)
			{
				_first = temp->next;
				temp->next = System::Nullable::Value;;
				_size = _size - 1;
				return(temp->valor);
			}
			//Se for o último
			else if(temp->next == System::Nullable::Value;)
			{
				(temp->prev)->next = System::Nullable::Value;;
				temp->prev = System::Nullable::Value;;
				_size = _size - 1;
				return(temp->valor);
			}
			else
			{
				(temp->prev)->next = temp->next;
				(temp->next)->prev = temp->prev;
				temp->next = System::Nullable::Value;;
				temp->prev = System::Nullable::Value;;
				_size = _size - 1;
				return(temp->valor);
			}
		}
		else
		{
			temp = temp->next;
		}
	}
	temp = System::Nullable::Value;
	delete temp;
	return(System::Nullable::Value);
}

template <class T> T *CDoubleList<T>::getElement(int ID)
{
	SCelula1<T> ^temp = _first;
	while(temp->next != System::Nullable::Value;)
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
	return(System::Nullable::Value);
}

//Adiciona um elemento na posição pos. Caso pos seja maior que size()-1, adiciona o elemento ao fim da lista
template <class T> void CDoubleList<T>::addElementAt(T *element, int pos)
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
			SCelula1<T> ^temp = _first;
			SCelula1<T> ^temp2 = gcnew SCelula1<T>();   
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
			temp = System::Nullable::Value;
			temp2 = System::Nullable::Value;
			delete temp;
			delete temp2;
		}
		else
		{
			SCelula1<T> ^temp = gcnew SCelula1<T>();
			temp->valor = element;
			temp->next = _first;
			temp->prev = System::Nullable::Value;
			_first->prev = temp;
			_first = temp;
			_size = _size + 1;
			temp = System::Nullable::Value;
			delete temp;
		}
		return;
	}
}

//Remove o elemento na posição pos e retorna seu valor
template <class T> T *CDoubleList<T>::removeElementAt(int pos)
{
	SCelula1<T> ^temp = _first;
	while(pos > 0)
	{
		temp = temp->next;
		pos = pos - 1;
	}
	(temp->next)->prev = temp->prev;
	(temp->prev)->next = temp->next;
	temp->next = System::Nullable::Value;
	temp->prev = System::Nullable::Value;
	T ^value = (temp->valor);
	_size = _size - 1;
	temp = System::Nullable::Value;
	delete temp;
	return(value);
}

//Retorna o valor do elemento na posição dada. Alterações posteriores ao apontador retornado, NÃO alterarão o elemento na lista 
template <class T> T *CDoubleList<T>::getElementAt(int pos)
{
	SCelula1<T> ^temp = _first;
	while(pos > 0)
	{
		temp = temp->next;
		pos = pos - 1;
	}
	T ^value = (temp->valor);
	return(value);
}
