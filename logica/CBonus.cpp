/*
* Classe CBonus
*
* Versão: 0.01
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever os bonus de um personagem
*
*/
#include "CAtributo.cpp"
#include "CBuff.cpp"
#ifndef _CBONUS
#define _CBONUS


class CBonus abstract
{
public:
	CBuff *origem;
	CBonus(){}
	void aplly(){}
	void remove(){}
};
// ------------------------------------------------------------------------------------------------------------
class CBonusPrimario : public CBonus
{
	CHabilidades *valor;
};
// ------------------------------------------------------------------------------------------------------------
class CBonusSecundario : public CBonus
{
	CHabilidadesSecundarias *valor;
};
#endif