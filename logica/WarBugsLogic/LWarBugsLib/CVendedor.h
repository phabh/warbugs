#pragma once
/*
* Classe CVendedor
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever cada personagem vendedor
*
*/
#ifndef _CVENDEDOR_H_
#define _CVENDEDOR_H_

#include <time.h>
#include "Enumerators.h"
#include "CPersonagemJogador.h"

class CVendedor : public CPersonagem
{
private:
	static int _totalItem[38];
	static int _itensComJogadores[38];
	static int _itemDemanda[38];
	Ponto *_ancora;
public:
	CVendedor();
	CVendedor(EstadoPersonagem estado, int dinheiro, CBolsa *inventario, Ponto *ancora);
	int getPrice(int itemIndex);
	void takeDecision();
	void speak();
	void buy(CPersonagemJogador *vendedor, CItem *item);
	void sell(CPersonagemJogador *comprador, CItem *item);

	void attack();
	void takeDamage(int damage);
	void die();
	void useItem(CItem *item);

	void update();
};
#endif