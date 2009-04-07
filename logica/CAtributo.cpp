/*
* Classe CAtributo
*
* Versão: 0.01
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever todos os atributos de um personagem
*
*/
#include "CLogicObject.cpp"
#include "CEquipamento.cpp"
#ifndef _CATRIBUTO
#define _CATRIBUTO


class CAtributo : public CLogicObject
{
};
// -------------------------------------------------------------------------------------------------------------------
class CHabilidades : public CAtributo
{
private:
	int _forca;
	int _agilidade;
	int _destreza;
	int _instinto;
	int _resistencia;
public:
	CHabilidades()
	{
		_forca = 0;
		_agilidade = 0;
		_destreza = 0;
		_instinto = 0;
		_resistencia = 0;
	}
	CHabilidades(int FOR, int AGI, int DES, int INS, int RES)
	{
		_forca = FOR;
		_agilidade = AGI;
		_destreza = DES;
		_instinto = INS;
		_resistencia = RES;
	}
	CHabilidades(CHabilidades *base)
	{
		_forca = base->getFOR();
		_agilidade = base->getAGI();
		_destreza = base->getDES();
		_instinto = base->getINS();
		_resistencia = base->getRES();
	}
	int getFOR()
	{
		return(_forca);
	}
	int getAGI()
	{
		return(_agilidade);
	}
	int getDES()
	{
		return(_destreza);
	}
	int getINS()
	{
		return(_instinto);
	}
	int getRES()
	{
		return(_resistencia);
	}
	void setFOR(int valor)
	{
		_forca = valor;
	}
	void setAGI(int valor)
	{
		_agilidade = valor;
	}
	void setDES(int valor)
	{
		_destreza = valor;
	}
	void setINS(int valor)
	{
		_instinto = valor;
	}
	void setRES(int valor)
	{
		_resistencia = valor;
	}
	void addFOR(int valor)
	{
		_forca = _forca + valor;
	}
	void addAGI(int valor)
	{
		_agilidade = _agilidade + valor;
	}
	void addDES(int valor)
	{
		_destreza = _destreza + valor;
	}
	void addINS(int valor)
	{
		_instinto = _instinto + valor;
	}
	void addRES(int valor)
	{
		_resistencia = _resistencia + valor;
	}
};
// -------------------------------------------------------------------------------------------------------------------
class CHabilidadesSecundarias : public CAtributo 
{
private:
	int _pv;//Pontos de vida
	int _pm;//Pontos de magia
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
};
// -------------------------------------------------------------------------------------------------------------------
class CLealdade : public CAtributo
{
private:
	int _aranha;
	int _besouro;
	int _escorpiao;
	int _louva;//Louva-a-Deus
	int _vespa;
public:
	CLealdade()
	{
		_aranha = 0;
		_besouro = 0;
		_escorpiao = 0;
		_louva = 0;
		_vespa = 0;
	}
	CLealdade(int SPD, int BTL, int SCR, int MNT, int WSP)
	{
		_aranha = SPD;
		_besouro = BTL;
		_escorpiao = SCR;
		_louva = MNT;
		_vespa = WSP;
	}
	CLealdade(CLealdade *base)
	{
		_aranha = base->getLoyaltyToSpider();
		_besouro = base->getLoyaltyToBeetle();
		_escorpiao = base->getLoyaltyToScorpion();
		_louva = base->getLoyaltyToMantis();
		_vespa = base->getLoyaltyToWasp();
	}
	int getLoyaltyToSpider()
	{
		return(_aranha);
	}
	int getLoyaltyToBeetle()
	{
		return(_besouro);
	}
	int getLoyaltyToScorpion()
	{
		return(_escorpiao);
	}
	int getLoyaltyToMantis()
	{
		return(_louva);
	}
	int getLoyaltyToWasp()
	{
		return(_vespa);
	}
	void setLoyaltyToSpider(int valor)
	{
		_aranha = valor;
	}
	void setLoyaltyToBeetle(int valor)
	{
		_besouro = valor;
	}
	void setLoyaltyToScorpion(int valor)
	{
		_escorpiao = valor;
	}
	void setLoyaltyToMantis(int valor)
	{
		_louva = valor;
	}
	void setLoyaltyToWasp(int valor)
	{
		_vespa = valor;
	}
	void addLoyaltyToSpider(int valor)
	{
		_aranha = _aranha + valor;
	}
	void addLoyaltyToBeetle(int valor)
	{
		_besouro = _besouro + valor;
	}
	void addLoyaltyToScorpion(int valor)
	{
		_escorpiao = _escorpiao + valor;
	}
	void addLoyaltyToMantis(int valor)
	{
		_louva = _louva + valor;
	}
	void addLoyaltyToWasp(int valor)
	{
		_vespa = _vespa + valor;
	}
	void addLoyalty(CLealdade *bonus)
	{
		_aranha = _aranha + bonus->getLoyaltyToSpider();
		_besouro = _besouro + bonus->getLoyaltyToBeetle();
		_escorpiao = _escorpiao + bonus->getLoyaltyToScorpion();
		_louva = _louva + bonus->getLoyaltyToMantis();
		_vespa = _vespa + bonus->getLoyaltyToWasp();
	}
};
#endif