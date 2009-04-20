/*
* Classe CQuest
*
* Versão: 0.01
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever as quests do jogo
*
*/
#ifndef _CQUEST
#define _CQUEST

#include "CQuest.h"

CQuest::CQuest(){}
void CQuest::beginQuest(/*CPersonagem *personagem*/){}
bool CQuest::tryFinish(){return(true);}
void CQuest::finishQuest(){}
void CQuest::getReward(){}

#endif