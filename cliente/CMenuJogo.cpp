#ifndef __CMenuJogo__
#define __CMenuJogo__

#include "CMenu.cpp"

#include "CHudChat.cpp"
#include "CHudMiniMapa.cpp"
#include "CHudRoleta.cpp"
#include "CHudStatus.cpp"

using namespace irr; 
using namespace core; 
using namespace scene; 
using namespace video; 
using namespace io; 
using namespace gui; 

class CMenuJogo : public CMenu
{

private:

	enum flagJogo {CHANGED, OBJSELECTED, INVENTARIO, CHAT, STATUS};
	ISceneNode *_nodoSelecionado;
	int _idPersonagem;

	IGUIListBox *_chatText;
	IGUIEditBox *_chatInput; 

	IGUIWindow *_invWindow,
			   *_chatWindow,	
			   *_statWindow;
	
	void updateHuds()
	{
		_gerenciadorHud->addButton(rect<s32>(440,500,540,540), 0, 100, L"Sair");
		_flags[CHANGED] = false;
	}

	void updateCommands()
	{
		_timer->update();

		if(_gerenciadorEventos.isMouseButtonReleased(MBLEFT))
		{		

			if(_gerenciadorEventos.getEventCallerByElement(EGET_BUTTON_CLICKED))
			{
				if (_gerenciadorEventos.getEventCallerByID() == 100)
					_myID = CREDITOS;
			}		
		}	

		if(_gerenciadorEventos.isKeyPressed(KEY_KEY_I))
		{
			if(_flags[INVENTARIO])
			{
				_invWindow->setVisible(false);
				_flags[INVENTARIO] = false;
			}
			else
			{
				_invWindow->setVisible(true);
				_flags[INVENTARIO] = true;
			}
		}

		if(_gerenciadorEventos.isKeyPressed(KEY_KEY_C))
		{
			if(_flags[CHAT])
			{
				_chatWindow->setVisible(false);
				_flags[CHAT] = false;
			}
			else
			{
				_chatWindow->setVisible(true);
				_flags[CHAT] = true;
			}
		}

		if(_gerenciadorEventos.isKeyPressed(KEY_KEY_S))
		{
			if(_flags[STATUS])
			{
				_statWindow->setVisible(false);
				_flags[STATUS] = false;
			}
			else
			{
				_statWindow->setVisible(true);
				_flags[STATUS] = true;
			}
		}
	}


	void updateGraphics()
	{
	}
	

public:

	CMenuJogo(){}
	
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
			_myID = JOGO;
			_arquivoCena = "recursos/cenas/jogo.irr";
			_timer = new CTimer();
			_timer->initialize();
			_nodoSelecionado = 0;
			_idPersonagem = -1;
			_flags[OBJSELECTED] = false;
			_flags[CHANGED] = true;
			_flags[INVENTARIO] = false;
			_flags[CHAT] = false;
			_flags[STATUS] = false;

			_dispositivo->setWindowCaption(L"Warbugs - BETA Version 0.1");

			_gerenciadorCena = _dispositivo->getSceneManager();   // Cria o gerenciador de cena
			_gerenciadorVideo = _dispositivo->getVideoDriver();   // Cria o driver para o v�deo
			_gerenciadorHud = _dispositivo->getGUIEnvironment(); // Cria o gerenciador de menu
			_gerenciadorAudio = createIrrKlangDevice();

			_musica[0] = _gerenciadorAudio->play2D("recursos/audio/jogo.ogg", true, false, false, ESM_AUTO_DETECT);
			
			_gerenciadorAudio->setSoundVolume(cfg.parametrosAudio.volumeMusica);

			if(_arquivoCena)
				_gerenciadorCena->loadScene(_arquivoCena);
			
			_skin = _gerenciadorHud->getSkin();
			_font = _gerenciadorHud->getFont("recursos/fonts/font_georgia.png");
			
			if (_font)
				_skin->setFont(_font);

			_skin->setFont(_gerenciadorHud->getBuiltInFont(), EGDF_TOOLTIP);

			
			_camera = _gerenciadorCena->addCameraSceneNode(0,vector3df(0,50,0), vector3df(0,0,50));		
			
			s32 Width = _gerenciadorVideo->getViewPort().getWidth();
			s32 Height = _gerenciadorVideo->getViewPort().getHeight();

			_invWindow = _gerenciadorHud->addWindow(rect<s32>(0, 0, 250, 200), false, L"Inventario"); 
			_invWindow->setVisible(true); 

			_invWindow->getCloseButton()->setEnabled(false); 
			_invWindow->getCloseButton()->setToolTipText(L""); 
			_invWindow->getCloseButton()->setVisible(false); 

			_chatWindow = _gerenciadorHud->addWindow(rect<s32>(0, Height-200, Width/4, Height), false, L"Chat");     
			
			_chatWindow->getCloseButton()->setEnabled(false); 
			_chatWindow->getCloseButton()->setToolTipText(L""); 
			_chatWindow->getCloseButton()->setVisible(false); 
			
			_chatText = _gerenciadorHud->addListBox(rect<s32>(5, 25, Width/4-5, 165), _chatWindow); 
			_chatInput = _gerenciadorHud->addEditBox(L"", rect<s32>(5, 170, Width/4-30, 195), true, _chatWindow);


			_statWindow = _gerenciadorHud->addWindow(rect<s32>(0, 0, 150, 80), false, L"Status"); 
			_statWindow->setVisible(true); 

			_statWindow->getCloseButton()->setEnabled(false); 
			_statWindow->getCloseButton()->setToolTipText(L""); 
			_statWindow->getCloseButton()->setVisible(false); 

			_invWindow->setVisible(false);
			_chatWindow->setVisible(false);
			_statWindow->setVisible(false);

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

				updateCommands();

				if(_myID != JOGO)
					_dispositivo->closeDevice();

				updateGraphics();

				if(_flags[CHANGED])
					updateHuds();

				if(_gerenciadorEventos.isKeyDown(KEY_ESCAPE))
				{
					_myID = SAIDA;
					_dispositivo->closeDevice();
				}	

				_gerenciadorEventos.startEventProcess(); // Ativa a escuta de eventos.
			}
		}

		_gerenciadorAudio->stopAllSounds();
		_dispositivo->drop(); // Deleta o dispositivo da mem�ria
		_gerenciadorAudio->drop(); // Deleta o gerenciador de som da mem�ria
		return _myID;
	}
};

#endif;