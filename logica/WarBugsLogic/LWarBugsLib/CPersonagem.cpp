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
	habilidadesPrimarias = new CHabilidades();
	bonusPrimario = new CBonusPrimario();
	inventario = new CBolsa();
	habilidadesSecundarias = new CHabilidadesSecundarias();
	bonusSecundario = new CBonusSecundario();
	//poderes = new CPoder();
	status = new CBuff();
}
//Getters e Setters
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

void CPersonagem::setStats(CHabilidadesSecundarias *stats)
{
	habilidadesSecundarias = stats;
}
void CPersonagem::setBaseStats(CHabilidades *stats)
{
	habilidadesPrimarias = stats;
}
void CPersonagem::setBonus(CBonus *bonus)
{
	bonusSecundario = (CBonusSecundario*)bonus;
}
void CPersonagem::setBaseBonus(CBonus *bonus)
{
	bonusPrimario = (CBonusPrimario*)bonus;
}
//Outros métodos
void CPersonagem::move(){}
void CPersonagem::die(){}
//void CPersonagem::useSkill(CPoder *skill){}
#endif