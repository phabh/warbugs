/*
* Classe CHabilidadesSecundarias
*
* Autor: Eder Figueiredo
*
* Objetivo: Descreve as habilidades que se derivam das primárias de um personagem
*
*/
#ifndef _CHABILIDADESSECUNDARIAS_CPP_
#define _CHABILIDADESSECUNDARIAS_CPP_

#include "CHabilidadesSecundarias.h"

CHabilidadesSecundarias::CHabilidadesSecundarias()
{
	setID(-1);
	_pv = 0;
	_pm = 0;
	_atqC = 0;
	_atqD = 0;
	_danoC = 0;
	_danoD = 0;
	_def = 0;
	_atRt = 0;
	_tc = 0;
}
CHabilidadesSecundarias::CHabilidadesSecundarias(int PV, int PM, int ATC, int ATD, int DMC, int DMD, int DEF, int ATR, int TC)
{
	setID(-1);
	_pv = PV;
	_pm = PM;
	_atqC = ATC;
	_atqD = ATD;
	_danoC = DMC;
	_danoD = DMD;
	_def = DEF;
	_atRt = ATR;
	_tc = TC;
}
CHabilidadesSecundarias::CHabilidadesSecundarias(CHabilidadesSecundarias *base)
{
	setID(-1);
	_pv = base->getPV();
	_pm = base->getPM();
	_atqC = base->getMeleeAttack();
	_atqD = base->getRangedAttack();
	_danoC = base->getMeleeDamage();
	_danoD = base->getRangedDamage();
	_def = base->getDefense();
	_atRt = base->getAttackRate();
	_tc = base->getChargeTime();
}
void CHabilidadesSecundarias::generate(CHabilidades *primarias, CEquipamento *equip)
{
	if((primarias != NULL)&&(equip != NULL))
	{
		_pv = primarias->getRES() * 5;
		_pm = primarias->getINS() * 5;
		_atqC = primarias->getFOR() + equip->arma->getMod();
		_danoC = (primarias->getFOR() * equip->arma->getMod());
		if(equip->arma->getRange())
		{
			_atqD = primarias->getDES() + equip->arma->getMod();
			_danoD = (primarias->getDES() * equip->arma->getMod());
		}
		_def = primarias->getRES() + (primarias->getAGI()/2);
		_atRt = primarias->getAGI() + equip->arma->getSpeed();
		_tc = 100;
	}
	else
	{
		//ERRO: PARÂMETRO NULO
	}
}
int CHabilidadesSecundarias::getPV()
{
	return(_pv);
}
int CHabilidadesSecundarias::getPM()
{
	return(_pm);
}
int CHabilidadesSecundarias::getMaxPV()
{
	return(_maxpv);
}
int CHabilidadesSecundarias::getMaxPM()
{
	return(_maxpm);
}
int CHabilidadesSecundarias::getMeleeAttack()
{
	return(_atqC);
}
int CHabilidadesSecundarias::getRangedAttack()
{
	return(_atqD);
}
int CHabilidadesSecundarias::getMeleeDamage()
{
	return(_danoC);
}
int CHabilidadesSecundarias::getRangedDamage()
{
	return(_danoD);
}
int CHabilidadesSecundarias::getDefense()
{
	return(_def);
}
int CHabilidadesSecundarias::getAttackRate()
{
	return(_atRt);
}
int CHabilidadesSecundarias::getChargeTime()
{
	return(_tc);
}
void CHabilidadesSecundarias::setPV(int valor)
{
	_pv = valor;
	if(_pv > _maxpv)
	{
		_pv = _maxpv;
	}
}
void CHabilidadesSecundarias::setPM(int valor)
{
	_pm = valor;
	if(_pm > _maxpm)
	{
		_pm = _maxpm;
	}
}
void CHabilidadesSecundarias::setMaxPV(int valor)
{
	_maxpv = valor;
}
void CHabilidadesSecundarias::setMaxPM(int valor)
{
	_maxpm = valor;
}
void CHabilidadesSecundarias::setMeleeAttack(int valor)
{
	_atqC = valor;
}
void CHabilidadesSecundarias::setRangedAttack(int valor)
{
	_atqD = valor;
}
void CHabilidadesSecundarias::setMeleeDamage(int valor)
{
	_danoC = valor;
}
void CHabilidadesSecundarias::setRangedDamage(int valor)
{
	_danoD = valor;
}
void CHabilidadesSecundarias::setDefense(int valor)
{
	_def = valor;
}
void CHabilidadesSecundarias::setAttackRate(int valor)
{
	_atRt = valor;
}
void CHabilidadesSecundarias::setChargeTime(int valor)
{
	_tc = valor;
	if(_tc > 100){_tc = 100;}
	else if(_tc < 0){_tc = 0;}
}
bool CHabilidadesSecundarias::addPV(int valor)
{
	_pv = _pv + valor;
	if(_pv > _maxpv)
	{
	_pv = _maxpv;
		return(true);
	}
	else if(_pv <= 0)
	{
		_pv = 0;
		return(false);
	}
	else return(true);
}
bool CHabilidadesSecundarias::addPM(int valor)
{
	_pm = _pm + valor;
	if(_pm > _maxpm)
	{
		_pm = _maxpm;
		return(true);
	}
	else if(_pm <= 0)
	{
		_pm = 0;
		return(false);
	}
	else return(true);
}
void CHabilidadesSecundarias::addMaxPV(int valor)
{
	_maxpv = _maxpv + valor;
}
void CHabilidadesSecundarias::addMaxPM(int valor)
{
	_maxpm = _maxpm + valor;
}
void CHabilidadesSecundarias::addMeleeAttack(int valor)
{
	_atqC = _atqC + valor;
}
void CHabilidadesSecundarias::addRangedAttack(int valor)
{
	_atqD = _atqD + valor;
}
void CHabilidadesSecundarias::addMeleeDamage(int valor)
{
	_danoC = _danoC + valor;
}
void CHabilidadesSecundarias::addRangedDamage(int valor)
{
	_danoD = _danoD + valor;
}
void CHabilidadesSecundarias::addDefense(int valor)
{
	_def = _def + valor;
}
void CHabilidadesSecundarias::addAttackRate(int valor)
{
	_atRt = _atRt + valor;
}
void CHabilidadesSecundarias::addChargeTime(int valor)
{
	_tc = _tc + valor;
	if(_tc > 100){_tc = 100;}
	else if(_tc < 0){_tc = 0;}
}
#endif