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
	CPortal(int ID, int cenarioID, float x, float z);
	CPortal(CPortal *base);
	int getID();
	int getDestiny();
	Ponto *getDestinyPoint();
	float getDestinyX();
	float getDestinyZ();
	void setID(int value);
	void setDestiny(int value);
	void setDestinyPoint(float x, float z);
	void setDestinyX(float value);
	void setDestinyZ(float value);
};
