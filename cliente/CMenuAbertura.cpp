#ifndef __CMenuAbertura__
#define __CMenuAbertura__

#include "CMenu.cpp"

class CMenuAbertura : public CMenu
{

private:

protected:

	void hudRefresh()
	{
		_gerenciadorCena->addTextSceneNode(_gerenciadorHud->getBuiltInFont(), 
										   L"TESTE!!!!!!!!",
										   SColor(255,255,255,255),
										   0, vector3df(0,0,0));
	}

	void update()
	{
	}
	

public:

	CMenuAbertura(){}
	
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
			_myID = ABERTURA;
			_arquivoCena = "recursos/cenas/abertura.irr";
			_timer = new CTimer();
			_timer->initialize();

			_dispositivo->setWindowCaption(L"Warbugs - BETA Version 0.1");

			_gerenciadorCena = _dispositivo->getSceneManager();   // Cria o gerenciador de cena
			_gerenciadorVideo = _dispositivo->getVideoDriver();   // Cria o driver para o vídeo
			_gerenciadorHud = _dispositivo->getGUIEnvironment(); // Cria o gerenciador de menu
			_gerenciadorAudio = createIrrKlangDevice();

			_musicaFundo = _gerenciadorAudio->play2D("recursos/audio/abertura.ogg", true, false, false, ESM_AUTO_DETECT);
			
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

	menuID execute()
	{

		hudRefresh();


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

				_gerenciadorEventos.startEventProcess(); // Ativa a escuta de eventos.
			
				_timer->update();

				update();


				if(_gerenciadorEventos.isKeyDown(KEY_ESCAPE))
				{
					//Sleep(5000);
					_dispositivo->drop();    // Deleta o dispositivo da memória
					_gerenciadorAudio->drop(); // Deleta o gerenciador de som da memória
					return SAIDA;
				}	
			}
		}

		_dispositivo->drop(); // Deleta o dispositivo da memória
		_gerenciadorAudio->drop(); // Deleta o gerenciador de som da memória
		return (ERRO);
	}

};

#endif;