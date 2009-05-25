#include "CGameCore.h"

//-----------------------------------------------------------------------------------------------------------------

CGameCore::CGameCore(int &startInit)
{
	startInit = SUCESSO;

	_connected = false;

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

	_dispositivoGrafico = createDevice(EDT_DIRECT3D9, 
		_gameConfig.parametrosVideo.WindowSize, 
		_gameConfig.parametrosVideo.Bits, 
		_gameConfig.parametrosVideo.Fullscreen, 
		_gameConfig.parametrosVideo.Stencilbuffer, 
		_gameConfig.parametrosVideo.Vsync, 									
		&_gerenciadorEventos);

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

	_gameSkin = _gerenciadorHud->getSkin();
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
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::drop()
{
	if(_connected)
	{
		_packageToSend.init(_dataToSend, PACKAGESIZE);
		_packageToSend.writeByte(0);
		_gameSocket->SendLine(_packageToSend);
		_gameSocket->Close();
	}
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


void CGameCore::playMusic( char* soundFile, bool looped, bool startPaused, bool track, E_STREAM_MODE modo, bool efeitos)
{
	_gameMusic = _dispositivoAudio->play2D(soundFile, looped, startPaused, track, modo, efeitos);
	_dispositivoAudio->setSoundVolume(_gameConfig.parametrosAudio.volumeMusica);
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

void CGameCore::loadGameData()
{
	_Data = new CGameData(_dispositivoGrafico);

	int estagio = 0; // estágio de loading

	while(estagio < 6) // Carrega elementos do jogo
	{
		_Data->loadStage(estagio);
		estagio++;
	}
}

//-----------------------------------------------------------------------------------------------------------------

bool CGameCore::conectar(char *login, char *password)
{
	char idPackage;

	strcpy(_myLogin, "");
	strcpy(_myPassword, "");

	strcpy(_myLogin, login);
	strcpy(_myPassword, password);

	_packageToSend.init(_dataToSend, PACKAGESIZE);
	_packageReceived.init(_dataReceived, PACKAGESIZE);

	try
	{
		_gameSocket = new CBugSocketClient(SERVERHOST, SERVERPORT);

		// Monta pacote
		_packageToSend.writeByte(LOGIN_REQUEST); // ID do pacote: LOGIN_REQUEST
		_packageToSend.writeString(_myLogin);      // Param1: login
		_packageToSend.writeString(_myPassword);   // Param2: senha

		// Envia pacote montado
		_gameSocket->SendLine(_packageToSend);

		// Recebe pacote de resposta
		_gameSocket->ReceiveLine(_packageReceived);

		// Se o pacote conter dados
		if(_packageReceived.getSize() > 0)
		{
			_packageReceived.beginReading();

			idPackage = _packageReceived.readByte();

			// Sucesso
			if(idPackage == LOGIN_OK)
			{
				cout << "\nConectado." << endl;
				_connected = true;
			}

			// Falha
			else if(idPackage == LOGIN_FAIL)
			{
				cout << "\nFalha ao conectar. Verificar login e senha." << endl;
				_packageToSend.init(_dataToSend, PACKAGESIZE);
				_packageToSend.writeByte(0);
				_gameSocket->SendLine(_packageToSend);
				_gameSocket->Close();
				_connected = false;
			}

			// Erro desconhecido
			else
			{
				cout << "\nMensagem inesperada do servidor" << endl;
				_packageToSend.init(_dataToSend, PACKAGESIZE);
				_packageToSend.writeByte(0);
				_gameSocket->SendLine(_packageToSend);
				_gameSocket->Close();
				_connected = false;
			}
		}

		// Pacote recebido está vazio
		else
		{
			cout << "\nMensagem vazia do servidor" << endl;
			_packageToSend.init(_dataToSend, PACKAGESIZE);
			_packageToSend.writeByte(0);
			_gameSocket->SendLine(_packageToSend);
			_gameSocket->Close();
			_connected = false;
		}
	}
	catch(...)
	{
		_connected = false;
		cout << "\nNão foi possivel encontrar o servidor." << endl;
	}

	return _connected;
}

//--------------------------------------------------------------------------------------

bool CGameCore::isConnected()
{
	return _connected;
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::enviarPacote(int packageID, int i1)
{
	_packageToSend.init(_dataToSend, sizeof(_dataToSend));

	_packageToSend.writeByte(packageID);
	_packageToSend.writeLong(i1);

	_gameSocket->SendLine(_packageToSend);
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::enviarPacote(int packageID, int i1, int i2)
{
	_packageToSend.init(_dataToSend, sizeof(_dataToSend));

	_packageToSend.writeByte(packageID);
	_packageToSend.writeLong(i1);
	_packageToSend.writeLong(i2);

	_gameSocket->SendLine(_packageToSend);	
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::enviarPacote(int packageID, int i1, int i2, int i3)
{
	_packageToSend.init(_dataToSend, sizeof(_dataToSend));

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

	_packageToSend.writeByte(packageID);
	_packageToSend.writeLong(i1);
	_packageToSend.writeString(s1);

	_gameSocket->SendLine(_packageToSend);
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::enviarPacote(int packageID, int i1, float f1, float f2)
{
	_packageToSend.init(_dataToSend, sizeof(_dataToSend));

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

	_packageToSend.writeByte(packageID);
	_packageToSend.writeString(s1);
	_packageToSend.writeString(s2);

	_gameSocket->SendLine(_packageToSend);
}

//-----------------------------------------------------------------------------------------------------------------