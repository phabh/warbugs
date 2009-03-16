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

class CDoubleList : public CLogicObject{
public:
	void initialize(CObjectCount &counter){
		CObject::initialize(counter);
	}
	TipoClasse getClass(){
		return(CDOUBLELIST);
	}
	int getID(){
		return(CObject::getID());
	}
};
#endif