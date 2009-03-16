#ifndef __CMenuSelecao__
#define __CMenuSelecao__

#include "CMenu.cpp"

enum flagSelecao {CHANGED, OBJSELECTED};

class CMenuSelecao : public CMenu
{

private:

	ISceneNode *_nodoSelecionado;
	int _idPersonagem;

	void updateHuds()
	{

		_gerenciadorHud->clear();
		_gerenciadorHud->addButton(rect<s32>(440,500,540,540), 0, 3, L"Criar");

		if(_flags[OBJSELECTED])
			_gerenciadorHud->addButton(rect<s32>(320,500,430,540), 0, 3, L"Jogar");

		_flags[CHANGED] = false;
	}

	menuID updateCommands()
	{
		_timer->update();

		if(_gerenciadorEventos.isMouseButtonReleased(MBLEFT))
		{
			// Clique com o botao esquerdo
						
			if(_flags[OBJSELECTED])
			{
				_flags[OBJSELECTED] = false; // Drop 3D
				_flags[CHANGED] = true;
			}
			else
			{
				_idPersonagem = -1;

				_nodoSelecionado = _gerenciadorCena->getSceneCollisionManager()->getSceneNodeFromScreenCoordinatesBB(_dispositivo->getCursorControl()->getPosition());

				if (_nodoSelecionado)
					_idPersonagem = _nodoSelecionado->getID();

				if(_idPersonagem > 0)
				{
				   _flags[OBJSELECTED] = true; // Get 3D
				   _flags[CHANGED] = true;
				}
			}
		}

		return _myID;
	}

	void updateGraphics()
	{
		_timer->update();
	}
	

public:

	CMenuSelecao(){}
	
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
			_myID = SELECAOPERSONAGEM;
			_arquivoCena = "recursos/cenas/selecao.irr";
			_timer = new CTimer();
			_timer->initialize();
			_nodoSelecionado = 0;
			_idPersonagem = -1;
			_flags[OBJSELECTED] = false;
			_flags[CHANGED] = false;

			_dispositivo->setWindowCaption(L"Warbugs - BETA Version 0.1");

			_gerenciadorCena = _dispositivo->getSceneManager();   // Cria o gerenciador de cena
			_gerenciadorVideo = _dispositivo->getVideoDriver();   // Cria o driver para o vídeo
			_gerenciadorHud = _dispositivo->getGUIEnvironment(); // Cria o gerenciador de menu
			_gerenciadorAudio = createIrrKlangDevice();

			_musica[0] = _gerenciadorAudio->play2D("recursos/audio/selecao.ogg", true, false, false, ESM_AUTO_DETECT);
			
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

				if(_myID != SELECAOPERSONAGEM)
					return(_myID);

				updateGraphics();

				if(_flags[CHANGED])
					updateHuds();

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