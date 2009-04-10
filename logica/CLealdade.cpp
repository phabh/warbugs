/*
* Classe CLealdade
*
* Autor: Eder Figueiredo
*
* Objetivo: Descreve a lealdade de um personagem com as raças
*
*/

#ifndef _CLEALDADE
#define _CLEALDADE
#include "CObject.cpp"
class CLealdade : public CObject
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