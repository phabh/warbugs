#pragma once

#include "CMenu.h"
#include "CVideoTexture.h"

class CMenuAbertura : public CMenu
{
	
private:

	CVideoTexture *_video;
	
	void graphicsDrawAddOn() {}

	void updateHuds() 
	{
		_flags[HUDCHANGED] = false;
	}

	void readCommands()	{}

	void updateGraphics() 
	{
		_video = CVideoTexture::createVideoTexture(_dispositivo, pathVideoAbertura);
		_video->setVolume(100);
		_video->playCutscene();
		_video->drop();

		_nextID = MN_LOGIN;
	}

public:

	CMenuAbertura(){}
	
	bool start(CGameCore *gameCore)
	{
		_temPacote = false;
		_gameCfg = new CArquivoConfig();
		TypeCfg cfg = _gameCfg->loadConfig();

		//_gameData = gameData;

	    _dispositivo      = gameCore->getGraphicDevice();
		_gerenciadorAudio = gameCore->getSoundDevice();

		_gerenciadorAudio->removeAllSoundSources();
		_gerenciadorEventos = (CGerEventos*)_dispositivo->getEventReceiver();

		_myID = _nextID = MN_ABERTURA;

		_dispositivo->setWindowCaption(L"Warbugs - BETA Version 0.1");

		_gerenciadorCena = _dispositivo->getSceneManager();   // Cria o gerenciador de cena
		_gerenciadorVideo = _dispositivo->getVideoDriver();   // Cria o driver para o vídeo
		_gerenciadorHud = _dispositivo->getGUIEnvironment();  // Cria o gerenciador de menu

        _flags[HUDCHANGED] = true;
/*
		_video = CVideoTexture::createVideoTexture(_dispositivo, "recursos/videos/movie.wmv");
		_video->setVolume(100);
		_video->playCutscene();
		_video->drop();

		_nextID = MN_LOGIN;*/

		return (true);
	}
};

