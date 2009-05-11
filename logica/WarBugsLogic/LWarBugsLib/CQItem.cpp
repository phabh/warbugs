/*
* Classe CQuestItem
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever todos os itens de quest do jogo
*
*/
#ifndef _CQITEM_CPP_
#define _CQITEM_CPP_

#include "CQItem.h"

CQItem::CQItem()
{
	setEstado(USADO);
	setPrice(0);
	setDropable(false);
	_quest = NULL;
}
CQItem::CQItem(TypeItens nome, EstadoItem estado, int preco, bool isdropable, CQuest *quest)
{
	setNome(nome);
	setEstado(estado);
	setPrice(preco);
	setDropable(isdropable);
	_quest = quest;
}
CQuest *CQItem::getQuest()
{
	return(_quest);
}
Atrib CQItem::getAtribute()
{
	return (NENHUM);
}

int CQItem::getValue()
{
	return -1;
}

#endif