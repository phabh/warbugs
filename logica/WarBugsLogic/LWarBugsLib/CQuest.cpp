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
CQuest::CQuest(CPersonagemJogador *jogador)
{
	setID(-1);
	_estado = Q_CLOSED;
	_jogador = jogador;
	_contratante = NULL;
	_itemNecessario = I_NONE;
	_inimigoNecessario = M_NONE;
	_qtdNecessariaItem = 0;
	_qtdNecessariaInimigo = 0;
	_monstrosDerrotados = 0;
	_itensPossuidos = 0;
	_recompensaItem = NULL;
	_recompensaDinheiro = 0;
	_recompensaXP = 0;
	_recompensaLealdade = new CLealdade();
}
CQuest::CQuest(CPersonagemJogador *jogador, CPersonagem *npc, int itemID, int qtdItem, int monstID, int qtdMonst, int rewdXp, int rewdMny, CLealdade *rewdLdd, CItem *rewdItm)
{
	setID(-1);
	_estado = Q_CLOSED;
	_jogador = jogador;
	_contratante = npc;
	_itemNecessario = (TypeItens)itemID;
	_inimigoNecessario = (TypeModelos)monstID;
	_qtdNecessariaItem = qtdItem;
	_qtdNecessariaInimigo = qtdMonst;
	_monstrosDerrotados = 0;
	_itensPossuidos = 0;
	_recompensaItem = rewdItm;
	_recompensaDinheiro = rewdMny;
	_recompensaXP = rewdXp;
	_recompensaLealdade = rewdLdd;
}


//Getters
CPersonagemJogador *CQuest::getPlayer()
{
	return(_jogador);
}
CPersonagem *CQuest::getNPC()
{
	return(_contratante);
}
int CQuest::getRequestedItem()
{
	return((int)_itemNecessario);
}
int CQuest::getRequestedEnemy()
{
	return((int)_inimigoNecessario);
}
int CQuest::getRequestedNumberOfItens()
{
	return(_qtdNecessariaItem);
}
int CQuest::getRequestedNumberOfEnemies()
{
	return(_qtdNecessariaInimigo);
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
void CQuest::setNPC(CPersonagem *npc)
{
	_contratante = npc;
}
void CQuest::setRequestedItem(int reqItem)
{
	_itemNecessario = (TypeItens)reqItem;
}
void CQuest::setRequestedEnemy(int reqEnemy)
{
	_inimigoNecessario = (TypeModelos)reqEnemy;
}
void CQuest::setRequestedNumberOfItens(int num)
{
	_qtdNecessariaItem = num;
}
void CQuest::setRequestedNumberOfEnemies(int num)
{
	_qtdNecessariaInimigo = num;
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
bool CQuest::testEnemyKilled(CPersonagem *personagem)
{
	if(personagem->getType() == _inimigoNecessario)
	{
		_monstrosDerrotados = _monstrosDerrotados + 1;
		return(true);
	}
	else
	{
		return(false);
	}
}
bool CQuest::testItemPicked(CItem *item)
{
	if(item->getType() == _itemNecessario)
	{
		_itensPossuidos = _itensPossuidos + 1;
		return(true);
	}
	else
	{
		return(false);
	}
}
void CQuest::beginQuest()
{
	_estado = Q_OPEN;
	_monstrosDerrotados = 0;
	_itensPossuidos = 0;
}
void CQuest::beginQuest(CPersonagemJogador *jogador, CPersonagem *npc, int itemID, int qtdItem, int monstID, int qtdMonst, int rewdXp, int rewdMny, CLealdade *rewdLdd, CItem *rewdItm)
{
	_estado = Q_OPEN;
	_jogador = jogador;
	_contratante = npc;
	_itemNecessario = (TypeItens)itemID;
	_inimigoNecessario = (TypeModelos)monstID;
	_qtdNecessariaItem = qtdItem;
	_qtdNecessariaInimigo = qtdMonst;
	_monstrosDerrotados = 0;
	_itensPossuidos = 0;
	_recompensaItem = rewdItm;
	_recompensaDinheiro = rewdMny;
	_recompensaXP = rewdXp;
	_recompensaLealdade = rewdLdd;
}
bool CQuest::tryFinish()
{
	if((_itensPossuidos >= _qtdNecessariaItem)&&(_monstrosDerrotados >= _qtdNecessariaInimigo))
	{
		_estado = Q_FINISHED;
		return(true);
	}
	else
	{
		return(false);
	}
}
void CQuest::finishQuest()
{
	_estado = Q_CLOSED;
}

#endif