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
	CPersonagem *_contratante;
	TypeItens _itemNecessario;
	TypeModelos _inimigoNecessario;
	int _monstrosDerrotados;
	int _itensPossuidos;
	int _qtdNecessariaItem;
	int _qtdNecessariaInimigo;
	CItem *_recompensaItem;
	int _recompensaDinheiro;
	int _recompensaXP;
	CLealdade *_recompensaLealdade;
	QuestState _estado;
public:
	CQuest(CPersonagemJogador *jogador);
	CQuest(CPersonagemJogador *jogador, CPersonagem *npc, int itemID, int qtdItem, int monstID, int qtdMonst, int rewdXp = 0, int rewdMny = 0, CLealdade *rewdLdd = new CLealdade(), CItem *rewdItm = NULL);

	//Getters
	CPersonagemJogador *getPlayer();
	CPersonagem *getNPC();
	int getRequestedItem();
	int getRequestedEnemy();
	int getRequestedNumberOfItens();
	int getRequestedNumberOfEnemies();
	int getReward();
	int getXPReward();
	CItem *getItemReward();
	CLealdade *getLoyaltyReward();
	//Setters
	void setPlayer(CPersonagemJogador *player);
	void setNPC(CPersonagem *npc);
	void setRequestedItem(int reqItem);
	void setRequestedEnemy(int reqEnemy);
	void setRequestedNumberOfItens(int num);
	void setRequestedNumberOfEnemies(int num);
	void setReward(int num);
	void setXPReward(int num);
	void setItemReward(CItem *item);
	void setLoyaltyReward(CLealdade *num);

	bool testEnemyKilled(CPersonagem *personagem);
	bool testItemPicked(CItem *item);
	void beginQuest();
	void beginQuest(CPersonagemJogador *jogador, CPersonagem *npc, int itemID, int qtdItem, int monstID, int qtdMonst, int rewdXp = 0, int rewdMny = 0, CLealdade *rewdLdd = new CLealdade(), CItem *rewdItm = NULL);
	bool tryFinish();
	void finishQuest();
};

#endif