#ifndef __CMenu__
#define __CMenu__

#include "irrlicht.h"
#include "irrklang.h"

#include "CArquivoConfig.cpp"
#include "CGerEventos.cpp"
#include "CTimer.cpp"

#include <iostream>

using namespace std; 

using namespace irr; 
using namespace core; 
using namespace scene; 
using namespace video; 
using namespace io; 
using namespace gui;

using namespace irrklang;

#pragma comment(lib, "Irrlicht.lib")
#pragma comment(lib, "irrKlang.lib")


enum menuID {ABERTURA, LOGIN, CONFIGURACAO, SELECAOPERSONAGEM, CRIACAOPERSONAGEM, JOGO, CREDITOS, SAIDA};


class CMenu
{

private:

	IrrlichtDevice *_dispositivo; 
	IVideoDriver *_gerenciadorVideo; 
	ISceneManager *_gerenciadorCena; 
	IGUIEnvironment *_gerenciadorHud;
	CGerEventos _gerenciadorEventos;
	ISoundEngine *_gerenciadorAudio;
	IGUISkin *_skin;
	IGUIFont *_font;
	ICameraSceneNode *_camera;
	menuID _myID;
	CTimer *_timer;
	ISound* _musicaFundo;
	
public:

	CMenu(TypeCfg cfg, bool &created, menuID id, char* arquivo )
	{
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
			created = false;
		}
		else
		{
			created = true;
			_myID = id;
			_timer = new CTimer();
			_timer->initialize();

			_dispositivo->setWindowCaption(L"Warbugs - BETA Version 0.1");

			_gerenciadorCena = _dispositivo->getSceneManager();   // Cria o gerenciador de cena
			_gerenciadorVideo = _dispositivo->getVideoDriver();   // Cria o driver para o vídeo
			_gerenciadorHud = _dispositivo->getGUIEnvironment(); // Cria o gerenciador de menu
			_gerenciadorAudio = createIrrKlangDevice();

			_musicaFundo = _gerenciadorAudio->play2D("recursos/audio/login.ogg", true, false, false, ESM_AUTO_DETECT);
			
			//_musicaFundo->setIsPaused(true);
			_gerenciadorAudio->setSoundVolume(cfg.parametrosAudio.volumeMusica);
			//	setVolume(cfg.parametrosAudio.volumeMusica);

			if(arquivo)
				_gerenciadorCena->loadScene(arquivo);
			
			_skin = _gerenciadorHud->getSkin();
			_font = _gerenciadorHud->getFont("recursos/fonts/font_georgia.png");
			
			if (_font)
				_skin->setFont(_font);

			_skin->setFont(_gerenciadorHud->getBuiltInFont(), EGDF_TOOLTIP);

			if(_myID != JOGO)
				_camera = _gerenciadorCena->addCameraSceneNode(0,vector3df(0,50,0), vector3df(0,0,50));

		}
	}

	int execute()
	{

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

				switch(_myID)
				{
					case (ABERTURA):
						telaAbertura();
						break;

					case (LOGIN):
						menuLogin();
						break;

					case (CONFIGURACAO):
						menuConfiguracao();
						break;

					case (CRIACAOPERSONAGEM):
						menuCriacaoPersonagem();
						break;

					case (JOGO):
						menuJogo();
						break;

					case (CREDITOS):
						menuCreditos();
						break;
					default:
						cout << "\nErro: ID de menu nao identificado" << endl;
				};

				if(_gerenciadorEventos.isKeyDown(KEY_ESCAPE))
				{
					menuSaida();

					//Sleep(5000);
					_dispositivo->drop();    // Deleta o dispositivo da memória
					_gerenciadorAudio->drop(); // Deleta o gerenciador de som da memória
					return SAIDA;
				}	
			}
		}

		_dispositivo->drop(); // Deleta o dispositivo da memória
		_gerenciadorAudio->drop(); // Deleta o gerenciador de som da memória
		return (2);
	}

	void telaAbertura()
	{
	}

	void menuLogin()
	{
		
		_gerenciadorCena->addTextSceneNode(_gerenciadorHud->getBuiltInFont(), 
										   L"TESTE!!!!!!!!",
										   SColor(255,255,255,255),
										   0, vector3df(0,0,0));
	}
	
	void menuConfiguracao()
	{

	}
	
	void menuCriacaoPersonagem()
	{
	}
	
	void menuJogo()
	{
	}
	
	void menuCreditos()
	{
	}
	
	void menuSaida()
	{
		_gerenciadorHud->addMessageBox(L"teste", L"Deseja fechar o jogo?", true, EMBF_OK, 0);
	}
};

#endif;