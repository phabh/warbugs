/*
* Classe CPoder
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever os poderes de um personagem
*
*/
#ifndef _CPODER_CPP_
#define _CPODER_CPP_

#include "CPoder.h"
//Skills
void CPoder::berserkTornado(CPersonagemJogador *user, int level)
{
	CBuff *temp;
	if(user->getStats()->addPM(-1)&&(user->getStats()->getChargeTime() >= 90))
	{
		switch(level)
		{
		case 0:
			break;
		case 1:
			temp = new CBuff(BERSERKER, 5*FPS, 10, user->getFOR(), -10);
			break;
		case 2:
			temp = new CBuff(BERSERKER, 7*FPS, 10, user->getFOR()+1, -10);
			break;
		case 3:
			temp = new CBuff(BERSERKER, 10*FPS, 15, user->getFOR()+1, -5);
			break;
		case 4:
			temp = new CBuff(BERSERKER, 10*FPS, 15, user->getFOR()+3, -5);
			break;
		case 5:
			temp = new CBuff(BERSERKER, 20*FPS, 20, user->getFOR()+5, -5);
			break;
		default:
			break;
		}
		user->getBuffs()->addBuff(temp, user);
		user->getStats()->addChargeTime(-90);
	}
	else
	{
		user->getStats()->addPM(1);
	}
}

void CPoder::ariete(CPersonagemJogador *user, CPersonagem *target, int level)
{
	int temp;
	int temp2;
	int ataque = user->getStats()->getMeleeAttack() + 20;;
	int dano;
	int dist = 10000;
	if(user->getStats()->addPM(-1)&&(user->getStats()->getChargeTime() >= 40))
	{
		user->setTarget(target);
		switch(level)
		{
		case 0:
			break;
		case 1:
			dist = 15;
			dano = user->getStats()->getMeleeDamage() + 5;
			break;
		case 2:
			dist = 15;
			dano = user->getStats()->getMeleeDamage() + 10;
			break;
		case 3:
			dist = 10;
			dano = user->getStats()->getMeleeDamage() + 10;
			break;
		case 4:
			dist = 10;
			dano = user->getStats()->getMeleeDamage() + 15;
			break;
		case 5:
			dist = 5;
			dano = user->getStats()->getMeleeDamage() + 15;
			break;
		default:
			break;
		}
		if(user->getDistanceToPoint(target->getPosition()) >= dist)
		{
			temp = user->getAttack();
			user->setAttack(ataque);
			temp2 = user->getDamage();
			user->setDamage(dano);

			user->attack();

			user->setAttack(temp);
			user->setDamage(temp2);
			user->getStats()->addChargeTime(-40);
		}
	}
	else
	{
		user->getStats()->addPM(1);
	}
}
void strike(CPersonagemJogador *user, int level)
{
	CBuff *temp;
	if(user->getStats()->addPM(-1)&&(user->getStats()->getChargeTime() >= 50))
	{
		switch(level)
		{
		case 0:
			break;
		case 1:
			temp = new CBuff(STRIKE, 5*FPS, user->getFOR(), 1);
			break;
		case 2:
			temp = new CBuff(STRIKE, 5*FPS, user->getFOR()+1, 3);
			break;
		case 3:
			temp = new CBuff(STRIKE, 7*FPS, user->getFOR()+3, 5);
			break;
		case 4:
			temp = new CBuff(STRIKE, 7*FPS, user->getFOR()+5, 7);
			break;
		case 5:
			temp = new CBuff(STRIKE, 10*FPS, user->getFOR()+10, 10);
			break;
		default:
			break;
		}
		user->getBuffs()->addBuff(temp, user);
		user->getStats()->addChargeTime(-50);
	}
	else
	{
		user->getStats()->addPM(1);
	}
}
//RaceTypes
void CPoder::beetleSkills(CPersonagemJogador *user, TipoPoder skillIndex, int skillLevel, CPersonagem *target)
{
	switch(skillIndex)
	{
	case SK_BERSERK_TORNADO:
		berserkTornado(user, skillLevel);
		break;
	case SK_ARIETE:
		ariete(user, target, skillLevel);
	case SK_STRIKE:
		strike(user, skillLevel);
	default:
		break;
	}
}

void CPoder::cast(CPersonagem *user, Raca userRace, TipoPoder skillIndex, int skillLevel, CPersonagem *target)
{
	switch(userRace)
	{
	case BESOURO:
		beetleSkills((CPersonagemJogador*)user, skillIndex, skillLevel, target);
		break;
	default:
		break;
	}
}

#endif