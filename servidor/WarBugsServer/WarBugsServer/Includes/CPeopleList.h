#pragma once
#include "Enumerators.h"

#ifndef _CPERSONAGEM_H_
#include "CPersonagem.h"
#ifndef _CPERSONAGEM_H_
class CPersonagem;
#endif
#endif

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
	CPersonagem *removePersonagemAt(int pos);
	CPersonagem *removePersonagem(int ID);
	CPersonagem *removeScenePersonagem(int sceneID);
	//CPersonagem *removePersonagem(CPersonagem *personagem);
	CPersonagem *getPersonagem(int IDpersonagem);
	CPersonagem *getScenePersonagem(int sceneID);
	CPersonagem *getElementAt(int index);

	bool havePersonagem(int ID);
};
