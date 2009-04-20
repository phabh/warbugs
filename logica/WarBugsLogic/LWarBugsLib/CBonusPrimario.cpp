/*
* Classe CBonusPrimario
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever os bonus primários de um personagem
*
*/
#ifndef _CBONUSPRIMARIO_CPP_
#define _CBONUSPRIMARIO_CPP_

#include "CBonusPrimario.h"
#include "CHabilidades.h"
#define NULL 0


CBonusPrimario::CBonusPrimario()
	{
		origem = NULL;
		next = NULL;
		prev = NULL;
		_valor = new CHabilidades();
	}
int CBonusPrimario::getValue(Atrib tipo)
	{
		switch(tipo)
		{
		case FOR:
			return(_valor->getFOR());
		case DES:
			return(_valor->getDES());
		case AGI:
			return(_valor->getAGI());
		case RES:
			return(_valor->getRES());
		case INS:
			return(_valor->getINS());
		default:
			return(0);
		}
	}
void CBonusPrimario::createBonus(int FOR_ATC, int AGI_ATD, int DES_DMC, int INS_DMD, int RES_DEF)
	{
		_valor = new CHabilidades(FOR_ATC, AGI_ATD, DES_DMC, INS_DMD, RES_DEF);
		/*_valor->setFOR(FOR);
		_valor->setDES(DES);
		_valor->setAGI(AGI);
		_valor->setRES(RES);
		_valor->setINS(INS);*/
		next = NULL;
		add(this);
	}
int CBonusPrimario::getTotalBonusOf(Atrib tipo)
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

