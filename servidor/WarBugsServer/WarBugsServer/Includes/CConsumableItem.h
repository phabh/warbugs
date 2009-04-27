#pragma once
/*
* Classe CConsumableItem
*
* Autor: Eder Figueiredo
*
* Objetivo: Descreve os itens consum�veis
*
*/
#ifndef _CCONSUMABLEITEM_H_
#define _CCONSUMABLEITEM_H_

#include "CItem.h"

class CConsumableItem : public CItem{
private:
	Atrib _atributo;//atributo a ser modificado
	int _valor; //Valor no qual o atributo ser� modificado
	bool _istemp;//indica se � um efeito tempor�rio ou n�o
	int _duracao;//dura��o caso seja temporario
public:
	CConsumableItem();
	CConsumableItem(Atrib att, int valor, bool istemp, int dur);
	CConsumableItem(CConsumableItem *item);
	//Getters e setters
	Atrib getAtribute();
	int getAtributeAsInt();
	int getValue();
	bool isTemp();
	int getDuration();
	void setAtribute(Atrib valor);
	void setValue(int valor);
	void setTemp(bool istemp);
	void setDuration(int valor);
};
#endif