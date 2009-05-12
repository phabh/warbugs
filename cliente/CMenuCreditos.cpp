#pragma once

#include "CMenu.h"
#include "CHudFadingTextList.cpp"

class CMenuCreditos : public CMenu
{


private:

	CHudFadingTextList _creditos;

	UINT ThreadReadPackets(LPVOID lParam)
	{
		while(_nextID == _myID)
			cout << "\nLeu pacotes.\n";
		return 0;
	}

	void graphicsDrawAddOn(){}

	void updateHuds()
	{
		_gerenciadorHud->clear();
        
		_creditos.start(_gerenciadorHud, _font, rect<s32>(0,0,500,500), 255, 1);

		_gerenciadorHud->addButton(rect<s32>(320, 500, 450, 532), 0, 600, L"Sair");
	}

	void readCommands()
	{
		//_timer->update();
		if(_gerenciadorEventos->isKeyPressed(KEY_ESCAPE))
		{
			_nextID = SAIDA;
		    return;
		}

		if(_gerenciadorEventos->getEventCallerByElement(EGET_BUTTON_CLICKED))
		{
			// Trata os cliques em botões
			if (_gerenciadorEventos->getEventCallerByID() == 600)
			{
				_nextID = SAIDA;
				cout << "\nSAI!";
				return;
			}
		}
	}

	void updateGraphics()
	{
		_creditos.addText(L"Testando creditos");
		_creditos.addText(L"Testando creditos2");
	}

public:


	CMenuCreditos(){}
	
	bool start(IrrlichtDevice *grafico, ISoundEngine *audio)
	{
		_gameCfg = new CArquivoConfig();
		TypeCfg cfg = _gameCfg->loadConfig();

	    _dispositivo = grafico;
		_gerenciadorEventos = (CGerEventos*)_dispositivo->getEventReceiver();
		_gerenciadorAudio = audio;
		_gerenciadorAudio->removeAllSoundSources();

		_myID = _nextID = CREDITOS;
		_arquivoCena = "recursos/cenas/creditos.irr";

		_dispositivo->setWindowCaption(L"Warbugs - BETA Version 0.1");

		_gerenciadorCena = _dispositivo->getSceneManager();   // Cria o gerenciador de cena
		_gerenciadorVideo = _dispositivo->getVideoDriver();   // Cria o driver para o vídeo
		_gerenciadorHud = _dispositivo->getGUIEnvironment(); // Cria o gerenciador de menu

		_musica = _gerenciadorAudio->play2D("recursos/audio/creditos.ogg", true, false, false, ESM_AUTO_DETECT);
		
		_gerenciadorAudio->setSoundVolume(cfg.parametrosAudio.volumeMusica);

		_gerenciadorCena->clear();
		if(_arquivoCena)
			_gerenciadorCena->loadScene(_arquivoCena);
		
		_skin = _gerenciadorHud->getSkin();
		_font = _gerenciadorHud->getFont("recursos/fonts/font_georgia.png");
		
		if (_font)
			_skin->setFont(_font);

		_skin->setFont(_gerenciadorHud->getBuiltInFont(), EGDF_TOOLTIP);

		_camera = _gerenciadorCena->addCameraSceneNode(0,vector3df(0,50,0), vector3df(0,0,50));	

		ILightSceneNode *luz = _gerenciadorCena->addLightSceneNode(0, vector3df(100, 100, 100));

		_flags[HUDCHANGED] = false;

		return (true);
	}

	menuID run()
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
	}
};