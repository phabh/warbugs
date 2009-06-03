#include "CMenuCreditos.h"

//-----------------------------------------------------------------------------------------------------------------

CMenuCreditos::CMenuCreditos()
{
}

//-----------------------------------------------------------------------------------------------------------------

bool CMenuCreditos::start(CGameCore *gameCore)
{
	gameCore->getAllManagers(_dispGrafico, _dispAudio, _gerEventos, _gerCena, _gerVideo, _gerHud, _gameConfig);

	_myID = _nextID = MN_CREDITOS;

	_menuFlag[HUDUPDATED] = false;

	return true;
}

//-----------------------------------------------------------------------------------------------------------------

void CMenuCreditos::graphicsDrawAddOn() 
{
}

//-----------------------------------------------------------------------------------------------------------------

void CMenuCreditos::updateHuds() 
{
	_menuFlag[HUDUPDATED] = true;
}

//-----------------------------------------------------------------------------------------------------------------

void CMenuCreditos::readCommands()	
{
}

//-----------------------------------------------------------------------------------------------------------------

void CMenuCreditos::updateGraphics() 
{
	_gameCore->playCutScene(CS_CREDITOS, 100);
	/*
	_video = CVideoTexture::createVideoTexture(_dispGrafico, pathVideoCreditos);
	_video->setVolume(100);
	_video->playCutscene();
	_video->drop();*/

	_nextID = MN_SAIDA;
}

//-----------------------------------------------------------------------------------------------------------------