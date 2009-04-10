#ifndef __CMenuCreditos__
#define __CMenuCreditos__

#include "CMenu.cpp"
#include "CHudFadingTextList.cpp"

class CMenuCreditos : public CMenu
{


private:

	CHudFadingTextList _creditos;

	void updateHuds()
	{
		_gerenciadorHud->clear();
        
		_creditos.start(_gerenciadorHud, _font, rect<s32>(0,0,500,500), 255, 1);

		_gerenciadorHud->addButton(rect<s32>(320, 500, 450, 532), 0, 500, L"Sair");
	}

	void updateCommands()
	{
		_timer->update();
		
		if(_gerenciadorEventos->getEventCallerByElement(EGET_BUTTON_CLICKED))
			if (_gerenciadorEventos->getEventCallerByID() == 500)
				_myID = SAIDA;
	}

	void updateGraphics()
	{
		_timer->update();

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

		_myID = CREDITOS;
		_arquivoCena = "recursos/cenas/creditos.irr";
		_timer = new CTimer();
		_timer->initialize();

		_dispositivo->setWindowCaption(L"Warbugs - BETA Version 0.1");

		_gerenciadorCena = _dispositivo->getSceneManager();   // Cria o gerenciador de cena
		_gerenciadorVideo = _dispositivo->getVideoDriver();   // Cria o driver para o vídeo
		_gerenciadorHud = _dispositivo->getGUIEnvironment(); // Cria o gerenciador de menu

		_musica[0] = _gerenciadorAudio->play2D("recursos/audio/creditos.ogg", true, false, false, ESM_AUTO_DETECT);
		
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

		return (true);
	}

	menuID run()
	{

		updateHuds();


		int i = 0;

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
	
				updateCommands();

				if(_myID != CREDITOS)
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