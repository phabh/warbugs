#pragma once
/*
* Classe CBuff
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever os buffs que serão utilizados durante o jogo
*
*/


#ifndef _CBUFF_H_
#define _CBUFF_H_

#ifndef MAXSTATS
#define MAXSTATS 5
#endif
#define SECOND 8

#include "Enumerators.h"
#include "CWarBugObject.h"

#ifndef _CPERSONAGEMJOGADOR_H_
class CPersonagemJogador;
#endif
//#include "CPersonagemJogador.h"

class CBuff : public CWarBugObject
{
private:
	int _duracao;
	int _indiceImagem;
	int _indiceEfeito;
	bool _badBuff;
	TipoBuff _tipoBuff;

	int _valor1;
	int _valor2;
	int _valor3;
public:
	CBuff *_next;

	CBuff();
	CBuff(TipoBuff tipo, int dur, int img, int efc, int val1, int val2, int val3);
	TipoBuff getTipo();
	int getTipoAsInt();
	int getDuration();
	void setDuration(int newDuration);
	void addDuration(int newDuration);
	void initialize(CObjectCount *counter);
	void addBuff(CBuff * buff);
	void remove(int index);
	void execute(CPersonagemJogador *jogador);
};
#endif