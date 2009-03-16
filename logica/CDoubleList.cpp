/*
* Classe CDoubleList
*
* Vers�o: 0.1
*
* Autor: Eder Figueiredo
*
* Objetivo: Estrutura de dados capaz de armazenar quaisquer objetos do warbugs
*
* Altera��es:
* 28/02/2009 - Cria��o da classe
*
*/
#ifndef _CLOGICOBJECT
#include "CLogicObject.cpp"
#endif
#define _CDOUBLELIST

class CDoubleList : public CLogicObject{
public:
	void inicializar(CObjectCount &counter){
		CObject::inicializar(counter);
	}
	TipoClasse getClass(){
		return(CDOUBLELIST);
	}
	int getID(){
		return(CObject::getID());
	}
};