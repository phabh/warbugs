/*
* Classe CScroll
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever os pergaminhos, que aumentam os atributos das armas
*
*/
#ifndef _CLOYALTYSCROLL_CPP_
#define _CLOYALTYSCROLL_CPP_

#include "CLoyaltyScroll.h"

CLoyaltyScroll::CLoyaltyScroll()
{
		_bonus = new CLealdade();
	}
	void CLoyaltyScroll::use(CLealdade *base)
	{
		base->addLoyalty(_bonus);
	}

	Atrib CLoyaltyScroll::getAtribute()
	{
		return (NENHUM);
	}

	int CLoyaltyScroll::getValue()
	{
		return -1;
	}
#endif