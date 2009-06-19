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
	initCPersonagem();
	setID(-1);
	coordenada = new Ponto();
	destino = new Ponto();
	dinheiro = 0;
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
	int tempLinha = 0, tempColuna = 0;
	Ponto *tempPos = new Ponto();
	for(int i = 0; i < cenario->playerCount(); i = i + 1)
	{
		if(this->getDistanceToPoint(cenario->getPlayerAt(i)->getPosition()) <= MAXMELEERANGE)
		{
			this->setTarget(cenario->getPlayerAt(i));
		}
		else
		{
			this->setTarget(NULL);
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
}
int CInimigo::getDEF()
{
	return(this->getStats()->getDefense());
}
bool CInimigo::tryAttack()
{
	int testValue = 0;
	if((this->getDistanceToPoint(alvo->getPosition()) <= MAXMELEERANGE))
	{
		testValue = this->getStats()->getMeleeAttack();

		if(testValue > alvo->getStats()->getDefense())
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
	else
	{
		return(false);
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
	if(getStats()->getPV() <= 0)
	{
		divisorxp->giveXP();
		estado = E_MORTO;
		respawn = ENEMYRESPAWNTIME;
	}
}
void CInimigo::useItem(CItem *item)
{
}
void CInimigo::update()
{
	status->executeBuffs(this, this->status);
	if(respawn > 0)
	{
		respawn = respawn - 1;
		if(respawn == 0)
		{
			estado = E_PARADO;
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