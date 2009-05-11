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
TypeItens CItem::getNome()
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
TipoItem CItem::getTipo()
{
	return(_tipo);
}
int CItem::getTipoAsInt()
{
	return((int)_tipo);
}
int CItem::getPrice()
{
	return(_preco);
}
bool CItem::isDropable()
{
	return(_dropavel);
}
//CPersonagem getOwner(){}
void CItem::setNome(TypeItens novoNome)
{
	_nome = novoNome;
}
void CItem::setEstado(EstadoItem novoEstado)
{
	_estado = novoEstado;
}
void CItem::setPrice(int novoPreco)
{
	_preco = novoPreco;
}
void CItem::setDropable(bool isdropable)
{
	_dropavel = isdropable;
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
#endif