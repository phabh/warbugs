#pragma once
#include <iostream>
using namespace std;
#include "Enumerators.h"
#include "CJogador.h"
	//#include "CWarBugObject.h"
	//#include "CCenario.h"
		//#include "CPersonagemJogador.h"

typedef SCelula<CJogador> SPlayerElemento;

class CPlayerList : public CWarBugObject
{
private:
	SPlayerElemento *_first;
	int _size;

public:
	CPlayerList(void);
	CPlayerList(CJogador * Jogador);

	bool isEmpty();
	int size();
	void addJogador(CJogador *Jogador);
	CJogador *removeJogadorByPosition(int pos);
	CJogador *removeJogador(int ID);
	//CJogador *removeJogador(CJogador *Jogador);
	CJogador *getJogador(int IDJogador);
	CJogador *getElementAt(int index);

	bool haveJogador(CJogador *Jogador);
};
