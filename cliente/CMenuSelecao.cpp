#pragma once

#include "CMenu.h"

class CMenuSelecao : public CMenu
{

private:

	
	ISceneNode *_nodoSelecionado;
	int _idPersonagem;

	float _camRotation;
	float _camCurrRotation;
/*
	UINT ThreadReadPackets(LPVOID lParam)
	{
		while(_nextID == _myID)
			cout << "\nLeu pacotes.\n";
		return 0;
	}*/

	void graphicsDrawAddOn(){}

	void updateHuds()
	{

		_gerenciadorHud->clear();
		
		_gerenciadorHud->addButton(rect<s32>(440,500,540,540), 0, 3, L"Criar");

		

		//if(_flags[OBJSELECTED])
		_gerenciadorHud->addButton(rect<s32>(320,500,430,540), 0, 4, L"Jogar");

		_gerenciadorHud->addButton(rect<s32>(140,10,240,50), 0, 5, L"<");
		_gerenciadorHud->addButton(rect<s32>(540,10,640,50), 0, 6, L">");

		_flags[HUDCHANGED] = false;
	}

	void readCommands()
	{
//		_timer->update();

		if(_gerenciadorEventos->isKeyDown(KEY_ESCAPE))
		{
			_nextID = SAIDA;
			return;
		}

		if(_gerenciadorEventos->getEventCallerByElement(EGET_BUTTON_CLICKED))
		{
			// Trata os cliques em botões
			switch (_gerenciadorEventos->getEventCallerByID())
			{
				case 3:
					_nextID = CRIACAOPERSONAGEM;
					return;
				break;

				case 4:
					_nextID =  JOGO;
					return;
				break;

				case 5:
					_camRotation+=90;
					cout << "\n" << _camRotation;
				break;

				case 6:
					_camRotation-=90;
					cout << "\n" << _camRotation;
				break;
			
				default:
					cout << "\nID de botao desconhecido." << endl;
			};
		}

		_camera->setRotation(vector3df(0, _camCurrRotation, 0));

		if(_gerenciadorEventos->isMouseButtonReleased(MBLEFT))
		{
			// Clique com o botao esquerdo
						
			if(_flags[OBJSELECTED])
			{
				_flags[OBJSELECTED] = false; // Drop 3D
				_flags[HUDCHANGED] = true;
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
				   _flags[HUDCHANGED] = true;
				}
			}		
		}
	}

	void updateGraphics()
	{
		//_timer->update();

		float delta = fabs(_camRotation - _camCurrRotation);

		if(	_camRotation != _camCurrRotation )
		{
			if(delta < 4)
				_camCurrRotation = _camRotation;
			else
			{
				if(_camRotation > _camCurrRotation)
					_camCurrRotation += 1*delta/100;

				else if(_camRotation < _camCurrRotation)
					_camCurrRotation -= 1*delta/100;
			}
		}

		cout << "\n" << _camCurrRotation;

		_camera->setRotation(vector3df(0,_camCurrRotation,0));
	}
	

public:

	CMenuSelecao(){}
	
	bool start(IrrlichtDevice *grafico, ISoundEngine *audio)
	{

		_gameCfg = new CArquivoConfig();
		TypeCfg cfg = _gameCfg->loadConfig();

	    _dispositivo = grafico;
		_gerenciadorEventos = (CGerEventos*)_dispositivo->getEventReceiver();
		_gerenciadorAudio = audio;
		_gerenciadorAudio->removeAllSoundSources();

		_myID = _nextID = SELECAOPERSONAGEM;
		_arquivoCena = "recursos/cenas/selecao.irr";
		//_timer = new CTimer();
		//_timer->initialize();
		_nodoSelecionado = 0;
		_idPersonagem = -1;
		_flags[OBJSELECTED] = false;
		_flags[HUDCHANGED] = false;

		_dispositivo->setWindowCaption(L"Warbugs - BETA Version 0.1");

		_gerenciadorCena = _dispositivo->getSceneManager();   // Cria o gerenciador de cena
		_gerenciadorVideo = _dispositivo->getVideoDriver();   // Cria o driver para o vídeo
		_gerenciadorHud = _dispositivo->getGUIEnvironment(); // Cria o gerenciador de menu
		
		_musica = _gerenciadorAudio->play2D("recursos/audio/selecao.ogg", true, false, false, ESM_AUTO_DETECT);
		
		_gerenciadorAudio->setSoundVolume(cfg.parametrosAudio.volumeMusica);

		_gerenciadorCena->clear();
		if(_arquivoCena)
			_gerenciadorCena->loadScene(_arquivoCena);
		
		_skin = _gerenciadorHud->getSkin();
		_font = _gerenciadorHud->getFont("recursos/fonts/font_georgia.png");
		
		if (_font)
			_skin->setFont(_font);

		_skin->setFont(_gerenciadorHud->getBuiltInFont(), EGDF_TOOLTIP);
		
		_camera = _gerenciadorCena->addCameraSceneNode(0, vector3df(0,0,0));

		_camera->bindTargetAndRotation(true);

		_camRotation = 0;
		_camCurrRotation = 0;

		return (true);
	}
/*
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
				_gerenciadorVideo->endScene();

				readCommands();

				updateGraphics();

				if(_flags[HUDCHANGED])
					updateHuds();

				_gerenciadorEventos->startEventProcess(); // Ativa a escuta de eventos.

				if(_nextID != _myID)
					return _nextID;
			}
		}

		_gerenciadorAudio->stopAllSounds();
		return _myID;
	}*/

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
