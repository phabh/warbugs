#include "CMenuJogo.h"

//-----------------------------------------------------------------------------------------------------------------

CMenuJogo::CMenuJogo()
{
}

//-----------------------------------------------------------------------------------------------------------------

bool CMenuJogo::start(CGameCore *gameCore)
{
	_gameCore = gameCore;

	_gameCore->getAllManagers(_dispGrafico, _dispAudio, _gerEventos, _gerCena, _gerVideo, _gerHud, _gameConfig);

	//_gameCore->loadGameScene(pathCenario[GAMESCENE_01]);

	_menuCamera = gameCore->createCamera( vector3df(0,0,0), vector3df(0,0,100), vector3df(0,0,0), 0, 179.0f/*true*/, false);

	_gameCore->playMusic(pathBackgroundSound[MM_JOGO]);

	_myID = _nextID = MN_JOGO;

	//_nodoSelecionado = 0;
	//_idPersonagem = -1;

	for(int i=0; i<NUMFLAGSMENU; i++)
		_menuFlag[i] = true;

	_menuFlag[OBJSELECTED] = false;
	_menuFlag[HUDUPDATED]  = false;
	_menuFlag[ALERTON]     = false;

	//_terreno = (ITerrainSceneNode*)_gerCena->getSceneNodeFromType(ESNT_TERRAIN, 0);

	_empty = _gerCena->addEmptySceneNode();


	luz = _gerCena->addLightSceneNode(0, vector3df(0,0,0/*500,500,500*/), SColorf(1.0f, 0.6f, 0.7f, 1.0f), 1200.0f);


	//_textura[0] = _gerenciadorVideo->getTexture("recursos/texturas/louva_lider.jpg");
	//_malha[0] = _gerCena->getMesh("recursos/modelos/besouro.b3d");
	//_modelo[0] = _gerCena->addAnimatedMeshSceneNode(_malha[0]);
	//_modelo[0]->setPosition(vector3df(990,_terreno->getHeight(990,980)+2,980));

	//_empty->setPosition(_modelo[0]->getPosition());

	_menuCamera->setParent(_empty);
	_menuCamera->setPosition( vector3df(-20,20,0));
	_menuCamera->setTarget(_empty->getAbsolutePosition());

	luz->setParent(_menuCamera);

	//luz->setPosition(_modelo[0]->getPosition()+vector3df(0,100,0));

	//_toonShader = new CToonShader(_dispGrafico, luz);

	//_modelo[0]->setAnimationSpeed(30);
	//_modelo[0]->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
	//_toonShader->apply(_modelo[0],"recursos/texturas/besouro1.jpg");

	//_malha[1] = _gerCena->getMesh("recursos/modelos/arvore.3ds");
	//_modelo[1] = _gerCena->addAnimatedMeshSceneNode(_malha[1]);
	//_modelo[1]->setPosition(vector3df(1000,_terreno->getHeight(1000,980)+2,980));
	//_modelo[1]->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
	//_toonShader->apply(_modelo[1],"recursos/texturas/arvore.jpg");

	//_malha[2] = _gerCena->getMesh("recursos/modelos/louva_lider.b3d");
	//_modelo[2] = _gerCena->addAnimatedMeshSceneNode(_malha[2]);
	//_modelo[2]->setPosition(vector3df(1100,_terreno->getHeight(1100,980)+2,980));
	//_modelo[2]->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
	//_toonShader->apply(_modelo[2],"recursos/texturas/louva_lider.jpg");
	//_modelo[2]->setID(5);

	//_direcao = 0.0f;
	//_velocidade = 0.1f;

	//s32 Width = _gerVideo->getViewPort().getWidth();
	//s32 Height = _gerVideo->getViewPort().getHeight();

	//_selector = _gerCena->createTerrainTriangleSelector(_terreno, 0);
	//_terreno->setTriangleSelector(_selector); 

	//cout << "\nIndex Count: " << _terreno->getIndexCount() << endl;
	//_selector = _terreno->getTriangleSelector();

	rotV = rotH = 0.0;

	
	_gameCore->enviarPacote(START_GAME, _gameCore->_myUserID, _gameCore->_myCharID);


	int retorno = PING_REQUEST;

				while(retorno == PING_REQUEST)
					retorno = _gameCore->receberPacote();

	if(retorno == ERRO_SAIR)
		_nextID = MN_LOGIN; // Desconecta e volta para a tela de login

	fillGameScene();
	

	return (true);
}

//-----------------------------------------------------------------------------------------------------------------

void CMenuJogo::fillGameScene()
{
	int retorno = SUCESSO;
	bool fim = false;

	do
	{
		retorno = _gameCore->receberPacote();

		switch (retorno)
		{
			case FINAL_PACOTES:	fim = true;	break;
			case ERRO_SAIR: fim = true; _nextID = MN_LOGIN; break;

		};

	}while(!fim);

}

//-----------------------------------------------------------------------------------------------------------------

void CMenuJogo::updateHuds()
{
	_gerHud->clear();

	//_font->draw(temp, rect<s32>(130,10,300,50), SColor(255,255,255,255));


	// Criar janela de mini mapa
	_mapWindow = _gerHud->addWindow(rect<s32>(0, 0, 200, 220), false, L"Mini Mapa"); 
	_mapWindow->getCloseButton()->setEnabled(false); 
	_mapWindow->getCloseButton()->setToolTipText(L""); 
	_mapWindow->getCloseButton()->setVisible(false);

	// Criar janela de invent�rio do jogador
	_invWindow = _gerHud->addWindow(rect<s32>(0, 0, 250, 200), false, L"Inventario"); 
	_invWindow->getCloseButton()->setEnabled(false); 
	_invWindow->getCloseButton()->setToolTipText(L""); 
	_invWindow->getCloseButton()->setVisible(false); 

	// Criar janela de status do jogador
	_statWindow = _gerHud->addWindow(rect<s32>(0, 0, 150, 80), false, L"Status"); 
	_statWindow->getCloseButton()->setEnabled(false); 
	_statWindow->getCloseButton()->setToolTipText(L""); 
	_statWindow->getCloseButton()->setVisible(false); 

	// Criar janela de configura��es do jogo
	_cfgWindow = _gerHud->addWindow(rect<s32>(0, 0, 500, 500), false, L"Config"); 
	_cfgWindow->getCloseButton()->setEnabled(false); 
	_cfgWindow->getCloseButton()->setVisible(false);
	_cfgWindow->getCloseButton()->setToolTipText(L""); 

	// Criar janela de chat
	_chatWindow = _gerHud->addWindow(rect<s32>(0, 600-200, 800/4, 600), false, L"Chat");     
	_chatWindow->getCloseButton()->setEnabled(false); 
	_chatWindow->getCloseButton()->setToolTipText(L""); 
	_chatWindow->getCloseButton()->setVisible(false); 

	_chatText = _gerHud->addListBox(rect<s32>(5, 25, 800/4-5, 165), _chatWindow); 
	_chatInput = _gerHud->addEditBox(L"", rect<s32>(5, 170, 800/4-30, 195), true, _chatWindow);


	_invWindow->setVisible(_menuFlag[INVENTARIOON]);

	_cfgWindow->setVisible(_menuFlag[CONFIGON]);

	_statWindow->setVisible(_menuFlag[STATUSON]);

	_gerHud->addButton(rect<s32>(440,500,540,540), 0, 8, L"Sair");
	_gerHud->addButton(rect<s32>(0,0,20,20), 0, 9, L"Config");

	_gerHud->addButton(rect<s32>(0+40,0,20+40,20), 0, 10, L"Inventario");
	_gerHud->addButton(rect<s32>(0+80,0,20+80,20), 0, 11, L"Status");
	_gerHud->addButton(rect<s32>(0+120,0,20+120,20), 0, 12, L"Mapa");
	_gerHud->addButton(rect<s32>(0+160,0,20+160,20), 0, 13, L"Trocar");
	_gerHud->addButton(rect<s32>(0+200,0,20+200,20), 0, 14, L"Equipar");
	_gerHud->addButton(rect<s32>(0+240,0,20+240,20), 0, 15, L"Mail");

	// Elementos GUI da janela de configura��o
	_gerHud->addCheckBox(_gameConfig.parametrosVideo.Stencilbuffer, rect<s32>(50,50,50+20,50+20), _cfgWindow,16, L"");
	_gerHud->addStaticText(L"Sombra", rect<s32>(50+20, 50, 50+50, 50+20), false, false, _cfgWindow, 17, true);

	_gerHud->addCheckBox(_gameConfig.parametrosVideo.AntiAlias, rect<s32>(50,80,50+20,80+20), _cfgWindow,18, L"");
	_gerHud->addStaticText(L"Anti-Aliasing", rect<s32>(50+20, 80, 50+50, 80+20), false, false, _cfgWindow, 19, true);

	_gerHud->addScrollBar(true, rect<s32>(50,80,50+50,80+20), _cfgWindow, 20);
	_gerHud->addStaticText(L"Anti-Aliasing", rect<s32>(50+60, 80, 50+80, 80+20), false, false, _cfgWindow, 21, true);


	// Elementos GUI da janela de minimapa
	IGUIButton *btnMiniMapa = _gerHud->addButton(rect<s32>(0,20,200,220), _mapWindow, 30);
	btnMiniMapa->setIsPushButton(true);

	btnMiniMapa->setPressedImage(_gerVideo->getTexture("recursos/texturas/minimapa.png"));
	btnMiniMapa->setImage(_gerVideo->getTexture("recursos/texturas/louva_lider.jpg"));

	if(_menuFlag[MAPAON])
	{
	}

	if(_menuFlag[BOLSAON])
	{
	}

	if(_menuFlag[ALERTON])
	{
	}

	if(_menuFlag[SHOPON])
	{
	}

	if(_menuFlag[EQUIPON])
	{
	}

	if(_menuFlag[TRADEON])
	{
	}

	_roleta = new CHudRoleta( 
		rect<s32>(600, 400, 800, 600),  // Area da roleta
		_gerHud,						 // Gerenciador de Hud
		_gerHud->getRootGUIElement(), // Raiz do gerenciador de Hud 
		_gerVideo->getTexture("recursos/huds/roleta.png"),   
		_gerVideo->getTexture("recursos/huds/ponteiro.png")
		);

	_menuFlag[HUDUPDATED] = true;
}

//-----------------------------------------------------------------------------------------------------------------

void CMenuJogo::readCommands()
{		
	temp = L"";
	temp += (int)_gerVideo->getFPS();

	_dispGrafico->setWindowCaption(temp.c_str());

	if(_gerEventos->isKeyDown(KEY_ESCAPE))
	{
		_nextID = MN_SAIDA;
		return;
	}

	if(_gerEventos->isMouseButtonReleased(MBLEFT))
	{	
		// BOT�O ESQUERDO DO MOUSE

		if(_gerEventos->getEventCallerByElement(EGET_BUTTON_CLICKED))
		{
			if (_gerEventos->getEventCallerByID() == 8)
			{
				_nextID = MN_CREDITOS;
				return;
			}
		}
		else
		{
			// N�o � clique de bot�o

			_idInimigo = -1;
			_nodoSelecionado = _gerCena->getSceneCollisionManager()->getSceneNodeFromScreenCoordinatesBB(_dispGrafico->getCursorControl()->getPosition());

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

				_posClick = _dispGrafico->getCursorControl()->getPosition();
				_raio = _gerCena->getSceneCollisionManager()->getRayFromScreenCoordinates(_posClick, _menuCamera);



				if(_gerCena->getSceneCollisionManager()->getCollisionPoint(_raio, _selector, _targetPosition, _trianguloCapt))
				{
					//_targetPosition = desiredPosition;
					_gerVideo->setTransform(ETS_WORLD, matrix4());
					_gerVideo->setMaterial(_material);
					_gerVideo->draw3DTriangle(_trianguloCapt, SColor(0,255,0,0));
				} 
				else
					_targetPosition = _modelo[0]->getPosition();

				cout << "\nAlvo X: " << _targetPosition.X << "\nAlvo Y: " << _targetPosition.Y << "\nAlvo Z: " << _targetPosition.Z << endl;
			}
		}
	}

	if(_gerEventos->wheelMoved())
	{
		_roleta->move(_gerEventos->getDeltaMouseWheelPosition());
	}

	if(_gerEventos->isKeyReleased(KEY_KEY_C))
	{
		// Mostrar | Esconder janela de configura��o do jogo
		_menuFlag[CONFIGON] = !_menuFlag[CONFIGON];
		_cfgWindow->setVisible(_menuFlag[CONFIGON]);
	}

	if(_gerEventos->isKeyReleased(KEY_KEY_M))
	{
		// Mostrar | Esconder janela de minimapa
		_menuFlag[MAPAON] = !_menuFlag[MAPAON];
		_mapWindow->setVisible(_menuFlag[MAPAON]);
	}

	if(_gerEventos->isKeyReleased(KEY_KEY_I))
	{
		// Mostrar | Esconder janela de invent�rio do jogador
		_menuFlag[INVENTARIOON] = !_menuFlag[INVENTARIOON];
		_invWindow->setVisible(_menuFlag[INVENTARIOON]);
	}

	if(_gerEventos->isKeyReleased(KEY_KEY_S))
	{
		// Mostrar | Esconder janela de status do jogador
		_menuFlag[STATUSON] = !_menuFlag[STATUSON];
		_statWindow->setVisible(_menuFlag[STATUSON]);
	}

	if(_gerEventos->isKeyReleased(KEY_KEY_E))
	{
		// Mostrar | Esconder janela de equipamentos do jogador
		_menuFlag[EQUIPON] = !_menuFlag[EQUIPON];
		_equipWindow->setVisible(_menuFlag[EQUIPON]);
	}

	if(_gerEventos->isKeyReleased(KEY_KEY_A))
	{
		// Mostrar | Esconder janela de alertas ao jogador
		_menuFlag[ALERTON] = !_menuFlag[ALERTON];
		_alertWindow->setVisible(_menuFlag[ALERTON]);
	}

	if(_gerEventos->isKeyDown(::KEY_UP))
	{
		_modelo[0]->setPosition(_modelo[0]->getPosition() + 
			vector3df(cos(((_direcao)*PI)/180)*_velocidade,
			0,
			-sin(((_direcao)*PI)/180)*_velocidade));
	}

	if(_gerEventos->isKeyDown(::KEY_DOWN))
	{
		_modelo[0]->setPosition(_modelo[0]->getPosition() + 
			vector3df(cos(((_direcao+180)*PI)/180)*_velocidade,
			0,
			-sin(((_direcao+180)*PI)/180)*_velocidade));
	}

	if(_gerEventos->isKeyDown(::KEY_LEFT))
	{
		_direcao-=1;
		_modelo[0]->setRotation(vector3df(0.f, _direcao, 0.f));
	}

	if(_gerEventos->isKeyDown(::KEY_RIGHT))
	{
		_direcao+=1;
		_modelo[0]->setRotation(vector3df(0.f, _direcao, 0.f));
	}


	// ROTACOES DA CAMERA
	if(_gerEventos->isKeyDown(KEY_NUMPAD2))
	{
		if(rotV < 80)
			rotV += 2;
	}

	if(_gerEventos->isKeyDown(KEY_NUMPAD8))
	{
		if(rotV > 10)
			rotV -= 2;
	}

	if(_gerEventos->isKeyDown(KEY_NUMPAD4))
	{
		rotH += 2;
		if(rotH >= 360.0)
			rotH -= 360.0;
	}

	if(_gerEventos->isKeyDown(KEY_NUMPAD6))
	{
		rotH -= 2;
		if(rotH < 0.0)
			rotH += 360.0;
	}
}

//-----------------------------------------------------------------------------------------------------------------

void CMenuJogo::updateGraphics()
{
	//_modelo[0]->setPosition(vector3df(_modelo[0]->getPosition().X, _terreno->getHeight(_modelo[0]->getPosition().X,_modelo[0]->getPosition().Z)+2, _modelo[0]->getPosition().Z));
	//_empty->setPosition(_modelo[0]->getPosition());
	//_empty->setRotation(rotacaoResultante(0, rotH, rotV));

	//_menuCamera->setTarget(_empty->getAbsolutePosition());
	//_toonShader->apply(_modelo[0],"recursos/texturas/besouro1.jpg");


	_roleta->update();
}

//-----------------------------------------------------------------------------------------------------------------

void CMenuJogo::graphicsDrawAddOn() 
{
	//if(_trianguloCapt.)
	//{
	_gerVideo->setTransform(ETS_WORLD, matrix4());
	_gerVideo->setMaterial(_material);
	_gerVideo->draw3DTriangle(_trianguloCapt, SColor(0,255,0,0));
	//}
}

//-----------------------------------------------------------------------------------------------------------------

vector3df CMenuJogo::rotacaoResultante(f32 rotX, f32 rotY, f32 rotZ)
{
	// Matrizes de rota��o
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
