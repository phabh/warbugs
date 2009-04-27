#pragma once
/*
* Classe CQuest
*
* Versão: 0.01
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever as quests do jogo
*
*/
#ifndef _CQUEST_H_
#define _CQUEST_H_

#include "CItem.h"
#include "CWarBugObject.h"
#include "CLealdade.h"

class CQuest : public CWarBugObject{
private:
	//CPersonagem *_jogador;
	CItem *_itemNecessario;
	int _qtdNecessaria;
	//NPC
	CItem * _recompensaItem;
	int _recompensaDinheiro;
	int _recompensaXP;
	CLealdade * _recompensaLealdade;
public:
	CQuest();
	void beginQuest(/*CPersonagem *personagem*/);
	bool tryFinish();
	void finishQuest();
	void getReward();
};

#endif