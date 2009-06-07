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


#include "CWarBugObject.h"

#ifndef _CPERSONAGEM_H_
#include "CPersonagem.h"
#ifndef _CPERSONAGEM_H_
class CPersonagem;
#endif
#endif

#ifndef _BUFFLIST_
#include "CBuffList.h"
#ifndef _BUFFLIST_
class CBuffList;
#endif
#endif

#define _CBUFF_H_
class CBuff : public CWarBugObject
{
private:
	int _duracao;
	bool _badBuff;
	TipoBuff _tipoBuff;
	CPersonagem *_causador;

	int _valor1;
	int _valor2;
	int _valor3;
public:

	CBuff();
	CBuff(TipoBuff tipo, int dur, CPersonagem *origem, int val1 = 0, int val2 = 0, int val3 = 0);
	TipoBuff getTipo();
	int getTipoAsInt();
	int getDuration();
	void setDuration(int newDuration);
	void addDuration(int valor);
	void addBuff(CBuffList * lista, CPersonagem *alvo);
	void remove(CPersonagem *alvo);
	void execute(CPersonagem *jogador, CBuffList *lista);
};
#endif