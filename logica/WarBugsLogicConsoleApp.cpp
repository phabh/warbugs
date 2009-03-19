// WarBugsLogicConsoleApp.cpp : main project file.

//Classes necess�rias
#include <iostream>
#include <string>
using namespace std;

//Classes da l�gica
#include "CConsumableItem.cpp"
#include "CScroll.cpp"
#include "CWeapon.cpp"
#include "CArmor.cpp"
#include "CDoubleList.cpp"

using namespace System;

//Declara��o de objetos necess�rios
CObjectCount *contadorObj = new CObjectCount();

int main(array<System::String ^> ^args)
{
	
	CWeapon *d = new CWeapon();
	CScroll *e = new CScroll();
	CArmor *f = new CArmor();
	CLealdade *g = new CLealdade();
	CLoyaltyScroll *h = new CLoyaltyScroll();
	
	d->initialize(contadorObj, ESCORPIAO, 1, 0, 0, 0, 0, 0, 0);
	e->initialize(contadorObj, 1, 10, 20, 30, 40, 50, 60);
	f->initialize(contadorObj, BESOURO, 0, 1, 0);

	/*TESTE DE UTILIZA��O DE SCROLL EM ARMADURA -> APROVADO!!!
	cout << "Defesa: " << f->getDef() << endl
		<< "Durabilidade: " << f->getDurability() << endl
		<< "Nivel Magico: " << f->getMagicLevel() << endl
		<<endl;
	f->useScroll(e);
	cout << "Defesa: " << f->getDef() << endl
		<< "Durabilidade: " << f->getDurability() << endl
		<< "Nivel Magico: " << f->getMagicLevel() << endl
		<<endl;*/
	

	/*TESTE DE UTILIZA��O DE SCROLL EM ARMA -> APROVADO!!!
	cout << "Modificador: " << d->getMod() << endl
	 << "Dano M�nimo: " << d->getMinDamage() << endl
	 << "Dano M�ximo: " << d->getMaxDamage() << endl
	 << "Velocidade: " << d->getSpeed() << endl
	 << "Alcance: " << d->getRange() << endl
	 << "Durabilidade: " << d->getDurability() << endl
	 << "Nivel Magico: " << d->getMagicLevel() << endl
	 << endl
	 << "Dados do pergaminho:" << endl
	 << "Modificador: " << e->getMod() << endl
	 << "Dano M�nimo: " << e->getMinDamage() << endl
	 << "Dano M�ximo: " << e->getMaxDamage() << endl
	 << "Velocidade: " << e->getSpeed() << endl
	 << "Alcance: " << e->getRange() << endl
	 << "Durabilidade: " << e->getDurability() << endl;

	d->useScroll(e);

	cout << "Dados do equip apos usar o pergaminho:" << endl
	 << "Modificador: " << d->getMod() << endl
	 << "Dano M�nimo: " << d->getMinDamage() << endl
	 << "Dano M�ximo: " << d->getMaxDamage() << endl
	 << "Velocidade: " << d->getSpeed() << endl
	 << "Alcance: " << d->getRange() << endl
	 << "Durabilidade: " << d->getDurability() << endl
	 << "Nivel Magico: " << d->getMagicLevel() << endl;

	e = new CScroll();
	e->initialize(contadorObj, 1, 10, 20, 30, 40, 50, 60);

	d->useScroll(e);

	cout << endl << "Dados do equip apos usar o pergaminho:" << endl
	 << "Modificador: " << d->getMod() << endl
	 << "Dano M�nimo: " << d->getMinDamage() << endl
	 << "Dano M�ximo: " << d->getMaxDamage() << endl
	 << "Velocidade: " << d->getSpeed() << endl
	 << "Alcance: " << d->getRange() << endl
	 << "Durabilidade: " << d->getDurability() << endl
	 << "Nivel Magico: " << d->getMagicLevel() << endl;*/

	
	cout << contadorObj->objCount << " objetos!!!!" << endl;
	cout << "COMPILOU!!!\n";
	system("PAUSE");
    return 0;
}