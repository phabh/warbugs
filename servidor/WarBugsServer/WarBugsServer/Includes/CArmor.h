#pragma once
/*
* Classe CArmor
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever as armaduras do jogo
*
*/
#ifndef _CARMOR_H_
#define _CARMOR_H_

#include "CItem.h"
#include "CScroll.h"

class CArmor : public CItem
{
private:
	Raca _raca;
	int _defesa;
	int _nivelMagico;

public:
	CArmor();
	CArmor(TypeItens nome, EstadoItem estado, int preco, bool isdropable, Raca raca, int def, int dur, int nM);
	void useScroll(CScroll *&scroll);
	Raca getRace();
	int getDef();
	int getMagicLevel();

	int getValue();
	Atrib getAtribute();
};
#endif