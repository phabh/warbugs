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

	_menuCamera = gameCore->createCamera( vector3df(0,0,0), vector3df(0,0,100), vector3df(0,0,0), 0, 179.0f/*true*/, true);

	_gameCore->playMusic(pathBackgroundSound[MM_SELECAO]);

	_myID = _nextID = MN_SELECAOPERSONAGEM;

	_menuFlag[HUDUPDATED]  = false;
	_menuFlag[OBJSELECTED] = false;

	_nodoSelecionado = 0;
	_idPersonagem = -1;
	_camRotation = 0;
	_camCurrRotation = 0;

	_luz = _gerCena->addLightSceneNode(0, vector3df(0,50,0/*500,500,500*/), SColorf(1.0f, 0.6f, 0.7f, 1.0f), 1200.0f);

	_toonShader = new CToonShader(_dispGrafico, _luz);

	_gameCore->enviarPacote(PERSONAGENS_REQUEST, _gameCore->_meuLoginID);
	_gameCore->receberPacote();

	if(_gameCore->_nSlotChars > 0)
	{
		for(int i=0; i<_gameCore->_nSlotChars; i++)
		{
			_gameCore->_personagem[i] = _gerCena->addAnimatedMeshSceneNode(_gerCena->getMesh(pathCharsModels[_gameCore->_vectPersonagem[i]._idModelo]), 0, _gameCore->_vectPersonagem[i]._id );

			_gameCore->_personagem[i]->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);

			_toonShader->apply(_gameCore->_personagem[i], pathTextureModels[_gameCore->_vectPersonagem[i]._idTextura]);

			_gameCore->_personagem[i]->setAnimationSpeed(0);

			switch (i)
			{

			case 0:
				_gameCore->_personagem[i]->setPosition(vector3df(0,0,50));
				_gameCore->_personagem[i]->setRotation(vector3df(0,0,0));
				break;

			case 1:
				_gameCore->_personagem[i]->setPosition(vector3df(50,0,0));
				_gameCore->_personagem[i]->setRotation(vector3df(0,90,0));
				break;

			case 2:
				_gameCore->_personagem[i]->setPosition(vector3df(0,0,-50));
				_gameCore->_personagem[i]->setRotation(vector3df(0,180,0));
				break;

			case 3:
				_gameCore->_personagem[i]->setPosition(vector3df(-50,0,0));
				_gameCore->_personagem[i]->setRotation(vector3df(0,270,0));
				break;
			}
		}
	}
	else
		_nextID = MN_CRIACAOPERSONAGEM;

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

	_gerHud->addButton(rect<s32>(320,500,430,540), 0, 4, L"Jogar");

	_gerHud->addButton(rect<s32>(140,10,240,50), 0, 5, L"<");
	_gerHud->addButton(rect<s32>(540,10,640,50), 0, 6, L">");

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

		case 5: // 
			_camRotation += 90;
			if(_camRotation > 360.0)
				_camRotation -= 360.0;
			break;

		case 6:
			_camRotation -= 90;
			if(_camRotation < 0.0)
				_camRotation += 360.0;
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