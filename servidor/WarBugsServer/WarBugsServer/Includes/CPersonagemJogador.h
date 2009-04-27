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
	char _nome[10];
	Raca _raca;
	CHabilidades *_habilidadesPrimarias;
	CBonusPrimario *_bonusPrimario;
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
	//VARIAVEIS PRO HIMURA
public:
	CPersonagemJogador *next;

	CPersonagemJogador();
	//Getters
	char *getName();
	int getFOR();
	int getDES();
	int getAGI();
	int getRES();
	int getINS();
	int getAttack();
	CHabilidades *getBaseStats();
	CBonusPrimario *getBaseBonus();
	//Setters
	void setName(char *name);
	void setRace(Raca raca);
	void setBaseStats(CHabilidades *stats);
	void setBaseBonus(CBonus *bonus);
	void setLevel(int level);
	void setXP(int xp);
	void setXPToNextLv(int xp);
	void setXPToPrev(int xp);
	void setPointsToDistribute(int points);
	void setMoney(int value);
	void setEquip(CEquipamento *equip);
	void setStatus(CBuff *status);
	void setLoyalty(CLealdade *lealdade);
	void setParty(irr::core::array<CPersonagemJogador*> *lista);
	void setFriends(irr::core::array<CPersonagemJogador*> *lista);
	void setPlayer(int playerID);
	void setTarget(CPersonagem *alvo);
	void setBareHands(bool isBareHands);
	void setAttack(int ataque);
	void setDamage(int dano);
	void setRange(int range);
	void setSpeed(int speed);
	//Outros Métodos
	//Manipulação de itens
	int haveItem(CItem * item);
	void addItem(CItem *item);
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