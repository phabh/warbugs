//#include <windows.h>
#include "CMenu.cpp"
#include "CMenuAbertura.cpp"
#include "CMenuLogin.cpp"

#include <iostream>

using namespace std;

int main()
{
	bool sucesso = true;
	menuID nextMenu = ABERTURA;

	CTimer *timer = new CTimer();

	//CArquivoConfig *gameCfg = new CArquivoConfig();
	//gameCfg->reset();

	CMenu *menuCorrente;
	
	while(nextMenu != SAIDA || nextMenu != ERRO)
	{
		menuCorrente = NULL;

		switch (nextMenu)
		{
			case ABERTURA:

				/*(CMenuAbertura*)*/menuCorrente = new CMenuAbertura();
				if( ((CMenuAbertura*)menuCorrente)->start())
					nextMenu = ((CMenuAbertura*)menuCorrente)->execute();
				break;

			case LOGIN:

				/*(CMenuLogin*)*/menuCorrente = new CMenuLogin();
				if( ((CMenuLogin*)menuCorrente)->start())
					nextMenu = ((CMenuLogin*)menuCorrente)->execute();
				break;

			case SELECAOPERSONAGEM:
				break;

			case CRIACAOPERSONAGEM:
				break;

			case JOGO:
				break;

			case CREDITOS:
				break;
		};
	}


	
	cout << "\n" << nextMenu << endl;

	return 1;
}