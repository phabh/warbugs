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
#include "CHabilidadesSecundarias.h"
#include "CBonusSecundario.h"

CPersonagem::CPersonagem()
{
	inventario = new irr::core::array<CItem*>();
	habilidadesSecundarias = new CHabilidadesSecundarias();
	bonusSecundario = new CBonusSecundario();
	poderes = new irr::core::array<CPoder*>();
	next = NULL;
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
//Outros métodos
void CPersonagem::move(){}
void CPersonagem::die(){}
void CPersonagem::useSkill(CPoder *skill){}
#endif