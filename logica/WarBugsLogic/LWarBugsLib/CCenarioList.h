#pragma once
#include <iostream>
using namespace std;
#include "Enumerators.h"
#include "CCenario.h"

typedef SCelula<CCenario> SCenarioElemento;

class CCenarioList : public CWarBugObject
{
private:
	SCenarioElemento *_first;
	int _size;

public:
	CCenarioList(void);
	CCenarioList(CCenario * Cenario);

	bool isEmpty();
	int size();
	void addCenario(CCenario *Cenario);
	CCenario *removeCenarioByPosition(int pos);
	CCenario *removeCenario(int ID);
	//CCenario *removeCenario(CCenario *Cenario);
	CCenario *getCenario(int IDCenario);
	CCenario *getElementAt(int index);

	bool haveCenario(int ID);

	void update();
};

