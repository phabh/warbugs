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
	_cenario = NULL;
}
CInimigo::CInimigo(CCenario *cenario)
{
	_cenario = cenario;
}
CCenario *CInimigo::getScene()
{
	return(_cenario);
}
void CInimigo::setScene(CCenario *newScene)
{
	_cenario = newScene;
}
void CInimigo::takeDecision()
{
	for(int i = 0; i < _cenario->personagemCount(); i = i + 1)
	{
		if(this->getDistanceToPoint(_cenario->getPlayerAt(i)->getPosition()) <= MAXMELEERANGE)
		{
			this->setTarget(_cenario->getPlayerAt(i));
		}
		else
		{
			this->setTarget(NULL);
		}
	}
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
void CInimigo::attack()
{
}
void CInimigo::takeDamage(int damage)
{
	this->getStats()->addPV((-1)*damage);
}
void CInimigo::die()
{
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