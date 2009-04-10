/*
* Classe CBonus
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever os bonus de um personagem
*
*/
#include "CHabilidades.cpp"
#include "CHabilidadesSecundarias.cpp"
#include "CBuff.cpp"
#ifndef _CBONUS
#define _CBONUS


class CBonus
{
protected:
	CBuff *origem;
public:
	CBonus()
	{
		origem = NULL;
	}
	CBuff getBuff()
	{
		return(*origem);
	}
	void setOrigem(CBuff *buff)
	{
		origem = buff;
	}
	void aplly(){}
	void remove(){}
};
#endif