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
	int _durabilidade;//Durabilidade do item
	//NECESSITA CLASSE JOGADOR -> apontador pro dono do item
public:

	CItem();
	TypeItens getBaseID();
	EstadoItem getEstado();
	int getEstadoAsInt();
	TipoItem getType();
	int getTypeAsInt();
	int getPrice();
	int getDurability();
	bool isDropable();
	//CPersonagem getOwner(){}
	void setBaseID(TypeItens valor);
	void setEstado(EstadoItem novoEstado);
	void setType(TipoItem tipo);
	void setPrice(int novoPreco);
	void setDropable(bool isdropable);
	void setDurability(int value);
	//void setOwner(CPersonagem *newOwner){}
	//M�todos de manipula��o de itens
	//virtual void use(CPersonagem *jogador)=0;
	//virtual void loot(CPersonagem *jogador)=0;
	//virtual void drop(CPersonagem *jogador)=0;
	//M�todos virtuais pra funcionar
	static void destroy(CItem *item);
	virtual int getValue()=0;
	virtual Atrib getAtribute()=0;
};
#endif