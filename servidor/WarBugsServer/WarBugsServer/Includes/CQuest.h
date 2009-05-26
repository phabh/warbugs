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
	TypeItens _itemNecessario;
	TypeModelos _inimigoNecessario;
	int _qtdNecessaria;
	//NPC
	CItem *_recompensaItem;
	int _recompensaDinheiro;
	int _recompensaXP;
	CLealdade *_recompensaLealdade;
public:
	CQuest(CPersonagemJogador *jogador);

	//Getters
	CPersonagemJogador *getPlayer();
	int getRequestedItem();
	int getRequestedEnemy();
	int getRequestedNumber();
	int getReward();
	int getXPReward();
	CItem *getItemReward();
	CLealdade *getLoyaltyReward();
	//Setters
	void setPlayer(CPersonagemJogador *player);
	void setRequestedItem(int reqItem);
	void setRequestedEnemy(int reqEnemy);
	void setRequestedNumber(int num);
	void setReward(int num);
	void setXPReward(int num);
	void setItemReward(CItem *item);
	void setLoyaltyReward(CLealdade *num);

	void beginQuest(/*CPersonagem *personagem*/);
	bool tryFinish();
	void finishQuest();
};

#endif