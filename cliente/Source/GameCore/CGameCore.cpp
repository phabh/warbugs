#include "CGameCore.h"

//-----------------------------------------------------------------------------------------------------------------

CGameCore::CGameCore(int &startInit)
{
	startInit = SUCESSO;

	_connected = false;

	_myUserID = -1;
	_myCharID = -1;

	_particleCount = 0;

	strcpy(_myLogin, "");
	strcpy(_myPassword, "");

	_fileCfg = new CArquivoConfig();

	//_fileCfg->reset();

	

	_gameConfig = _fileCfg->loadConfig();

	/*
	RECT desktop; // Faz uma referência para a tela do desktop   
	const HWND hDesktop = GetDesktopWindow(); // Captura a dimensão da tela 
	GetWindowRect(hDesktop, &desktop);  */ 

	//_gameConfig->parametrosVideo.WindowSize.Width = 1024;//desktop.right;
	//_gameConfig->parametrosVideo.WindowSize.Height = 768;//desktop.bottom;
	//_gameConfig->parametrosVideo.Fullscreen = true;

	_dispositivoGrafico = createDevice(::EDT_OPENGL,//EDT_DIRECT3D9, 
		_gameConfig.parametrosVideo.WindowSize, 
		_gameConfig.parametrosVideo.Bits, 
		_gameConfig.parametrosVideo.Fullscreen, 
		_gameConfig.parametrosVideo.Stencilbuffer, 
		_gameConfig.parametrosVideo.Vsync, 									
		&_gerenciadorEventos);

	sWidth = _gameConfig.parametrosVideo.WindowSize.Width;
	sHeight = _gameConfig.parametrosVideo.WindowSize.Height;

	if(!_dispositivoGrafico)
	{
		cout << "\nERRO 0x00: Falha ao inicializar o dispositivo grafico.";
		startInit = ERRO;
	}

	if(startInit == SUCESSO)
	{
		_dispositivoAudio = createIrrKlangDevice();

		if(!_dispositivoAudio)
		{
			cout << "\nERRO 0x01: Falha ao inicializar o dispositivo de audio.";
			startInit = ERRO;
		}
	}

	_gerenciadorCena  = _dispositivoGrafico->getSceneManager();
	_gerenciadorVideo = _dispositivoGrafico->getVideoDriver();
	_gerenciadorHud   = _dispositivoGrafico->getGUIEnvironment();


	_dispositivoGrafico->setWindowCaption(tituloJanela.c_str());

	loadSkin(HS_PADRAO);

	_listaParticulas = new CListaParticulas();

	_gameData = new CGameData(_dispositivoGrafico);
	_gameScene = new CGameScene();

	for(int i = 0; i < CS_COUNT; i++)
		_cutScene[i] = CVideoTexture::createVideoTexture(_dispositivoGrafico, pathCutScene[i]);
}

//-----------------------------------------------------------------------------------------------------------------

IParticleSystemSceneNode* CGameCore::addPaticleNode(TypeParticle tipo, int tempoVida, vector3df posicao, vector3df escala)
{

	IParticleSystemSceneNode* ps = NULL;

	switch(tipo)
	{
	case P_FOGO:

		ps = _gerenciadorCena->addParticleSystemSceneNode(false);

		IParticleEmitter* emissor = ps->createBoxEmitter(
			aabbox3d<f32>(-5, 0, -5, 5, 1, 5), // tamanho do box do emissor
			vector3df(0.0f, 0.05f, 0.0f),      // direção inicial
			80, 100,                           // taxa de emissão
			SColor(0, 255, 255, 255),          // cor mais escura
			SColor(0, 255, 255, 255),          // cor mais clara
			(u32)tempoVida*0.4, tempoVida, 0,                      // idade mínima, máxima e ângulo
			dimension2df(5.0, 5.0),          // tamanho mínimo
			dimension2df(10.0, 10.0));         // tamanho máximo

		ps->setEmitter(emissor);
		emissor->drop();

		IParticleAffector* efeito = ps->createFadeOutParticleAffector();
		ps->addAffector(efeito);
		efeito->drop();

		ps->setPosition(posicao);
		ps->setScale(escala);

		ps->setMaterialFlag(EMF_LIGHTING, false);
		ps->setMaterialFlag(EMF_ZWRITE_ENABLE, false);
		ps->setMaterialTexture(0, _gerenciadorVideo->getTexture(pathParticleImage[P_FOGO]));
		ps->setMaterialType(EMT_TRANSPARENT_VERTEX_ALPHA);

		ps->setID(_particleCount); 
		_listaParticulas->addElement(ps, _particleCount);
		_particleCount++;

		break;
	};

	return ps;
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::addContour(ISceneNode* oNode, f32 fThickness, SColor cColor)
{
	if(!oNode) 
		return;

	SMaterial originalMaterial[MATERIAL_MAX_TEXTURES],
		tempMaterial;

	tempMaterial.DiffuseColor = tempMaterial.SpecularColor = tempMaterial.AmbientColor = tempMaterial.EmissiveColor = cColor;
	tempMaterial.Lighting = true;
	tempMaterial.Wireframe = true;
	tempMaterial.Thickness = fThickness;
	tempMaterial.FrontfaceCulling = true;
	tempMaterial.BackfaceCulling = false;

	for(u32 i=0; i<oNode->getMaterialCount(); i++)
	{
		originalMaterial[i] = oNode->getMaterial(i);
		oNode->getMaterial(i) = tempMaterial;
	}

	oNode->render();

	for(u32 i=0; i<oNode->getMaterialCount(); i++)
		oNode->getMaterial(i) = originalMaterial[i];
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::contourAll(ISceneNode* node) 
{ 
	if (node->getType() == ESNT_MESH || node->getType() == ESNT_ANIMATED_MESH )
	{
		if( node->getAutomaticCulling() != EAC_OFF)
			addContour(node);
	}  

	list<ISceneNode*>::ConstIterator begin = node->getChildren().begin(); 
	list<ISceneNode*>::ConstIterator end   = node->getChildren().end(); 

	for (; begin != end; ++begin) 
		contourAll(*begin); 
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::drop()
{
	if(_connected)
	{
		enviarPacote(DISCONNECT);
		_gameSocket->Close();
	}

	for(int i = 0; i < CS_COUNT; i++)
		_cutScene[i]->drop();

	_dispositivoGrafico->drop(); // Deleta o dispositivo grafico da memória
	_dispositivoAudio->drop();   // Deleta o dispositivo de audio da memória
}

//-----------------------------------------------------------------------------------------------------------------

IrrlichtDevice* CGameCore::getGraphicDevice()
{
	return this->_dispositivoGrafico;
}

//-----------------------------------------------------------------------------------------------------------------

ISoundEngine* CGameCore::getSoundDevice()
{
	return this->_dispositivoAudio;
}

//-----------------------------------------------------------------------------------------------------------------

CGerEventos * CGameCore::getEventManager()
{
	return (CGerEventos*)_dispositivoGrafico->getEventReceiver();
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::getAllManagers(IrrlichtDevice*&dispGrafico, ISoundEngine*&dispAudio, CGerEventos*&gerEventos, ISceneManager*&gerCena, IVideoDriver*&gerVideo, IGUIEnvironment*&gerHud, TypeCfg &gameCfg)
{
	dispGrafico = _dispositivoGrafico; 
	dispAudio   = _dispositivoAudio;
	gerEventos  = (CGerEventos*)_dispositivoGrafico->getEventReceiver();
	gerCena     = _gerenciadorCena;
	gerVideo    = _gerenciadorVideo; 
	gerHud      = _gerenciadorHud;
	gameCfg     = _gameConfig = _fileCfg->loadConfig();;

	gerCena->clear(); // Limpa toda a cena do jogo
	dispAudio->removeAllSoundSources(); // Remove todos os sons pendentes
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::loadSkin(int idSkin)
{
	IFileSystem* sistemaArquivos = _dispositivoGrafico->getFileSystem();

	SImageGUISkinConfig hudCfg = LoadGUISkinFromFile(sistemaArquivos, _gerenciadorVideo, pathHudSkin[idSkin]);

	_gameSkin = new CHudImageSkin(_gerenciadorVideo, _gerenciadorHud->getSkin());

	_gameSkin->loadConfig(hudCfg);

	_gameFont[FONT_PEQUENA] = _gerenciadorHud->getFont(pathFonts[FONT_PEQUENA]);
	_gameFont[FONT_GRANDE]	= _gerenciadorHud->getFont(pathFonts[FONT_GRANDE]);

	if (_gameFont[FONT_PEQUENA] && _gameFont[FONT_GRANDE])
	{
		_gameSkin->setFont(_gameFont[FONT_PEQUENA], EGDF_DEFAULT); // font padrão
		//_gameSkin->setFont(_gerenciadorHud->getBuiltInFont(), EGDF_BUTTON);  // botoes
		_gameSkin->setFont(_gameFont[FONT_GRANDE], EGDF_WINDOW);  // Titulo da janela
		//_gameSkin->setFont(_gerenciadorHud->getBuiltInFont(), EGDF_MENU);    // itens de menu
		//_gameSkin->setFont(_gerenciadorHud->getBuiltInFont(), EGDF_TOOLTIP); // tooltips
	}

	_gerenciadorHud->setSkin(_gameSkin);
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::playMusic( char* soundFile, bool looped, bool startPaused, bool track, E_STREAM_MODE modo, bool efeitos)
{
	_gameMusic = _dispositivoAudio->play2D(soundFile, looped, startPaused, track, modo, efeitos);
	_dispositivoAudio->setSoundVolume(_gameConfig.parametrosAudio.volumeMusica);
}

//-----------------------------------------------------------------------------------------------------------------

bool CGameCore::playCutScene( int idCutScene, int volume)
{
	if(volume > 100)
		volume = 100;

	if(volume < 0)
		volume = 0;

	_cutScene[idCutScene]->setVolume(volume);

	return _cutScene[idCutScene]->playCutscene();
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::loadMenuScene(c8* sceneFile)
{
	_gerenciadorCena->loadScene(sceneFile);
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::loadGameScene(c8* sceneFile)
{
	_gerenciadorCena->loadScene(sceneFile);
}

//-----------------------------------------------------------------------------------------------------------------

ICameraSceneNode* CGameCore::createCamera( vector3df posicao, vector3df target, vector3df rotacao, ISceneNode *parent, float angulo/*bool isOrtogonal*/, bool bind)
{
	_gameCamera = _gerenciadorCena->addCameraSceneNode(parent, posicao, target);

	_gameCamera->bindTargetAndRotation(bind);

	_gameCamera->setRotation(rotacao);
	/*
	if(angulo != 180.0f)
	_gameCamera->setFOV(PI / ( 180.0f / (180.0f - angulo)));
	else
	_gameCamera->setFOV(PI / ( 180.0f / (180.0f - 179.0f)));
	*/
	return _gameCamera;
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::createLight(ISceneNode *parent, vector3df posicao, f32 raio)
{
	_luz = _gerenciadorCena->addLightSceneNode(parent, posicao, SColorf(1.0f, 0.6f, 0.7f, 1.0f), raio);
}

//-----------------------------------------------------------------------------------------------------------------
/*
void CGameCore::loadGameData()
{
//_Data = new CGameData(_dispositivoGrafico);

_barraLoad = new CHudProgressBar(_gerenciadorHud->getRootGUIElement(), _gerenciadorHud, rect<s32>(10,150,610,180));

_barraLoad->setProgress(0.0);

int estagio = 0; // estágio de loading
float progresso = 0.000;

while(estagio < 6) // Carrega elementos do jogo
{
_gameData->loadStage(estagio);
_barraLoad->setProgress(_gameData->porcentagem/100.00);
estagio++;
}

_barraLoad->drop();	
}*/

void CGameCore::loadGameData(int stage)
{
	if(stage < LS_COUNT)
	{
		_gameData->loadStage(stage);
		_barraLoad->setProgress(_gameData->porcentagem/100.000);
	}
	else if(stage == LS_COUNT)
		_barraLoad->drop();
}

//-----------------------------------------------------------------------------------------------------------------

bool CGameCore::conectar(char *login, char *password)
{
	strcpy(_myLogin, "");
	strcpy(_myPassword, "");

	strcpy(_myLogin, login);
	strcpy(_myPassword, password);

	_packageToSend.init(_dataToSend, PACKAGESIZE);
	_packageReceived.init(_dataReceived, PACKAGESIZE);

	try
	{
		_gameSocket = new CBugSocketClient(SERVERHOST, SERVERPORT);

		enviarPacote(LOGIN_REQUEST, _myLogin, _myPassword);

		receberPacote();
	}
	catch(...)
	{
		_connected = false;
		cout << "\nNão foi possivel encontrar o servidor." << endl;
	}

	return _connected;
}

//--------------------------------------------------------------------------------------

void CGameCore::initToonShader()
{
	if(_luz!= NULL && _dispositivoGrafico != NULL)
		_toonShader = new CToonShader(_dispositivoGrafico, _luz);
}

//--------------------------------------------------------------------------------------

IAnimatedMesh* CGameCore::getMAnimMesh(int idMesh)
{
	return _gameData->dataGeometryChars[idMesh];
}

//--------------------------------------------------------------------------------------

ITexture* CGameCore::getMTexture(int idTexture)
{
	return _gameData->dataTxChars[idTexture];
}

//--------------------------------------------------------------------------------------

bool CGameCore::isConnected()
{
	return _connected;
}

//--------------------------------------------------------------------------------------

int CGameCore::getNumCharSlots()
{
	return _numMyChars;
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::enviarPacote(int packageID)
{
	_packageToSend.init(_dataToSend, sizeof(_dataToSend));
	_packageToSend.clear();

	_packageToSend.writeByte(packageID);

	_gameSocket->SendLine(_packageToSend);
}
//-----------------------------------------------------------------------------------------------------------------

void CGameCore::enviarPacote(int packageID, int i1)
{
	_packageToSend.init(_dataToSend, sizeof(_dataToSend));
	_packageToSend.clear();

	_packageToSend.writeByte(packageID);
	_packageToSend.writeLong(i1);

	_gameSocket->SendLine(_packageToSend);
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::enviarPacote(int packageID, int i1, int i2)
{
	_packageToSend.init(_dataToSend, sizeof(_dataToSend));
	_packageToSend.clear();

	_packageToSend.writeByte(packageID);
	_packageToSend.writeLong(i1);
	_packageToSend.writeLong(i2);

	_gameSocket->SendLine(_packageToSend);	
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::enviarPacote(int packageID, int i1, int i2, char *s1 )
{
	_packageToSend.init(_dataToSend, sizeof(_dataToSend));
	_packageToSend.clear();

	_packageToSend.writeByte(packageID);
	_packageToSend.writeLong(i1);
	_packageToSend.writeLong(i2);
	_packageToSend.writeString(s1);

	_gameSocket->SendLine(_packageToSend);	
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::enviarPacote(int packageID, int i1, int i2, int i3)
{
	_packageToSend.init(_dataToSend, sizeof(_dataToSend));
	_packageToSend.clear();

	_packageToSend.writeByte(packageID);
	_packageToSend.writeLong(i1);
	_packageToSend.writeLong(i2);
	_packageToSend.writeLong(i3);

	_gameSocket->SendLine(_packageToSend);
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::enviarPacote(int packageID, int i1, int i2, int i3, int i4)
{
	_packageToSend.init(_dataToSend, sizeof(_dataToSend));
	_packageToSend.clear();

	_packageToSend.writeByte(packageID);
	_packageToSend.writeLong(i1);
	_packageToSend.writeLong(i2);
	_packageToSend.writeLong(i3);
	_packageToSend.writeLong(i4);

	_gameSocket->SendLine(_packageToSend);
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::enviarPacote(int packageID, int i1, int i2, int i3, int i4, int i5, int i6)
{
	_packageToSend.init(_dataToSend, sizeof(_dataToSend));
	_packageToSend.clear();

	_packageToSend.writeByte(packageID);
	_packageToSend.writeLong(i1);
	_packageToSend.writeLong(i2);
	_packageToSend.writeLong(i3);
	_packageToSend.writeLong(i4);
	_packageToSend.writeLong(i5);
	_packageToSend.writeLong(i6);

	_gameSocket->SendLine(_packageToSend);
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::enviarPacote(int packageID, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9)
{
	_packageToSend.init(_dataToSend, sizeof(_dataToSend));
	_packageToSend.clear();

	_packageToSend.writeByte(packageID);
	_packageToSend.writeLong(i1);
	_packageToSend.writeLong(i2);
	_packageToSend.writeLong(i3);
	_packageToSend.writeLong(i4);
	_packageToSend.writeLong(i5);
	_packageToSend.writeLong(i6);
	_packageToSend.writeLong(i7);
	_packageToSend.writeLong(i8);
	_packageToSend.writeLong(i9);

	_gameSocket->SendLine(_packageToSend);
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::enviarPacote(int packageID, int i1, char *s1)
{
	_packageToSend.init(_dataToSend, sizeof(_dataToSend));
	_packageToSend.clear();

	_packageToSend.writeByte(packageID);
	_packageToSend.writeLong(i1);
	_packageToSend.writeString(s1);

	_gameSocket->SendLine(_packageToSend);
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::enviarPacote(int packageID, int i1, float f1, float f2)
{
	_packageToSend.init(_dataToSend, sizeof(_dataToSend));
	_packageToSend.clear();

	_packageToSend.writeByte(packageID);
	_packageToSend.writeLong(i1);
	_packageToSend.writeFloat(f1);
	_packageToSend.writeFloat(f2);

	_gameSocket->SendLine(_packageToSend);
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::enviarPacote(int packageID, int i1, int i2, int i3, float f1, float f2)
{
	_packageToSend.init(_dataToSend, sizeof(_dataToSend));
	_packageToSend.clear();

	_packageToSend.writeByte(packageID);
	_packageToSend.writeLong(i1);
	_packageToSend.writeLong(i2);
	_packageToSend.writeLong(i3);
	_packageToSend.writeFloat(f1);
	_packageToSend.writeFloat(f2);

	_gameSocket->SendLine(_packageToSend);
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::enviarPacote(int packageID, char *s1, char *s2)
{
	_packageToSend.init(_dataToSend, sizeof(_dataToSend));
	_packageToSend.clear();

	_packageToSend.writeByte(packageID);
	_packageToSend.writeString(s1);
	_packageToSend.writeString(s2);

	_gameSocket->SendLine(_packageToSend);
}

//-----------------------------------------------------------------------------------------------------------------

int CGameCore::receberPacote()
{
	int retorno = SUCESSO;

	_packageReceived.clear();
	_gameSocket->ReceiveLine(_packageReceived);

	if(_packageReceived.getSize() != 0) // Se o pacote não extiver vazio
	{
		_packageReceived.beginReading();

		switch(_packageReceived.readByte()) // Lê o byte de identificação do pacote
		{

		case SHOW_PERSONAGENS: // CODIGO: MOSTRAR PERSONAGENS DO JOGADOR

			_numMyChars = _packageReceived.readInt(); // número de personagens cadastrados

			for(int i=0; i<_numMyChars; i++)
			{
				_myStructChar[i]._id = _packageReceived.readInt();
				_myStructChar[i]._nome = _packageReceived.readString();
				_myStructChar[i]._nivel = _packageReceived.readInt();

				_myStructChar[i]._agilidade = _packageReceived.readInt();
				_myStructChar[i]._destreza = _packageReceived.readInt();
				_myStructChar[i]._forca = _packageReceived.readInt();
				_myStructChar[i]._instinto = _packageReceived.readInt();
				_myStructChar[i]._resistencia = _packageReceived.readInt();

				_myStructChar[i]._taxaAtaque = _packageReceived.readInt();
				_myStructChar[i]._tempoCarga = _packageReceived.readInt();
				_myStructChar[i]._defesa = _packageReceived.readInt();
				_myStructChar[i]._ataqueCorporal = _packageReceived.readInt();
				_myStructChar[i]._danoCorporal = _packageReceived.readInt();
				_myStructChar[i]._raioAtaque = _packageReceived.readInt();
				_myStructChar[i]._raioDano = _packageReceived.readInt();

				_myStructChar[i]._idModelo = _packageReceived.readInt();
				_myStructChar[i]._idTextura = _packageReceived.readInt();
				_myStructChar[i]._idHud = _packageReceived.readInt();

				_myChar[i] = _gerenciadorCena->addAnimatedMeshSceneNode( getMAnimMesh(_myStructChar[i]._idModelo), 0, _myStructChar[i]._id );
				_toonShader->apply( _myChar[i], pathTextureModels[_myStructChar[i]._idTextura] );
				_myChar[i]->setAnimationSpeed(5);

				switch (i)
				{
				case 0:
					_myChar[i]->setPosition(vector3df(-10,0,30));
					_myChar[i]->setRotation(vector3df(0,80,0));
					break;

				case 1:
					_myChar[i]->setPosition(vector3df(10,0,30));
					_myChar[i]->setRotation(vector3df(0,100,0));
					break;
				};
			}

			break;

		case  CREATE_PLAYER_OK: // CODIGO: CRIAÇÃO DE PERSONAGEM OK

			cout << "\nPersonagem criado com sucesso." << endl;

			break;

		case  CREATE_PLAYER_FAIL: // CODIGO: CRIAÇÃO DE PERSONAGEM FALHOU

			retorno = ERRO;
			cout << "\nErro ao criar personagem." << endl;

			break;

		case  DELETE_PLAYER_OK: // CODIGO: REMOÇÃO DE PERSONAGEM OK

			cout << "\nPersonagem excluido com sucesso." << endl;

			break;

		case  DELETE_PLAYER_FAIL: // CODIGO: REMOÇÃO DE PERSONAGEM FALHOU

			retorno = ERRO;
			cout << "\nErro ao excluir personagem." << endl;

			break;


		case LOGIN_OK: // CODIGO: LOGIN EFETUADO COM SUCESSO

			_myUserID = _packageReceived.readInt();
			cout << "\nConectado." << endl;
			_connected = true;

			break;

		case  LOGIN_FAIL: // CODIGO: FALHA NA AUTENTICAÇÃO DO LOGIN

			cout << "\nFalha ao conectar. Verificar login e senha." << endl;
			enviarPacote(DISCONNECT);
			_gameSocket->Close();
			_connected = false;
			retorno = ERRO;

			break;

		default: // CODIGO: MENSAGEM NÃO IDENTIFICADA, DESCONECTAR

			cout << "\nMensagem desconhecida do servidor." << endl;
			enviarPacote(DISCONNECT);
			_gameSocket->Close();
			_connected = false;
			retorno = ERRO;
		};
	}
	else // CODIGO: SERVIDOR NÃO RESPONDE
	{
		cout << "\nServidor não responde." << endl;
		enviarPacote(DISCONNECT);
		_gameSocket->Close();
		_connected = false;
		retorno = ERRO;
	}

	return retorno;
}