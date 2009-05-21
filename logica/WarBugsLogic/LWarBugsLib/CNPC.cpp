/*
* Classe CNPC
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever cada personagem npc
*
*/
#ifndef _CNPC_CPP_
#define _CNPC_CPP_

#include "CNPC.h"

CNPC::CNPC()
{
	//CPersonagem::CPersonagem();
}
void CNPC::takeDecision()
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
void CNPC::speak(CPersonagemJogador *alvo)
{
	destino->x = this->getPosition()->x;
	destino->z = this->getPosition()->z;
}
void CNPC::giveQuest(CPersonagemJogador *alvo)
{
	alvo->acceptQuest(_quest);
}
void CNPC::update()
{
	if((destino->x != this->getPosition()->x)||(destino->z != this->getPosition()->z))
	{
		this->move();
	}
	else
	{
		this->takeDecision();
	}
}
#endif
