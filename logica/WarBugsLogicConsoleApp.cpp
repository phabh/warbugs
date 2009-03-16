// WarBugsLogicConsoleApp.cpp : main project file.

//Classes necess�rias
#include <iostream>
#include <string>
using namespace std;

//Classes da l�gica
#include "CItem.cpp"
#include "CDoubleList.cpp"

using namespace System;

//Declara��o de objetos necess�rios
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
	cout << contadorObj.objCount << endl;
	cout << "COMPILOU!!!\n";
	system("PAUSE");
    return 0;
}