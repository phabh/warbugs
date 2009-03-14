//#include <windows.h>
#include "CMenu.cpp"

#include <iostream>

using namespace std;

int main()
{
	bool sucesso = true;
	int nextMenu;

	CTimer *timer = new CTimer();


	CArquivoConfig *gameCfg = new CArquivoConfig();


	gameCfg->reset();

	CMenu *listaMenus;

	listaMenus = new CMenu( gameCfg->loadConfig(), sucesso, LOGIN, "recursos/cenas/login.irr" );

	if(sucesso)
		nextMenu = listaMenus->execute();


	
	cout << "\n" << nextMenu << endl;

	return 1;
}