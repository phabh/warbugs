/*
* Classe CHabilidadesSecundarias
*
* Autor: Eder Figueiredo
*
* Objetivo: Descreve as habilidades que se derivam das primárias de um personagem
*
*/
#ifndef _CHABILIDADESSECUNDARIAS
#define _CHABILIDADESSECUNDARIAS
#include "CObject.cpp"
#include "CEquipamento.cpp"
#include "CHabilidades.cpp"
class CHabilidadesSecundarias : public CObject 
{
private:
	int _pv;//Pontos de vida
	int _pm;//Pontos de magia
	int _maxpv;//Pontos de vida maximos
	int _maxpm;//Pontos de magia maximos
	int _atqC;//Ataque Corpo-a-Corpo
	int _atqD;//Ataque a disância
	int _danoC;//Dano Corpo-a-Corpo
	int _danoD;//Dano a distância
	int _def;//Defesa
	int _atRt;//Taxa de frequência de ataque
	int _tc;//Tempo de carga

public:
	CHabilidadesSecundarias()
	{
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
	CHabilidadesSecundarias(int PV, int PM, int ATC, int ATD, int DMC, int DMD, int DEF, int ATR, int TC)
	{
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
	CHabilidadesSecundarias(CHabilidadesSecundarias *base)
	{
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
	void generate(CHabilidades *primarias, CEquipamento *equip)
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
	int getPV()
	{
		return(_pv);
	}
	int getPM()
	{
		return(_pm);
	}
	int getMaxPV()
	{
		return(_maxpv);
	}
	int getMaxPM()
	{
		return(_maxpm);
	}
	int getMeleeAttack()
	{
		return(_atqC);
	}
	int getRangedAttack()
	{
		return(_atqD);
	}
	int getMeleeDamage()
	{
		return(_danoC);
	}
	int getRangedDamage()
	{
		return(_danoD);
	}
	int getDefense()
	{
		return(_def);
	}
	int getAttackRate()
	{
		return(_atRt);
	}
	int getChargeTime()
	{
		return(_tc);
	}
	void setPV(int valor)
	{
		_pv = valor;
		if(_pv > _maxpv)
		{
			_pv = _maxpv;
		}
	}
	void setPM(int valor)
	{
		_pm = valor;
		if(_pm > _maxpm)
		{
			_pm = _maxpm;
		}
	}
	void setMaxPV(int valor)
	{
		_maxpv = valor;
	}
	void setMaxPM(int valor)
	{
		_maxpm = valor;
	}
	void setMeleeAttack(int valor)
	{
		_atqC = valor;
	}
	void setRangedAttack(int valor)
	{
		_atqD = valor;
	}
	void setMeleeDamage(int valor)
	{
		_danoC = valor;
	}
	void setRangedDamage(int valor)
	{
		_danoD = valor;
	}
	void setDefense(int valor)
	{
		_def = valor;
	}
	void setAttackRate(int valor)
	{
		_atRt = valor;
	}
	void setChargeTime(int valor)
	{
		_tc = valor;
		if(_tc > 100){_tc = 100;}
		else if(_tc < 0){_tc = 0;}
	}
	void addPV(int valor)
	{
		_pv = _pv + valor;
		if(_pv > _maxpv)
		{
			_pv = _maxpv;
		}
	}
	void addPM(int valor)
	{
		_pm = _pm + valor;
		if(_pm > _maxpm)
		{
			_pm = _maxpm;
		}
	}
	void addMaxPV(int valor)
	{
		_maxpv = _maxpv + valor;
	}
	void addMaxPM(int valor)
	{
		_maxpm = _maxpm + valor;
	}
	void addMeleeAttack(int valor)
	{
		_atqC = _atqC + valor;
	}
	void addRangedAttack(int valor)
	{
		_atqD = _atqD + valor;
	}
	void addMeleeDamage(int valor)
	{
		_danoC = _danoC + valor;
	}
	void addRangedDamage(int valor)
	{
		_danoD = _danoD + valor;
	}
	void addDefense(int valor)
	{
		_def = _def + valor;
	}
	void addAttackRate(int valor)
	{
		_atRt = _atRt + valor;
	}
	void addChargeTime(int valor)
	{
		_tc = _tc + valor;
		if(_tc > 100){_tc = 100;}
		else if(_tc < 0){_tc = 0;}
	}
};
#endif