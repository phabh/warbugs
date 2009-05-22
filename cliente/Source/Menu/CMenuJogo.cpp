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

	int _idPersonagem, _idInimigo;
	ITriangleSelector* _selector;
	
	bool _combate;

	IGUIListBox *_chatText;
	IGUIEditBox *_chatInput; 

	IGUIWindow *_invWindow,
		*_chatWindow,	
		*_statWindow,
		*_cfgWindow,
		*_mapWindow,
		*_equipWindow,
		*_alertWindow;

	CHudRoleta *_roleta;

	ITerrainSceneNode *_terreno;
	IAnimatedMesh *_malha[10];
	ITexture *_textura[10];
	IAnimatedMeshSceneNode *_modelo[10];

	float _direcao, _velocidade;

	float rotV, rotH;

	ISceneNode *_empty;
	ILightSceneNode *luz;


	// Variáveis para tratar o click do mouse no terreno
	SMaterial _material;
	vector3df _coordenadaCapt;
	triangle3df _trianguloCapt;
	position2di _posClick;
	line3df _raio;
	ISceneNode *_nodoSelecionado;
	vector3df _targetPosition;

	//! rotacaoResultante
	/*!
	\Calcula a rotação resultante entre três eixos (X,Y,Z).
	\Retorna o vetor de rotação absoluta resultante
	*/
	vector3df rotacaoResultante(f32 rotX, f32 rotY, f32 rotZ)
	{
		// Matrizes de rotação
		matrix4 mRotX; 
		matrix4 mRotY;
		matrix4 mRotZ;
		matrix4 mRotResultante;

		mRotResultante.setRotationDegrees(vector3df(0, 0, 0));

		// Matrizes separadas para os eixos coordenados
		mRotX.setRotationDegrees(vector3df(rotX, 0, 0)); 
		mRotY.setRotationDegrees(vector3df(0, rotY, 0));
		mRotZ.setRotationDegrees(vector3df(0, 0, rotZ));

		// Produto de vetores
		mRotResultante *= mRotX;
		mRotResultante *= mRotY;
		mRotResultante *= mRotZ;

		return mRotResultante.getRotationDegrees();
	}

//-----------------------------------------------------------------------------------------------------------------
// TRATAMENTO DE HUDS
//-----------------------------------------------------------------------------------------------------------------

	void updateHuds()
	{
		_gerenciadorHud->clear();

		//_font->draw(temp, rect<s32>(130,10,300,50), SColor(255,255,255,255));


		// Criar janela de mini mapa
		_mapWindow = _gerenciadorHud->addWindow(rect<s32>(0, 0, 200, 220), false, L"Mini Mapa"); 
		_mapWindow->getCloseButton()->setEnabled(false); 
		_mapWindow->getCloseButton()->setToolTipText(L""); 
		_mapWindow->getCloseButton()->setVisible(false);

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

		_gerenciadorHud->addButton(rect<s32>(0+40,0,20+40,20), 0, 10, L"Inventario");
		_gerenciadorHud->addButton(rect<s32>(0+80,0,20+80,20), 0, 11, L"Status");
		_gerenciadorHud->addButton(rect<s32>(0+120,0,20+120,20), 0, 12, L"Mapa");
		_gerenciadorHud->addButton(rect<s32>(0+160,0,20+160,20), 0, 13, L"Trocar");
		_gerenciadorHud->addButton(rect<s32>(0+200,0,20+200,20), 0, 14, L"Equipar");
		_gerenciadorHud->addButton(rect<s32>(0+240,0,20+240,20), 0, 15, L"Mail");

		// Elementos GUI da janela de configuração
		_gerenciadorHud->addCheckBox(_gameCfg->loadConfig().parametrosVideo.Stencilbuffer, rect<s32>(50,50,50+20,50+20), _cfgWindow,16, L"");
		_gerenciadorHud->addStaticText(L"Sombra", rect<s32>(50+20, 50, 50+50, 50+20), false, false, _cfgWindow, 17, true);

		_gerenciadorHud->addCheckBox(_gameCfg->loadConfig().parametrosVideo.AntiAlias, rect<s32>(50,80,50+20,80+20), _cfgWindow,18, L"");
		_gerenciadorHud->addStaticText(L"Anti-Aliasing", rect<s32>(50+20, 80, 50+50, 80+20), false, false, _cfgWindow, 19, true);

		_gerenciadorHud->addScrollBar(true, rect<s32>(50,80,50+50,80+20), _cfgWindow, 20);
		_gerenciadorHud->addStaticText(L"Anti-Aliasing", rect<s32>(50+60, 80, 50+80, 80+20), false, false, _cfgWindow, 21, true);


		// Elementos GUI da janela de minimapa
		IGUIButton *btnMiniMapa = _gerenciadorHud->addButton(rect<s32>(0,20,200,220), _mapWindow, 30);
		btnMiniMapa->setIsPushButton(true);

		btnMiniMapa->setPressedImage(_gerenciadorVideo->getTexture("recursos/texturas/minimapa.png"));
		btnMiniMapa->setImage(_gerenciadorVideo->getTexture("recursos/texturas/louva_lider.jpg"));

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

//-----------------------------------------------------------------------------------------------------------------
// TRATAMENTO DE COMANDOS
//-----------------------------------------------------------------------------------------------------------------
	
	void readCommands()
	{		
		temp = L"";
		temp += (int)_gerenciadorVideo->getFPS();

		_dispositivo->setWindowCaption(temp.c_str());

		if(_gerenciadorEventos->isKeyDown(KEY_ESCAPE))
		{
			_nextID = MN_SAIDA;
			return;
		}

		if(_gerenciadorEventos->isMouseButtonReleased(MBLEFT))
		{	
			// BOTÃO ESQUERDO DO MOUSE

			if(_gerenciadorEventos->getEventCallerByElement(EGET_BUTTON_CLICKED))
			{
				if (_gerenciadorEventos->getEventCallerByID() == 8)
				{
					_nextID = MN_CREDITOS;
					return;
				}
			}
			else
			{
				// Não é clique de botão

				_idInimigo = -1;
				_nodoSelecionado = _gerenciadorCena->getSceneCollisionManager()->getSceneNodeFromScreenCoordinatesBB(_dispositivo->getCursorControl()->getPosition());

				_idInimigo = _nodoSelecionado->getID();

				if(_idInimigo > 0)
				{
					_combate = true;
					_targetPosition = _nodoSelecionado->getPosition();
					cout << "\nCombate TRUE.\n";
					cout << "\nAlvo X: " << _targetPosition.X << "\nAlvo Y: " << _targetPosition.Y << "\nAlvo Z: " << _targetPosition.Z << endl;
				}
				else
				{
					_combate = false;
					cout << "\nCombate FALSE.\n";

					_material.Lighting = false;

					_posClick = _dispositivo->getCursorControl()->getPosition();
					_raio = _gerenciadorCena->getSceneCollisionManager()->getRayFromScreenCoordinates(_posClick, _camera);

					

					if(_gerenciadorCena->getSceneCollisionManager()->getCollisionPoint(_raio, _selector, _targetPosition, _trianguloCapt))
					{
						//_targetPosition = desiredPosition;
						_gerenciadorVideo->setTransform(ETS_WORLD, matrix4());
						_gerenciadorVideo->setMaterial(_material);
						_gerenciadorVideo->draw3DTriangle(_trianguloCapt, SColor(0,255,0,0));
					} 
					else
						_targetPosition = _modelo[0]->getPosition();

					cout << "\nAlvo X: " << _targetPosition.X << "\nAlvo Y: " << _targetPosition.Y << "\nAlvo Z: " << _targetPosition.Z << endl;
				}
			}
		}

		if(_gerenciadorEventos->wheelMoved())
		{
			_roleta->move(_gerenciadorEventos->getDeltaMouseWheelPosition());
		}

		if(_gerenciadorEventos->isKeyReleased(KEY_KEY_C))
		{
			// Mostrar | Esconder janela de configuração do jogo
			_flags[CONFIGON] = !_flags[CONFIGON];
			_cfgWindow->setVisible(_flags[CONFIGON]);
		}




		if(_gerenciadorEventos->isKeyReleased(KEY_KEY_M))
		{
			// Mostrar | Esconder janela de minimapa
			_flags[MAPAON] = !_flags[MAPAON];
			_mapWindow->setVisible(_flags[MAPAON]);
		}

		if(_gerenciadorEventos->isKeyReleased(KEY_KEY_I))
		{
			// Mostrar | Esconder janela de inventário do jogador
			_flags[INVENTARIOON] = !_flags[INVENTARIOON];
			_invWindow->setVisible(_flags[INVENTARIOON]);
		}

		if(_gerenciadorEventos->isKeyReleased(KEY_KEY_S))
		{
			// Mostrar | Esconder janela de status do jogador
			_flags[STATUSON] = !_flags[STATUSON];
			_statWindow->setVisible(_flags[STATUSON]);
		}

		if(_gerenciadorEventos->isKeyReleased(KEY_KEY_E))
		{
			// Mostrar | Esconder janela de equipamentos do jogador
			_flags[EQUIPON] = !_flags[EQUIPON];
			_equipWindow->setVisible(_flags[EQUIPON]);
		}

		if(_gerenciadorEventos->isKeyReleased(KEY_KEY_A))
		{
			// Mostrar | Esconder janela de alertas ao jogador
			_flags[ALERTON] = !_flags[ALERTON];
			_alertWindow->setVisible(_flags[ALERTON]);
		}

		if(_gerenciadorEventos->isKeyDown(::KEY_UP))
		{
			_modelo[0]->setPosition(_modelo[0]->getPosition() + 
				vector3df(cos(((_direcao)*PI)/180)*_velocidade,
				0,
				-sin(((_direcao)*PI)/180)*_velocidade));
		}

		if(_gerenciadorEventos->isKeyDown(::KEY_DOWN))
		{
			_modelo[0]->setPosition(_modelo[0]->getPosition() + 
				vector3df(cos(((_direcao+180)*PI)/180)*_velocidade,
				0,
				-sin(((_direcao+180)*PI)/180)*_velocidade));
		}

		if(_gerenciadorEventos->isKeyDown(::KEY_LEFT))
		{
			_direcao-=1;
			_modelo[0]->setRotation(vector3df(0.f, _direcao, 0.f));
		}

		if(_gerenciadorEventos->isKeyDown(::KEY_RIGHT))
		{
			_direcao+=1;
			_modelo[0]->setRotation(vector3df(0.f, _direcao, 0.f));
		}


		// ROTACOES DA CAMERA
		if(_gerenciadorEventos->isKeyDown(KEY_NUMPAD2))
		{
			if(rotV < 80)
				rotV += 2;
		}

		if(_gerenciadorEventos->isKeyDown(KEY_NUMPAD8))
		{
			if(rotV > 10)
				rotV -= 2;
		}

		if(_gerenciadorEventos->isKeyDown(KEY_NUMPAD4))
		{
			rotH += 2;
			if(rotH >= 360.0)
				rotH -= 360.0;
		}

		if(_gerenciadorEventos->isKeyDown(KEY_NUMPAD6))
		{
			rotH -= 2;
			if(rotH < 0.0)
				rotH += 360.0;
		}
	}

	void updateGraphics()
	{
		_modelo[0]->setPosition(vector3df(_modelo[0]->getPosition().X, _terreno->getHeight(_modelo[0]->getPosition().X,_modelo[0]->getPosition().Z)+2, _modelo[0]->getPosition().Z));
		_empty->setPosition(_modelo[0]->getPosition());
		_empty->setRotation(rotacaoResultante(0, rotH, rotV));

		_camera->setTarget(_empty->getPosition());
		//luz->setPosition(_camera->getPosition());

		//_toonShader->apply(_modelo[0],"recursos/texturas/besouro1.jpg");
		//luz->setPosition(_modelo[0]->getPosition()+vector3df(0,100,0));

		_roleta->update();
	}

	void graphicsDrawAddOn() 
	{
		//if(_trianguloCapt.)
		//{
			_gerenciadorVideo->setTransform(ETS_WORLD, matrix4());
			_gerenciadorVideo->setMaterial(_material);
			_gerenciadorVideo->draw3DTriangle(_trianguloCapt, SColor(0,255,0,0));
		//}
	}

public:

	stringw temp;

	CMenuJogo(){}

	bool start(IrrlichtDevice *grafico, ISoundEngine *audio, CGameData *gameData)
	{
		_gameCfg = new CArquivoConfig();
		TypeCfg cfg = _gameCfg->loadConfig();

		_gameData = gameData;

		_dispositivo = grafico;
		_gerenciadorEventos = (CGerEventos*)_dispositivo->getEventReceiver();
		_gerenciadorAudio = audio;
		_gerenciadorAudio->removeAllSoundSources();

		_myID = _nextID = MN_JOGO;
		_arquivoCena = "recursos/cenas/jogo.irr";

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
		_font = _gerenciadorHud->getFont("recursos/fonts/mplus8.xml");

		if (_font)
			_skin->setFont(_font);

		_skin->setFont(_gerenciadorHud->getBuiltInFont(), EGDF_TOOLTIP);

		_terreno = (ITerrainSceneNode*)_gerenciadorCena->getSceneNodeFromType(ESNT_TERRAIN, 0);

		_empty = _gerenciadorCena->addEmptySceneNode();

		_camera = _gerenciadorCena->addCameraSceneNode();

		//------------

		luz = _gerenciadorCena->addLightSceneNode(0, vector3df(0,0,0/*500,500,500*/), SColorf(1.0f, 0.6f, 0.7f, 1.0f), 1200.0f);


		//_textura[0] = _gerenciadorVideo->getTexture("recursos/texturas/louva_lider.jpg");
		_malha[0] = _gerenciadorCena->getMesh("recursos/modelos/besouro.b3d");
		_modelo[0] = _gerenciadorCena->addAnimatedMeshSceneNode(_malha[0]);
		_modelo[0]->setPosition(vector3df(990,_terreno->getHeight(990,980)+2,980));

		//_empty->setPosition(_modelo[0]->getPosition());

		_camera->setParent(_empty);
		_camera->setPosition( vector3df(-20,20,0));
		_camera->setTarget(_empty->getPosition());

		luz->setParent(_camera);

		//luz->setPosition(_modelo[0]->getPosition()+vector3df(0,100,0));

		_toonShader = new CToonShader(_dispositivo, luz);

		_modelo[0]->setAnimationSpeed(30);
		_modelo[0]->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
		_toonShader->apply(_modelo[0],"recursos/texturas/besouro1.jpg");

		_malha[1] = _gerenciadorCena->getMesh("recursos/modelos/arvore.3ds");
		_modelo[1] = _gerenciadorCena->addAnimatedMeshSceneNode(_malha[1]);
		_modelo[1]->setPosition(vector3df(1000,_terreno->getHeight(1000,980)+2,980));
		_modelo[1]->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
		_toonShader->apply(_modelo[1],"recursos/texturas/arvore.jpg");

		_malha[2] = _gerenciadorCena->getMesh("recursos/modelos/louva_lider.b3d");
		_modelo[2] = _gerenciadorCena->addAnimatedMeshSceneNode(_malha[2]);
		_modelo[2]->setPosition(vector3df(1100,_terreno->getHeight(1100,980)+2,980));
		_modelo[2]->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
		_toonShader->apply(_modelo[2],"recursos/texturas/louva_lider.jpg");
		_modelo[2]->setID(5);

		_direcao = 0.0f;
		_velocidade = 0.1f;

		s32 Width = _gerenciadorVideo->getViewPort().getWidth();
		s32 Height = _gerenciadorVideo->getViewPort().getHeight();

		_selector = _gerenciadorCena->createTerrainTriangleSelector(_terreno, 0);
		_terreno->setTriangleSelector(_selector); 

		cout << "\nIndex Count: " << _terreno->getIndexCount() << endl;
		//_selector = _terreno->getTriangleSelector();

		rotV = rotH = 0.0;

		return (true);
	}
};