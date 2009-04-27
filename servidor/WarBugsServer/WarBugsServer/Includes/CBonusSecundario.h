#pragma once
/*
* Classe CBonusPrimario
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever os bonus primários de um personagem
*
*/
#ifndef _CBONUSSECUNDARIO_H_
#define _CBONUSSECUNDARIO_H_

#include "CHabilidadesSecundarias.h"
#include "CBuff.h"
#include "CBonus.h"

class CBonusSecundario : public CBonus
{
private:
	CHabilidadesSecundarias *_valor;
public:
	CBonusSecundario();
	int getValue(Atrib tipo);
	void createBonus(int FOR_ATC, int AGI_ATD, int DES_DMC, int INS_DMD, int RES_DEF);
	int getTotalBonusOf(Atrib tipo);
};
#endif