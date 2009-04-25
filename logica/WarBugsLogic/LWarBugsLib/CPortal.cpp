#include "CPortal.h"

CPortal::CPortal()
{
	_ID = 0;
	_cenarioDestino = 0;
	_posicaoDestino = NULL;
}
CPortal::CPortal(int ID, int cenarioID, Ponto *posicao)
{
	_ID = ID;
	_cenarioDestino = cenarioID;
	_posicaoDestino = posicao;
}
CPortal::CPortal(int ID, int cenarioID, int x, int y)
{
	_ID = ID;
	_cenarioDestino = cenarioID;
	_posicaoDestino->x = x;
	_posicaoDestino->y = y;
}
CPortal::CPortal(CPortal *base)
{
	_ID = base->getID();
	_cenarioDestino = base->getDestiny();
	_posicaoDestino = base->getDestinyPoint();
}
int CPortal::getID()
{
	return(_ID);
}
int CPortal::getDestiny()
{
	return(_cenarioDestino);
}
Ponto *CPortal::getDestinyPoint()
{
	return(_posicaoDestino);
}
int CPortal::getDestinyX()
{
	return(_posicaoDestino->x);
}
int CPortal::getDestinyY()
{
	return(_posicaoDestino->y);
}
void CPortal::setID(int value)
{
	_ID = value;
}
void CPortal::setDestiny(int value)
{
	_cenarioDestino = value;
}
void CPortal::setDestinyPoint(int x, int y)
{
	_posicaoDestino->x = x;
	_posicaoDestino->y = y;
}
void CPortal::setDestinyX(int value)
{
	_posicaoDestino->x = value;
}
void CPortal::setDestinyY(int value)
{
	_posicaoDestino->y = value;
}