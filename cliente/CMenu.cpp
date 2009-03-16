#ifndef __CMenu__
#define __CMenu__

#include "irrlicht.h"
#include "irrklang.h"

#include "CArquivoConfig.cpp"
#include "CGerEventos.cpp"
#include "CTimer.cpp"

#include <iostream>

using namespace std; 

using namespace irr; 
using namespace core; 
using namespace scene; 
using namespace video; 
using namespace io; 
using namespace gui;

using namespace irrklang;

#pragma comment(lib, "Irrlicht.lib")
#pragma comment(lib, "irrKlang.lib")

enum menuID {ABERTURA, LOGIN, CONFIGURACAO, SELECAOPERSONAGEM, CRIACAOPERSONAGEM, JOGO, CREDITOS, SAIDA, ERRO};

class CMenu
{

protected:

	IrrlichtDevice *_dispositivo; 
	IVideoDriver *_gerenciadorVideo; 
	ISceneManager *_gerenciadorCena; 
	IGUIEnvironment *_gerenciadorHud;
	CGerEventos _gerenciadorEventos;
	ISoundEngine *_gerenciadorAudio;
	IGUISkin *_skin;
	IGUIFont *_font;
	ICameraSceneNode *_camera;
	menuID _myID;
	CTimer *_timer;
	ISound* _musicaFundo;
	CArquivoConfig *_gameCfg;
	char *_arquivoCena;
	bool _flags[10];

	virtual void hudRefresh() {}
	virtual void update() {}
	
public:

	CMenu(){}
	virtual bool start() { return false; }
	virtual menuID execute() { return ERRO; }
};

#endif;