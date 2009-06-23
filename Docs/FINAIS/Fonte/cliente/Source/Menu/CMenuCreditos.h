#pragma once

#include "CMenu.h"
#include "CVideoTexture.h"

class CMenuCreditos : public CMenu
{

private:

	CVideoTexture *_video;

	void graphicsDrawAddOn();
	void updateHuds(); 
	void readCommands();
	void updateGraphics();
	void receivePackages();

public:

	CMenuCreditos();
	bool start(CGameCore *gameCore);
};