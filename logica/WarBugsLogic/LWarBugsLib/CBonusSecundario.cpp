/*
* Classe CBonusPrimario
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever os bonus primários de um personagem
*
*/
#ifndef _CBONUSSECUNDARIO_CPP_
#define _CBONUSSECUNDARIO_CPP_

#include "CBonusSecundario.h"

CBonusSecundario::CBonusSecundario()
	{
		origem = NORMAL;
		next = NULL;
		prev = NULL;
		_valor = new CHabilidadesSecundarias();
	}
	int CBonusSecundario::getValue(Atrib tipo)
	{
		switch(tipo)
		{
		case ATTACKMELEE:
			return(_valor->getMeleeAttack());
		case ATTACKRANGED:
			return(_valor->getRangedAttack());
		case DAMAGEMELEE:
			return(_valor->getMeleeDamage());
		case DAMAGERANGED:
			return(_valor->getRangedDamage());
		case DEFESA:
			return(_valor->getDefense());
		default:
			return(0);
		}
	}
	void CBonusSecundario::createBonus(int FOR_ATC, int AGI_ATD, int DES_DMC, int INS_DMD, int RES_DEF)
	{
		_valor = new CHabilidadesSecundarias(0, 0, FOR_ATC, AGI_ATD, DES_DMC, INS_DMD, RES_DEF, 0, 0);
		/*_valor->setMeleeAttack(ATC);
		_valor->setRangedAttack(ATD);
		_valor->setMeleeDamage(DMC);
		_valor->setRangedDamage(DMD);
		_valor->setDefense(DEF);*/
		next = NULL;
		add(this);
	}
	int CBonusSecundario::getTotalBonusOf(Atrib tipo)
	{
		CBonus *temp = this;
		int resultado = 0;
		while(temp->next != NULL)
		{
			resultado = resultado + temp->getValue(tipo);
			temp = temp->next;
		}
		return(resultado);
	}
#endif