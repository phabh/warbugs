/*
* Classe CWeapon
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever as armas do jogo
*
*/
#ifndef _CWEAPON_CPP_
#define _CWEAPON_CPP_

#include "CWeapon.h"

CWeapon::CWeapon()
{
		_raca = TODAS;
		_modificador = 0;
		_danoMin = 0;
		_danoMax = 0;
		_velocidade = 0;
		_alcance = 0;
		_durabilidade = 0;
		_nivelMagico = 0;
	}
	//Métodos da CObject
	void CWeapon::initialize(CObjectCount *counter, Raca raca, int mod, int danM, int danX, int spd, int rng, int dur, int nM)
	{
		CItem::initialize(counter);
		_raca = raca;
		_modificador = mod;
		_danoMin = danM;
		_danoMax = danX;
		_velocidade = spd;
		_alcance = rng;
		_durabilidade = dur;
		_nivelMagico = nM;
	}
	TipoClasse CWeapon::getClass()
	{
		return(CWEAPON);
	}
	int CWeapon::getID()
	{
		return(CWarBugObject::getID());
	}	
	//Outros métodos
	void CWeapon::useScroll(CScroll *&scroll)
	{
		if(scroll != NULL)
		{
			_modificador = _modificador + scroll->getMod();
			_danoMin = _danoMin + scroll->getMinDamage();
			_danoMax = _danoMax + scroll->getMaxDamage();
			_velocidade = _velocidade + scroll->getSpeed();
			_alcance = _alcance + scroll->getRange();
			_durabilidade = _durabilidade + scroll->getDurability();
			if((scroll->getMod())||
				(scroll->getMinDamage())||
				(scroll->getMaxDamage())||
				(scroll->getSpeed())||
				(scroll->getRange()))
			{
				_nivelMagico = _nivelMagico + 1;
			}
			//scroll->setOwner(null);
			delete scroll;
			scroll = NULL;
		}
	}
	int CWeapon::getMod()
	{
		return(_modificador);
	}
	int CWeapon::getMinDamage()
	{
		return(_danoMin);
	}
	int CWeapon::getMaxDamage()
	{
		return(_danoMax);
	}
	int CWeapon::getSpeed()
	{
		return(_velocidade);
	}
	int CWeapon::getRange()
	{
		return(_alcance);
	}
	int CWeapon::getDurability()
	{
		return(_durabilidade);
	}
	int CWeapon::getMagicLevel()
	{
		return(_nivelMagico);
	}
	Atrib CWeapon::getAtribute()
	{
		return (NENHUM);
	}
	int CWeapon::getValue()
	{
		return -1;
	}

#endif