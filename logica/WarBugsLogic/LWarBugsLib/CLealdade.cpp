/*
* Classe CLealdade
*
* Autor: Eder Figueiredo
*
* Objetivo: Descreve a lealdade de um personagem com as raças
*
*/

#ifndef _CLEALDADE_CPP_
#define _CLEALDADE_CPP_

#include "CLealdade.h"

CLealdade::CLealdade()
	{
		_aranha = 0;
		_besouro = 0;
		_escorpiao = 0;
		_louva = 0;
		_vespa = 0;
	}
	CLealdade::CLealdade(int SPD, int BTL, int SCR, int MNT, int WSP)
	{
		_aranha = SPD;
		_besouro = BTL;
		_escorpiao = SCR;
		_louva = MNT;
		_vespa = WSP;
	}
	CLealdade::CLealdade(CLealdade *base)
	{
		_aranha = base->getLoyaltyToSpider();
		_besouro = base->getLoyaltyToBeetle();
		_escorpiao = base->getLoyaltyToScorpion();
		_louva = base->getLoyaltyToMantis();
		_vespa = base->getLoyaltyToWasp();
	}
	int CLealdade::getLoyaltyToSpider()
	{
		return(_aranha);
	}
	int CLealdade::getLoyaltyToBeetle()
	{
		return(_besouro);
	}
	int CLealdade::getLoyaltyToScorpion()
	{
		return(_escorpiao);
	}
	int CLealdade::getLoyaltyToMantis()
	{
		return(_louva);
	}
	int CLealdade::getLoyaltyToWasp()
	{
		return(_vespa);
	}
	void CLealdade::setLoyaltyToSpider(int valor)
	{
		_aranha = valor;
	}
	void CLealdade::setLoyaltyToBeetle(int valor)
	{
		_besouro = valor;
	}
	void CLealdade::setLoyaltyToScorpion(int valor)
	{
		_escorpiao = valor;
	}
	void CLealdade::setLoyaltyToMantis(int valor)
	{
		_louva = valor;
	}
	void CLealdade::setLoyaltyToWasp(int valor)
	{
		_vespa = valor;
	}
	void CLealdade::addLoyaltyToSpider(int valor)
	{
		_aranha = _aranha + valor;
	}
	void CLealdade::addLoyaltyToBeetle(int valor)
	{
		_besouro = _besouro + valor;
	}
	void CLealdade::addLoyaltyToScorpion(int valor)
	{
		_escorpiao = _escorpiao + valor;
	}
	void CLealdade::addLoyaltyToMantis(int valor)
	{
		_louva = _louva + valor;
	}
	void CLealdade::addLoyaltyToWasp(int valor)
	{
		_vespa = _vespa + valor;
	}
	void CLealdade::addLoyalty(CLealdade *bonus)
	{
		_aranha = _aranha + bonus->getLoyaltyToSpider();
		_besouro = _besouro + bonus->getLoyaltyToBeetle();
		_escorpiao = _escorpiao + bonus->getLoyaltyToScorpion();
		_louva = _louva + bonus->getLoyaltyToMantis();
		_vespa = _vespa + bonus->getLoyaltyToWasp();
	}
#endif