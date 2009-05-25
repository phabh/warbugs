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
	CPeopleList *_jogadores;//Lista de personagens
	CPeopleList *_inimigos;
	CPeopleList *_npcs;
	CPeopleList *_vendedores;
	CBolsaList *_itens;//Lista de itens
	CPortal *_saidaNorte;
	CPortal *_saidaSul;
	CPortal *_saidaLeft;
	CPortal *_saidaRight;
public:

	CCenario(int ID, CPeopleList *players, CPeopleList *monsters, CPeopleList *npcs, CBolsaList *bolsa, CPortal *saidaNorte, CPortal *saidaSul, CPortal *saidaLeft, CPortal *saidaRight);
	void enterScene();
	int personagemCount();
	int itemCount();
	CPersonagemJogador *getPlayer(int idJogador);
	CInimigo *getMonster(int idInimigo);
	CNPC *getNpc(int idNpc);
	CBolsa *getBag(int idBag);
	CVendedor *getVendedor(int idVendedor);

	CPersonagemJogador *getPlayerAt(int idJogador);
	CInimigo *getMonsterAt(int idInimigo);
	CNPC *getNpcAt(int idNpc);
	CBolsa *getBagAt(int idBag);
	CVendedor *getVendedorAt(int idVendedor);

	CPortal *getExit(Direcoes idPortal);

	void setExit(CPortal *newExit, Direcoes idPortal);

	void addPlayer(CPersonagem *jogador);
	void addMonster(CPersonagem *inimigo);
	void addNpc(CPersonagem *npc);
	void addBag(CBolsa *bolsa);
	void addVendedor(CVendedor *vendedor);

	CPersonagemJogador *removePlayer(int idJogador);
	CInimigo *removeMonster(int idInimigo);
	CNPC *removeNPC(int idNPC);
	CBolsa *removeBag(int idBag);
	CVendedor *removeVendedor(int idVendedor);

	void update();
};
#endif