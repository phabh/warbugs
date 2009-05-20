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

#include "Enumerators.h"
#include "CPersonagemJogador.h"

class CVendedor : public CPersonagem
{
private:
	static int _totalItem[38];
	static int _itensComJogadores[38];
	static int _itemDemanda[38];
public:
	CVendedor();
	CVendedor(EstadoPersonagem estado, int dinheiro, CBolsa *inventario);
	int getPrice(int itemIndex);
	void speak();
	void buy(CPersonagemJogador *vendedor, CItem *item);
	void sell(CPersonagemJogador *comprador, CItem *item);
};
#endif