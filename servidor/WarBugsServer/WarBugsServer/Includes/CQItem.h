#pragma once
/*
* Classe CQuestItem
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever todos os itens de quest do jogo
*
*/
#ifndef _CQITEM_H_
#define _CQITEM_H_

#include "CItem.h"
#include "CQuest.h"

class CQItem : public CItem
{
private:
	CQuest * _quest;
public:
	CQItem();
	void initialize(CObjectCount *counter);
	TipoClasse getClass();
	//Métodos de manipulação de itens
	//virtual void use(CPersonagem *jogador)=0;
	//virtual void loot(CPersonagem *jogador)=0;
	//virtual void drop(CPersonagem *jogador)=0;
	//Métodos virtuais pra funcionar
	int getValue();
	Atrib getAtribute();
};

#endif