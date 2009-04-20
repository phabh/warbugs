/*
* Classe CItem
*
* Autor: Eder Figueiredo
*
* Objetivo: Encapsular os dados b�sicos comuns a todos os itens
*
*/
#ifndef _CITEM_CPP_
//Define a cria��o da classe
#define _CITEM_CPP_

#include "CItem.h"

CItem::CItem(){}
	string CItem::getNome()
	{
		return(_nome);
	}
	string CItem::getDescricao()
	{
		return(_descricao);
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
	int CItem::getPreco()
	{
		return(_preco);
	}
	bool CItem::isDropable()
	{
		return(_dropavel);
	}
	//CPersonagem getOwner(){}
	void CItem::setNome(string novoNome)
	{
		_nome = novoNome;
	}
	void CItem::setDescricao(string novaDesc)
	{
		_descricao = novaDesc;
	}
	void CItem::setEstado(EstadoItem novoEstado)
	{
		_estado = novoEstado;
	}
	void CItem::setPreco(int novoPreco)
	{
		_preco = novoPreco;
	}
	void CItem::setDropable(bool isdropable)
	{
		_dropavel = isdropable;
	}
	//void setOwner(CPersonagem *newOwner){}
	//M�todos da CObject
	void CItem::initialize(CObjectCount *counter)
	{
		C3DObject::initialize(counter);
	}
	TipoClasse CItem::getClass()
	{
		return(CITEM);
	}
	//M�todos de manipula��o de itens
	//virtual void use(CPersonagem *jogador)=0;
	//virtual void loot(CPersonagem *jogador)=0;
	//virtual void drop(CPersonagem *jogador)=0;
	//M�todos virtuais pra funcionar
	Atrib CItem::getAtribute()
	{
		return (NENHUM);
	}

	int CItem::getValue()
	{
		return -1;
	}

#endif