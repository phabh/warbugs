#pragma once
/*
* Classe CDivisorXP
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever a lista de personagens que causaram dano a um inimigo para a divisao de xp
*
*/
#ifndef _CDIVXP_H_
#define _CDIVXP_H_

#ifndef _CPERSONAGEM_H_
#include "CPersonagem.h"
#ifndef _CPERSONAGEM_H_
class CPersonagem;
#endif
#endif

struct SDivisorXP
{
	int dano;
	CPersonagem *causador;
	SDivisorXP *next;

	SDivisorXP()
	{
		dano = 0;
		causador = NULL;
		next = NULL;
	}
	SDivisorXP(int dmg, CPersonagem *atkr, SDivisorXP *nxt)
	{
		dano = dmg;
		causador = atkr;
		next = nxt;
	}
};

class CDivisorXP
{
private:
	CPersonagem *_owner;
	SDivisorXP *_first;
	int _size;
public:
	CDivisorXP()
	{
		_first = new SDivisorXP();
		_size = 0;
	}
	bool isEmpty()
	{
		return(_size == 0);
	}
	void addAttacker(CPersonagem *atkr, int dmg)
	{
		SDivisorXP *nodo = new SDivisorXP(dmg, atkr, NULL);
		if(isEmpty())
		{
			_first = nodo;
			_size = 1;
		}
		else
		{
			SDivisorXP *temp = _first;
			while(temp->next != NULL)
			{
				if(temp->causador->getID() == atkr->getID())
				{
					temp->dano = temp->dano + dmg;
					return;
				}
				else
				{
					temp = temp->next;
				}
			}
			temp->next = nodo;
			_size = _size + 1;
			temp = NULL;
			delete temp;
		}
		nodo = NULL;
		delete nodo;
	}
	void cleanUp()
	{
		_size = 0;
		_first = NULL;
		delete _first;
	}
	void giveXP()
	{
		float aux;
		int xp;
		while(_first != NULL)
		{
			aux = ((float)(_first->dano * 100))/((float)(_owner->getStats()->getMaxPV()));
			xp = (int)(((float)(BASEXPVALUE *_first->causador->getLevel()))*aux) - (BASEXPVALUE/XPREDUCTIONFACTOR * _first->causador->getLevel());
			_first->causador->addXP(xp);
			_first = _first->next;
		}
		cleanUp();
	}

};
#endif