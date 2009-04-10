#ifndef __CMenu__
#define __CMenu__

#include "irrlicht.h"
#include "irrklang.h"

#include "CArquivoConfig.cpp"
#include "CGerEventos.cpp"
#include "CTimer.cpp"
#include "CToonShader.cpp"

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
	CGerEventos *_gerenciadorEventos;
	ISoundEngine *_gerenciadorAudio;
	IGUISkin *_skin;
	IGUIFont *_font;
	ICameraSceneNode *_camera;
	menuID _myID;
	CTimer *_timer;
	ISound* _musica[6];
	CArquivoConfig *_gameCfg;
	char *_arquivoCena;
	bool _flags[10];

	CToonShader *_toonShader;

	virtual void updateHuds()=0;// {}
	virtual void updateCommands()=0;// {}
	virtual void updateGraphics()=0;// {}
	
public:

	CMenu(){}
	virtual bool start(IrrlichtDevice *grafico, ISoundEngine *audio)= 0;// { return false; }
	virtual menuID run() = 0;//{ return ERRO; }
};

#endif;