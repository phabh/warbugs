#pragma once

#include "Setup.h"
#include "CGameData.cpp"
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

	IrrlichtDevice *dispositivoGrafico; 
	ISoundEngine *dispositivoAudio;
	CGerEventos gerenciadorEventos;

	menuID nextMenu = ABERTURA;

	CArquivoConfig *gameCfg = new CArquivoConfig();

	TypeCfg cfg = gameCfg->loadConfig();

	RECT desktop; // Faz uma referência para a tela do desktop   
	const HWND hDesktop = GetDesktopWindow(); // Captura a dimensão da tela 
	GetWindowRect(hDesktop, &desktop);   

	cfg.parametrosVideo.WindowSize.Width = desktop.right;
	cfg.parametrosVideo.WindowSize.Height = desktop.bottom;
	cfg.parametrosVideo.Fullscreen = false;

	dispositivoGrafico = createDevice(EDT_DIRECT3D9, 
		  							cfg.parametrosVideo.WindowSize, 
									cfg.parametrosVideo.Bits, 
									cfg.parametrosVideo.Fullscreen, 
									cfg.parametrosVideo.Stencilbuffer, 
									cfg.parametrosVideo.Vsync, 									
									&gerenciadorEventos);


	if(!dispositivoGrafico)
	{
		cout << "\nERRO 0x00: Falha ao inicializar o dispositivo grafico.";
		nextMenu = SAIDA;
	}
		
	dispositivoAudio = createIrrKlangDevice();

	if(!dispositivoAudio)
	{
		cout << "\nERRO 0x01: Falha ao inicializar o dispositivo de audio.";
		nextMenu = SAIDA;
	}


	int estagio = 0;

	CGameData *_gameData= new CGameData();
	_gameData->start(dispositivoGrafico);

	while(estagio < 6)
	{
		_gameData->loadGameData(estagio);
	    estagio++;
	}



	while(nextMenu != SAIDA && nextMenu != ERRO)
	{
		menuCorrente = NULL;

		switch (nextMenu)
		{
			case ABERTURA:

				menuCorrente = new CMenuAbertura();
				if( ((CMenuAbertura*)menuCorrente)->start(dispositivoGrafico, dispositivoAudio))
					nextMenu = ((CMenuAbertura*)menuCorrente)->run();
				break;

			case LOGIN:

				menuCorrente = new CMenuLogin();
				if( ((CMenuLogin*)menuCorrente)->start(dispositivoGrafico, dispositivoAudio))
					nextMenu = ((CMenuLogin*)menuCorrente)->run();
				break;

			case SELECAOPERSONAGEM:

				menuCorrente = new CMenuSelecao();
				if( ((CMenuSelecao*)menuCorrente)->start(dispositivoGrafico, dispositivoAudio))
					nextMenu = ((CMenuSelecao*)menuCorrente)->run();
				break;

			case CRIACAOPERSONAGEM:
				menuCorrente = new CMenuCriacao();
				if( ((CMenuCriacao*)menuCorrente)->start(dispositivoGrafico, dispositivoAudio))
					nextMenu = ((CMenuCriacao*)menuCorrente)->run();
				break;

			case JOGO:
				menuCorrente = new CMenuJogo();
				if( ((CMenuJogo*)menuCorrente)->start(dispositivoGrafico, dispositivoAudio))
					nextMenu = ((CMenuJogo*)menuCorrente)->run();
				break;

			case CREDITOS:
				menuCorrente = new CMenuCreditos();
				if( ((CMenuCreditos*)menuCorrente)->start(dispositivoGrafico, dispositivoAudio))
					nextMenu = ((CMenuCreditos*)menuCorrente)->run();
				break;

			default:
				cout << "\nID de menu nao identificado." << endl;
		};
	}

	dispositivoGrafico->drop(); // Deleta o dispositivo grafico da memória
    dispositivoAudio->drop();   // Deleta o dispositivo de audio da memória

	return 1;
}