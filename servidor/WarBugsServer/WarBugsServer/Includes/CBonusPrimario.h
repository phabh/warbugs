#pragma once
/*
* Classe CBonusPrimario
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever os bonus primários de um personagem
*
*/
#ifndef _CBONUSPRIMARIO_H_
#define _CBONUSPRIMARIO_H_

//#include "CHabilidades.h"
//#include "CHabilidadesSecundarias.h"
//#include "CBuff.h"
#include "CBonus.h"

#ifndef _CHABILIDADES_H_
class CHabilidades;
#endif

class CBonusPrimario : public CBonus
{
private:
	CHabilidades *_valor;
public:
	CBonusPrimario();
	int getValue(Atrib tipo);
	void createBonus(int FOR_ATC, int AGI_ATD, int DES_DMC, int INS_DMD, int RES_DEF);
	int getTotalBonusOf(Atrib tipo);
};
#endif