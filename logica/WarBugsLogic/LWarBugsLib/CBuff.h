#pragma once
/*
* Classe CBuff
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever os buffs que ser�o utilizados durante o jogo
*
*/


#ifndef _CBUFF_H_


#include "CWarBugObject.h"

#ifndef _CPERSONAGEMJOGADOR_H_
#include "CPersonagemJogador.h"
#endif

#define _CBUFF_H_
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
	CBuff(TipoBuff tipo, int dur, /*int img, int efc,*/ int val1 = 0, int val2 = 0, int val3 = 0);
	TipoBuff getTipo();
	int getTipoAsInt();
	int getDuration();
	void setDuration(int newDuration);
	void addDuration(int newDuration);
	void initialize(CObjectCount *counter);
	void addBuff(CBuff * buff, CPersonagemJogador *alvo);
	void remove(int index, CPersonagemJogador *alvo);
	void execute(CPersonagemJogador *jogador);
};
#endif