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

#include "CPersonagemJogador.h"

class CVendedor : public CPersonagem
{
public:
	CVendedor();
	CVendedor(EstadoPersonagem estado, int dinheiro, CBolsa *inventario);
	void speak();
	void buy(CPersonagemJogador *vendedor, CItem *item);
	void sell(CPersonagemJogador *comprador, CItem *item);
};
#endif