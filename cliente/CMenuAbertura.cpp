#pragma once

#include "CMenu.h"
#include "IVideoTexture.h"

class CMenuAbertura : public CMenu
{

private:

	IVideoTexture *_video;

	UINT ThreadReadPackets(LPVOID lParam)
	{
		while(_nextID == _myID)
			cout << "\nLeu pacotes.\n";
		return 0;
	}
	
	void graphicsDrawAddOn() {}

	void updateHuds() {}

	void readCommands()	{}

	void updateGraphics() {}

public:

	CMenuAbertura(){}
	
	bool start(IrrlichtDevice *grafico, ISoundEngine *audio)
	{
		_gameCfg = new CArquivoConfig();
		TypeCfg cfg = _gameCfg->loadConfig();

	    _dispositivo = grafico;
		_gerenciadorEventos = (CGerEventos*)_dispositivo->getEventReceiver();

		_gerenciadorAudio = audio;
		_gerenciadorAudio->removeAllSoundSources();

		_myID = _nextID = ABERTURA;


		_dispositivo->setWindowCaption(L"Warbugs - BETA Version 0.1");

		_gerenciadorCena = _dispositivo->getSceneManager();   // Cria o gerenciador de cena
		_gerenciadorVideo = _dispositivo->getVideoDriver();   // Cria o driver para o vídeo
		_gerenciadorHud = _dispositivo->getGUIEnvironment();  // Cria o gerenciador de menu

        _flags[HUDCHANGED] = false;

		_video = IVideoTexture::createVideoTexture(_dispositivo, "recursos/videos/video.wmv");
		_video->setVolume(100);
		_video->playCutscene();
		_video->drop();

		_nextID = LOGIN;

		return (true);
	}
};

