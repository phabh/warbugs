#ifndef __CMenuLogin__
#define __CMenuLogin__

#include "CMenu.cpp"

class CMenuLogin : public CMenu
{

private:

	void updateHuds()
	{

		_gerenciadorHud->clear();
		_gerenciadorHud->addEditBox(L"login", rect<s32>(300,500,400,520), true, 0, 10);
		_gerenciadorHud->addEditBox(L"senha", rect<s32>(300,530,400,550), true, 0, 20);
		_gerenciadorHud->addButton(rect<s32>(420,500,520,550), 0, 30, L"conectar");
	}

	menuID updateCommands()
	{
		_timer->update();

		if(_gerenciadorEventos.getEventCallerByElement(EGET_BUTTON_CLICKED))
		{
			// Trata os cliques em botões

			if (_gerenciadorEventos.getEventCallerByID() == 30)
			{
				// Clicou no botão conectar
				_gerenciadorAudio->stopAllSounds();
				_dispositivo->drop();    // Deleta o dispositivo da memória
				_gerenciadorAudio->drop(); // Deleta o gerenciador de som da memória
				return SELECAOPERSONAGEM;
			}
		}

		return _myID;
	}

	void updateGraphics()
	{
		_timer->update();
	}
	

public:

	CMenuLogin(){}
	
	bool start()
	{

		//TypeCfg cfg, bool &created, menuID id, char* arquivo

		_gameCfg = new CArquivoConfig();
		TypeCfg cfg = _gameCfg->loadConfig();

		_dispositivo = createDevice(EDT_DIRECT3D9, 
		  							cfg.parametrosVideo.WindowSize, 
									cfg.parametrosVideo.Bits, 
									cfg.parametrosVideo.Fullscreen, 
									cfg.parametrosVideo.Stencilbuffer, 
									cfg.parametrosVideo.Vsync, 									
									&_gerenciadorEventos);

		if(!_dispositivo)
		{
			cout << "\nERRO 0x00: Falha ao criar dispositivo.";
			return(false);
		}
		else
		{
			_myID = LOGIN;
			_arquivoCena = "recursos/cenas/login.irr";
			_timer = new CTimer();
			_timer->initialize();

			_dispositivo->setWindowCaption(L"Warbugs - BETA Version 0.1");

			_gerenciadorCena = _dispositivo->getSceneManager();   // Cria o gerenciador de cena
			_gerenciadorVideo = _dispositivo->getVideoDriver();   // Cria o driver para o vídeo
			_gerenciadorHud = _dispositivo->getGUIEnvironment(); // Cria o gerenciador de menu
			_gerenciadorAudio = createIrrKlangDevice();

			_musica[0] = _gerenciadorAudio->play2D("recursos/audio/login.ogg", true, false, false, ESM_AUTO_DETECT);
			
			//_musicaFundo->setIsPaused(true);
			_gerenciadorAudio->setSoundVolume(cfg.parametrosAudio.volumeMusica);
			//	setVolume(cfg.parametrosAudio.volumeMusica);

			if(_arquivoCena)
				_gerenciadorCena->loadScene(_arquivoCena);
			
			_skin = _gerenciadorHud->getSkin();
			_font = _gerenciadorHud->getFont("recursos/fonts/font_georgia.png");
			
			if (_font)
				_skin->setFont(_font);

			_skin->setFont(_gerenciadorHud->getBuiltInFont(), EGDF_TOOLTIP);

			
			_camera = _gerenciadorCena->addCameraSceneNode(0,vector3df(0,50,0), vector3df(0,0,50));

			
		}
		return (true);
	}

	menuID run()
	{

		updateHuds();


		while(_dispositivo->run())
		{
			if (_dispositivo->isWindowActive())
			{
				_gerenciadorEventos.endEventProcess(); // Desativa a escuta de eventos para desenhar.
			
				// Start Render
				_gerenciadorVideo->beginScene(true, true, SColor(255, 0, 0, 0));
			
					_gerenciadorCena->drawAll(); 
					_gerenciadorHud->drawAll();
		
				_gerenciadorVideo->endScene();
				// Stop Render

				
			
				_timer->update();

				_myID = updateCommands();

				if(_myID != LOGIN)
					return(_myID);

				updateGraphics();

				if(_gerenciadorEventos.isKeyDown(KEY_ESCAPE))
				{
					_gerenciadorAudio->stopAllSounds();
					_dispositivo->drop();    // Deleta o dispositivo da memória
					_gerenciadorAudio->drop(); // Deleta o gerenciador de som da memória
					return SAIDA;
				}	

				_gerenciadorEventos.startEventProcess(); // Ativa a escuta de eventos.
			}
		}

		_gerenciadorAudio->stopAllSounds();
		_dispositivo->drop(); // Deleta o dispositivo da memória
		_gerenciadorAudio->drop(); // Deleta o gerenciador de som da memória
		return (SAIDA);
	}
};

#endif;