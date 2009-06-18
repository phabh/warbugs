#include "CGameCore.h"

//-----------------------------------------------------------------------------------------------------------------

CGameCore::CGameCore(int &startInit)
{
	startInit = SUCESSO;

	_connected = false;

	_numMyChars = 0;
	_myUserID = -1;
	_myCharID = -1;
	_myCharSceneID = -1;
	_myMapSceneID = -1;



	_particleCount = 0;

	strcpy(_myLogin, "");
	strcpy(_myPassword, "");

	_fileCfg = new CArquivoConfig();

	//_fileCfg->reset();

	_gameConfig = _fileCfg->loadConfig();

	/*
	RECT desktop; // Faz uma refer�ncia para a tela do desktop   
	const HWND hDesktop = GetDesktopWindow(); // Captura a dimens�o da tela 
	GetWindowRect(hDesktop, &desktop);  */ 

	//_gameConfig->parametrosVideo.WindowSize.Width = 1024;//desktop.right;
	//_gameConfig->parametrosVideo.WindowSize.Height = 768;//desktop.bottom;
	//_gameConfig->parametrosVideo.Fullscreen = true;

	_dispositivoGrafico = createDevice(EDT_OPENGL,//EDT_DIRECT3D9, 
		_gameConfig.parametrosVideo.WindowSize, 
		_gameConfig.parametrosVideo.Bits, 
		false,//_gameConfig.parametrosVideo.Fullscreen, 
		_gameConfig.parametrosVideo.Stencilbuffer, 
		_gameConfig.parametrosVideo.Vsync, 									
		&_gerenciadorEventos);

	sWidth = _gameConfig.parametrosVideo.WindowSize.Width;
	sHeight = _gameConfig.parametrosVideo.WindowSize.Height;

	if(!_dispositivoGrafico)
	{
		cout << "\nERRO 0x00: Falha ao inicializar o dispositivo grafico.";
		startInit = ERRO_SAIR;
	}

	if(startInit == SUCESSO)
	{
		_dispositivoAudio = createIrrKlangDevice();

		if(!_dispositivoAudio)
		{
			cout << "\nERRO 0x01: Falha ao inicializar o dispositivo de audio.";
			startInit = ERRO_SAIR;
		}
	}

	_gerenciadorCena  = _dispositivoGrafico->getSceneManager();
	_gerenciadorVideo = _dispositivoGrafico->getVideoDriver();
	_gerenciadorHud   = _dispositivoGrafico->getGUIEnvironment();


	_dispositivoGrafico->setWindowCaption(tituloJanela.c_str());

	loadSkin(HS_PADRAO);

	_listaParticulas = new CListaParticulas();

	_gameData = new CGameData(_dispositivoGrafico);
	//_gameScene = new CGameScene();

	_listaPersonagens = new ListaPersonagem();
	_listaBolsas = new ListaBolsa();

	_fileMtx = new CArquivoMatrizes();
	//_fileMtx->reset();
	/*
	for(int i = 0; i < CS_COUNT; i++)
	_cutScene[i] = CVideoTexture::createVideoTexture(_dispositivoGrafico, pathCutScene[i]);*/
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
			vector3df(0.0f, 0.05f, 0.0f),      // dire��o inicial
			80, 100,                           // taxa de emiss�o
			SColor(0, 255, 255, 255),          // cor mais escura
			SColor(0, 255, 255, 255),          // cor mais clara
			(u32)tempoVida*0.4, tempoVida, 0,                      // idade m�nima, m�xima e �ngulo
			dimension2df(5.0, 5.0),          // tamanho m�nimo
			dimension2df(10.0, 10.0));         // tamanho m�ximo

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

float CGameCore::getDistancia(vector3df v1, vector3df v2)
{
	float dx = abs(v1.X - v2.X);
	float dz = abs(v1.Z - v2.Z);

	return sqrt(dx*dx + dz*dz);
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
		if( getDistancia(node->getAbsolutePosition(), _gameCamera->getAbsolutePosition()) > 300)
		{		
			node->setVisible(false);
		}
		else
		{
			node->setVisible(true);
			if( node->getAutomaticCulling() != EAC_OFF)
				addContour(node);
		}  
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

	//for(int i = 0; i < CS_COUNT; i++)
	//	_cutScene[i]->drop();

	_dispositivoGrafico->drop(); // Deleta o dispositivo grafico da mem�ria
	_dispositivoAudio->drop();   // Deleta o dispositivo de audio da mem�ria
}

//-----------------------------------------------------------------------------------------------------------------

vector3df CGameCore::rotacaoResultante(f32 rotX, f32 rotY, f32 rotZ)
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
	gameCfg     = _gameConfig = _fileCfg->loadConfig();

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
		_gameSkin->setFont(_gameFont[FONT_PEQUENA], EGDF_DEFAULT); // font padr�o
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

	if(_myMapSceneID >=0)
	{
		_sceneTerrain = (ITerrainSceneNode*)_gerenciadorCena->getSceneNodeFromType(ESNT_TERRAIN, 0);

		_sceneTris = _gerenciadorCena->createTerrainTriangleSelector(_sceneTerrain, 0);
		//createTerrainTriangleSelector (_sceneTerrain->getTriangleSelector();

		_sceneTerrain->setTriangleSelector(_sceneTris); 
	}
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

int estagio = 0; // est�gio de loading
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

SMatrix CGameCore::loadSceneMatrix(int idScene)
{
	_cenario = _fileMtx->getMatrix(idScene);

	return(_cenario);
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::addBolsa(int idBolsa, float posX, float posZ)
{
	// Inclui uma bolsa no cen�rio
	SBolsa *bolsa = new SBolsa();

	bolsa->_idBolsa = idBolsa;
	bolsa->posicao = upd3DPosition(posX, posZ);

	_listaBolsas->addElement(bolsa, bolsa->_idBolsa);
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::addPersonagem( CPersonagem *personagem )
{
	int r = personagem->_raca;
	int c = personagem->_classe;

	personagem->_modelo = _gerenciadorCena->addAnimatedMeshSceneNode(_gerenciadorCena->getMesh(pathMtxCharsModels[r][c]));
	personagem->_modelo->setMaterialFlag(EMF_LIGHTING, false);
	personagem->_modelo->setMaterialTexture(0, _gerenciadorVideo->getTexture(pathMtxCharsTextures[r][c]));
	personagem->_modelo->setPosition(personagem->_posicao);

	_listaPersonagens->addElement(personagem, personagem->getId());

	if(personagem->getId() == _myCharSceneID)
	{
		_myPlayerChar = personagem;

		_emptyCam = _gerenciadorCena->addEmptySceneNode();
		_emptyCam->setPosition(_myPlayerChar->_posicao);
		_gameCamera->setParent(_emptyCam);
		_gameCamera->setPosition( vector3df(-20,20,0));
		_gameCamera->setTarget(_emptyCam->getPosition());
	}
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::removeBolsa(int idBolsa)
{
	// Remove uma bolsa do cen�rio do cliente
	_listaBolsas->removeElement(idBolsa);
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::removePersonagem( int idPersonagem )
{
	_listaPersonagens->removeElement(idPersonagem);
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::updMoon(int idLua)
{
	_sceneMoon = idLua;
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::updMapPortals(int idQuadPortal1, int idQuadPortal2, int idQuadPortal3, int idQuadPortal4)
{
	_portal[0]._id = idQuadPortal1;
	getQuadLinhaColuna(idQuadPortal1,  _portal[0]._linha, _portal[0]._coluna);
	_portal[0]._center = getQuadCenter(_portal[0]._linha, _portal[0]._coluna);

	_portal[1]._id = idQuadPortal2;
	getQuadLinhaColuna(idQuadPortal2,  _portal[1]._linha, _portal[1]._coluna);
	_portal[1]._center = getQuadCenter(_portal[1]._linha, _portal[1]._coluna);

	_portal[2]._id = idQuadPortal3;
	getQuadLinhaColuna(idQuadPortal3,  _portal[2]._linha, _portal[2]._coluna);
	_portal[2]._center = getQuadCenter(_portal[2]._linha, _portal[2]._coluna);

	_portal[3]._id = idQuadPortal4;
	getQuadLinhaColuna(idQuadPortal4,  _portal[3]._linha, _portal[3]._coluna);
	_portal[3]._center = getQuadCenter(_portal[3]._linha, _portal[3]._coluna);
}

//-----------------------------------------------------------------------------------------------------------------

vector3df CGameCore::getQuadCenter(int linha, int coluna)
{
	vector3df center;

	center.X = (linha * TAMQUADRANTE) + (TAMQUADRANTE/2);
	center.Y = 0.0;
	center.Z = (coluna * TAMQUADRANTE) + (TAMQUADRANTE/2);

	return center;
}

//-----------------------------------------------------------------------------------------------------------------

vector3df CGameCore::getQuadCenter(int idQuad)
{
	int linha, coluna;

	getQuadLinhaColuna(idQuad, linha, coluna);

	return getQuadCenter(linha, coluna);
}

//-----------------------------------------------------------------------------------------------------------------

vector3df CGameCore::getQuadCenter(vector3df posicao)
{
	int linha, coluna;

	getQuadLinhaColuna(posicao, linha, coluna);

	return getQuadCenter(linha, coluna);
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::getQuadLinhaColuna(vector3df posicao, int &linha, int &coluna)
{
	linha  = posicao.Z / TAMQUADRANTE; // TAMQUADRANTE � a dimens�o de um quadrante em pixels
	coluna = posicao.X / TAMQUADRANTE;
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::getQuadLinhaColuna(int idQuad, int &linha, int &coluna)
{
	linha  = idQuad / MAPMAXCOL;
	coluna = idQuad % MAPMAXCOL;
}

//-----------------------------------------------------------------------------------------------------------------

int CGameCore::getQuadID(vector3df posicao)
{
	int linha, coluna;

	getQuadLinhaColuna(posicao, linha, coluna);

	return getQuadID(linha, coluna);
}

//-----------------------------------------------------------------------------------------------------------------

int CGameCore::getQuadID(int linha, int coluna)
{
	return ( coluna + (linha * MAPMAXCOL) );
}

//-----------------------------------------------------------------------------------------------------------------

bool CGameCore::conectar(char *login, char *password)
{
	int retorno = PING_REQUEST;

	strcpy(_myLogin, "");
	strcpy(_myPassword, "");

	strcpy(_myLogin, login);
	strcpy(_myPassword, password);

	//_packageToSend.init(_dataToSend, PACKAGESIZE);
//	_packageReceived.init(_dataReceived, PACKAGESIZE);

	try
	{

		_gameSocket = new CBugSocketClient(SERVERHOST, SERVERPORT);

		//CBugSocketSelect::CBugSocketSelect(_gameSocket, 0, NonBlockingSocket);

		enviarPacote(LOGIN_REQUEST, _myLogin, _myPassword);

		while(retorno == PING_REQUEST)
			retorno = receberPacote();
	}
	catch(...)
	{
		_connected = false;
		cout << "\nN�o foi possivel encontrar o servidor." << endl;
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

//--------------------------------------------------------------------------------------

vector3df CGameCore::upd3DPosition(float posX, float posZ)
{
	return vector3df(posX, _sceneTerrain->getHeight(posX, posZ), posZ);
}

//--------------------------------------------------------------------------------------

int CGameCore::manhattan(int linhaO, int colunaO, int linhaD, int colunaD)
{
	int deltaL, deltaC;

	deltaL = abs(linhaD - linhaO);
	deltaC = abs(colunaD - colunaO);

	return deltaL + deltaC;
}

//--------------------------------------------------------------------------------------

int CGameCore::pathfindingRTA(CPersonagem *personagem)
{

	vector3df origem = personagem->_posicao;
	vector3df destino = personagem->_destino;

	int direcaoProximoPasso = -1;

	int idQuadSucessor = -1;

	int idQuadOrigem  = getQuadID(origem);
	int idQuadDestino = getQuadID(destino);

	int melhorVizinho1 = -1;
	int melhorVizinho2 = -1;

	int lin_o, col_o, lin_d, col_d;

	int custoFuncao[8];

	int custoVizinho, menorCusto1, menorCusto2;

	menorCusto1 = 9999999;
	menorCusto2 = 9999999;

	int custoAdjacencia = 0;

	float lembranca;

	getQuadLinhaColuna(idQuadDestino, lin_d, col_d);

	for (int i = 0; i < 8; i++)
	{

		getQuadLinhaColuna(idQuadOrigem, lin_o, col_o);


		switch (i)
		{
		default:
		case 0: col_o +=  0; lin_o +=  1; custoAdjacencia = 1; break;  // Norte
		case 1: col_o +=  1; lin_o +=  1; custoAdjacencia = 2; break;  // Nordeste
		case 2: col_o +=  1; lin_o +=  0; custoAdjacencia = 1; break;  // Leste
		case 3: col_o +=  1; lin_o += -1; custoAdjacencia = 2; break;  // Sudeste
		case 4: col_o +=  0; lin_o += -1; custoAdjacencia = 1; break;  // Sul
		case 5: col_o += -1; lin_o += -1; custoAdjacencia = 2; break;  // Sudoeste
		case 6: col_o += -1; lin_o +=  0; custoAdjacencia = 1; break;  // Oeste
		case 7: col_o += -1; lin_o +=  1; custoAdjacencia = 2; break;  // Noroeste
		}

		if (_cenario.isPassable[lin_o][col_o])
		{
			idQuadSucessor = getQuadID(lin_o, col_o); // pega indice do quadrante vizinho  

			lembranca = personagem->_memoria.Pesquisar(idQuadSucessor); // procura na mem�ria o indice do sucessor

			if (lembranca == NULL)
				custoFuncao[i] = manhattan(lin_o, col_o, lin_d, col_d) + custoAdjacencia;
			else
				custoFuncao[i] = lembranca + custoAdjacencia;


			if (custoFuncao[i] < menorCusto1)
			{
				melhorVizinho2 = melhorVizinho1;
				menorCusto2 = menorCusto1; // atualiza o segundo menor

				melhorVizinho1 = idQuadSucessor;
				menorCusto1 = custoFuncao[i];
				direcaoProximoPasso = i;
			}

		}
		else
			custoFuncao[i] = 9999999;
	}

	if (melhorVizinho2 == -1) // se teve apenas uma op��o de movimento, segundo menor = menor de todos
	{
		melhorVizinho2 = melhorVizinho1;
		menorCusto2 = menorCusto1;
	}

	if (melhorVizinho2 != -1) // se teve alguma op��o de movimento
		personagem->_memoria.Inserir(idQuadOrigem, menorCusto2);

	if(idQuadDestino == melhorVizinho1)
		personagem->_memoria.Reset();

	return direcaoProximoPasso;
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::enviarPacote(int packageID)
{
	char _dataToSend[PACKAGESIZE];
	_packageToSend.init(_dataToSend, sizeof(_dataToSend));
	_packageToSend.clear();

	_packageToSend.writeInt(0);
	_packageToSend.writeInt(packageID);

	std::string temp;
	temp.append(_packageToSend._data);
	_gameSocket->SendBytes(temp);

	if(packageID == DISCONNECT)
		Sleep(100);
}
//-----------------------------------------------------------------------------------------------------------------

void CGameCore::enviarPacote(int packageID, int i1)
{
	char _dataToSend[PACKAGESIZE];
	_packageToSend.init(_dataToSend, sizeof(_dataToSend));
	_packageToSend.clear();

	_packageToSend.writeInt(0);
	_packageToSend.writeInt(packageID);
	_packageToSend.writeInt(i1);

	_gameSocket->SendLine(_packageToSend);
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::enviarPacote(int packageID, int i1, int i2)
{
	char _dataToSend[PACKAGESIZE];
	_packageToSend.init(_dataToSend, sizeof(_dataToSend));
	_packageToSend.clear();

	_packageToSend.writeInt(0);
	_packageToSend.writeInt(packageID);
	_packageToSend.writeInt(i1);
	_packageToSend.writeInt(i2);

	_gameSocket->SendLine(_packageToSend);
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::enviarPacote(int packageID, int i1, int i2, char *s1 )
{
	char _dataToSend[PACKAGESIZE];
	_packageToSend.init(_dataToSend, sizeof(_dataToSend));
	_packageToSend.clear();

	_packageToSend.writeInt(0);
	_packageToSend.writeInt(packageID);
	_packageToSend.writeInt(i1);
	_packageToSend.writeInt(i2);
	_packageToSend.writeString(s1);

	_gameSocket->SendLine(_packageToSend);
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::enviarPacote(int packageID, int i1, int i2, int i3)
{
	char _dataToSend[PACKAGESIZE];
	_packageToSend.init(_dataToSend, sizeof(_dataToSend));
	_packageToSend.clear();

	_packageToSend.writeInt(0);
	_packageToSend.writeInt(packageID);
	_packageToSend.writeInt(i1);
	_packageToSend.writeInt(i2);
	_packageToSend.writeInt(i3);

	_gameSocket->SendLine(_packageToSend);
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::enviarPacote(int packageID, int i1, int i2, int i3, int i4)
{
	char _dataToSend[PACKAGESIZE];
	_packageToSend.init(_dataToSend, sizeof(_dataToSend));
	_packageToSend.clear();

	_packageToSend.writeInt(0);
	_packageToSend.writeInt(packageID);
	_packageToSend.writeInt(i1);
	_packageToSend.writeInt(i2);
	_packageToSend.writeInt(i3);
	_packageToSend.writeInt(i4);

	_gameSocket->SendLine(_packageToSend);
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::enviarPacote(int packageID, int i1, int i2, int i3, int i4, int i5, int i6)
{
	char _dataToSend[PACKAGESIZE];
	_packageToSend.init(_dataToSend, sizeof(_dataToSend));
	_packageToSend.clear();

	_packageToSend.writeInt(0);
	_packageToSend.writeInt(packageID);
	_packageToSend.writeInt(i1);
	_packageToSend.writeInt(i2);
	_packageToSend.writeInt(i3);
	_packageToSend.writeInt(i4);
	_packageToSend.writeInt(i5);
	_packageToSend.writeInt(i6);

	_gameSocket->SendLine(_packageToSend);
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::enviarPacote(int packageID, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9)
{
	char _dataToSend[PACKAGESIZE];
	_packageToSend.init(_dataToSend, sizeof(_dataToSend));
	_packageToSend.clear();

	_packageToSend.writeInt(0);
	_packageToSend.writeInt(packageID);
	_packageToSend.writeInt(i1);
	_packageToSend.writeInt(i2);
	_packageToSend.writeInt(i3);
	_packageToSend.writeInt(i4);
	_packageToSend.writeInt(i5);
	_packageToSend.writeInt(i6);
	_packageToSend.writeInt(i7);
	_packageToSend.writeInt(i8);
	_packageToSend.writeInt(i9);

	_gameSocket->SendLine(_packageToSend);
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::enviarPacote(int packageID, int i1, char *s1)
{
	char _dataToSend[PACKAGESIZE];
	_packageToSend.init(_dataToSend, sizeof(_dataToSend));
	_packageToSend.clear();

	_packageToSend.writeInt(0);
	_packageToSend.writeInt(packageID);
	_packageToSend.writeInt(i1);
	_packageToSend.writeString(s1);

	_gameSocket->SendLine(_packageToSend);
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::enviarPacote(int packageID, int i1, float f1, float f2)
{
	char _dataToSend[PACKAGESIZE];
	_packageToSend.init(_dataToSend, sizeof(_dataToSend));
	_packageToSend.clear();

	_packageToSend.writeInt(0);
	_packageToSend.writeInt(packageID);
	_packageToSend.writeInt(i1);
	_packageToSend.writeFloat(f1);
	_packageToSend.writeFloat(f2);

	_gameSocket->SendLine(_packageToSend);
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::enviarPacote(int packageID, int i1, int i2, int i3, float f1, float f2)
{
	char _dataToSend[PACKAGESIZE];
	_packageToSend.init(_dataToSend, sizeof(_dataToSend));
	_packageToSend.clear();

	_packageToSend.writeInt(0);
	_packageToSend.writeInt(packageID);
	_packageToSend.writeInt(i1);
	_packageToSend.writeInt(i2);
	_packageToSend.writeInt(i3);
	_packageToSend.writeFloat(f1);
	_packageToSend.writeFloat(f2);

	_gameSocket->SendLine(_packageToSend);
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::enviarPacote(int packageID, char *s1, char *s2)
{
	char _dataToSend[PACKAGESIZE];
	_packageToSend.init(_dataToSend, sizeof(_dataToSend));
	_packageToSend.clear();

	_packageToSend.writeInt(0);
	_packageToSend.writeInt(packageID);
	_packageToSend.writeString(s1);
	_packageToSend.writeString(s2);

	_gameSocket->SendLine(_packageToSend);
}

//-----------------------------------------------------------------------------------------------------------------

int CGameCore::receberPacote()
{
	int retorno = SUCESSO;

	short buffs;

	float x, z;

	int potencia;

	int i;

	CPersonagem *personagem = new CPersonagem();
	
	char _dataReceived[PACKAGESIZE];

	_packageReceived.init(_dataReceived, PACKAGESIZE);

	_packageReceived.clear();

	_gameSocket->ReceiveLine(_packageReceived);

	if(_packageReceived.getSize() != 0) // Se o pacote n�o extiver vazio
	{
		_packageReceived.beginReading();

		i = _packageReceived.readInt();

		

		if(i == 0)
		{
			i = _packageReceived.readInt();

			switch(i) // L� o byte de identifica��o do pacote
			{

			case SHOW_PERSONAGENS: // CODIGO: MOSTRAR PERSONAGENS DO JOGADOR

				_numMyChars = _packageReceived.readInt(); // n�mero de personagens cadastrados

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
					_myChar[i]->setMaterialFlag(EMF_LIGHTING, false);
					_myChar[i]->setMaterialTexture(0, _gerenciadorVideo->getTexture(pathTextureModels[_myStructChar[i]._idTextura]));


					//	_toonShader->apply( _myChar[i], pathTextureModels[_myStructChar[i]._idTextura] );
					_myChar[i]->setAnimationSpeed(5);

					switch (i)
					{
					case 0:
						_myChar[i]->setPosition(vector3df(-10,-5,30));
						_myChar[i]->setRotation(vector3df(0,-10,0));
						break;

					case 1:
						_myChar[i]->setPosition(vector3df(10,-5,30));
						_myChar[i]->setRotation(vector3df(0,20,0));
						break;
					};
				}

				break;

			case ENTER_CENARIO: // CODIGO: ENTROU EM UM CEN�RIO COM SUCESSO.


				_myMapSceneID  = _packageReceived.readInt();
				loadGameScene(pathCenario[_myMapSceneID]);

				_myCharSceneID = _packageReceived.readInt();

				updMapPortals(_packageReceived.readInt(), _packageReceived.readInt(), _packageReceived.readInt(), _packageReceived.readInt());

				cout << "\nPersonagem entrou no cen�rio." << endl;

				break;

			case  START_GAME_FAIL: // CODIGO: INICIALIZA��O DO CEN�RIO FALHOU.

				enviarPacote(DISCONNECT);
				_gameSocket->Close();
				_connected = false;
				retorno = ERRO_SAIR;
				cout << "\nErro ao inicializar o cen�rio." << endl;

				break;

			case  UPDATE_POSITION: // CODIGO: ATUALIZA A POSI��O DE UM PERSONAGEM

				personagem = _listaPersonagens->getElement(_packageReceived.readInt());

				x = (_packageReceived.readInt()/100.00);		
				z = (_packageReceived.readInt()/100.00);
				personagem->_posicao = upd3DPosition(x,z);
				personagem->_modelo->setPosition(personagem->_posicao);
				personagem->_direcao = (_packageReceived.readInt()/100.00); 

				//cout << "\nPosi��o de personagem atualizada." << endl;

				break;

			case ADD_PERSONAGEM: // CODIGO: INSER��O DE PERSONAGEM NO CEN�RIO

				personagem->_id = _packageReceived.readInt();
				//personagem->_nome = new char[30];
				//strcpy(personagem->_nome, _packageReceived.readString());
				personagem->_posicao = upd3DPosition(_packageReceived.readFloat(), _packageReceived.readFloat());

				personagem->_pv = _packageReceived.readInt();
				personagem->_pp = _packageReceived.readInt();
				personagem->_xp = _packageReceived.readInt();

				personagem->_pvMax = _packageReceived.readInt();
				personagem->_ppMax = _packageReceived.readInt();
				personagem->_xpMax = _packageReceived.readInt();

				personagem->_nivel = _packageReceived.readInt();

				buffs = _packageReceived.readShort();

				for(int i = 0; i < BUFF_COUNT; i++)
				{
					potencia = 1;

					for(int j = 0; j < i; j++)
						potencia = potencia * 2;

					personagem->_buff[i] = (bool)(buffs & potencia);
				}

				//for(int i=0; i<BUFF_COUNT; i++)
				//	 buffs & pow(2, i);

				personagem->_raca = _packageReceived.readInt();
				personagem->_classe = _packageReceived.readInt();
				personagem->_estado = _packageReceived.readInt();

				personagem->_ultimoEstado = personagem->_estado;

				personagem->_velAnim = _packageReceived.readFloat();

				personagem->_direcao = _packageReceived.readInt();
				personagem->_idBaseArma = _packageReceived.readInt();
				personagem->_idBaseArmadura = _packageReceived.readInt();

				addPersonagem(personagem);
				//Sleep(1);

				break;

			case ADD_BOLSA: // CODIGO: ADICIONAR BOLSA AO CEN�RIO

				addBolsa(_packageReceived.readInt(), _packageReceived.readFloat(), _packageReceived.readFloat());
				cout << "\nBolsa inserida no cen�rio." << endl;

				break;

			case REMOVE_BOLSA: // CODIGO: REMOVER BOLSA DO CEN�RIO

				removeBolsa(_packageReceived.readInt());
				cout << "\nBolsa removida do cen�rio." << endl;

				break;

			case SCENE_FULL: // CODIGO: FALHA AO ENTRAR NO CEN�RIO. CAPACIDADE M�XIMA ATINGIDA.

				cout << "\nO cen�rio de destino atingiu a capacidade m�xima." << endl;

				break;

			case PING: // CODIGO: PING.

				retorno = PING_REQUEST;
				enviarPacote(PING);
				cout << "\nPing." << endl;

				break;

			case NO_LOYALTY: // CODIGO: FALHA AO ENTRAR NO CEN�RIO. FALTA LEALDADE.

				cout << "\nSeu personagem n�o possui lealdade suficiente para entrar nesse cen�rio." << endl;

				break;

			case PORTAL_FAIL: // CODIGO: FALHA AO CARREGAR O NOVO CEN�RIO. 

				enviarPacote(DISCONNECT);
				_gameSocket->Close();
				_connected = false;
				retorno = ERRO_SAIR;

				cout << "\nFalha ao carregar o novo cen�rio." << endl;

				break;

			case  CREATE_PLAYER_OK: // CODIGO: CRIA��O DE PERSONAGEM OK

				cout << "\nPersonagem criado com sucesso." << endl;

				break;

			case  CREATE_PLAYER_FAIL: // CODIGO: CRIA��O DE PERSONAGEM FALHOU

				retorno = ERRO_CONTINUE;
				cout << "\nErro ao criar personagem." << endl;

				break;

			case  DELETE_PLAYER_OK: // CODIGO: REMO��O DE PERSONAGEM OK

				cout << "\nPersonagem excluido com sucesso." << endl;

				break;

			case  DELETE_PLAYER_FAIL: // CODIGO: REMO��O DE PERSONAGEM FALHOU

				retorno = ERRO_CONTINUE;
				cout << "\nErro ao excluir personagem." << endl;

				break;

			case  END_FRAME: // CODIGO: FINAL DE UM CICLO DE PACOTES

				retorno = FINAL_PACOTES;
				//cout << "\nEnd-Frame." << endl;

				break;


			case LOGIN_OK: // CODIGO: LOGIN EFETUADO COM SUCESSO

				_myUserID = _packageReceived.readInt();
				cout << "\nConectado." << endl;
				_connected = true;

				break;

			case  LOGIN_FAIL: // CODIGO: FALHA NA AUTENTICA��O DO LOGIN

				cout << "\nFalha ao conectar. Verificar login e senha." << endl;
				enviarPacote(DISCONNECT);
				_gameSocket->Close();
				_connected = false;
				retorno = ERRO_SAIR;

				break;

			case  DOUBLE_LOGIN: // CODIGO: FALHA DE LOGIN SIMULT�NEO

				cout << "\nErro de login simultaneo." << endl;
				//enviarPacote(DISCONNECT);
				_gameSocket->Close();
				_connected = false;
				retorno = ERRO_SAIR;

				break;

			case  DISCONNECT: // CODIGO: RECEBEU DISCONNECT DO SERVIDOR

				cout << "\nO servidor te desconectou." << endl;
				//enviarPacote(DISCONNECT);
				_gameSocket->Close();
				_connected = false;
				retorno = ERRO_SAIR;

				break;

			default: 
				cout << "\n i:" << i << endl;
				break;// CODIGO: MENSAGEM N�O IDENTIFICADA, DESCONECTAR

				//cout << "\nMensagem desconhecida do servidor." << endl;
				//enviarPacote(DISCONNECT);
				//_gameSocket->Close();
				//_connected = false;
				//retorno = ERRO_SAIR;
			};
		}
		else
			cout << "\nLixo:" << i << endl;
	}
	else // CODIGO: SERVIDOR N�O RESPONDE
	{
		cout << "\nServidor n�o responde." << endl;
		enviarPacote(DISCONNECT);
		_gameSocket->Close();
		_connected = false;
		retorno = ERRO_SAIR;
	}

	return retorno;
}