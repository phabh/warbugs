#pragma once

#include "CMenu.h"

class CMenuLogin : public CMenu
{

private:

	void graphicsDrawAddOn(){}

	void updateHuds()
	{
		_gerenciadorHud->clear();
		IGUIImage *img =_gerenciadorHud->addImage(rect<s32>(0, 0, _dispositivo->getVideoDriver()->getScreenSize().Width, _dispositivo->getVideoDriver()->getScreenSize().Height), 0, -1, L"");
		img->setImage(_gerenciadorVideo->getTexture("recursos/texturas/huds/tx2d_bg_login.jpg"));
		_gerenciadorHud->addEditBox(L"login", rect<s32>(300,500,400,520), true, 0, 10);
		_gerenciadorHud->addEditBox(L"senha", rect<s32>(300,530,400,550), true, 0, 20);
		_gerenciadorHud->addButton(rect<s32>(420,500,520,550), 0, 2, L"conectar");
	}

	void readCommands()
	{
		if(_gerenciadorEventos->isKeyDown(KEY_ESCAPE))
		{
			_nextID = SAIDA;
			return;
		}

		if(_gerenciadorEventos->getEventCallerByElement(EGET_BUTTON_CLICKED))
		{
			// Trata os cliques em botões

			if (_gerenciadorEventos->getEventCallerByID() == 2)
			{
				// Clicou no botão conectar
				_nextID = SELECAOPERSONAGEM;
				return;
			}
		}
	}

	void updateGraphics()
	{
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

		_myID = _nextID = LOGIN;
		//_arquivoCena = "recursos/cenas/login.irr";


		_dispositivo->setWindowCaption(L"Warbugs - BETA Version 0.1");

		_gerenciadorCena = _dispositivo->getSceneManager();   // Cria o gerenciador de cena
		_gerenciadorVideo = _dispositivo->getVideoDriver();   // Cria o driver para o vídeo
		_gerenciadorHud = _dispositivo->getGUIEnvironment(); // Cria o gerenciador de menu

		_musica = _gerenciadorAudio->play2D("recursos/audio/login.ogg", true, false, false, ESM_AUTO_DETECT);
		
		_gerenciadorAudio->setSoundVolume(cfg.parametrosAudio.volumeMusica);

		_gerenciadorCena->clear();
		//if(_arquivoCena)
		//	_gerenciadorCena->loadScene(_arquivoCena);
		
		_skin = _gerenciadorHud->getSkin();
		_font = _gerenciadorHud->getFont("recursos/fonts/font_georgia.png");
		
		if (_font)
			_skin->setFont(_font);

		_skin->setFont(_gerenciadorHud->getBuiltInFont(), EGDF_TOOLTIP);
		
		_camera = _gerenciadorCena->addCameraSceneNode(0,vector3df(0,50,0), vector3df(0,0,50));

		_flags[HUDCHANGED] = false;

		return (true);
	}
};
