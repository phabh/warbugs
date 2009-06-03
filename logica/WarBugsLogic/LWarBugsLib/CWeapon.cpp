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
	setID(-1);
	setDurability(0);
	_raca = ALLRACE;
	_modificador = 0;
	_danoMin = 0;
	_danoMax = 0;
	_velocidade = 0;
	_alcance = 0;
	_nivelMagico = 0;
}
//Métodos da CObject
CWeapon::CWeapon(TypeItens nome, EstadoItem estado, int preco, bool isdropable, Raca raca, int mod, int danM, int danX, int spd, int rng, int dur, int nM)
{
	setID(-1);
	setDurability(dur);
	setNome(nome);
	setEstado(estado);
	setPrice(preco);
	setDropable(isdropable);
	_raca = raca;
	_modificador = mod;
	_danoMin = danM;
	_danoMax = danX;
	_velocidade = spd;
	_alcance = rng;
	_nivelMagico = nM;
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
		setDurability(getDurability() + scroll->getDurability());
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
Raca CWeapon::getRace()
{
	return(_raca);
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