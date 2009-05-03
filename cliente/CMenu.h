#pragma once

#include "Setup.h"
#include "CArquivoConfig.cpp"
#include "CGerEventos.cpp"
#include "CToonShader.cpp"

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
	ISceneNode *_nodoSelecionado;
	ICameraSceneNode *_camera;
	menuID _myID, _nextID;
	ISound* _musica;
	ISound* _hudFX[NUMFXHUD];
	CArquivoConfig *_gameCfg;
	char *_arquivoCena;
	bool _flags[NUMFLAGSMENU];

	CToonShader *_toonShader;

	virtual void updateHuds() = 0;
	virtual void readCommands() = 0;
	virtual void updateGraphics() = 0;
	virtual void graphicsDrawAddOn() = 0;
	
public:

	enum flagMenu {HUDCHANGED, OBJSELECTED, INVENTARIOON, CHATON, STATUSON, MAPAON, TRADEON, EQUIPON, SHOPON, BOLSAON, ALERTON, CONFIGON };

	CMenu(){}
	virtual bool start(IrrlichtDevice *grafico, ISoundEngine *audio) = 0;
	menuID run();
};
