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
	int _durabilidade;
	int _nivelMagico;

public:
	CArmor();
	//Métodos da CObject
	void initialize(CObjectCount *counter, Raca raca, int def, int dur, int nM);
	TipoClasse getClass();
	int getID();
	void useScroll(CScroll *&scroll);
	int getDef();
	int getDurability();
	int getMagicLevel();

	int getValue();
	Atrib getAtribute();
};
#endif