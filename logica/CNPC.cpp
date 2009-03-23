/*
* Classe CNPC
*
* Versão: 0.01
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever cada personagem npc
*
*/
#ifndef _CNPC
#define _CNPC
#include "CPersonagem.cpp"
#include "CPersonagemJogador.cpp"
#include <string>
using namespace std;
#include "CQuest.cpp"

class CNPC : public CPersonagem{
private:
	//lista de quests disponiveis
	//lista de falas disponiveis
public:
	CNPC(){}
	void speak(CPersonagemJogador *alvo){}
	void giveQuest (CPersonagemJogador *alvo){}
};

#endif
