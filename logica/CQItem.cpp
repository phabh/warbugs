/*
* Classe CQuestItem
*
* Vers�o: 0.01
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever todos os itens de quest do jogo
*
*/

#ifndef _CQITEM
#define _CQITEM
#include "CItem.cpp"
#include "CQuest.cpp"

class CQItem : public CItem{
private:
	CQuest * _quest;
public:
	CQItem(){
	}
};

#endif