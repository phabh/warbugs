/*
* Classe CBonus
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever os bonus de um personagem
*
*/
#ifndef _CBONUS_CPP_
#define _CBONUS_CPP_
#include <iostream>
#include "CBonus.h"
#include "CBuff.h"

CBonus::CBonus()
{
	origem = NULL;
	next = NULL;
	prev = NULL;
}
CBuff CBonus::getBuff()
{
	return(*origem);
}
void CBonus::setOrigem(CBuff *buff)
{
	origem = buff;
}
void CBonus::add(CBonus *bonus)
{
	CBonus * temp;
	temp = this;
	while(temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = bonus;
	bonus->prev = temp;
	temp = NULL;
	delete temp;
}
void CBonus::remove()
{
	CBonus *temp = this;
	CBonus *temp2 = NULL;
        
	 temp2 = temp->prev;
	 if(temp->prev != NULL)
		 temp2->next = temp->next;
     temp2 = temp->next;
     if(temp->next != NULL)
		 temp2->prev = temp->prev;
   		 
	 temp = NULL;
	 temp2 = NULL;
	 delete temp;
	 delete temp2;
}
#endif