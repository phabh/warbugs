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
#ifndef _CBONUS
#define _CBONUS
#include "CAtributo.cpp"
#include "CBuff.cpp"

class CBonus abstract{
public:
	CBuff *origem;
	CBonus(){}
	void aplly(){}
	void remove(){}
};
// ------------------------------------------------------------------------------------------------------------
class CBonusPrimario : public CBonus{
	CHabilidades *valor;
};
// ------------------------------------------------------------------------------------------------------------
class CBonusSecundario : public CBonus{
	CHabilidadesSecundarias *valor;
};
#endif