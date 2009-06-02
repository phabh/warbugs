#pragma once

#include "CMenuAbertura.h"

//-----------------------------------------------------------------------------------------------------------------

CMenuAbertura::CMenuAbertura()
{
}

//-----------------------------------------------------------------------------------------------------------------

bool CMenuAbertura::start(CGameCore *gameCore)
{
	gameCore->getAllManagers(_dispGrafico, _dispAudio, _gerEventos, _gerCena, _gerVideo, _gerHud, _gameConfig);

	_myID = _nextID = MN_ABERTURA;

	_menuFlag[HUDUPDATED] = false;

	return true;
}

//-----------------------------------------------------------------------------------------------------------------

void CMenuAbertura::graphicsDrawAddOn() 
{
}

//-----------------------------------------------------------------------------------------------------------------

void CMenuAbertura::updateHuds() 
{
	_menuFlag[HUDUPDATED] = true;
}

//-----------------------------------------------------------------------------------------------------------------

void CMenuAbertura::readCommands()	
{
}

//-----------------------------------------------------------------------------------------------------------------

void CMenuAbertura::updateGraphics() 
{/*
	_video = CVideoTexture::createVideoTexture(_dispGrafico, pathVideoAbertura);
	_video->setVolume(100);
	_video->playCutscene();
	_video->drop();*/

	_nextID = MN_LOGIN;
}

//-----------------------------------------------------------------------------------------------------------------