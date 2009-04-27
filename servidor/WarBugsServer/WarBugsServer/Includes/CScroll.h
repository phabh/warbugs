#pragma once
/*
* Classe CScroll
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever os pergaminhos, que aumentam os atributos das armas
*
*/
#ifndef _CSCROLL_H_
#define _CSCROLL_H_

#include "CItem.h"
#include "CLealdade.h"

class CScroll : public CItem
{
private:
	int _bModificador;
	int _bDanoMin;
	int _bDanoMax;
	int _bVelocidade;
	int _bAlcance;
	int _bDefesa;
	int _bDurabilidade;

public:
	CScroll();
	//Métodos da CObject
	void initialize(CObjectCount *counter, int mod, int danM, int danX, int spd, int rng, int def, int dur);
	TipoClasse getClass();
	int getID();
	int getMod();
	int getMinDamage();
	int getMaxDamage();
	int getSpeed();
	int getRange();
	int getDef();
	int getDurability();

	void initialize(CObjectCount *counter);
	//Métodos de manipulação de itens
	//virtual void use(CPersonagem *jogador)=0;
	//virtual void loot(CPersonagem *jogador)=0;
	//virtual void drop(CPersonagem *jogador)=0;
	//Métodos virtuais pra funcionar
	int getValue();
	Atrib getAtribute();
};
#endif