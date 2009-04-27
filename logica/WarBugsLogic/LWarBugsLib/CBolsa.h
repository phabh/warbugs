#pragma once
#include <iostream>
using namespace std;
#include "CItem.h"

class CBolsa : C3DObject
{
private:
	CItem *_item;
	CBolsa *_next;
	int _size;

public:
	CBolsa(void);
	CBolsa(CBolsa * base);
	CBolsa(CItem * item);

	CItem *getThis();
	CBolsa *getNext();
	void setThis(CItem *item);
	void setNext(CBolsa *next);

	bool isEmpty();
	int size();
	void addItem(CItem *item);
	CItem *removeItem(int IDItem);
	CItem *getItem(intIDItem);
};
