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
#include "CItem.cpp"
#include "CObject.cpp"
#include "CLealdade.cpp"
#ifndef _CQUEST
#define _CQUEST

class CQuest : public CObject{
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
	void beginQuest(/*CPersonagem *personagem*/){}
	bool tryFinish(){}
	void finishQuest(){}
	void getReward(){}
};

#endif