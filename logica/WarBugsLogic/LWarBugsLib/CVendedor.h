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
	static int _maxDemanda;
	static int _minDemanda;
	static int _maxOferta;
	static int _minOferta;
	static int _itemDemanda[MAXITEMTYPES];
	static int _itemOferta[MAXITEMTYPES];
	static int _precoBase[MAXITEMTYPES];
	static int _MEDIANADEMANDA;
	static int _MEDIANAOFERTA;
	static int _MEDIANADURABILIDADE;
	static int _DESCONTOLEALDADE;
	static int _DESCONTOTEMPO;
	

	int _meta;
	int _restanteMeta;
	int _metaRateada;
	int _tempoSemVender;
	int _tecnicaDeMercado;
	Ponto *_ancora;
public:
	CVendedor();
	CVendedor(EstadoPersonagem estado, int dinheiro, CBolsa *inventario, Ponto *ancora);

	//Métodos da economia
	static void plusDemand(int typeItem);
	static void plusOffer(int typeItem);
	static int normalizeDemand(int typeItem);
	static int normalizeOffer(int typeItem);
	static int stockValue(CItem *item);
	void setLeftToGoal();
	int getSellingPrice(CItem *item);
	int getBuyPrice(CItem *item);
	int getFinalPriceSell(CItem *item, CPersonagemJogador *jogador);
	int getFinalPriceBuy(CItem *item, CPersonagemJogador *jogador);

	void takeDecision();
	void speak();
	void buy(CPersonagemJogador *vendedor, CItem *item);
	void sell(CPersonagemJogador *comprador, CItem *item);

	bool tryAttack();
	void attack();
	void takeDamage(int damage, CPersonagem *atkr);
	void die();
	void useItem(CItem *item);

	void update();
};
#endif