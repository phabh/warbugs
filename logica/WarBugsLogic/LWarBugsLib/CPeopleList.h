#pragma once
#include "CPersonagem.h"
#include <iostream>
using namespace std;

typedef struct SCharCelula
{
	CPersonagem *personagem;
	SCharCelula *prev;
	SCharCelula *next;
} SCharElemento;


class CPeopleList
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
	CPersonagem *removePersonagem(int IDpersonagem);
	CPersonagem *removePersonagem(CPersonagem *personagem);
	CPersonagem *getPersonagem(int IDpersonagem);

	bool havePersonagem(CPersonagem *personagem);
};
