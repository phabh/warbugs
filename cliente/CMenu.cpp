#pragma once

#include "CMenu.h"

menuID CMenu::run()
{
	ITimer *cronometroMS = _dispositivo->getTimer(); 

	u32 tempoInicial,
		tempoCorrido;

	updateHuds();

	while(_dispositivo->run())
	{
		tempoInicial = cronometroMS->getRealTime(); // Milisegundos

		if(_myID > ABERTURA && _myID < CREDITOS)
		{
			//Ler pacotes
		}

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
			{
				// Se for necessário redesenhar o HUD
				updateHuds();
			}

			if(_nextID != _myID)
			{
				// Solicitou troca de Menu
				break;
			}
			else
			{
				tempoCorrido = cronometroMS->getRealTime() - tempoInicial;

				if(tempoCorrido < 33) // 30ms = 1000/30
					_dispositivo->sleep(33 - tempoCorrido); // Adormece para manter o FPS
			}

			// Ativa a escuta de eventos. SEMPRE deve ser a última linha do while.
			_gerenciadorEventos->startEventProcess(); 
		}
	}

	_gerenciadorAudio->stopAllSounds();
	return _nextID;
}