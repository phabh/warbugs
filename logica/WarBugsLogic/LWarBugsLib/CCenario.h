#pragma once
#include <iostream>
using namespace std;
#include "Enumerators.h"
#include "C3DObject.h"
#include "CBolsaList.h"
#include "CItem.h"
#include "CPeopleList.h"
#include "CPersonagem.h"
#include "CPersonagemJogador.h"
#include "CInimigo.h"
#include "CNPC.h"
#include "CPortal.h"

class CCenario : public C3DObject
{
private:
	char _nomeCenario[10];
	CPeopleList *_jogadores;//Lista de personagens
	CPeopleList *_inimigos;
	CPeopleList *_npcs;
	CBolsaList *_itens;//Lista de itens
	CPortal *_saidaNorte;
	CPortal *_saidaSul;
	CPortal *_saidaLeft;
	CPortal *_saidaRight;
public:

	CCenario(int ID, char name[10], CPeopleList *players, CPeopleList *monsters, CPeopleList *npcs, CBolsaList *bolsa, CPortal *saidaNorte, CPortal *saidaSul, CPortal *saidaLeft, CPortal *saidaRight);
	void enterScene();
	int personagemCount();
	int itemCount();
	char *getName();
	CPersonagemJogador *getPlayer(int idJogador);
	CInimigo *getMonster(int idInimigo);
	CNPC *getNpc(int idNpc);
	CItem *getItem(int idItem);
	CPortal *getExit(Direcoes idPortal);

	void setID(int value);
	void setName(char *value);
	void setExit(CPortal *newExit, Direcoes idPortal);

	void addPlayer(CPersonagem *jogador);
	void addMonster(CPersonagem *inimigo);
	void addNpc(CPersonagem *npc);

	CPersonagemJogador *removePlayer(int idJogador);
	CInimigo *removeMonster(int idInimigo);
	CNPC *removeNPC(int idNPC);
};
