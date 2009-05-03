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
	void addBolsa(CBolsa *Bolsa);
	//CBolsa *removeBolsa(int posBolsa);
	CBolsa *removeBolsa(int IDBolsa);
	CBolsa *removeBolsa(CBolsa *Bolsa);
	CBolsa *getBolsa(int IDBolsa);

	bool haveBolsa(CBolsa *Bolsa);
};
