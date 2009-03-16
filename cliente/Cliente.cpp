#include "CMenu.cpp"
#include "CMenuAbertura.cpp"
#include "CMenuLogin.cpp"
#include "CMenuSelecao.cpp"

#include <iostream>

using namespace std;

int main()
{
	CMenu *menuCorrente;

	menuID nextMenu = ABERTURA;

	CTimer *timer = new CTimer();

	CArquivoConfig *gameCfg = new CArquivoConfig();
	gameCfg->reset();
	
	while(nextMenu != SAIDA && nextMenu != ERRO)
	{
		menuCorrente = NULL;

		switch (nextMenu)
		{
			case ABERTURA:

				menuCorrente = new CMenuAbertura();
				if( ((CMenuAbertura*)menuCorrente)->start())
					nextMenu = ((CMenuAbertura*)menuCorrente)->run();
				break;

			case LOGIN:

				menuCorrente = new CMenuLogin();
				if( ((CMenuLogin*)menuCorrente)->start())
					nextMenu = ((CMenuLogin*)menuCorrente)->run();
				break;

			case SELECAOPERSONAGEM:

				menuCorrente = new CMenuSelecao();
				if( ((CMenuSelecao*)menuCorrente)->start())
					nextMenu = ((CMenuSelecao*)menuCorrente)->run();
				break;

			case CRIACAOPERSONAGEM:
				break;

			case JOGO:
				break;

			case CREDITOS:
				break;
		};
	}

	return 1;
}