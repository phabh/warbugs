#include "CMenuLogin.h"

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
		_gameCore->_barraLoad->setProgress(0.01f);

		//_gerHud->addButton(rect<s32>(420,500,520,550), 0, 101, L"conectar");
	}
	if(_loadingStage > LS_COUNT)
	{
		IGUIImage *img =_gerHud->addImage(rect<s32>(0, 0, _gerVideo->getScreenSize().Width, _gerVideo->getScreenSize().Height), 0, -1, L"");
		img->setImage(_gerVideo->getTexture("recursos/texturas/huds/tx2d_bg_login.jpg"));

		Login = _gerHud->addEditBox(L"fantini", rect<s32>(300,500,400,520), true, 0, 10);
		Password = _gerHud->addEditBox(L"wurzelion", rect<s32>(300,530,400,550), true, 0, 20);
		Password->setPasswordBox(true);
		Login->setMax(15);
		Password->setMax(15);

		_gerHud->addButton(rect<s32>(420,500,520,550), 0, 101, L"conectar");
	}
	_menuFlag[HUDUPDATED] = true;
}

//-----------------------------------------------------------------------------------------------------------------

void CMenuLogin::readCommands()
{
	if(_gerEventos->isKeyDown(KEY_ESCAPE))
	{
		_nextID = MN_SAIDA;
		return;
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

			_gameCore->conectar( _login, _senha);

			if(_gameCore->isConnected())
			{
				_nextID = MN_SELECAOPERSONAGEM;
				return;
			}
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------

void CMenuLogin::updateGraphics()
{
	if(_loadingStage <= LS_COUNT)
	{
		_gameCore->loadGameData(_loadingStage);

		if(_loadingStage == LS_COUNT)
			_menuFlag[HUDUPDATED] = false;

		_loadingStage++;
	}
}

//-----------------------------------------------------------------------------------------------------------------