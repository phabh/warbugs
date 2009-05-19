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

CInimigo::CInimigo(){}
int CInimigo::takeDecision()
{
	return((clock()%8)+1);
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
	else if((destino->x != getPosition()->x)||(destino->z != getPosition()->z))
	{
		move();
	}
	else if((destino->x == getPosition()->x)||(destino->z == getPosition()->z))
	{
		takeDecision();
	}

	if(getStats()->getPV() <= 0)
	{
		estado = MORTO;
		respawn = ENEMYRESPAWNTIME;
	}
}
#endif