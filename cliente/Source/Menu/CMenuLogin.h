#pragma once

#include "CMenu.h"

class CMenuLogin : public CMenu
{

private:

	IGUIEditBox *Login,
				*Password;

	char _login[15],
		  _senha[15];

	void graphicsDrawAddOn();
	void updateHuds();
	void readCommands();
	void updateGraphics();

public:

	CMenuLogin();
	bool start(CGameCore *gameCore);
};
