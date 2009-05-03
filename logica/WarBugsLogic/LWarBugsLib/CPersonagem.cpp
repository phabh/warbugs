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
	inventario = new CBolsa();
	habilidadesSecundarias = new CHabilidadesSecundarias();
	bonusSecundario = new CBonusSecundario();
	//poderes = new CPoder();
	_status = new CBuff();
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
	return(_status);
}
//Outros métodos
void CPersonagem::move(){}
void CPersonagem::die(){}
//void CPersonagem::useSkill(CPoder *skill){}
#endif