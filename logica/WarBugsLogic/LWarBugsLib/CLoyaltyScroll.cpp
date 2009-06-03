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
	setID(-1);
	setDurability(100);
	_bonus = new CLealdade();
}
CLoyaltyScroll::CLoyaltyScroll(TypeItens nome, EstadoItem estado, int preco, bool isdropable,int aranha, int besouro, int louvadeus, int escorpiao, int vespa)
{
	setID(-1);
	setDurability(100);
	setNome(nome);
	setEstado(estado);
	setPrice(preco);
	setDropable(isdropable);
	_bonus->setLoyaltyToBeetle(besouro);
	_bonus->setLoyaltyToMantis(louvadeus);
	_bonus->setLoyaltyToScorpion(escorpiao);
	_bonus->setLoyaltyToSpider(aranha);
	_bonus->setLoyaltyToWasp(vespa);
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