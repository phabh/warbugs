/*
* Classe CQuest
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever as quests do jogo
*
*/
#ifndef _CQUEST
#define _CQUEST

#include "CQuest.h"

CQuest::CQuest()
{
	_jogador = new CPersonagemJogador();
	_itemNecessario = I_NONE;
	_inimigoNecessario = M_NONE;
	_qtdNecessaria = 0;
	_recompensaItem = NULL;
	_recompensaDinheiro = 0;
	_recompensaXP = 0;
	_recompensaLealdade = new CLealdade();
}
//Getters
CPersonagemJogador *CQuest::getPlayer()
{
	return(_jogador);
}
int CQuest::getRequestedItem()
{
	if(_itemNecessario != I_NONE)
		return((int)_itemNecessario);
	else if(_inimigoNecessario != M_NONE)
		return(getRequestedEnemy());
	else
		return(0);
}
int CQuest::getRequestedEnemy()
{
	if(_inimigoNecessario != M_NONE)
		return((int)_inimigoNecessario);
	else if(_itemNecessario != I_NONE)
		return(getRequestedItem());
	else
		return(0);
}
int CQuest::getRequestedNumber()
{
	return(_qtdNecessaria);
}
int CQuest::getReward()
{
	return(_recompensaDinheiro);
}
int CQuest::getXPReward()
{
	return(_recompensaXP);
}
CItem *CQuest::getItemReward()
{
	return(_recompensaItem);
}
CLealdade *CQuest::getLoyaltyReward()
{
	return(_recompensaLealdade);
}
//Setters
void CQuest::setPlayer(CPersonagemJogador *player)
{
	_jogador = player;
}
void CQuest::setRequestedItem(int reqItem)
{
	_itemNecessario = (TypeItens)reqItem;
}
void CQuest::setRequestedEnemy(int reqEnemy)
{
	_inimigoNecessario = (TypeModelos)reqEnemy;
}
void CQuest::setRequestedNumber(int num)
{
	_qtdNecessaria = num;
}
void CQuest::setReward(int num)
{
	_recompensaDinheiro = num;
}
void CQuest::setXPReward(int num)
{
	_recompensaXP = num;
}
void CQuest::setItemReward(CItem *item)
{
	_recompensaItem = item;
}
void CQuest::setLoyaltyReward(CLealdade *num)
{
	_recompensaLealdade = num;
}
//
void CQuest::beginQuest(/*CPersonagem *personagem*/)
{
}
bool CQuest::tryFinish()
{
	return(true);
}
void CQuest::finishQuest()
{
}

#endif