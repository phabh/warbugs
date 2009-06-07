/*
* Classe CItem
*
* Autor: Eder Figueiredo
*
* Objetivo: Encapsular os dados básicos comuns a todos os itens
*
*/
#ifndef _CITEM_CPP_
//Define a criação da classe
#define _CITEM_CPP_

#include "CItem.h"

CItem::CItem()
{
}
TypeItens CItem::getBaseID()
{
	return(_nome);
}
EstadoItem CItem::getEstado()
{
	return(_estado);
}
int CItem::getEstadoAsInt()
{
	return((int)_estado);
}
TipoItem CItem::getType()
{
	return(_tipo);
}
int CItem::getTypeAsInt()
{
	return((int)_tipo);
}
int CItem::getPrice()
{
	return(_preco);
}
int CItem::getDurability()
{
	return(_durabilidade);
}
bool CItem::isDropable()
{
	return(_dropavel);
}
//CPersonagem getOwner(){}
void CItem::setBaseID(TypeItens novoNome)
{
	_nome = novoNome;
}
void CItem::setEstado(EstadoItem novoEstado)
{
	_estado = novoEstado;
}
void CItem::setType(TipoItem tipo)
{
	_tipo = tipo;
}
void CItem::setPrice(int novoPreco)
{
	_preco = novoPreco;
}
void CItem::setDropable(bool isdropable)
{
	_dropavel = isdropable;
}
void CItem::setDurability(int value)
{
	if(value > 0)
	{
		if(value <= 100)
		{
			_durabilidade = value;
		}
		else
		{
			_durabilidade = 100;
		}
	}
	else
	{
		CItem::destroy(this);
	}
}
//void setOwner(CPersonagem *newOwner){}
//Métodos de manipulação de itens
//virtual void use(CPersonagem *jogador)=0;
//virtual void loot(CPersonagem *jogador)=0;
//virtual void drop(CPersonagem *jogador)=0;
//Métodos virtuais pra funcionar
/*Atrib CItem::getAtribute()
{
	return (NENHUM);
}
int CItem::getValue()
{
	return -1;
}*/
void CItem::destroy(CItem *item)
{
	item = NULL;
	delete item;
}
#endif