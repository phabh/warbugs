#include "CMenuSelecao.h"

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
	
	_gameCore->playMusic(pathBackgroundSound[MM_SELECAO]);

	_myID = _nextID = MN_SELECAOPERSONAGEM;

	_menuFlag[HUDUPDATED]  = false;
	_menuFlag[OBJSELECTED] = false;

	_nodeChar = 0;
	_idChar = -1;
	_camRotation = 0;
	_camCurrRotation = 0;

	_gameCore->enviarPacote(PERSONAGENS_REQUEST, _gameCore->_myUserID);

	_gameCore->receberPacote();

	if(_gameCore->_numMyChars == 0) // Se n�o possuo personagem algum
		_nextID = MN_CRIACAOPERSONAGEM; // Ir direto ao menu de cria��o

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
		_gerHud->addButton(rect<s32>(440,650,540,690), 0, 204, L"Jogar");

	_gerHud->addButton(rect<s32>(240,550,340,590), 0, 202, L"Remover1");
	_gerHud->addButton(rect<s32>(640,550,740,590), 0, 203, L"Remover2");

	//_gerHud->addButton(rect<s32>(140,10,240,50), 0, 5, L"<");
	//_gerHud->addButton(rect<s32>(540,10,640,50), 0, 6, L">");

	_menuFlag[HUDUPDATED] = true;
}

//-----------------------------------------------------------------------------------------------------------------

void CMenuSelecao::readCommands()
{

	int slotPersonagem = 0;

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
			
			if(_gameCore->receberPacote() == SUCESSO)
				this->start(_gameCore);

			break;

		case 203:

			_gameCore->enviarPacote(DELETE_PERSONAGEM, _gameCore->_myUserID, _gameCore->_myStructChar[1]._id, _gameCore->_myStructChar[1]._nome );
			
			if(_gameCore->receberPacote() == SUCESSO)
				this->start(_gameCore);

			break;
/*
		case 204:
			_nextID =  MN_JOGO;
			return;
			break;*/

		default:
			cout << "\nID de botao desconhecido." << endl;
		};
	}

	_menuCamera->setRotation(vector3df(0, _camCurrRotation, 0));

	if(_gerEventos->isMouseButtonReleased(MBLEFT))
	{
		// Clique com o botao esquerdo
/*
		if(_menuFlag[OBJSELECTED])
		{
			_menuFlag[OBJSELECTED] = false; // Drop 3D
			_menuFlag[HUDUPDATED] = false;
		}
		else
		{
			_idChar = -1;

			_nodeChar = _gerCena->getSceneCollisionManager()->getSceneNodeFromScreenCoordinatesBB(_dispGrafico->getCursorControl()->getPosition());

			if (_nodeChar)
				_idChar = _nodeChar->getID();

			if(_idChar > 0)
			{
				_menuFlag[OBJSELECTED] = true; // Get 3D
				_menuFlag[HUDUPDATED] = false;
			}
		}	*/	
	}
}

//-----------------------------------------------------------------------------------------------------------------

void CMenuSelecao::updateGraphics()
{
}

//-----------------------------------------------------------------------------------------------------------------