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
#include "CPersonagemJogador.h"
#include "CQuest.h"
#include <string>
using namespace std;

class CNPC : public CPersonagem{
private:
	//lista de quests disponiveis
	//lista de falas disponiveis
public:
	CNPC();
	void speak(CPersonagemJogador *alvo);
	void giveQuest (CPersonagemJogador *alvo);
};

#endif
