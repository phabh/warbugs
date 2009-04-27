#pragma once

class CClientEquipment
{
private:
	int _arma;
	int _armadura;
public:
	CClientEquipment(void);
	CClientEquipment(int arma, int armadura);
	CClientEquipment(CClientEquipment * base);
	int getWeapon();
	int getArmor();
	void setWeapon(int indiceArma);
	void serArmor(int indiceArmadura);
};
