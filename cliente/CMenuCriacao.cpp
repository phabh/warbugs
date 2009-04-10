#ifndef __CMenuCriacao__
#define __CMenuCriacao__

#include "CMenu.cpp"

class CMenuCriacao : public CMenu
{

private:

	enum flagCriacao {CHANGED, OBJSELECTED};

	ISceneNode *_nodoSelecionado;
	int _idPersonagem;

	void updateHuds()
	{

		_gerenciadorHud->clear();
		_gerenciadorHud->addButton(rect<s32>(440,500,540,540), 0, 100, L"Criar");

		_flags[CHANGED] = false;
	}

	void updateCommands()
	{
		_timer->update();

		if(_gerenciadorEventos->isMouseButtonReleased(MBLEFT))
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

			if(_gerenciadorEventos->getEventCallerByElement(EGET_BUTTON_CLICKED))
			{
				// Trata os cliques em botões

				switch (_gerenciadorEventos->getEventCallerByID())
				{
					case 100:
						_myID = SELECAOPERSONAGEM;
					break;
					
					default:
						cout << "\nID de botao desconhecido." << endl;
				};
			}		
		}
	}

	void updateGraphics()
	{
		_timer->update();
	}
	

public:

	CMenuCriacao(){}
	
	bool start(IrrlichtDevice *grafico, ISoundEngine *audio)
	{

		_gameCfg = new CArquivoConfig();
		TypeCfg cfg = _gameCfg->loadConfig();

		
		_dispositivo = grafico;
		_gerenciadorEventos = (CGerEventos*)_dispositivo->getEventReceiver();
		_gerenciadorAudio = audio;
		_gerenciadorAudio->removeAllSoundSources();
		
		_myID = CRIACAOPERSONAGEM;
		_arquivoCena = "recursos/cenas/criacao.irr";
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

		_musica[0] = _gerenciadorAudio->play2D("recursos/audio/criacao.ogg", true, false, false, ESM_AUTO_DETECT);
		
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

				if(_myID != CRIACAOPERSONAGEM)
					return _myID;

				updateGraphics();

				if(_flags[CHANGED])
					updateHuds();

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