#pragma once
/*
* Classe CLealdade
*
* Autor: Eder Figueiredo
*
* Objetivo: Descreve a lealdade de um personagem com as raças
*
*/

#ifndef _CLEALDADE_H_
#define _CLEALDADE_H_

#include "CWarBugObject.h"

class CLealdade : public CWarBugObject
{
private:
	int _aranha;
	int _besouro;
	int _escorpiao;
	int _louva;//Louva-a-Deus
	int _vespa;
public:
	CLealdade();
	CLealdade(int SPD, int BTL, int SCR, int MNT, int WSP);
	CLealdade(CLealdade *base);
	int getLoyaltyToSpider();
	int getLoyaltyToBeetle();
	int getLoyaltyToScorpion();
	int getLoyaltyToMantis();
	int getLoyaltyToWasp();
	void setLoyaltyToSpider(int valor);
	void setLoyaltyToBeetle(int valor);
	void setLoyaltyToScorpion(int valor);
	void setLoyaltyToMantis(int valor);
	void setLoyaltyToWasp(int valor);
	void addLoyaltyToSpider(int valor);
	void addLoyaltyToBeetle(int valor);
	void addLoyaltyToScorpion(int valor);
	void addLoyaltyToMantis(int valor);
	void addLoyaltyToWasp(int valor);
	void addLoyalty(CLealdade *bonus);
};
#endif