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
	setBuffs(new CBuffList());
}
CVendedor::CVendedor(EstadoPersonagem estado, int dinheiro, CBolsa *inventario, Ponto *ancora)
{
	_ancora = ancora;
	setState(estado);
	setMoney(dinheiro);
	setBolsa(inventario);
	setPosition(ancora);
	setStats(new CHabilidadesSecundarias());
	setBonus(new CBonusSecundario());
	setBaseStats(new CHabilidades());
	setBaseBonus(new CBonusPrimario());
	setBuffs(new CBuffList());
}
void CVendedor::takeDecision()
{
	if(this->getDistanceToPoint(_ancora) >= 100)
	{
		destino = _ancora;
	}
	else
	{
		switch((clock()%8)+1)
		{
		case 0:
			destino->x = destino->x - QUADRANTESIZE;
			destino->z = destino->z + QUADRANTESIZE;
			break;
		case 1:
			destino->x = destino->x;
			destino->z = destino->z + QUADRANTESIZE;
			break;
		case 2:
			destino->x = destino->x + QUADRANTESIZE;
			destino->z = destino->z + QUADRANTESIZE;
			break;
		case 3:
			destino->x = destino->x - QUADRANTESIZE;
			destino->z = destino->z;
			break;
		case 4:
			destino->x = destino->x + QUADRANTESIZE;
			destino->z = destino->z;
			break;
		case 5:
			destino->x = destino->x - QUADRANTESIZE;
			destino->z = destino->z - QUADRANTESIZE;
			break;
		case 6:
			destino->x = destino->x;
			destino->z = destino->z - QUADRANTESIZE;
			break;
		case 7:
			destino->x = destino->x + QUADRANTESIZE;
			destino->z = destino->z - QUADRANTESIZE;
			break;
		}
	}
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