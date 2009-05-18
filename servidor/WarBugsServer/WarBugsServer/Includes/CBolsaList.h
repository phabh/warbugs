#pragma once
#include <iostream>
using namespace std;
#include "Enumerators.h"
#include "CBolsa.h"

typedef SCelula<CBolsa> SBagElemento;

class CBolsaList : public CWarBugObject
{
private:
	SBagElemento *_first;
	int _size;

public:
	CBolsaList(void);
	CBolsaList(CBolsa * Bolsa);

	bool isEmpty();
	int size();
	void addBag(CBolsa *Bolsa);
	CBolsa *removeBolsaByPosition(int pos);
	CBolsa *removeBolsa(int ID);
	//CBolsa *removeBolsa(CBolsa *Bolsa);
	CBolsa *getBolsa(int IDBolsa);
	CBolsa *getElementAt(int index);

	bool haveBolsa(int ID);
};
