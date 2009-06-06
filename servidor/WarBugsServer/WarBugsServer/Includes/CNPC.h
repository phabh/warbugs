#pragma once
/*
* Classe CNPC
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever cada personagem npc
*
*/
#ifndef _CNPC_H_
#define _CNPC_H_

//#include "CPersonagem.h"
#include <time.h>
#include "CPersonagemJogador.h"
#include "CQuest.h"
#include <string>
using namespace std;

class CNPC : public CPersonagem
{
private:
	Ponto *_ancora;
	CQuest *_quest;
	//lista de quests disponiveis'
	//lista de falas disponiveis
public:
	CNPC();
	void takeDecision();
	void speak(CPersonagemJogador *alvo);
	void giveQuest (CPersonagemJogador *alvo);

	bool tryAttack();
	void attack();
	void takeDamage(int damage, CPersonagem *atkr);
	void die();
	void useItem(CItem *item);

	void update();
};

#endif
