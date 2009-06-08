#include "CMenu.h"

TypeMenuID CMenu::run()
{
	ITimer *cronometroMS = _dispGrafico->getTimer(); 

	u32 tempoInicial,
		tempoCorrido;

	updateHuds();

	while(_dispGrafico->run())
	{
		tempoInicial = cronometroMS->getRealTime(); // Milisegundos

		if(_myID == MN_JOGO)
		{
			receivePackages();
		}

		if (_dispGrafico->isWindowActive())
		{
			_gerEventos->endEventProcess(); // Desativa a escuta de eventos para desenhar.

			_gerVideo->beginScene(true, true, SColor(255, 0, 0, 0));
			_gerCena->drawAll(); 
			_gerHud->drawAll();
			graphicsDrawAddOn();
			_gerVideo->endScene();

			readCommands();

			updateGraphics();

			if(!_menuFlag[HUDUPDATED])
			{
				// Se o HUD não estiver atualizado
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
					_dispGrafico->sleep(33 - tempoCorrido); // Adormece para manter o FPS
			}

			// Ativa a escuta de eventos. SEMPRE deve ser a última linha do while.
			_gerEventos->startEventProcess(); 
		}
	}
	_dispAudio->stopAllSounds();

	return _nextID;
}