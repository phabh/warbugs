#pragma once

#include "CMenu.h"
#include "CVideoTexture.h"

#define eu reinterpret_cast<CMenuAbertura*>(lParam)

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
		_video = CVideoTexture::createVideoTexture(_dispositivo, "recursos/videos/video.wmv");
		_video->setVolume(100);
		_video->playCutscene();
		_video->drop();

		_nextID = LOGIN;
	}

public:

	CMenuAbertura(){}
	
	bool start(IrrlichtDevice *grafico, ISoundEngine *audio, CGameData *gameData)
	{
		_temPacote = false;
		_gameCfg = new CArquivoConfig();
		TypeCfg cfg = _gameCfg->loadConfig();

		_gameData = gameData;

	    _dispositivo = grafico;
		_gerenciadorEventos = (CGerEventos*)_dispositivo->getEventReceiver();

		_gerenciadorAudio = audio;
		_gerenciadorAudio->removeAllSoundSources();

		_myID = _nextID = ABERTURA;


		_dispositivo->setWindowCaption(L"Warbugs - BETA Version 0.1");

		_gerenciadorCena = _dispositivo->getSceneManager();   // Cria o gerenciador de cena
		_gerenciadorVideo = _dispositivo->getVideoDriver();   // Cria o driver para o vídeo
		_gerenciadorHud = _dispositivo->getGUIEnvironment();  // Cria o gerenciador de menu

        _flags[HUDCHANGED] = true;
/*
		_video = IVideoTexture::createVideoTexture(_dispositivo, "recursos/videos/video.wmv");
		_video->setVolume(100);
		_video->playCutscene();
		_video->drop();

		_nextID = LOGIN;*/

		return (true);
	}
};

