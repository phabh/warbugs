#pragma once

#include "PathSetup.h"
#include "MsgSetup.h"

class CGameData
{

private:

	IrrlichtDevice  *_dispositivo; 
	IVideoDriver    *_gerenciadorVideo; 
	ISceneManager   *_gerenciadorCena; 
	IGUIEnvironment *_gerenciadorHud;

	float porcentagem;   // Porcentagem de loading
	float _totalLoading; // Total de elementos a carregar na mem�ria
	float _dataLoaded;   // Total de elementos carregados

public:

	ITexture *dataTxScenes[NUMCENARIOS], // Texturas dos cen�rios
			 *dataTxProps[NUMPROPS],	 // Texturas dos objetos est�ticos do cen�rio
			 *dataTxHuds[NUMMENUHUDS],   // Texturas dos huds
			 *dataTxChars[NUM3DPERS],	 // Texturas dos personagens 3D
			 *dataTxItens[NUM3DITENS],	 // Texturas dos itens 3D
			 *dataTx2DItens[NUM2DOBJS];  // Texturas dos itens para Hud 2D 

	IAnimatedMesh *dataGeometryChars[NUM3DPERS],  // Malha animada 3D dos personagens
				  *dataGeometryItens[NUM3DITENS], // Malha animada 3D dos itens
				  *dataGeometryProps[NUMPROPS];   // Malha animada 3D dos objetos est�ticos do cen�rio

	CGameData(IrrlichtDevice *grafico);
	void loadStage(int stage);
};