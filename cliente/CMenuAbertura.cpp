#ifndef __CMenuAbertura__
#define __CMenuAbertura__

#include "CMenu.cpp"

class CMenuAbertura : public CMenu
{


private:

	void updateHuds()
	{
		_gerenciadorHud->clear();
		_gerenciadorHud->addButton(rect<s32>(320, 500, 450, 532), 0, 100, L"pular video");
	}

	menuID updateCommands()
	{
		_timer->update();
		
		if(_gerenciadorEventos.getEventCallerByElement(EGET_BUTTON_CLICKED))
		{
			// Trata os cliques em botões

			if (_gerenciadorEventos.getEventCallerByID() == 100)
			{
				// Clicou no botão 1 (pular video)
				_gerenciadorAudio->stopAllSounds();
				_dispositivo->drop();    // Deleta o dispositivo da memória
				_gerenciadorAudio->drop(); // Deleta o gerenciador de som da memória
				return LOGIN;
			}
		}

		return _myID;
	}

	void updateGraphics()
	{
		_timer->update();
	}
	

public:

	CMenuAbertura(){}
	
	bool start()
	{
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
			_myID = ABERTURA;
			_arquivoCena = "recursos/cenas/abertura.irr";
			_timer = new CTimer();
			_timer->initialize();

			_dispositivo->setWindowCaption(L"Warbugs - BETA Version 0.1");

			_gerenciadorCena = _dispositivo->getSceneManager();   // Cria o gerenciador de cena
			_gerenciadorVideo = _dispositivo->getVideoDriver();   // Cria o driver para o vídeo
			_gerenciadorHud = _dispositivo->getGUIEnvironment(); // Cria o gerenciador de menu
			_gerenciadorAudio = createIrrKlangDevice();

			_musica[0] = _gerenciadorAudio->play2D("recursos/audio/abertura.ogg", true, false, false, ESM_AUTO_DETECT);
			
			_gerenciadorAudio->setSoundVolume(cfg.parametrosAudio.volumeMusica);

			if(_arquivoCena)
				_gerenciadorCena->loadScene(_arquivoCena);
			
			_skin = _gerenciadorHud->getSkin();
			_font = _gerenciadorHud->getFont("recursos/fonts/font_georgia.png");
			
			if (_font)
				_skin->setFont(_font);

			_skin->setFont(_gerenciadorHud->getBuiltInFont(), EGDF_TOOLTIP);
	
			_camera = _gerenciadorCena->addCameraSceneNode(0,vector3df(0,50,0), vector3df(0,0,50));	

			ILightSceneNode *luz = _gerenciadorCena->addLightSceneNode(0, vector3df(100, 100, 100));

			_toonShader = new CToonShader(_dispositivo, luz);

			ISceneNode *modelo = _gerenciadorCena->addMeshSceneNode(_gerenciadorCena->getMesh("recursos/modelos/besouro.dae"));
			modelo->setPosition(vector3df(0,20,50));
			modelo->setRotation(vector3df(-90,0,0));
			modelo->setScale(vector3df(3,3,3));


			_toonShader->apply(modelo, "recursos/texturas/besouro.jpg");

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
	
				_myID = updateCommands();

				if(_myID != ABERTURA)
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