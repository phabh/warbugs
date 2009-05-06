#pragma once
#include <iostream>
using namespace std;
#include "Enumerators.h"
#include "CItem.h"

typedef SCelula<CItem> SElemento;

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
	CItem *removeItemByPosition(int posItem);
	CItem *removeItem(int IDItem);
	CItem *removeItem(CItem *item);
	CItem *getItem(int IDItem);

	bool haveItem(CItem *item);
};
