#pragma once
#include <iostream>
using namespace std;
#include "cwarbugobject.h"
#include "CItem.h"
#include "CPersonagem.h"

class CCenario : public CWarBugObject
{
private:
	int _idCenario;
	char _nomeCenario[10];
	CPersonagem *jogadores;//Lista de personagens
	CPersonagem *inimigos;
	CPersonagem *npcs;
	CItem *itens;//Lista de itens
	//CPortal _saida
	CCenario *_next;

public:
	CCenario(void);
	void enterScene();
	int personagemCount();
	int itemCount();
	CItem *getItem(int idItem);
	CPersonagem *getPersonagem(int idPersonagem);
};
