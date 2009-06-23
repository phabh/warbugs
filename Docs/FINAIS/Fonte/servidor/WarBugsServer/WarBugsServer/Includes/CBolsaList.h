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
	CBolsa *removeBagAt(int pos);
	CBolsa *removeBag(int ID);
	CBolsa *removeSceneBag(int sceneID);
	//CBolsa *removeBolsa(CBolsa *Bolsa);
	CBolsa *getBag(int IDBolsa);
	CBolsa *getSceneBag(int sceneID);
	CBolsa *getElementAt(int index);

	bool haveBag(int ID);
};
