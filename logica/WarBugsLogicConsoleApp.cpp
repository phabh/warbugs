// WarBugsLogicConsoleApp.cpp : main project file.

//Classes necessárias
#include <iostream>
#include <string>
using namespace std;

//Classes da lógica
#include "CItem.cpp"
#include "CDoubleList.cpp"

using namespace System;

//Declaração de objetos necessários
CObjectCount contadorObj;

int main(array<System::String ^> ^args)
{
	CDoubleList a;
	a.inicializar(contadorObj);
	cout << a.getID() << endl;
	CDoubleList b;
	b.inicializar(contadorObj);
	cout << b.getID() << endl;
	CDoubleList c;
	c.inicializar(contadorObj);
	cout << c.getID() << endl;
	cout << contadorObj.objCount << endl;
	cout << "COMPILOU!!!\n";
	system("PAUSE");
    return 0;
}