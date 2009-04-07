/*
* Classe CScroll
*
* Versão: 0.01
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever os pergaminhos, que aumentam os atributos das armas
*
*/
#include "CItem.cpp"
#include "CAtributo.cpp"
#ifndef _CSCROLL
#define _CSCROLL


class CScroll : public CItem
{
private:
	int _bModificador;
	int _bDanoMin;
	int _bDanoMax;
	int _bVelocidade;
	int _bAlcance;
	int _bDefesa;
	int _bDurabilidade;

public:
	CScroll()
	{
		_bModificador = 0;
		_bDanoMin = 0;
		_bDanoMax = 0;
		_bVelocidade = 0;
		_bAlcance = 0;
		_bDefesa = 0;
		_bDurabilidade = 0;
	}
	//Métodos da CObject
	void initialize(CObjectCount *counter, int mod, int danM, int danX, int spd, int rng, int def, int dur)
	{
		CItem::initialize(counter);
		_bModificador = mod;
		_bDanoMin = danM;
		_bDanoMax = danX;
		_bVelocidade = spd;
		_bAlcance = rng;
		_bDefesa = def;
		_bDurabilidade = dur;
	}
	TipoClasse getClass()
	{
		return(CSCROLL);
	}


	int getID()
	{
		return(CObject::getID());
	}

	int getMod()
	{
		return(_bModificador);
	}
	int getMinDamage()
	{
		return(_bDanoMin);
	}
	int getMaxDamage()
	{
		return(_bDanoMax);
	}
	int getSpeed()
	{
		return(_bVelocidade);
	}
	int getRange()
	{
		return(_bAlcance);
	}
	int getDef()
	{
		return(_bDefesa);
	}
	int getDurability()
	{
		return(_bDurabilidade);
	}
};
// -------------------------------------------------------------------------------------------------------------------
class CLoyaltyScroll : public CItem
{
/*private:
	CLealdade *_bonus;
public:
	CLoyaltyScroll(){
		_bonus = new CLealdade();
	}
	void use(CLealdade *base){
		base->addLoyalty(_bonus);
	}*/
};
#endif