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
	int _meta;
	int _restanteMeta;
	int _porcentagem;
	int _tempoSemVender;
	int _tecnicaDeMercado;
	Ponto *_ancora;
public:
	CVendedor();
	CVendedor(EstadoPersonagem estado, int dinheiro, CBolsa *inventario, Ponto *ancora);

	static void init();

	//Métodos da economia
	void plusDemand(int typeItem);
	void plusOffer(int typeItem);
	int normalizeDemand(int typeItem);
	int normalizeOffer(int typeItem);
	int stockValue(CItem *item);
	void setLeftToGoal();
	int getSellingPrice(CItem *item);
	int getBuyPrice(CItem *item);
	int getFinalPriceSell(CItem *item, CPersonagemJogador *jogador);
	int getFinalPriceBuy(CItem *item, CPersonagemJogador *jogador);

	void takeDecision();
	void speak();
	void buy(CPersonagemJogador *vendedor, CItem *item);
	void sell(CPersonagemJogador *comprador, CItem *item);

	int getDEF();
	bool tryAttack();
	void attack();
	void takeDamage(int damage, CPersonagem *atkr);
	void die();
	void useItem(CItem *item);

	void update();
};
#endif