#pragma once
/*
* Classe CWeapon
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever as armas do jogo
*
*/
#ifndef _CWEAPON_H_
#define _CWEAPON_H_

#define MAXMELEERANGE 10

#include "CItem.h"
#include "CScroll.h"

class CWeapon : public CItem{
private:
	Raca _raca;
	int _modificador;
	int _danoMin;
	int _danoMax;
	int _velocidade;
	int _alcance;
	int _durabilidade;
	int _nivelMagico;

public:
	CWeapon();
	//Métodos da CObject
	void initialize(CObjectCount *counter, Raca raca, int mod, int danM, int danX, int spd, int rng, int dur, int nM);
	TipoClasse getClass();
	int getID();
	//Outros métodos
	void useScroll(CScroll *&scroll);
	int getMod();
	int getMinDamage();
	int getMaxDamage();
	int getSpeed();
	int getRange();
	int getDurability();
	int getMagicLevel();

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