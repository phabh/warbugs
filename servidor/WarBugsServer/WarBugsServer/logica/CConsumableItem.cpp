/*
* Classe CConsumableItem
*
* Versão: 0.01
*
* Autor: Eder Figueiredo
*
* Objetivo: Descreve os itens consumíveis
*
*/


#include "CItem.cpp"
#ifndef _CCONSUMABLEITEM
#define _CCONSUMABLEITEM
class CConsumableItem : public CItem{
private:
	Atrib _atributo;//atributo a ser modificado
	int _valor; //Valor no qual o atributo será modificado
	bool _istemp;//indica se é um efeito temporário ou não
	int _duracao;//duração caso seja temporario
public:
	CConsumableItem()
	{
		_atributo = NENHUM;
		_valor = 0;
		_istemp = false;
		_duracao = 0;
	}
	CConsumableItem(Atrib att, int valor, bool istemp, int dur)
	{
		_atributo = att;
		_valor = valor;
		_istemp = istemp;
		_duracao = dur;
	}
	CConsumableItem(CConsumableItem *item)
	{
		_atributo = item->getAtribute();
		_valor = item->getValue();
		_istemp = item->isTemp();
		_duracao = item->getDuration();
	}
	//Getters e setters
	Atrib getAtribute()
	{
		return(_atributo);
	}
	int getAtributeAsInt()
	{
		return((int)_atributo);
	}
	int getValue()
	{
		return(_valor);
	}
	bool isTemp()
	{
		return(_istemp);
	}
	int getDuration()
	{
		return(_duracao);
	}
	void setAtribute(Atrib valor)
	{
		this->_atributo = valor;
	}
	void setValue(int valor)
	{
		this->_valor = valor;
	}
	void setTemp(bool istemp)
	{
		this->_istemp = istemp;
	}
	void setDuration(int valor)
	{
		this->_duracao = valor;
	}
};
#endif