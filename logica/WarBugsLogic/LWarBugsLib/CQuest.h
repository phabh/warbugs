#pragma once
/*
* Classe CQuest
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever as quests do jogo
*
*/
#ifndef _CQUEST_H_

#include "CWarBugObject.h"

#ifndef _CPERSONAGEMJOGADOR_H_
#include "CPersonagemJogador.h"
#ifndef _CPERSONAGEMJOGADOR_H_
class CPersonagemJogador;
#endif
#endif

#include "CLealdade.h"

#define _CQUEST_H_
class CQuest : public CWarBugObject{
private:
	CPersonagemJogador *_jogador;
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