/*
* Classe CPersonagemJogador
*
* Versão: 0.01
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever cada personagem controlado por um jogador
*
*/
#ifndef _CPERSONAGEMJOGADOR
#define _CPERSONAGEMJOGADOR
#include "CPersonagem.cpp"
#include "CEquipamento.cpp"
#include "CBuff.cpp"
#include "CAtributo.cpp"
#include "CQuest.cpp"

class CPersonagemJogador : public CPersonagem{
	CHabilidades *_habilidadesPrimarias;
	CBonusPrimario *_bonusPrimario;
	int _nivel;
	int _experiencia;
	int _dinheiro;
	CEquipamento *_equip;
	CBuff *_status;
	CLealdade *_lealdade;
	//Lista da party
	//Lista de amigos
	int _jogadorID;
public:
	CPersonagemJogador(){}
	//Getters e setters
	void equip(CItem *item){}
	void unequip(CItem *item){}
	void addFriend(CPersonagemJogador *newFriend){}
	void removeFriend(CPersonagemJogador *jogador){}
	void createParty(){}
	void joinParty(CPersonagemJogador *lider){}
	void leaveParty(CPersonagemJogador *lider){}
	void acceptQuest(CQuest *quest){}
	void speakToPlayer(CPersonagemJogador *alvo){}
	void speakToNPC(CPersonagem *alvo){}
};
#endif