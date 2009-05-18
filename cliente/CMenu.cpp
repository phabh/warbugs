#pragma once

#include "CMenu.h"

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
			}

			_gerenciadorEventos->startEventProcess(); // Ativa a escuta de eventos.
		}
	}

	_gerenciadorAudio->stopAllSounds();
	return _nextID;
}