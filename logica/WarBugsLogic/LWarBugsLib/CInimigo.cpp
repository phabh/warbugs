/*
* Classe CInimigo
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever cada personagem inimigo
*
*/
#ifndef _CINIMIGO_CPP_
#define _CINIMIGO_CPP_

#include "CInimigo.h"

CInimigo::CInimigo()
{
	setID(-1);
	coordenada = new Ponto();
	destino = new Ponto();
	dinheiro = 0;
	baseMoveSpeed = 0;
	habilidadesPrimarias = new CHabilidades();
	bonusPrimario = new CBonusPrimario();
	inventario = new CBolsa();
	habilidadesSecundarias = new CHabilidadesSecundarias();
	bonusSecundario = new CBonusSecundario();
	status = new CBuffList();
	cenario = NULL;
}
void CInimigo::takeDecision()
{
	for(int i = 0; i < cenario->playerCount(); i = i + 1)
	{
		if(this->getDistanceToPoint(cenario->getPlayerAt(i)->getPosition()) <= MAXMELEERANGE)
		{
			this->setTarget(cenario->getPlayerAt(i));
		}
		else
		{
			this->setTarget(NULL);
		}
	}
	switch((clock()%8))
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
void CInimigo::attack()
{
}
void CInimigo::takeDamage(int damage, CPersonagem *atkr)
{
	this->getStats()->addPV((-1)*damage);
	divisorxp->addAttacker(atkr, damage);
}
void CInimigo::die()
{
	divisorxp->giveXP();
	if(getStats()->getPV() <= 0)
	{
		estado = MORTO;
		respawn = ENEMYRESPAWNTIME;
	}
}
void CInimigo::useItem(CItem *item)
{
}
void CInimigo::update()
{
	if(respawn > 0)
	{
		respawn = respawn - 1;
		if(respawn == 0)
		{
			estado = PARADO;
		}
	}
	else if(this->getTarget() != NULL)
	{
		this->attack();
	}
	else if((destino->x != this->getPosition()->x)||(destino->z != this->getPosition()->z))
	{
		this->move();
	}
	else// if((destino->x == getPosition()->x)||(destino->z == getPosition()->z))
	{
		this->takeDecision();
	}

	die();
}
#endif