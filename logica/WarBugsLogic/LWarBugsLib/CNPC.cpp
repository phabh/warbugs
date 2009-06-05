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
	setID(-1);
	//CPersonagem::CPersonagem();
	coordenada = new Ponto();
	dinheiro = 0;
	baseMoveSpeed = 0;
	habilidadesPrimarias = new CHabilidades();
	bonusPrimario = new CBonusPrimario();
	inventario = new CBolsa();
	habilidadesSecundarias = new CHabilidadesSecundarias();
	bonusSecundario = new CBonusSecundario();
	status = new CBuffList();
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
bool CNPC::tryAttack()
{
	return(true);
}
void CNPC::attack()
{
}
void CNPC::takeDamage(int damage, CPersonagem *atkr)
{
	this->getStats()->addPV((-1)*damage);
	divisorxp->addAttacker(atkr, damage);
}
void CNPC::die()
{
}
void CNPC::useItem(CItem *item)
{
}
void CNPC::update()
{
	status->executeBuffs(this, this->status);
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
