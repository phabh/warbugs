#pragma once
#include <iostream>
using namespace std;
#include "Enumerators.h"
#include "CJogador.h"

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
	CJogador *removeJogadorByPosition(int posJogador);
	CJogador *removeJogador(int IDJogador);
	CJogador *removeJogador(CJogador *Jogador);
	CJogador *getJogador(int IDJogador);

	bool haveJogador(CJogador *Jogador);
};
