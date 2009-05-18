#pragma once
#include "Enumerators.h"
#include "CPersonagem.h"
#include <iostream>
using namespace std;

typedef SCelula<CPersonagem> SCharElemento;

class CPeopleList : public CWarBugObject
{
private:
	SCharElemento *_first;
	int _size;

public:
	CPeopleList(void);
	CPeopleList(CPersonagem * personagem);

	bool isEmpty();
	int size();
	void addPersonagem(CPersonagem *personagem);
	CPersonagem *removePersonagemByPosition(int pos);
	CPersonagem *removePersonagem(int ID);
	//CPersonagem *removePersonagem(CPersonagem *personagem);
	CPersonagem *getPersonagem(int IDpersonagem);
	CPersonagem *getElementAt(int index);

	bool havePersonagem(int ID);
};
