#pragma once
#include <iostream>
using namespace std;
#include "CItem.h"

typedef struct SCelula
{
	CItem *item;
	SCelula *prev;
	SCelula *next;
} SElemento;


class CBolsa : public C3DObject
{
private:
	SElemento *_first;
	int _size;

public:
	CBolsa(void);
	CBolsa(CItem * item);

	bool isEmpty();
	int size();
	void addItem(CItem *item);
	//CItem *removeItem(int posItem);
	CItem *removeItem(int IDItem);
	CItem *removeItem(CItem *item);
	CItem *getItem(int IDItem);

	bool haveItem(CItem *item);
};
