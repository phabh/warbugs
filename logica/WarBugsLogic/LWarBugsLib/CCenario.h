#pragma once
#include <iostream>
using namespace std;
#include "C3DObject.h"
#include "CItem.h"
#include "CPersonagem.h"
#include "CPersonagemJogador.h"
#include "CInimigo.h"
#include "CNPC.h"
#include "CPortal.h"

class CCenario : public C3DObject
{
private:
	int _idCenario;
	char _nomeCenario[10];
	CPersonagem *jogadores;//Lista de personagens
	CPersonagem *inimigos;
	CPersonagem *npcs;
	CItem *itens;//Lista de itens
	CPortal *_saida;
public:

	CCenario *_next;

	CCenario(void);
	void enterScene();
	int personagemCount();
	int itemCount();
	int getID();
	char *getName();
	CPersonagemJogador *getPlayer(int idJogador);
	CInimigo *getMonster(int idInimigo);
	CNPC *getNpc(int idNpc);
	CItem *getItem(int idItem);
	CPortal *getExit(int idPortal);

	void setID(int value);
	void setName(char *value);
	void setExit(CPortal *newExit);

	void addPlayer(CPersonagem *jogador);
	void addMonster(CPersonagem *inimigo);
	void addNpc(CPersonagem *npc);

	CPersonagemJogador *removePlayer(int idJogador);
	CInimigo *removeMonster(int idInimigo);
	CNPC *removeNPC(int idNPC);
};
