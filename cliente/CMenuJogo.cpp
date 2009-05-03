#pragma once

#include "CMenu.h"
#include "CHudChat.cpp"
#include "CHudMiniMapa.cpp"
#include "CHudRoleta.cpp"
#include "CHudStatus.cpp"
#include "CPersonagem.h"
#include "CCenario.h"

class CMenuJogo : public CMenu
{

private:


	int _idPersonagem;

	IGUIListBox *_chatText;
	IGUIEditBox *_chatInput; 

	IGUIWindow *_invWindow,
			   *_chatWindow,	
			   *_statWindow,
			   *_cfgWindow;

	CHudRoleta *_roleta;

	ITerrainSceneNode *_terreno;
	IAnimatedMesh *_malha[10];
	ITexture *_textura[10];
	IAnimatedMeshSceneNode *_modelo[10];

	float _direcao, _velocidade;

	//minipama
	CHudMiniMapa *_miniMapa;
	aabbox3df _terrenoBox;
	ITexture* _heightmapTx;
	dimension2d<s32> _miniMapaDim;
	position2d<s32> _miniMapaPos;
	dimension2d<s32> _terrenoBoxDim;

	void updateHuds()
	{
		_gerenciadorHud->clear();
		
        //_font->draw(temp, rect<s32>(130,10,300,50), SColor(255,255,255,255));

		// Criar janela de inventário do jogador
		_invWindow = _gerenciadorHud->addWindow(rect<s32>(0, 0, 250, 200), false, L"Inventario"); 
		_invWindow->getCloseButton()->setEnabled(false); 
		_invWindow->getCloseButton()->setToolTipText(L""); 
		_invWindow->getCloseButton()->setVisible(false); 

		// Criar janela de status do jogador
		_statWindow = _gerenciadorHud->addWindow(rect<s32>(0, 0, 150, 80), false, L"Status"); 
		_statWindow->getCloseButton()->setEnabled(false); 
		_statWindow->getCloseButton()->setToolTipText(L""); 
		_statWindow->getCloseButton()->setVisible(false); 

		// Criar janela de configurações do jogo
		_cfgWindow = _gerenciadorHud->addWindow(rect<s32>(0, 0, 500, 500), false, L"Config"); 
		_cfgWindow->getCloseButton()->setEnabled(false); 
		_cfgWindow->getCloseButton()->setVisible(false);
		_cfgWindow->getCloseButton()->setToolTipText(L""); 

		// Criar janela de chat
		_chatWindow = _gerenciadorHud->addWindow(rect<s32>(0, 600-200, 800/4, 600), false, L"Chat");     
		_chatWindow->getCloseButton()->setEnabled(false); 
		_chatWindow->getCloseButton()->setToolTipText(L""); 
		_chatWindow->getCloseButton()->setVisible(false); 

		_chatText = _gerenciadorHud->addListBox(rect<s32>(5, 25, 800/4-5, 165), _chatWindow); 
		_chatInput = _gerenciadorHud->addEditBox(L"", rect<s32>(5, 170, 800/4-30, 195), true, _chatWindow);


		_invWindow->setVisible(_flags[INVENTARIOON]);
				
		_cfgWindow->setVisible(_flags[CONFIGON]);

		_statWindow->setVisible(_flags[STATUSON]);

		_gerenciadorHud->addButton(rect<s32>(440,500,540,540), 0, 8, L"Sair");
		_gerenciadorHud->addButton(rect<s32>(0,0,20,20), 0, 9, L"Config");

		_gerenciadorHud->addButton(rect<s32>(0+40,0,20+40,20), _cfgWindow, 10, L"Inventario");
		_gerenciadorHud->addButton(rect<s32>(0+80,0,20+80,20), 0, 11, L"Status");
		_gerenciadorHud->addButton(rect<s32>(0+120,0,20+120,20), 0, 12, L"Mapa");
		_gerenciadorHud->addButton(rect<s32>(0+160,0,20+160,20), 0, 13, L"Trocar");
		_gerenciadorHud->addButton(rect<s32>(0+200,0,20+200,20), 0, 14, L"Equipar");
		_gerenciadorHud->addButton(rect<s32>(0+240,0,20+240,20), 0, 15, L"Mail");

		


		if(_flags[MAPAON])
		{
		}

		if(_flags[BOLSAON])
		{
		}

		if(_flags[ALERTON])
		{
		}

		if(_flags[SHOPON])
		{
		}

		if(_flags[EQUIPON])
		{
		}

		if(_flags[TRADEON])
		{
		}

		_roleta = new CHudRoleta( 
		rect<s32>(600, 400, 800, 600),  // Area da roleta
		_gerenciadorHud,						 // Gerenciador de Hud
		_gerenciadorHud->getRootGUIElement(), // Raiz do gerenciador de Hud 
		_gerenciadorVideo->getTexture("recursos/huds/roleta.png"),   
		_gerenciadorVideo->getTexture("recursos/huds/ponteiro.png")
		);

		_flags[HUDCHANGED] = false;
	}

	void readCommands()
	{
		//_timer->update();
		
		temp = L"";
		temp += (int)_gerenciadorVideo->getFPS();

		_dispositivo->setWindowCaption(temp.c_str());
		
		if(_gerenciadorEventos->isKeyDown(KEY_ESCAPE))
		{
			_nextID = SAIDA;
			return;
		}

		if(_gerenciadorEventos->isMouseButtonReleased(MBLEFT))
		{		

			if(_gerenciadorEventos->getEventCallerByElement(EGET_BUTTON_CLICKED))
			{
				if (_gerenciadorEventos->getEventCallerByID() == 8)
				{
					_nextID = CREDITOS;
					return;
				}
			}		
		}

		if(_gerenciadorEventos->wheelMoved())
		{
			_roleta->move(_gerenciadorEventos->getDeltaMouseWheelPosition());
		}

		if(_gerenciadorEventos->isKeyReleased(KEY_KEY_C))
		{
			_flags[CONFIGON] = !_flags[CONFIGON];
			_cfgWindow->setVisible(_flags[CONFIGON]);
		}
/*
		 
	    if(_gerenciadorEventos->isKeyPressed(KEY_KEY_H))
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

		if(_gerenciadorEventos->isKeyPressed(KEY_KEY_I))
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

		if(_gerenciadorEventos->isKeyPressed(KEY_KEY_C))
		{
			if(_flags[CFG])
			{
				_cfgWindow->setVisible(false);
				_flags[CFG] = false;
			}
			else
			{
				_cfgWindow->setVisible(true);
				_flags[CFG] = true;
			}
		}

		if(_gerenciadorEventos->isKeyPressed(KEY_KEY_T))
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

*/





		if(_gerenciadorEventos->isKeyDown(KEY_KEY_W))
		{
			_modelo[0]->setPosition(_modelo[0]->getPosition() + 
				                   vector3df(cos(((_direcao)*PI)/180)*_velocidade,
								   0,
								   -sin(((_direcao)*PI)/180)*_velocidade));
		}

		if(_gerenciadorEventos->isKeyDown(KEY_KEY_S))
		{
			_modelo[0]->setPosition(_modelo[0]->getPosition() + 
				                    vector3df(cos(((_direcao+180)*PI)/180)*_velocidade,
									0,
                                    -sin(((_direcao+180)*PI)/180)*_velocidade));
		}

		if(_gerenciadorEventos->isKeyDown(KEY_KEY_A))
		{
		   _direcao-=1;
		   _modelo[0]->setRotation(vector3df(0.f, _direcao, 0.f));
		}

		if(_gerenciadorEventos->isKeyDown(KEY_KEY_D))
		{
		   _direcao+=1;
		   _modelo[0]->setRotation(vector3df(0.f, _direcao, 0.f));
		}

	}


	void updateGraphics()
	{

		_modelo[0]->setPosition(vector3df(_modelo[0]->getPosition().X, _terreno->getHeight(_modelo[0]->getPosition().X,_modelo[0]->getPosition().Z)+2, _modelo[0]->getPosition().Z));
		_camera->setPosition(_modelo[0]->getPosition() + vector3df(-20,30,0));
		_camera->setTarget(_modelo[0]->getPosition());

		_roleta->update();
	}

	void graphicsDrawAddOn() 
	{
		_gerenciadorVideo->draw2DImage(_heightmapTx, _miniMapaPos);
	}
	

public:

	stringw temp;


	CMenuJogo(){}
	
	bool start(IrrlichtDevice *grafico, ISoundEngine *audio)
	{

		_gameCfg = new CArquivoConfig();
		TypeCfg cfg = _gameCfg->loadConfig();
		

	    _dispositivo = grafico;
		_gerenciadorEventos = (CGerEventos*)_dispositivo->getEventReceiver();
		_gerenciadorAudio = audio;
		_gerenciadorAudio->removeAllSoundSources();

		_myID = _nextID = JOGO;
		_arquivoCena = "recursos/cenas/jogo.irr";
		//_timer = new CTimer();
		//_timer->initialize();
		_nodoSelecionado = 0;
		_idPersonagem = -1;
		

		for(int i=0; i<NUMFLAGSMENU; i++)
		   _flags[i] = true;

		_flags[OBJSELECTED] = false;
		_flags[HUDCHANGED] = false;
		_flags[ALERTON] = false;

		_dispositivo->setWindowCaption(L"Warbugs - BETA Version 0.1");

		_gerenciadorCena = _dispositivo->getSceneManager();   // Cria o gerenciador de cena
		_gerenciadorVideo = _dispositivo->getVideoDriver();   // Cria o driver para o vídeo
		_gerenciadorHud = _dispositivo->getGUIEnvironment(); // Cria o gerenciador de menu

		_musica = _gerenciadorAudio->play2D("recursos/audio/jogo.ogg", true, false, false, ESM_AUTO_DETECT);
		
		_gerenciadorAudio->setSoundVolume(cfg.parametrosAudio.volumeMusica);

		_gerenciadorCena->clear();
		if(_arquivoCena)
			_gerenciadorCena->loadScene(_arquivoCena);
		
		_skin = _gerenciadorHud->getSkin();
		_font = _gerenciadorHud->getFont("recursos/fonts/font_georgia.png");
		
		if (_font)
			_skin->setFont(_font);

		_skin->setFont(_gerenciadorHud->getBuiltInFont(), EGDF_TOOLTIP);

		_terreno = (ITerrainSceneNode*)_gerenciadorCena->getSceneNodeFromType(ESNT_TERRAIN, 0);
		

		//MINIMAPA
		_terrenoBox = _terreno->getBoundingBox();

		_heightmapTx = _gerenciadorVideo->getTexture("recursos/texturas/minimapa.png"); //map 

		_miniMapaDim = _heightmapTx->getSize(); 
		 
		_miniMapaPos.X = 600; 
		_miniMapaPos.Y = 0; 

		_terrenoBoxDim = dimension2d<s32>((s32)abs(_terrenoBox.MaxEdge.X) - (s32)abs(_terrenoBox.MinEdge.X), 
								   (s32)abs(_terrenoBox.MaxEdge.Z) - (s32)abs(_terrenoBox.MinEdge.Z));

		//------------

	    _textura[0] = _gerenciadorVideo->getTexture("recursos/texturas/louva_lider.jpg");
		_malha[0] = _gerenciadorCena->getMesh("recursos/modelos/louva_lider.3ds");

		_modelo[0] = _gerenciadorCena->addAnimatedMeshSceneNode(_malha[0]);
		_modelo[0]->setMaterialFlag(EMF_LIGHTING, false);
		_modelo[0]->setMaterialTexture(0, _textura[0]);

		_modelo[0]->setPosition(vector3df(990,_terreno->getHeight(990,980)+2,980));

		ISceneNode* node = 0;
		node = _gerenciadorCena->addLightSceneNode(0, vector3df(500,500,500), SColorf(1.0f, 0.6f, 0.7f, 1.0f), 1200.0f);
        
		/*ISceneNodeAnimator* anim = 0;
        anim = _gerenciadorCena->createFlyCircleAnimator (vector3df(0,250,0),250.0f);
        node->addAnimator(anim);
        anim->drop();*/

        _modelo[0]->addShadowVolumeSceneNode(_malha[0],-1,true, 1000);
        _gerenciadorCena->setShadowColor(SColor(150,0,0,0));

        _modelo[0]->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);


		_camera = _gerenciadorCena->addCameraSceneNode();
		

		_camera->setPosition(_modelo[0]->getPosition() + vector3df(-20,30,0));
		_camera->setTarget(_modelo[0]->getPosition());

		_direcao = 0.0f;
		_velocidade = 0.1f;

		s32 Width = _gerenciadorVideo->getViewPort().getWidth();
		s32 Height = _gerenciadorVideo->getViewPort().getHeight();

		return (true);
	}
};
