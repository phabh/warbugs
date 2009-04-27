#pragma once
/*
* Classe CConsumableItem
*
* Autor: Eder Figueiredo
*
* Objetivo: Descreve os itens consumíveis
*
*/
#ifndef _CCONSUMABLEITEM_H_
#define _CCONSUMABLEITEM_H_

#include "CItem.h"

class CConsumableItem : public CItem{
private:
	Atrib _atributo;//atributo a ser modificado
	int _valor; //Valor no qual o atributo será modificado
	bool _istemp;//indica se é um efeito temporário ou não
	int _duracao;//duração caso seja temporario
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