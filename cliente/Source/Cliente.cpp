#pragma once

#include "Setup.h"
#include "CGameCore.h"
#include "CMenu.h"
#include "CMenuAbertura.cpp"
#include "CMenuLogin.cpp"
#include "CMenuSelecao.cpp"
#include "CMenuCriacao.cpp"
#include "CMenuJogo.cpp" 
#include "CMenuCreditos.cpp"

int main()
{
	CMenu *menuCorrente;

	int feedbackInit;

	CGameCore *Warbugs = new CGameCore(feedbackInit); // Inicializa a engine e retorna o feedback

	if(feedbackInit == SUCESSO)
	{
		Warbugs->loadGameData(); // Carrega os dados do jogo na memória

		menuID nextMenu = MN_ABERTURA;

		while(nextMenu != MN_SAIDA && nextMenu != MN_ERRO)
		{
			menuCorrente = NULL;

			switch (nextMenu)
			{

			case MN_ABERTURA:

				menuCorrente = new CMenuAbertura();
				if( ((CMenuAbertura*)menuCorrente)->start(Warbugs))
					nextMenu = ((CMenuAbertura*)menuCorrente)->run();
				break;

			case MN_LOGIN:

				menuCorrente = new CMenuLogin();
				if( ((CMenuLogin*)menuCorrente)->start(Warbugs/*dispositivoGrafico, dispositivoAudio, gameData*/))
					nextMenu = ((CMenuLogin*)menuCorrente)->run();
				break;

			case MN_SELECAOPERSONAGEM:

				menuCorrente = new CMenuSelecao();
				if( ((CMenuSelecao*)menuCorrente)->start(Warbugs/*dispositivoGrafico, dispositivoAudio, gameData*/))
					nextMenu = ((CMenuSelecao*)menuCorrente)->run();
				break;

			case MN_CRIACAOPERSONAGEM:
				menuCorrente = new CMenuCriacao();
				if( ((CMenuCriacao*)menuCorrente)->start(Warbugs/*dispositivoGrafico, dispositivoAudio, gameData*/))
					nextMenu = ((CMenuCriacao*)menuCorrente)->run();
				break;

			case MN_JOGO:
				menuCorrente = new CMenuJogo();
				if( ((CMenuJogo*)menuCorrente)->start(Warbugs/*dispositivoGrafico, dispositivoAudio, gameData*/))
					nextMenu = ((CMenuJogo*)menuCorrente)->run();
				break;

			case MN_CREDITOS:
				menuCorrente = new CMenuCreditos();
				if( ((CMenuCreditos*)menuCorrente)->start(Warbugs/*dispositivoGrafico, dispositivoAudio, gameData*/))
					nextMenu = ((CMenuCreditos*)menuCorrente)->run();
				break;

			default:
				cout << "\nID de menu nao identificado." << endl;
			};
		}

		Warbugs->drop(); // Descarrega dispositivos gráficos e sonoros.

		return 1;
	}
	else
	{
		system("pause");
		return 0;
	}
}