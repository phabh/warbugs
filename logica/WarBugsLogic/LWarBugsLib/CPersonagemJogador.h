#pragma once
/*
* Classe CPersonagemJogador
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever cada personagem controlado por um jogador
*
*/
#ifndef _CPERSONAGEMJOGADOR_H_
#define _CPERSONAGEMJOGADOR_H_

//Constantes
#define MAXFRIENDS 10
#define MAXPARTYSIZE 4
#ifndef MAXSTATS
#define MAXSTATS 5
#endif
#define MAXITENS 10
//end Constantes

#include "CPersonagem.h"
#include "CEquipamento.h"
//#include "CBuff.h"
#ifndef _CBUFF_H_
class CBuff;
#endif
#include "CHabilidades.h"
#include "CLealdade.h"
#include "CQuest.h"
#include "CBonusPrimario.h"
#include "CConsumableItem.h"
#include <irrlicht.h>

class CPersonagemJogador : public CPersonagem
{
	CHabilidades *_habilidadesPrimarias;
	CBonus *_bonusPrimario;
	int _nivel;
	int _experiencia;
	int _xpToNextLv;
	int _xpToPrevLv;
	int _pontoDistribuir;
	int _dinheiro;
	CEquipamento *_equip;
	CBuff *_status;
	CLealdade *_lealdade;
	irr::core::array<CPersonagemJogador*> *_party;
	irr::core::array<CPersonagemJogador*> *_friends;
	int _jogadorID;
	//Combate
	CPersonagem *_alvo;
	bool _bareHands;
	int _ataque;
	int _dano;
	int _range;
	int _speed;

public:
	CPersonagemJogador();
	//Getters e setters
	int getFOR();
	int getDES();
	int getAGI();
	int getRES();
	int getINS();
	int getAttack();
	void setParty(irr::core::array<CPersonagemJogador*> *lista);
	//Outros Métodos
	//Manipulação de itens
	int haveItem(CItem * item);
	void getItem(CItem *item);
	void dropItem(CItem *item);
	void useItem(CItem *item);
	void equip(CItem *item);
	void unequip(CItem *item);
	//Friends Manipulation
	int isFriend(CPersonagemJogador *jogador);
	void addFriend(CPersonagemJogador *newFriend);
	void removeFriend(CPersonagemJogador *jogador);
	//Party Manipulation
	bool isPartyLeader();
	int isPartyMember(CPersonagemJogador* jogador);
	void addPartyMember (CPersonagemJogador *jogador);
	void removePartyMember(CPersonagemJogador *jogador);
	void givePartyAlliesID(irr::core::array<CPersonagemJogador*> *lista);
	void updateAlliesID();
	void createParty();
	void joinParty(CPersonagemJogador *lider);
	void leaveParty(CPersonagemJogador *lider);
	//Quest
	void acceptQuest(CQuest *quest);
	//Speaking
	void speakToPlayer(CPersonagemJogador *alvo);
	void speakToNPC(CPersonagem *alvo);
	//Batalha
	void takeDamage(int damage);
	void attack();
	//Level Up
	void updateXP();
	bool haveLevelUp();
	bool haveLevelDown();
	void distibutePoints(int points, int atribute);
};
#endif