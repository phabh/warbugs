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
		user->getBuffs()->addBuff(temp, user);
		user->getStats()->addChargeTime(-50);
	}
	else
	{
		user->getStats()->addPM(1);
	}
}
void CPoder::piercingShot(CPersonagemJogador * user, int level)
{
	CBuff *temp;
	switch(level)
	{
	case 0:
		break;
	case 1:
		temp = new CBuff(BUFF_PIERCESHOT, 10*FPS, user, 5, 2,0);
		break;
	case 2:
		temp = new CBuff(BUFF_PIERCESHOT, 10*FPS, user, 7, 3,0);
		break;
	case 3:
		temp = new CBuff(BUFF_PIERCESHOT, 10*FPS, user, 10, 5,0);
		break;
	case 4:
		temp = new CBuff(BUFF_PIERCESHOT, 10*FPS, user, 15, 7,0);
		break;
	case 5:
		temp = new CBuff(BUFF_PIERCESHOT, 10*FPS, user, 30, 10,0);
		break;
	}
	user->getBuffs()->addBuff(temp, user);
}
void CPoder::stunningShot(CPersonagemJogador *user, CPersonagem *target, int level)
{
	CBuff *temp;
	if(user->getStats()->addPM(-5)&&(user->getStats()->getChargeTime() >= 20))
	{
		switch(level)
		{
		case 0:
			break;
		case 1:
			temp = new CBuff(BUFF_STUN, 5*FPS, user, user->getDES(),0,0);
			break;
		case 2:
			temp = new CBuff(BUFF_STUN, 7*FPS, user, user->getDES()+1,0,0);
			break;
		case 3:
			temp = new CBuff(BUFF_STUN, 7*FPS, user, user->getDES()+5,0,0);
			break;
		case 4:
			temp = new CBuff(BUFF_STUN, 7*FPS, user, user->getDES()+7,0,0);
			break;
		case 5:
			temp = new CBuff(BUFF_STUN, 7*FPS, user, user->getDES()+10,0,0);
			break;
		}
		target->getBuffs()->addBuff(temp, target);
	}
	else
	{
		user->getStats()->addPM(5);
	}
}
void CPoder::numbingOnion(CPersonagemJogador *user, CPersonagem *target, int level)
{
	CBuff *temp;
	CPeopleList *player = user->getScene()->getPlayerList();
	CPeopleList *monster = user->getScene()->getMonsterList();
	CPeopleList *npc = user->getScene()->getNPCList();
	CPeopleList *salesman = user->getScene()->getSalesmanList();
	switch(level)
	{
	case 0:
		break;
	case 1:
		temp = new CBuff(BUFF_ATORDOADO, 1*FPS, user, 3,0,0);
		break;
	case 2:
		temp = new CBuff(BUFF_ATORDOADO, 1*FPS, user, 5,0,0);
		break;
	case 3:
		temp = new CBuff(BUFF_ATORDOADO, 1*FPS, user, 5,3,0);
		break;
	case 4:
		temp = new CBuff(BUFF_ATORDOADO, 1*FPS, user, 5,3,0);
		break;
	case 5:
		temp = new CBuff(BUFF_ATORDOADO, 1*FPS, user, 5,5,0);
		break;
	}
	for(int i = 0; max(max(player->size(), monster->size()),max(npc->size(), salesman->size())); i = i + 1)
	{
		if(i < player->size())
			if(user->getDistanceToPoint(player->getElementAt(i)->getPosition()) <= 10*METRO)
			{
				player->getElementAt(i)->getBuffs()->addBuff(temp, player->getElementAt(i));
			}
		if(i < monster->size())
			if((user->getDistanceToPoint(monster->getElementAt(i)->getPosition()) <= 10*METRO)&&(monster->getElementAt(i)->getSceneID() != user->getSceneID()))
			{
				monster->getElementAt(i)->getBuffs()->addBuff(temp, player->getElementAt(i));
			}
		if(i < npc->size())
			if(user->getDistanceToPoint(npc->getElementAt(i)->getPosition()) <= 10*METRO)
			{
				npc->getElementAt(i)->getBuffs()->addBuff(temp, player->getElementAt(i));
			}
		if(i < salesman->size())
			if(user->getDistanceToPoint(salesman->getElementAt(i)->getPosition()) <= 10*METRO)
			{
				salesman->getElementAt(i)->getBuffs()->addBuff(temp, player->getElementAt(i));
			}
	}
	temp = NULL;
	player = NULL;
	monster = NULL;
	npc = NULL;
	salesman = NULL;
	delete temp;
	delete player;
	delete monster;
	delete npc;
	delete salesman;
}
void CPoder::stealItem(CPersonagem *user, CPersonagem *target)
{
	if(user->getStats()->addPM(-10)&&(user->getStats()->getChargeTime() >= 40))
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
	else
	{
		user->getStats()->addPM(10);
	}
}
void CPoder::breakItem(CPersonagem *user, CPersonagem *target)
{
	if(user->getStats()->addPM(-10)&&(user->getStats()->getChargeTime() >= 90))
	{
		int indexToBreak = (clock()%target->getBolsa()->size());
		CItem *temp;
		if(user->tryAttack())
		{
			temp = target->getBolsa()->removeItemAt(indexToBreak);
		}
		temp = NULL;
		delete temp;
	}
	else
	{
		user->getStats()->addPM(10);
	}
}
void CPoder::stinkGas(CPersonagem *user)
{
	CBuff *temp;
	CPeopleList *player = user->getScene()->getPlayerList();
	CPeopleList *monster = user->getScene()->getMonsterList();
	CPeopleList *npc = user->getScene()->getNPCList();
	CPeopleList *salesman = user->getScene()->getSalesmanList();
	for(int i = 0; max(max(player->size(), monster->size()),max(npc->size(), salesman->size())); i = i + 1)
	{
		if(i < player->size())
			if(user->getDistanceToPoint(player->getElementAt(i)->getPosition()) <= 10*METRO)
			{
				temp = new CBuff(BUFF_VENENO, 5*FPS, user, 3, 200, 5);
				player->getElementAt(i)->getBuffs()->addBuff(temp, player->getElementAt(i));
			}
		if(i < monster->size())
			if((user->getDistanceToPoint(monster->getElementAt(i)->getPosition()) <= 10*METRO)&&(monster->getElementAt(i)->getSceneID() != user->getSceneID()))
			{
				temp = new CBuff(BUFF_VENENO, 5*FPS, user, 3, 200, 5);
				monster->getElementAt(i)->getBuffs()->addBuff(temp, player->getElementAt(i));
			}
		if(i < npc->size())
			if(user->getDistanceToPoint(npc->getElementAt(i)->getPosition()) <= 10*METRO)
			{
				temp = new CBuff(BUFF_VENENO, 5*FPS, user, 3, 200, 5);
				npc->getElementAt(i)->getBuffs()->addBuff(temp, player->getElementAt(i));
			}
		if(i < salesman->size())
			if(user->getDistanceToPoint(salesman->getElementAt(i)->getPosition()) <= 10*METRO)
			{
				temp = new CBuff(BUFF_VENENO, 5*FPS, user, 3, 200, 5);
				salesman->getElementAt(i)->getBuffs()->addBuff(temp, player->getElementAt(i));
			}
	}
	player = NULL;
	monster = NULL;
	npc = NULL;
	salesman = NULL;
	delete player;
	delete monster;
	delete npc;
	delete salesman;
}
void CPoder::lightSpeed(CPersonagem *user)
{
	CBuff *temp;
	if(user->getStats()->addPM(-10)&&(user->getStats()->getChargeTime() >= 100))
	{
		temp = new CBuff(BUFF_CHI, 5*FPS, user, 50,0,0);
		user->getBuffs()->addBuff(temp, user);
	}
	else
	{
		user->getStats()->addPM(10);
	}
}
void CPoder::explode(CPersonagem *user)
{
	if(user->getStats()->addPM(-1)&&(user->getStats()->getChargeTime() >= 90))
	{
		CPeopleList *player = user->getScene()->getPlayerList();
		CPeopleList *monster = user->getScene()->getMonsterList();
		CPeopleList *npc = user->getScene()->getNPCList();
		CPeopleList *salesman = user->getScene()->getSalesmanList();
		for(int i = 0; max(max(player->size(), monster->size()),max(npc->size(), salesman->size())); i = i + 1)
		{
			if(i < player->size())
				if(user->getDistanceToPoint(player->getElementAt(i)->getPosition()) <= 10*METRO)
				{
					player->getElementAt(i)->getStats()->addPV(-100);
				}
			if(i < monster->size())
				if((user->getDistanceToPoint(monster->getElementAt(i)->getPosition()) <= 10*METRO)&&(monster->getElementAt(i)->getSceneID() != user->getSceneID()))
				{
					monster->getElementAt(i)->getStats()->addPV(-100);
				}
			if(i < npc->size())
				if(user->getDistanceToPoint(npc->getElementAt(i)->getPosition()) <= 10*METRO)
				{
					npc->getElementAt(i)->getStats()->addPV(-100);
				}
			if(i < salesman->size())
				if(user->getDistanceToPoint(salesman->getElementAt(i)->getPosition()) <= 10*METRO)
				{
					salesman->getElementAt(i)->getStats()->addPV(-100);
				}
		}
		player = NULL;
		monster = NULL;
		npc = NULL;
		salesman = NULL;
		delete player;
		delete monster;
		delete npc;
		delete salesman;
	}
	else
	{
		user->getStats()->addPM(1);
	}
}
void CPoder::killingNeedle(CPersonagem *user, CPersonagem *target)
{
	if(user->getStats()->addPM(-1)&&(user->getStats()->getChargeTime() >= 5))
	{
		target->getStats()->addPV(-50);
	}
	else
	{
		user->getStats()->addPM(1);
	}
}
void CPoder::eat(CPersonagem *user, CPersonagem *target)
{
	if(user->getStats()->addPM(-10)&&(user->getStats()->getChargeTime() >= 10))
	{
		target->getStats()->setPV(0);
		target->die();
	}
	else
	{
		user->getStats()->addPM(10);
	}
}
void CPoder::invisible(CPersonagem *user)
{
	CBuff *temp = new CBuff(BUFF_INVISIVEL, -1, user, 50, 1, 0);
}
void CPoder::summonAnts()
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
	switch(skillIndex)
	{
	case SK_BREAK:
		breakItem(user, target);
		break;
	default:
		break;
	}
}
void CPoder::shaverSkills(CPersonagem *user, TipoPoder skillIndex, int skillLevel, CPersonagem *target)
{
	switch(skillIndex)
	{
	case SK_STINK_GAS:
		stinkGas(user);
		break;
	default:
		break;
	}
}
void CPoder::lizardSkills(CPersonagem *user, TipoPoder skillIndex, int skillLevel, CPersonagem *target)
{
	switch(skillIndex)
	{
	case SK_LIGHT_SPEED:
		lightSpeed(user);
		break;
	default:
		break;
	}
}
void CPoder::ladybugSkills(CPersonagem *user, TipoPoder skillIndex, int skillLevel, CPersonagem *target)
{
	switch(skillIndex)
	{
	case SK_ATOMIC_EXPLOSION:
		explode(user);
		break;
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