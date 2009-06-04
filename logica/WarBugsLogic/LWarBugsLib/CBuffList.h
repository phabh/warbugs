#pragma once
#include <iostream>
using namespace std;
#include "Enumerators.h"

#ifndef _CPERSONAGEM_H_
#include "CPersonagem.h"
#ifndef _CPERSONAGEM_H_
class CPersonagem;
#endif
#endif

#ifndef _CBUFF_H_
#include "CBuff.h"
#ifndef _CBUFF_H_
class CBuff;
#endif
#endif

#ifndef _BUFFLIST_
#define _BUFFLIST_
typedef SCelula<CBuff> SBuffElemento;
class CBuffList : public CWarBugObject
{
private:
	SBuffElemento *_first;
	int _size;

public:
	CBuffList(void);
	CBuffList(CBuff * Buff);

	bool isEmpty();
	int size();
	void addBuff(CBuff *Buff);
	CBuff *removeBuffAt(int pos);
	CBuff *removeBuff(int ID);
	CBuff *removeBuff(CBuff *Buff);
	CBuff *getBuff(int IDBuff);
	CBuff *getBuff(CBuff *buff);
	CBuff *getElementAt(int index);

	bool haveBuff(CBuff *Buff);

	void executeBuffs(CPersonagem *jogador, CBuffList *lista);
};
#endif