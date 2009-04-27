#include "CClientEquipment.h"

CClientEquipment::CClientEquipment(void)
{
	_arma = -1;
	_armadura = -1;
}
CClientEquipment::CClientEquipment(int arma, int armadura)
{
	_arma = arma;
	_armadura = armadura;
}
CClientEquipment::CClientEquipment(CClientEquipment * base)
{
	_arma = base->getArma();
	_armadura = base->getArmadura();
}
int CClientEquipment::getWeapon()
{
	return(_arma);
}
int CClientEquipment::getArmor()
{
	return(_armadura);
}
void CClientEquipment::setWeapon(int indiceArma)
{
	_arma = indiceArma;
}
void CClientEquipment::serArmor(int indiceArmadura)
{
	_armadura = indiceArmadura;
}
