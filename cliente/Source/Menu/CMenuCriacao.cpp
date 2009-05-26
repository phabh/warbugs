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
	_nodoSelecionado = 0;
	_idPersonagem = -1;

	_menuFlag[OBJSELECTED] = false;
	_menuFlag[HUDUPDATED] = false;

	_particula[0] = _gameCore->addPaticleNode(P_FOGO, 2000, vector3df(0,0,50), vector3df(1,1,1));

	luz = _gerCena->addLightSceneNode(0, vector3df(0,50,0/*500,500,500*/), SColorf(1.0f, 0.6f, 0.7f, 1.0f), 1200.0f);

	_toonShader = new CToonShader(_dispGrafico,luz);

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
	_gerHud->addButton(rect<s32>(440,500,540,540), 0, 7, L"Criar");
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
			_idPersonagem = -1;
			_nodoSelecionado = _gerCena->getSceneCollisionManager()->getSceneNodeFromScreenCoordinatesBB(_dispGrafico->getCursorControl()->getPosition());

			if (_nodoSelecionado)
				_idPersonagem = _nodoSelecionado->getID();

			if(_idPersonagem > 0)
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
			case 7:
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
}

//-----------------------------------------------------------------------------------------------------------------