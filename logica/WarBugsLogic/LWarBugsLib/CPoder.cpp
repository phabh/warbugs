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
			temp = new CBuff(BUFF_BERSERKER, 5*FPS, user, 10, user->getFOR(), -10);
			break;
		case 2:
			temp = new CBuff(BUFF_BERSERKER, 7*FPS, user, 10, user->getFOR()+1, -10);
			break;
		case 3:
			temp = new CBuff(BUFF_BERSERKER, 10*FPS, user, 15, user->getFOR()+1, -5);
			break;
		case 4:
			temp = new CBuff(BUFF_BERSERKER, 10*FPS, user, 15, user->getFOR()+3, -5);
			break;
		case 5:
			temp = new CBuff(BUFF_BERSERKER, 20*FPS, user, 20, user->getFOR()+5, -5);
			break;
		default:
			break;
		}
		user->getBuffs()->addBuff(temp);
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
void CPoder::strike(CPersonagemJogador *user, int level)
{
	CBuff *temp;
	if(user->getStats()->addPM(-1)&&(user->getStats()->getChargeTime() >= 50))
	{
		switch(level)
		{
		case 0:
			break;
		case 1:
			temp = new CBuff(BUFF_STRIKE, 5*FPS, user, user->getFOR(), 1);
			break;
		case 2:
			temp = new CBuff(BUFF_STRIKE, 5*FPS, user, user->getFOR()+1, 3);
			break;
		case 3:
			temp = new CBuff(BUFF_STRIKE, 7*FPS, user, user->getFOR()+3, 5);
			break;
		case 4:
			temp = new CBuff(BUFF_STRIKE, 7*FPS, user, user->getFOR()+5, 7);
			break;
		case 5:
			temp = new CBuff(BUFF_STRIKE, 10*FPS, user, user->getFOR()+10, 10);
			break;
		default:
			break;
		}
		user->getBuffs()->addBuff(temp);
		user->getStats()->addChargeTime(-50);
	}
	else
	{
		user->getStats()->addPM(1);
	}
}
void CPoder::stealItem(CPersonagem *user, CPersonagem *target)
{
	int indexToSteal = (clock()%target->getBolsa()->size());
	CItem *temp;
	if(user->tryAttack())
	{
		temp = target->getBolsa()->removeItemAt(indexToSteal);
		user->getBolsa()->addItem(temp);
	}
	temp = NULL;
	delete temp;
}
void CPoder::breakItem(CPersonagem *user, CPersonagem *target)
{
}
void CPoder::lightSpeed(CPersonagem *user)
{
}
void CPoder::explode(CPersonagem *user)
{
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
void CPoder::antSkills(CPersonagem *user, TipoPoder skillIndex, int skillLevel, CPersonagem *target)
{
	switch(skillIndex)
	{
	case SK_STEAL:
		stealItem(user, target);
		break;
	default:
		break;
	}
}
void CPoder::termiteSkills(CPersonagem *user, TipoPoder skillIndex, int skillLevel, CPersonagem *target)
{
}
void CPoder::shaverSkills(CPersonagem *user, TipoPoder skillIndex, int skillLevel, CPersonagem *target)
{
}
void CPoder::lizardSkills(CPersonagem *user, TipoPoder skillIndex, int skillLevel, CPersonagem *target)
{
}
void CPoder::ladybugSkills(CPersonagem *user, TipoPoder skillIndex, int skillLevel, CPersonagem *target)
{
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