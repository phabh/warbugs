#include "CMenuSelecao.h"

//-----------------------------------------------------------------------------------------------------------------

CMenuSelecao::CMenuSelecao()
{
}

//-----------------------------------------------------------------------------------------------------------------

bool CMenuSelecao::start(CGameCore *gameCore)
{
	gameCore->getAllManagers(_dispGrafico, _dispAudio, _gerEventos, _gerCena, _gerVideo, _gerHud, _gameConfig);

	gameCore->loadGameScene(pathArquivoCena[MC_SELECAO]);

	_menuCamera = gameCore->createCamera( vector3df(0,0,0), vector3df(0,0,100), vector3df(0,0,0), 0, 179.0f/*true*/, true);

	gameCore->playMusic(pathBackgroundSound[MM_SELECAO]);

	_myID = _nextID = MN_SELECAOPERSONAGEM;

	_menuFlag[HUDUPDATED]  = false;
	_menuFlag[OBJSELECTED] = false;

	_nodoSelecionado = 0;
	_idPersonagem = -1;
	_camRotation = 0;
	_camCurrRotation = 0;

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

	_gerHud->addButton(rect<s32>(440,500,540,540), 0, 3, L"Criar");

	//if(_flags[OBJSELECTED])
	_gerHud->addButton(rect<s32>(320,500,430,540), 0, 4, L"Jogar");

	_gerHud->addButton(rect<s32>(140,10,240,50), 0, 5, L"<");
	_gerHud->addButton(rect<s32>(540,10,640,50), 0, 6, L">");

	_menuFlag[HUDUPDATED] = true;
}

//-----------------------------------------------------------------------------------------------------------------

void CMenuSelecao::readCommands()
{

	if(_gerEventos->isKeyDown(KEY_ESCAPE))
	{
		_nextID = MN_SAIDA;
		return;
	}

	if(_gerEventos->getEventCallerByElement(EGET_BUTTON_CLICKED))
	{
		// Trata os cliques em botões
		switch (_gerEventos->getEventCallerByID())
		{
		case 3:
			_nextID = MN_CRIACAOPERSONAGEM;
			return;
			break;

		case 4:
			_nextID =  MN_JOGO;
			return;
			break;

		case 5:
			_camRotation+=90;
			if(_camRotation > 360.0)
				_camRotation -= 360.0;
			//cout << "\n" << _camRotation;
			break;

		case 6:
			_camRotation-=90;
			if(_camRotation < 0.0)
				_camRotation += 360.0;
			//cout << "\n" << _camRotation;
			break;

		default:
			cout << "\nID de botao desconhecido." << endl;
		};
	}

	_menuCamera->setRotation(vector3df(0, _camCurrRotation, 0));

	if(_gerEventos->isMouseButtonReleased(MBLEFT))
	{
		// Clique com o botao esquerdo

		if(_menuFlag[OBJSELECTED])
		{
			_menuFlag[OBJSELECTED] = false; // Drop 3D
			_menuFlag[HUDUPDATED] = false;
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
				_menuFlag[HUDUPDATED] = false;
			}
		}		
	}
}

//-----------------------------------------------------------------------------------------------------------------

void CMenuSelecao::updateGraphics()
{
	float delta = fabs(_camRotation - _camCurrRotation);

	if(	_camRotation != _camCurrRotation )
	{
		if(delta < 2)
			_camCurrRotation = _camRotation;
		else
		{
			if(_camRotation > _camCurrRotation)
				_camCurrRotation += 2*delta/50;

			else if(_camRotation < _camCurrRotation)
				_camCurrRotation -= 2*delta/50;
		}
	}

	_menuCamera->setRotation(vector3df(0,_camCurrRotation,0));
}

//-----------------------------------------------------------------------------------------------------------------