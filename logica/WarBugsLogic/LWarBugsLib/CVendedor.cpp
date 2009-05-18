/*
* Classe CVendedor
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever cada personagem vendedor
*
*/
#ifndef _CVENDEDOR_CPP_
#define _CVENDEDOR_CPP_

#include "CVendedor.h"

CVendedor::CVendedor()
{
	setState(PARADO);
	setMoney(0);
	setBolsa(new CBolsa());
	setStats(new CHabilidadesSecundarias());
	setBonus(new CBonusSecundario());
	setBaseStats(new CHabilidades());
	setBaseBonus(new CBonusPrimario());
	setBuffs(new CBuff());
}
CVendedor::CVendedor(EstadoPersonagem estado, int dinheiro, CBolsa *inventario)
{
	setState(estado);
	setMoney(dinheiro);
	setBolsa(inventario);
	setStats(new CHabilidadesSecundarias());
	setBonus(new CBonusSecundario());
	setBaseStats(new CHabilidades());
	setBaseBonus(new CBonusPrimario());
	setBuffs(new CBuff());
}
void CVendedor::speak(){}
void CVendedor::buy(CPersonagemJogador *vendedor, CItem *item)
{
	if((vendedor->haveItem(item)) && (getMoney() >= item->getPrice()/2))
	{
		vendedor->getBolsa()->removeItem(item->getID());
		vendedor->addMoney(item->getPrice()/2);
		getBolsa()->addItem(item);
	}
}
void CVendedor::sell(CPersonagemJogador *comprador, CItem *item)
{
	if((getBolsa()->haveItem(item->getID())) && (comprador->getMoney() >= item->getPrice()))
	{
		getBolsa()->removeItem(item->getID());
		comprador->addMoney((-1)*item->getPrice());
		comprador->getBolsa()->addItem(item);
	}
}
#endif