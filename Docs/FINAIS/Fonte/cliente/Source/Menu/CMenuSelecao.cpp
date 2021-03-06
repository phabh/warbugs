#include "CMenuSelecao.h"


//-----------------------------------------------------------------------------------------------------------------

void CMenuSelecao::receivePackages()
{
}

//-----------------------------------------------------------------------------------------------------------------

CMenuSelecao::CMenuSelecao()
{
}

//-----------------------------------------------------------------------------------------------------------------

bool CMenuSelecao::start(CGameCore *gameCore)
{
	_gameCore = gameCore;

	_gameCore->getAllManagers(_dispGrafico, _dispAudio, _gerEventos, _gerCena, _gerVideo, _gerHud, _gameConfig);

	_gameCore->loadGameScene(pathArquivoCena[MC_SELECAO]);

	_menuCamera = _gameCore->createCamera( vector3df(0,0,0), vector3df(0,0,100), vector3df(0,0,0), 0, 179.0f/*true*/, true);

	_gameCore->createLight(_menuCamera, vector3df(0,0,0), 1200.0f);

	_gameCore->initToonShader();

	_myID = _nextID = MN_SELECAOPERSONAGEM;

	_menuFlag[HUDUPDATED]  = false;
	_menuFlag[OBJSELECTED] = false;

	_nodeChar = 0;
	_idChar = -1;
	_camRotation = 0;
	_camCurrRotation = 0;

	_gameCore->enviarPacote(PERSONAGENS_REQUEST, _gameCore->_myUserID);

	int retorno = PING_REQUEST;

	while(retorno == PING_REQUEST)
		retorno = _gameCore->receberPacote();

	if(_gameCore->_numMyChars == 0) // Se n�o possuo personagem algum
		_nextID = MN_CRIACAOPERSONAGEM; // Ir direto ao menu de cria��o

	//_gameCore->playCutScene(CS_TRANSICAO, 100);

	_gameCore->playMusic(pathBackgroundSound[MM_SELECAO]);

	return true;
}

//-----------------------------------------------------------------------------------------------------------------

void CMenuSelecao::graphicsDrawAddOn()
{
}

//-----------------------------------------------------------------------------------------------------------------

void CMenuSelecao::updateHuds()
{
	_gerHud->clear();

	if(_gameCore->_numMyChars < 2)
		_gerHud->addButton(rect<s32>(440,550,540,590), 0, 201 , L"Criar");

	if(_gameCore->_numMyChars > 0)
	{
		if(_gameCore->_numMyChars > 1)
		{
			_gerHud->addButton(rect<s32>(640,650,740,690), 0, 205, L"Jogar 2");
			_gerHud->addButton(rect<s32>(640,550,740,590), 0, 203, L"Remover 2");
		}

		_gerHud->addButton(rect<s32>(240,650,340,690), 0, 204, L"Jogar 1");
		_gerHud->addButton(rect<s32>(240,550,340,590), 0, 202, L"Remover 1");
	}

	_menuFlag[HUDUPDATED] = true;
}

//-----------------------------------------------------------------------------------------------------------------

void CMenuSelecao::readCommands()
{

	int slotPersonagem = 0;

	int retorno = PING_REQUEST;

	if(_gerEventos->isKeyDown(KEY_ESCAPE))
	{
		_nextID = MN_SAIDA;
		return;
	}

	if(_gerEventos->getEventCallerByElement(EGET_BUTTON_CLICKED))
	{
		// Trata os cliques em bot�es
		switch (_gerEventos->getEventCallerByID())
		{

		case 201:

			_nextID = MN_CRIACAOPERSONAGEM;
			return;

			break;

		case 202: 

			_gameCore->enviarPacote(DELETE_PERSONAGEM, _gameCore->_myUserID, _gameCore->_myStructChar[0]._id, _gameCore->_myStructChar[0]._nome );

			while(retorno == PING_REQUEST)
				retorno = _gameCore->receberPacote();

			if(retorno == SUCESSO)
				this->start(_gameCore);

			break;

		case 203:

			_gameCore->enviarPacote(DELETE_PERSONAGEM, _gameCore->_myUserID, _gameCore->_myStructChar[1]._id, _gameCore->_myStructChar[1]._nome );

			while(retorno == PING_REQUEST)
				retorno = _gameCore->receberPacote();

			if(retorno == SUCESSO)
				this->start(_gameCore);

			break;

		case 204:
			_gameCore->_myCharID = _gameCore->_myStructChar[0]._id;
			_nextID =  MN_JOGO;
			return;
			break;

		case 205:
			_gameCore->_myCharID = _gameCore->_myStructChar[1]._id;
			_nextID =  MN_JOGO;
			return;
			break;

		default:
			cout << "\nID de botao desconhecido." << endl;
		};
	}

	_menuCamera->setRotation(vector3df(0, _camCurrRotation, 0));

}

//-----------------------------------------------------------------------------------------------------------------

void CMenuSelecao::updateGraphics()
{
}

//-----------------------------------------------------------------------------------------------------------------