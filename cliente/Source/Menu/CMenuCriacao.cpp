#include "CMenuCriacao.h"

//-----------------------------------------------------------------------------------------------------------------

CMenuCriacao::CMenuCriacao()
{
}

//-----------------------------------------------------------------------------------------------------------------

bool CMenuCriacao::start(CGameCore *gameCore)
{
	_gameCore = gameCore;

	_gameCore->getAllManagers(_dispGrafico, _dispAudio, _gerEventos, _gerCena, _gerVideo, _gerHud, _gameConfig);

	_gameCore->loadGameScene(pathArquivoCena[MC_CRIACAO]);

	_menuCamera = gameCore->createCamera( vector3df(0,0,0), vector3df(0,0,100), vector3df(0,0,0), 0, 179.0f/*true*/, true);

	_gameCore->playMusic(pathBackgroundSound[MM_CRIACAO]);

	_myID = _nextID = MN_CRIACAOPERSONAGEM;
	_nodeChar = 0;
	_idChar = -1;
	_camRotation = 18.5;
	_camCurrRotation = 18.5;

	_tipoPersonagem = S_ARANHA;

	_menuFlag[OBJSELECTED] = false;
	_menuFlag[HUDUPDATED] = false;

	_particula[0] = _gameCore->addPaticleNode(P_FOGO, 700, vector3df(-86.5, 30.0, -0.0), vector3df(1,1,1));
	_particula[1] = _gameCore->addPaticleNode(P_FOGO, 700, vector3df(-26.0, 30.0, -84.5), vector3df(1,1,1));
	_particula[2] = _gameCore->addPaticleNode(P_FOGO, 700, vector3df( 71.5, 30.0, -53.0), vector3df(1,1,1));
	_particula[3] = _gameCore->addPaticleNode(P_FOGO, 700, vector3df( 71.5, 30.0, 53.0), vector3df(1,1,1));
	_particula[4] = _gameCore->addPaticleNode(P_FOGO, 700, vector3df(-26.0, 30.0, 84.5), vector3df(1,1,1));

	_luz = _gerCena->addLightSceneNode(0, vector3df(0,50,0/*500,500,500*/), SColorf(1.0f, 0.6f, 0.7f, 1.0f), 1200.0f);

	_toonShader = new CToonShader(_dispGrafico, _luz);

	return true;
}

//-----------------------------------------------------------------------------------------------------------------

void CMenuCriacao::graphicsDrawAddOn()
{
}

//-----------------------------------------------------------------------------------------------------------------

void CMenuCriacao::updateHuds()
{
	_gerHud->clear();

	_gerHud->addButton(rect<s32>(140,10,240,50), 0, 301, L"<");
	_gerHud->addButton(rect<s32>(540,10,640,50), 0, 302, L">");
	_gerHud->addButton(rect<s32>(440, 600, 540, 640), 0, 303, L"Criar");

	_menuFlag[HUDUPDATED] = true;
}

//-----------------------------------------------------------------------------------------------------------------

void CMenuCriacao::readCommands()
{
	if(_gerEventos->isKeyPressed(KEY_ESCAPE))
	{
		_nextID = MN_SAIDA;
		return;
	}

	if(_gerEventos->isMouseButtonReleased(MBLEFT))
	{
		// Clique com o botao esquerdo

		if(_menuFlag[OBJSELECTED])
		{
			_menuFlag[OBJSELECTED] = false; // Drop 3D
			_menuFlag[HUDUPDATED] = true;
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
				_menuFlag[HUDUPDATED] = true;
			}
		}

		if(_gerEventos->getEventCallerByElement(EGET_BUTTON_CLICKED))
		{
			// Trata os cliques em botões

			switch (_gerEventos->getEventCallerByID())
			{

			case 301:
				_camRotation -= 72;
				_tipoPersonagem--;

				if(_tipoPersonagem < 0)
					_tipoPersonagem = S_COUNT -1;

				cout << "\nIDRaca: " << _tipoPersonagem << endl; 

				break;

			case 302:
				_camRotation += 72;
				_tipoPersonagem++;

				_tipoPersonagem = _tipoPersonagem % S_COUNT;
				cout << "\nIDRaca: " << _tipoPersonagem << endl; 

				break;

			case 303:
				
				_gameCore->enviarPacote(CREATE_PERSONAGEM, _gameCore->_myUserID, _tipoPersonagem+2, "Fulano");  

				if(_gameCore->receberPacote() == SUCESSO)
					_nextID = MN_SELECAOPERSONAGEM;

				return;
				break;

			default:
				cout << "\nID de botao desconhecido." << endl;
			};
		}		
	}
}

//-----------------------------------------------------------------------------------------------------------------

void CMenuCriacao::updateGraphics()
{
	float delta = fabs(_camRotation - _camCurrRotation);

	if(	_camRotation != _camCurrRotation )
	{
		if(delta < 5)
			_camCurrRotation = _camRotation;
		else
		{
			if(_camRotation > _camCurrRotation)
				_camCurrRotation += 2*delta/50;

			else if(_camRotation < _camCurrRotation)
				_camCurrRotation -= 2*delta/50;
		}
	}

	_menuCamera->setRotation(vector3df(0, _camCurrRotation, 0));
}

//-----------------------------------------------------------------------------------------------------------------