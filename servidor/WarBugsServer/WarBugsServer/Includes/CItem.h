#pragma once
/*
* Classe CItem
*
* Autor: Eder Figueiredo
*
* Objetivo: Encapsular os dados b�sicos comuns a todos os itens
*
*/
#ifndef _CITEM_H_
#define _CITEM_H_

#include "Enumerators.h"
#include "C3DObject.h"
#include <string>
using namespace std;

class CItem : public C3DObject
{
private:
	TypeItens _nome;//Nome do item
	EstadoItem _estado;//Estado atual do item, se ele esta no chao, no inventario de alguem, ou se ele esta equipado em alguem
	TipoItem _tipo;//Qual o tipo do item, pra dar o cast nas fun��es de outras classes que usarem itens
	int _preco;//Pre�o de compra do item
	bool _dropavel;//Identifica se o item pode ou n�o ser dropado
	//NECESSITA CLASSE JOGADOR -> apontador pro dono do item
public:

	CItem();
	TypeItens getNome();
	EstadoItem getEstado();
	int getEstadoAsInt();
	TipoItem getTipo();
	int getTipoAsInt();
	int getPreco();
	bool isDropable();
	//CPersonagem getOwner(){}
	void setNome(TypeItens novoNome);
	void setEstado(EstadoItem novoEstado);
	void setPreco(int novoPreco);
	void setDropable(bool isdropable);
	//void setOwner(CPersonagem *newOwner){}
	//M�todos de manipula��o de itens
	//virtual void use(CPersonagem *jogador)=0;
	//virtual void loot(CPersonagem *jogador)=0;
	//virtual void drop(CPersonagem *jogador)=0;
	//M�todos virtuais pra funcionar
	virtual int getValue()=0;
	virtual Atrib getAtribute()=0;
};
#endif