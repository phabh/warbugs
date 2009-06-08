#pragma once

#include "CMenuAbertura.h"

//-----------------------------------------------------------------------------------------------------------------

void CMenuAbertura::receivePackages()
{
}

//-----------------------------------------------------------------------------------------------------------------

CMenuAbertura::CMenuAbertura()
{
}

//-----------------------------------------------------------------------------------------------------------------

bool CMenuAbertura::start(CGameCore *gameCore)
{
	gameCore->getAllManagers(_dispGrafico, _dispAudio, _gerEventos, _gerCena, _gerVideo, _gerHud, _gameConfig);
	_gameCore = gameCore;

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
{
	//_gameCore->playCutScene(CS_ABERTURA, 100);

	_nextID = MN_LOGIN;
}

//-----------------------------------------------------------------------------------------------------------------