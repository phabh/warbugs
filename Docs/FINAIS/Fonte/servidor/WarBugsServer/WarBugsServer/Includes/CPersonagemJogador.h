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
#include <iostream>
using namespace std;

#include "CClientSocketThread.h"
#ifndef _CPERSONAGEM_H_
#include "CPersonagem.h"
#ifndef _CPERSONAGEM_H_
class CPersonagem;
#endif
#endif
	//#include "CHabilidadesSecundarias.h"
		//#include "CWarBugObject.h"
		//#include "CEquipamento.h"
		//#include "CHabilidades.h"
	//#include "CBolsa.h"
		//#include "CItem.h"
	//#include "CBonusPrimario.h"
		//#include "CHabilidades.h"
		//#include "CBonus.h"
	//#include "CBonusSecundario.h"
		//#include "CHabilidadesSecundarias.h"
		//#include "CBonus.h"
#ifndef _CQUEST_H_
#include "CQuest.h"
	//#include "CLealdade.h"
#ifndef _CQUEST_H_
class CQuest;
#endif
#endif

#include "CDivisorXP.h"

#define _CPERSONAGEMJOGADOR_H_
class CPersonagemJogador : public CPersonagem
{
	CClientSocketThread *_socketJogador;
	
	int _skillLevel[3];
	int _pontoDistribuir;
	int _skillPontoDistribuir;
	CEquipamento *_equip;
	//CBuff *_status;
	CLealdade *_lealdade;
	CQuest *_quest;
	//irr::core::array<CPersonagemJogador*> *_party;
	//irr::core::array<CPersonagemJogador*> *_friends;
	int _jogadorID;
	//Combate
	bool _bareHands;
	int _ataque;
	int _dano;
	int _range;
	int _speed;

	bool _tradeOn;// = false;
	bool _tradeConfirmation;// = false;
	int _idTrader;// = -1;
	int _idItemTrade;// = -1;
	int _idMoneyTrade;// = -1;


public:

	CPersonagemJogador();
	//Getters
	int getSkillLevel(int skillIndex);
	int getAttack();
	int getDamage();
	bool isTradeOn();
	bool isTradeConfirmated();
	int getIDTrader();
	int getIDItemTrade();
	int getIDMoneyTrade();
	CLealdade *getLoyalty();
	CEquipamento *getEquip();
	int getPointsLeft();
	int getSkillPointsLeft();
	CClientSocketThread *getSocket();
	
	//Setters
	void setPointsToDistribute(int points);
	void setSkillPointsToDistribute(int value);
	void setEquip(CEquipamento *equip);
	//void setStatus(CBuff *status);
	void setLoyalty(CLealdade *lealdade);
	//void setParty(irr::core::array<CPersonagemJogador*> *lista);
	//void setFriends(irr::core::array<CPersonagemJogador*> *lista);
	void setPlayer(int playerID);
	
	void setBareHands(bool isBareHands);
	void setAttack(int ataque);
	void setDamage(int dano);
	void setRange(int range);
	void setSpeed(int speed);
	void setTradeOn(bool value);
	void setTradeConfirmated(bool value);
	void setIDTrader(int value);
	void setIDItemTrade(int value);
	void setIDMoneyTrade(int value);
	void setSocket(CClientSocketThread * socket);

	//Outros M�todos
	//Manipula��o de itens
	int haveItem(CItem * item);
	void addItem(CItem *item);
	void dropItem(CItem *item);
	void useItem(CItem *item);
	void equip(CItem *item);
	void unequip(CItem *item);
	//Friends Manipulation
	/*int isFriend(CPersonagemJogador *jogador);
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
	void leaveParty(CPersonagemJogador *lider);*/
	//Quest
	void acceptQuest(CQuest *quest);
	//Speaking
	void speakToPlayer(CPersonagemJogador *alvo);
	void speakToNPC(CPersonagem *alvo);
	//Batalha
	void takeDamage(int damage, CPersonagem *atkr);
	int getDEF();
	bool tryAttack();
	void attack();
	//Level Up
	void updateXP();
	bool haveLevelUp();
	bool haveLevelDown();
	void distibutePoints(int points, int atribute);
	void distibuteSkillPoints(int points, int skillIndex);

	void die();
	void checkInventory();
	void update();
};
#endif