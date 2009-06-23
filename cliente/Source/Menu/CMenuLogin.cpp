#include "CMenuLogin.h"

//-----------------------------------------------------------------------------------------------------------------

void CMenuLogin::receivePackages()
{
}

//-----------------------------------------------------------------------------------------------------------------

CMenuLogin::CMenuLogin()
{
}

//-----------------------------------------------------------------------------------------------------------------

bool CMenuLogin::start(CGameCore *gameCore)
{
	_gameCore = gameCore;

	_gameCore->getAllManagers(_dispGrafico, _dispAudio, _gerEventos, _gerCena, _gerVideo, _gerHud, _gameConfig);

	_gameCore->playMusic(pathBackgroundSound[MM_LOGIN]);

	_myID = _nextID = MN_LOGIN;

	_menuFlag[HUDUPDATED] = false;

	_loadingStage = LS_PERSONAGENS;


	std::string line;
	size_t separ_pos;

	ifstream serverFile (pathServerSetup);
	
	if (serverFile.is_open())
	{
		//while (!serverFile.eof() )
		//{
			getline (serverFile, line);
		//}
		serverFile.close();

		separ_pos = line.find_first_of(":");
		
		_gameCore->SERVERHOST = line.substr(0, separ_pos);
		_gameCore->SERVERPORT = atoi( (line.substr(separ_pos+1, line.size())).c_str() );		
		/*
		cout << "\n" << _gameCore->SERVERHOST << endl;
		cout << "\n" << _gameCore->SERVERPORT << endl;
		system("pause");*/
	}
	else
	{
		cout << "\nFalha ao abrir o arquivo servidor.txt" << endl;
		system("pause");
	}

	return true;
}

//-----------------------------------------------------------------------------------------------------------------

void CMenuLogin::graphicsDrawAddOn()
{
}

//-----------------------------------------------------------------------------------------------------------------

void CMenuLogin::updateHuds()
{
	_gerHud->clear();

	if(_loadingStage == LS_PERSONAGENS) 
	{
		_gameCore->_barraLoad = new CHudProgressBar(_gerHud->getRootGUIElement(), _gerHud, rect<s32>( 0+100, _gameCore->sHeight-200, _gameCore->sWidth-100, _gameCore->sHeight-100));
		_gameCore->_barraLoad->setProgress(0.00001f);
	}

	if(_loadingStage > LS_COUNT)
	{
		IGUIImage *img =_gerHud->addImage(_gerVideo->getTexture("recursos/huds/bg_login.png"), position2d<s32>(/*112, 84*/0,0));

		Login = _gerHud->addEditBox(L"fantini", rect<s32>(400,700,500,720), true, 0, 10);
		Password = _gerHud->addEditBox(L"wurzelion", rect<s32>(400,730,500,750), true, 0, 20);
		Password->setPasswordBox(true);
		Login->setMax(15);
		Password->setMax(15);

		_gerHud->addButton(rect<s32>(520,700,620,750), 0, 101, L"conectar");
		//IGUIButton *connect;
		//addNewBtn(connect, rect<s32>(550,700,602,752), 0, 101, 0, L"conectar", true, false, H_CONECTAR, H_CONECTAR);
	}

	for (u32 i=0; i<EGDC_COUNT ; ++i)
	{
		SColor col = _gerHud->getSkin()->getColor((EGUI_DEFAULT_COLOR)i);
		col.setAlpha(255);
		_gerHud->getSkin()->setColor((EGUI_DEFAULT_COLOR)i, col);
	}

	_menuFlag[HUDUPDATED] = true;
}

//-----------------------------------------------------------------------------------------------------------------

void CMenuLogin::readCommands()
{

	IGUIElement *temp = _gerHud->getFocus();
	//_gerHud->setFocus(NULL);
	

	if(_gerEventos->isKeyDown(KEY_ESCAPE))
	{
		_nextID = MN_SAIDA;
		return;
	}
    
	if(_gerEventos->isKeyPressed(KEY_RETURN))
	{
		_gerHud->setFocus(NULL);
	}
	
	if(_gerEventos->isKeyReleased(KEY_RETURN))
	{
		
		//_nextID = MN_SAIDA;
		//return;
		cout << "\nENTER!\n";
	}

	if(_gerEventos->getEventCallerByElement(EGET_BUTTON_CLICKED))
	{
		// Trata os cliques em botões
		if (_gerEventos->getEventCallerByID() == 101)
		{
			// Clicou no botão conectar

			stringc str1(Login->getText());
			strcpy(_login, str1.c_str()); 

			stringc str2(Password->getText());
			strcpy(_senha, str2.c_str()); 

			_gameCore->conectar( _login, _senha); // TESTE


			if(_gameCore->isConnected())
			{
				_nextID = MN_SELECAOPERSONAGEM;
				return;
			}
		}
	}
	_gerHud->setFocus(temp);
}

//-----------------------------------------------------------------------------------------------------------------

void CMenuLogin::updateGraphics()
{
	if(_loadingStage <= LS_COUNT)
	{
		//if(!_gameCore->_gameData->isDataLoaded())
		//{ 
		_gameCore->loadGameData(_loadingStage);

		if(_loadingStage == LS_COUNT)
			_menuFlag[HUDUPDATED] = false;

		_loadingStage++;
		//}
		//else
		//	_loadingStage == LS_PERSONAGENS;
	}
}

//-----------------------------------------------------------------------------------------------------------------