/*
* Classe CQuestItem
*
* Versão: 0.01
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever todos os itens de quest do jogo
*
*/
#include "CItem.cpp"
#include "CQuest.cpp"
#ifndef _CQITEM
#define _CQITEM


class CQItem : public CItem{
private:
	CQuest * _quest;
public:
	CQItem(){
	}
};

#endif