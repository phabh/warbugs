/*
* Classe CPersonagem
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever todos os personagens do jogo
*
*/
#ifndef _CPERSONAGEM_CPP_
#define _CPERSONAGEM_CPP_

#include "CPersonagem.h"

#include "CBuff.h"

CPersonagem::CPersonagem()
{
	dinheiro = 0;
	habilidadesPrimarias = new CHabilidades();
	bonusPrimario = new CBonusPrimario();
	inventario = new CBolsa();
	habilidadesSecundarias = new CHabilidadesSecundarias();
	bonusSecundario = new CBonusSecundario();
	//poderes = new CPoder();
	status = new CBuff();
}
//Getters
int CPersonagem::getFOR()
{
	return(habilidadesPrimarias->getFOR() + bonusPrimario->getTotalBonusOf(FOR));
}
int CPersonagem::getDES()
{
	return(habilidadesPrimarias->getDES() + bonusPrimario->getTotalBonusOf(DES));
}
int CPersonagem::getAGI()
{
	return(habilidadesPrimarias->getAGI() + bonusPrimario->getTotalBonusOf(AGI));
}
int CPersonagem::getRES()
{
	return(habilidadesPrimarias->getRES() + bonusPrimario->getTotalBonusOf(RES));
}
int CPersonagem::getINS()
{
	return(habilidadesPrimarias->getINS() + bonusPrimario->getTotalBonusOf(INS));
}
EstadoPersonagem CPersonagem::getState()
{
	return(estado);
}
int CPersonagem::getMoney()
{
	return(dinheiro);
}
CBolsa *CPersonagem::getBolsa()
{
	return(inventario);
}
CHabilidadesSecundarias *CPersonagem::getStats()
{
	return(habilidadesSecundarias);
}
CBonus *CPersonagem::getBonus()
{
	return(bonusSecundario);
}
CBuff *CPersonagem::getBuffs()
{
	return(status);
}
CHabilidades *CPersonagem::getBaseStats()
{
	return(habilidadesPrimarias);
}
CBonusPrimario *CPersonagem::getBaseBonus()
{
	return(bonusPrimario);
}
//Setters
void CPersonagem::setState(EstadoPersonagem newState)
{
	estado = newState;
}
void CPersonagem::setMoney(int value)
{
	dinheiro = value;
}
void CPersonagem::setBolsa(CBolsa *bolsa)
{
	inventario = bolsa;
}
void CPersonagem::setStats(CHabilidadesSecundarias *stats)
{
	habilidadesSecundarias = stats;
}
void CPersonagem::setBaseStats(CHabilidades *stats)
{
	habilidadesPrimarias = stats;
}
void CPersonagem::setBuffs(CBuff *buff)
{
	status = buff;
}
void CPersonagem::setBonus(CBonus *bonus)
{
	bonusSecundario = (CBonusSecundario*)bonus;
}
void CPersonagem::setBaseBonus(CBonus *bonus)
{
	bonusPrimario = (CBonusPrimario*)bonus;
}

void CPersonagem::addMoney(int value)
{
	dinheiro = dinheiro + value;
}
//Outros métodos
void CPersonagem::move(){}
void CPersonagem::die(){}
//void CPersonagem::useSkill(CPoder *skill){}
#endif