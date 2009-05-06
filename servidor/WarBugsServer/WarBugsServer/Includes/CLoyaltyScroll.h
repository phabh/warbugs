#pragma once
/*
* Classe CScroll
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever os pergaminhos, que aumentam os atributos das armas
*
*/
#ifndef _CLOYALTYSCROLL_H_
#define _CLOYALTYSCROLL_H_

#include "CItem.h"
#include "CLealdade.h"

class CLoyaltyScroll : public CItem
{
private:
	CLealdade *_bonus;
public:
	CLoyaltyScroll();
	CLoyaltyScroll(TypeItens nome, EstadoItem estado, int preco, bool isdropable,int aranha, int besouro, int louvadeus, int escorpiao, int vespa);
	void use(CLealdade *base);
	int getValue();
	Atrib getAtribute();
};
#endif