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

	void updateCommands()
	{
		_timer->update();

		if(_gerenciadorEventos->getEventCallerByElement(EGET_BUTTON_CLICKED))
		{
			// Trata os cliques em botões

			if (_gerenciadorEventos->getEventCallerByID() == 30)
			{
				// Clicou no botão conectar
				_myID = SELECAOPERSONAGEM;
			}
		}
	}

	void updateGraphics()
	{
		_timer->update();
	}
	

public:

	CMenuLogin(){}
	
	bool start(IrrlichtDevice *grafico, ISoundEngine *audio)
	{

		_gameCfg = new CArquivoConfig();
		TypeCfg cfg = _gameCfg->loadConfig();

	    _dispositivo = grafico;
		_gerenciadorEventos = (CGerEventos*)_dispositivo->getEventReceiver();
		_gerenciadorAudio = audio;
		_gerenciadorAudio->removeAllSoundSources();

		_myID = LOGIN;
		_arquivoCena = "recursos/cenas/login.irr";
		_timer = new CTimer();
		_timer->initialize();

		_dispositivo->setWindowCaption(L"Warbugs - BETA Version 0.1");

		_gerenciadorCena = _dispositivo->getSceneManager();   // Cria o gerenciador de cena
		_gerenciadorVideo = _dispositivo->getVideoDriver();   // Cria o driver para o vídeo
		_gerenciadorHud = _dispositivo->getGUIEnvironment(); // Cria o gerenciador de menu

		_musica[0] = _gerenciadorAudio->play2D("recursos/audio/login.ogg", true, false, false, ESM_AUTO_DETECT);
		
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
			
				// Start Render
				_gerenciadorVideo->beginScene(true, true, SColor(255, 0, 0, 0));
			
					_gerenciadorCena->drawAll(); 
					_gerenciadorHud->drawAll();
		
				_gerenciadorVideo->endScene();
				// Stop Render

				
			
				_timer->update();

				updateCommands();

				if(_myID != LOGIN)
					return _myID;

				updateGraphics();

				if(_gerenciadorEventos->isKeyDown(KEY_ESCAPE))
				{
					_myID = SAIDA;
					return _myID;
				}	

				_gerenciadorEventos->startEventProcess(); // Ativa a escuta de eventos.
			}
		}

		_gerenciadorAudio->stopAllSounds();
		return _myID;
	}
};

#endif;