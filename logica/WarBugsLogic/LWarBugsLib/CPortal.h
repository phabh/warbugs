#pragma once

#include <iostream>
using namespace std;
#include "C3Dobject.h"

class CPortal : public C3DObject
{
private:
	int _ID;
	int _cenarioDestino;
	Ponto *_posicaoDestino;
public:
	CPortal *_next;

	CPortal();
	CPortal(int ID, int cenarioID, Ponto *posicao);
	CPortal(int ID, int cenarioID, int x, int y);
	CPortal(CPortal *base);
	int getID();
	int getDestiny();
	Ponto *getDestinyPoint();
	int getDestinyX();
	int getDestinyY();
	void setID(int value);
	void setDestiny(int value);
	void setDestinyPoint(int x, int y);
	void setDestinyX(int value);
	void setDestinyY(int value);
};
