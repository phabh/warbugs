#include "CPortal.h"

CPortal::CPortal()
{
	setID(-1);
	_cenarioDestino = 0;
	_posicaoDestino = NULL;
}
CPortal::CPortal(int ID, int cenarioID, Ponto *posicao)
{
	setID(ID);
	_cenarioDestino = cenarioID;
	_posicaoDestino = posicao;
}
CPortal::CPortal(int ID, int cenarioID, float x, float z)
{
	setID(ID);
	_cenarioDestino = cenarioID;
	_posicaoDestino->x = x;
	_posicaoDestino->z = z;
}
CPortal::CPortal(CPortal *base)
{
	setID(base->getID());
	_cenarioDestino = base->getDestiny();
	_posicaoDestino = base->getDestinyPoint();
}
int CPortal::getDestiny()
{
	return(_cenarioDestino);
}
Ponto *CPortal::getDestinyPoint()
{
	return(_posicaoDestino);
}
float CPortal::getDestinyX()
{
	return(_posicaoDestino->x);
}
float CPortal::getDestinyZ()
{
	return(_posicaoDestino->z);
}
void CPortal::setDestiny(int value)
{
	_cenarioDestino = value;
}
void CPortal::setDestinyPoint(float x, float z)
{
	_posicaoDestino->x = x;
	_posicaoDestino->z = z;
}
void CPortal::setDestinyX(float value)
{
	_posicaoDestino->x = value;
}
void CPortal::setDestinyZ(float value)
{
	_posicaoDestino->z = value;
}