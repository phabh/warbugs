#pragma once

#include "CMenu.h"
#include "CVideoTexture.h"

class CMenuAbertura : public CMenu
{
	
private:

	CVideoTexture *_video;
	
	void graphicsDrawAddOn();
	void updateHuds();
	void readCommands();
	void updateGraphics();

public:

	CMenuAbertura();
	bool start(CGameCore *gameCore);
};

