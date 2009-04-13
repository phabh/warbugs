/*
* Classe CDoubleList
*
* Versão: 0.1
*
* Autor: Eder Figueiredo
*
* Objetivo: Estrutura de dados capaz de armazenar quaisquer objetos do warbugs
*
*/
#include "CLogicObject.cpp"

#ifndef _CDOUBLELIST
#define _CDOUBLELIST
template<typename A>
class CData{
public:
	A *data;
	CData<A> *next;
	CData<A> *prev;
};
template<typename T>
class CDoubleList : public CLogicObject{
private:
	 CData<T> *_first;
	 int _size;
public:
	bool isEmpty(){
		return(!_size);
	}
	void pushBack(T dadoObj){
		T *dado = &dadoObj;
		CData<T> *temp = NULL;
		CData<T> *first = _first;
		if(isEmpty()){
			_first->data = dado;
			_first->next = NULL;
			_first->prev = NULL;
		}
		else{
			while(first->next != NULL){
				first = first->next;
			}
			temp->data = dado;
			temp->prev = first;
			temp->next = NULL;
			first->next = temp;
			temp = NULL;
			first = NULL;
			delete first;
			delete temp;
		}
		_size = _size+1;
	}
	void pushFront(T dadoObj){
		T *dado = &dadoObj;
		CData<T> *temp = NULL;
		if(isEmpty()){
			_first->data = dado;
			_first->next = NULL;
			_first->prev = NULL;
		}
		else{
			temp->data = dado;
			temp->next = _first;
			temp->prev = NULL;
			_first->prev = temp;
			_first = temp;
			temp = NULL;
			delete temp;
		}
		_size = _size + 1;
	}
	T popBack(){
		CData<T> *temp = NULL;
		T dado;
		if(!isEmpty()){
			temp = _first;
			while(temp->next != NULL){
				temp = temp->next;
			}
			(temp->prev)->next = NULL;
			dado = *temp->data
			temp = NULL;
			delete temp;
			_size = _size-1;
			return(dado);
		}
		else{
			return(NULL);
		}
	}
	T popFront(){
		CData<T> *temp = NULL;
		T dado;
		if(!isEmpty()){
			temp = _first->next;
			temp->prev = NULL;
			dado = *_first->data;
			temp = _first;
			_first = _first->next;
			temp = NULL;
			delete temp;
			_size = _size-1;
			return(dado);
		}
		else{
			return(NULL);
		}
	}
	T getFirstValue(){
		return(*_first->data);
	}
	CData<T> *getFirstElement(){
		return(_first);
	}
	int getSize(){
		return(_size);
	}
	CDoubleList(){
		_size = 0;
		_first = NULL;
	}
	//Métodos CObject
	void initialize(CObjectCount *counter){
		CObject::initialize(counter);
	}
	TipoClasse getClass(){
		return(CDOUBLELIST);
	}
	int getID(){
		return(CObject::getID());
	}
	void update(){}
	void loadDBData(){}
};
#endif