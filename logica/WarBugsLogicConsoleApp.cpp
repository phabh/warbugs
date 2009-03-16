// WarBugsLogicConsoleApp.cpp : main project file.

//Classes necessárias
#include <iostream>
#include <string>
using namespace std;

//Classes da lógica
#include "CConsumableItem.cpp"
#include "CScroll.cpp"
#include "CWeapon.cpp"
#include "CDoubleList.cpp"

using namespace System;

//Declaração de objetos necessários
CObjectCount contadorObj;

int main(array<System::String ^> ^args)
{
	CDoubleList a;
	a.initialize(contadorObj);
	cout << a.getID() << endl;

	CDoubleList b;
	b.initialize(contadorObj);
	cout << b.getID() << endl;

	CDoubleList c;
	c.initialize(contadorObj);
	cout << c.getID() << endl;

	CWeapon d;
	d.initialize(contadorObj, ESCORPIAO, 1, 10, 20, 3, 10, 30, 0);
	cout << d.getID() << endl;

	CScroll e;
	e.initialize(contadorObj, 1, 0, 0, 0, 0, 0, 0);
	cout << e.getID()<< endl;
	
	cout << contadorObj.objCount << " objetos!!!!" << endl;
	cout << "COMPILOU!!!\n";
	system("PAUSE");
    return 0;
}