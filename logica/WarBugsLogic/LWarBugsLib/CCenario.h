#pragma once
#ifndef _CCENARIO_H_
#include <iostream>
using namespace std;
#include "Enumerators.h"
#include "C3DObject.h"
#include "CBolsaList.h"
	//#include "CBolsa.h"
		//#include "CItem.h"
#include "CPeopleList.h"
	//#include "CPersonagem.h"
#include "CPersonagemJogador.h"
#ifndef _CINIMIGO_H_
#include "CInimigo.h"
#ifndef _CINIMIGO_H_
class CInimigo;
#endif
#endif
#include "CNPC.h"
#include "CPortal.h"
#include "CVendedor.h"

#define _CCENARIO_H_
class CCenario : public C3DObject
{
private:
	CObjectCount *_contador;
	CPeopleList *_jogadores;//Lista de personagens
	CPeopleList *_inimigos;
	CPeopleList *_npcs;
	CPeopleList *_vendedores;
	CBolsaList *_itens;//Lista de itens
	CPortal *_saidaNorte;
	CPortal *_saidaSul;
	CPortal *_saidaLeft;
	CPortal *_saidaRight;

	Raca _lealdadeNecessaria;
	int _quantidadeNecessaria;
public:

	CCenario(int ID, CPeopleList *players, CPeopleList *monsters, CPeopleList *npcs, CPeopleList *vendedores, CBolsaList *bolsa, CPortal *saidaNorte, CPortal *saidaSul, CPortal *saidaLeft, CPortal *saidaRight);	
	bool isSceneFull();
	bool haveLoyaltyRequired(CPersonagemJogador *jogador);
	int playerCount();
	int bagCount();
	int monsterCount();
	int NPCCount();
	int salesmanCount();

	CPeopleList *getPlayerList();
	CPeopleList *getMonsterList();
	CPeopleList *getNPCList();
	CPeopleList *getSalesmanList();

	CPersonagemJogador *getPlayer(int idJogador);
	CInimigo *getMonster(int idInimigo);
	CNPC *getNpc(int idNpc);
	CBolsa *getBag(int idBag);
	CVendedor *getSalesman(int idVendedor);

	CPersonagemJogador *getPlayerAt(int pos);
	CInimigo *getMonsterAt(int pos);
	CNPC *getNpcAt(int pos);
	CBolsa *getBagAt(int pos);
	CVendedor *getSalesmanAt(int pos);

	CPortal *getExit(TypeDirecao idPortal);
	Raca getRaceNeeded();
	int getRaceNeededAsInt();
	int getLoyaltyRequired();

	void setExit(CPortal *newExit, TypeDirecao idPortal);
	void setRaceNeeded(Raca race);
	void setLoyaltyRequired(int value);

	void addPlayer(CPersonagem *jogador);
	void addMonster(CPersonagem *inimigo);
	void addNpc(CPersonagem *npc);
	void addBag(CBolsa *bolsa);
	void addSalesman(CVendedor *vendedor);

	CPersonagemJogador *removePlayer(int idJogador);
	CInimigo *removeMonster(int idInimigo);
	CNPC *removeNPC(int idNPC);
	CBolsa *removeBag(int idBag);
	CVendedor *removeSalesman(int idVendedor);

	void update();
};
#endif