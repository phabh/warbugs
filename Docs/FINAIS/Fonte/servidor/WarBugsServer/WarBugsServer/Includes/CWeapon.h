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
	int _nivelMagico;

public:
	CWeapon();
	CWeapon(TypeItens nome, EstadoItem estado, int preco, bool isdropable, Raca raca, int mod, int danM, int danX, int spd, int rng, int dur, int nM);
	//Outros m�todos
	void useScroll(CScroll *&scroll);
	Raca getRace();
	int getMod();
	int getMinDamage();
	int getMaxDamage();
	int getSpeed();
	int getRange();
	int getMagicLevel();

	//M�todos de manipula��o de itens
	//virtual void use(CPersonagem *jogador)=0;
	//virtual void loot(CPersonagem *jogador)=0;
	//virtual void drop(CPersonagem *jogador)=0;
	//M�todos virtuais pra funcionar
	int getValue();
	Atrib getAtribute();

	void setAll(Raca raca, int mod, int danM, int danX, int spd, int rng, int dur, int nM);
};
#endif