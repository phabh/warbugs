#pragma once

#include "CMenu.h"

class CMenuCriacao : public CMenu
{

private:

	ISceneNode *_nodoSelecionado;
	int _idPersonagem;

	void graphicsDrawAddOn(){}

	void updateHuds()
	{

		_gerenciadorHud->clear();
		_gerenciadorHud->addButton(rect<s32>(440,500,540,540), 0, 7, L"Criar");

		_flags[HUDCHANGED] = false;
	}

	void readCommands()
	{
		//_timer->update();

		if(_gerenciadorEventos->isKeyPressed(KEY_ESCAPE))
		{
			_nextID = MN_SAIDA;
		    return;
		}
 
		if(_gerenciadorEventos->isMouseButtonReleased(MBLEFT))
		{
			// Clique com o botao esquerdo
						
			if(_flags[OBJSELECTED])
			{
				_flags[OBJSELECTED] = false; // Drop 3D
				_flags[HUDCHANGED] = true;
			}
			else
			{
				_idPersonagem = -1;
				_nodoSelecionado = _gerenciadorCena->getSceneCollisionManager()->getSceneNodeFromScreenCoordinatesBB(_dispositivo->getCursorControl()->getPosition());

				if (_nodoSelecionado)
					_idPersonagem = _nodoSelecionado->getID();

				if(_idPersonagem > 0)
				{
				   _flags[OBJSELECTED] = true; // Get 3D
				   _flags[HUDCHANGED] = true;
				}
			}

			if(_gerenciadorEventos->getEventCallerByElement(EGET_BUTTON_CLICKED))
			{
				// Trata os cliques em bot�es

				switch (_gerenciadorEventos->getEventCallerByID())
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

	void updateGraphics()
	{
		//_timer->update();
	}
	

public:

	CMenuCriacao(){}
	
	bool start(CGameCore *gameCore)
	{
		_gameCfg = new CArquivoConfig();
		TypeCfg cfg = _gameCfg->loadConfig();

		//_gameData = gameData;

		_dispositivo      = gameCore->getGraphicDevice();
		_gerenciadorAudio = gameCore->getSoundDevice();

		_gerenciadorAudio->removeAllSoundSources();
		_gerenciadorEventos = (CGerEventos*)_dispositivo->getEventReceiver();
	
		_myID = _nextID = MN_CRIACAOPERSONAGEM;

		//_arquivoCena = "recursos/cenas/criacao.irr";

		_nodoSelecionado = 0;
		_idPersonagem = -1;
		_flags[OBJSELECTED] = false;
		_flags[HUDCHANGED] = false;

		_dispositivo->setWindowCaption(L"Warbugs - BETA Version 0.1");

		_gerenciadorCena = _dispositivo->getSceneManager();   // Cria o gerenciador de cena
		_gerenciadorVideo = _dispositivo->getVideoDriver();   // Cria o driver para o v�deo
		_gerenciadorHud = _dispositivo->getGUIEnvironment(); // Cria o gerenciador de menu

		_musica = _gerenciadorAudio->play2D("recursos/audio/criacao.ogg", true, false, false, ESM_AUTO_DETECT);
		
		_gerenciadorAudio->setSoundVolume(cfg.parametrosAudio.volumeMusica);

		_gerenciadorCena->clear(); // Limpa toda a cena do jogo
		
		//if(_arquivoCena)
		_gerenciadorCena->loadScene(pathArquivoCena[MN_CRIACAOPERSONAGEM]);
		
		_skin = _gerenciadorHud->getSkin();
		_font = _gerenciadorHud->getFont("recursos/fonts/font_georgia.png");
		
		if (_font)
			_skin->setFont(_font);

		_skin->setFont(_gerenciadorHud->getBuiltInFont(), EGDF_TOOLTIP);

		
		_camera = _gerenciadorCena->addCameraSceneNode(0,vector3df(0,50,0), vector3df(0,0,50));

		return (true);
	}
};
