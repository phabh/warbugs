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
#ifndef _CCENARIO_H_
#include "CCenario.h"
#ifndef _CCENARIO_H_
class CCenario;
#endif
#endif

CNPC::CNPC()
{
	initCPersonagem();
	setID(-1);
	coordenada = new Ponto();
	dinheiro = 0;
	habilidadesPrimarias = new CHabilidades();
	bonusPrimario = new CBonusPrimario();
	inventario = new CBolsa();
	habilidadesSecundarias = new CHabilidadesSecundarias();
	bonusSecundario = new CBonusSecundario();
	status = new CBuffList();
}
void CNPC::takeDecision()
{
	int tempLinha = 0, tempColuna = 0;
	Ponto *tempPos = new Ponto();
	if(this->getDistanceToPoint(_ancora) >= 100)
	{
		destino = _ancora;
	}
	else
	{
		tempPos->x = this->getPosition()->x;
		tempPos->z = this->getPosition()->z;
		this->getScene()->getQuadLinhaColuna(tempPos, tempLinha, tempColuna);
		switch((clock()%8))
		{
		case 0:
			if((tempLinha > 0)&&(tempColuna < (MAPMAXCOL-1)))
			{
				tempPos = this->getScene()->getQuadCenter(tempLinha-1, tempColuna+1);
				if(this->getScene()->matrizDeCaminhamento[tempLinha][tempColuna] == PASSAVEL)
				{
					destino = this->getScene()->getQuadCenter(tempPos);
				}
				else
				{
					destino = this->getPosition();
				}
			}
			break;
		case 1:
			if(tempColuna < (MAPMAXCOL-1))
			{
				tempPos = this->getScene()->getQuadCenter(tempLinha, tempColuna+1);
				if(this->getScene()->matrizDeCaminhamento[tempLinha][tempColuna] == PASSAVEL)
				{
					destino = this->getScene()->getQuadCenter(tempPos);
				}
				else
				{
					destino = this->getPosition();
				}
			}
			break;
		case 2:
			if((tempLinha < (MAPMAXCOL-1))&&(tempColuna < (MAPMAXCOL-1)))
			{
				tempPos = this->getScene()->getQuadCenter(tempLinha+1, tempColuna+1);
				if(this->getScene()->matrizDeCaminhamento[tempLinha][tempColuna] == PASSAVEL)
				{
					destino = this->getScene()->getQuadCenter(tempPos);
				}
				else
				{
					destino = this->getPosition();
				}
			}
			break;
		case 3:
			if(tempLinha > 0)
			{
				tempPos = this->getScene()->getQuadCenter(tempLinha-1, tempColuna);
				if(this->getScene()->matrizDeCaminhamento[tempLinha][tempColuna] == PASSAVEL)
				{
					destino = this->getScene()->getQuadCenter(tempPos);
				}
				else
				{
					destino = this->getPosition();
				}
			}
			break;
		case 4:
			if(tempLinha < (MAPMAXCOL-1))
			{
				tempPos = this->getScene()->getQuadCenter(tempLinha+1, tempColuna);
				if(this->getScene()->matrizDeCaminhamento[tempLinha][tempColuna] == PASSAVEL)
				{
					destino = this->getScene()->getQuadCenter(tempPos);
				}
				else
				{
					destino = this->getPosition();
				}
			}
			break;
		case 5:
			if((tempLinha > 0)&&(tempColuna > 0))
			{
				tempPos = this->getScene()->getQuadCenter(tempLinha-1, tempColuna-1);
				if(this->getScene()->matrizDeCaminhamento[tempLinha][tempColuna] == PASSAVEL)
				{
					destino = this->getScene()->getQuadCenter(tempPos);
				}
				else
				{
					destino = this->getPosition();
				}
			}
			break;
		case 6:
			if(tempColuna > 0)
			{
				tempPos = this->getScene()->getQuadCenter(tempLinha, tempColuna-1);
				if(this->getScene()->matrizDeCaminhamento[tempLinha][tempColuna] == PASSAVEL)
				{
					destino = this->getScene()->getQuadCenter(tempPos);
				}
				else
				{
					destino = this->getPosition();
				}
			}
			break;
		case 7:
			if((tempLinha < (MAPMAXCOL-1))&&(tempColuna > 0))
			{
				tempPos = this->getScene()->getQuadCenter(tempLinha+1, tempColuna-1);
				if(this->getScene()->matrizDeCaminhamento[tempLinha][tempColuna] == PASSAVEL)
				{
					destino = this->getScene()->getQuadCenter(tempPos);
				}
				else
				{
					destino = this->getPosition();
				}
			}
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
int CNPC::getDEF()
{
	return(this->getStats()->getDefense());
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
