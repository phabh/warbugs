#pragma once
/*
* Classe CBonus
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever os bonus de um personagem
*
*/
#ifndef _CBONUS_H_
#define _CBONUS_H_
#include <iostream>
using namespace std;
#include "Enumerators.h"

class CBonus
{
protected:
	TipoBuff origem;
public:
	CBonus *prev;
	CBonus *next;
public:
	CBonus();
	TipoBuff getBuff();
	void setOrigem(TipoBuff buff);
	void add(CBonus *bonus);
	void remove();
	void removeElement(TipoBuff indice);
	//Métodos virtuais
	virtual int getValue(Atrib tipo)=0;
	virtual void createBonus(int FOR_ATC, int AGI_ATD, int DES_DMC, int INS_DMD, int RES_DEF)=0;
	virtual int getTotalBonusOf(Atrib tipo)=0;
};
#endif