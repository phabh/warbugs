/*
* Classe CConsumableItem
*
* Autor: Eder Figueiredo
*
* Objetivo: Descreve os itens consumíveis
*
*/
#ifndef _CCONSUMABLEITEM_CPP_
#define _CCONSUMABLEITEM_CPP_

#include "CConsumableItem.h"

CConsumableItem::CConsumableItem()
{
	setID(-1);
	_atributo = NENHUM;
	_valor = 0;
	_istemp = false;
	_duracao = 0;
}
CConsumableItem::CConsumableItem(TypeItens nome, EstadoItem estado, int preco, bool isdropable, Atrib att, int valor, bool istemp, int dur)
{
	setID(-1);
	setNome(nome);
	setEstado(estado);
	setPrice(preco);
	setDropable(isdropable);
	_atributo = att;
	_valor = valor;
	_istemp = istemp;
	_duracao = dur;
}
/*CConsumableItem::CConsumableItem(CConsumableItem *item)
{
	_atributo = item->getAtribute();
	_valor = item->getValue();
	_istemp = item->isTemp();
	_duracao = item->getDuration();
}*/
//Getters e setters
Atrib CConsumableItem::getAtribute()
{
	return(_atributo);
}
int CConsumableItem::getAtributeAsInt()
{
	return((int)_atributo);
}
int CConsumableItem::getValue()
{
	return(_valor);
}
bool CConsumableItem::isTemp()
{
	return(_istemp);
}
int CConsumableItem::getDuration()
{
	return(_duracao);
}
void CConsumableItem::setAtribute(Atrib valor)
{
	this->_atributo = valor;
}
void CConsumableItem::setValue(int valor)
{
	this->_valor = valor;
}
void CConsumableItem::setTemp(bool istemp)
{
	this->_istemp = istemp;
}
void CConsumableItem::setDuration(int valor)
{
	this->_duracao = valor;
}
#endif