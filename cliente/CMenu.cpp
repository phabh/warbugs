#pragma once

#include "CMenu.h"
/*
menuID CMenu::run()
{
	
	HANDLE hThrd[2]; // Cria referências para as threads
	DWORD IDThread1, IDThread2; // Variáveis para guardar os IDs das threads
		
	InitializeCriticalSection(&m_cs); // Inicializar sessão crítica

	// Criar threads usando a função CreateThread
	hThrd[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) ThreadIrrlicht, (LPVOID)NULL, 0, &IDThread1);       
	hThrd[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) ThreadReadPackets, (LPVOID)NULL, 0, &IDThread2); 
	
	WaitForMultipleObjects(2, hThrd, TRUE, INFINITE); // Esperar a execução da thread principal (tempo infinito)

	DeleteCriticalSection(&m_cs); // Deletar a sessão crítica

	return _nextID;
}*/
/*

void CMenu::ThreadIrrlicht(LPVOID lParam)
{
	updateHuds();

	while(_dispositivo->run())
	{
		if (_dispositivo->isWindowActive())
		{
			_gerenciadorEventos->endEventProcess(); // Desativa a escuta de eventos para desenhar.
		
			_gerenciadorVideo->beginScene(true, true, SColor(255, 0, 0, 0));
				_gerenciadorCena->drawAll(); 
				_gerenciadorHud->drawAll();
				graphicsDrawAddOn();
			_gerenciadorVideo->endScene();

			readCommands();

			updateGraphics();

			if(_flags[HUDCHANGED])
				updateHuds();

			if(_nextID != _myID)
			{
				break;
				//return _nextID;
			}

			_gerenciadorEventos->startEventProcess(); // Ativa a escuta de eventos.
		}
	}

	_gerenciadorAudio->stopAllSounds();

	//return 0;
}

void CMenu::ThreadReadPackets(LPVOID lParam)
{
	while(_nextID == _myID)
		cout << "\nLeu pacotes0.\n";
	//return 0;
}*/
/*
menuID CMenu::run()
{
	updateHuds();

	while(_dispositivo->run())
	{
		if (_dispositivo->isWindowActive())
		{
			_gerenciadorEventos->endEventProcess(); // Desativa a escuta de eventos para desenhar.
		
			_gerenciadorVideo->beginScene(true, true, SColor(255, 0, 0, 0));
				_gerenciadorCena->drawAll(); 
				_gerenciadorHud->drawAll();
				graphicsDrawAddOn();
			_gerenciadorVideo->endScene();

			readCommands();

			updateGraphics();

			if(_flags[HUDCHANGED])
				updateHuds();

			if(_nextID != _myID)
			{
				break;
				//return _nextID;
			}

			_gerenciadorEventos->startEventProcess(); // Ativa a escuta de eventos.
		}
	}

	_gerenciadorAudio->stopAllSounds();
	return _nextID;
}*/