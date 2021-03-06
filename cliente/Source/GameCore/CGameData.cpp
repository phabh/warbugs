#include "CGameData.h"

CGameData::CGameData(IrrlichtDevice *grafico)
{
	_gameLoaded = false;
	porcentagem = 0.0f;
	_dataLoaded = 0;

	_dispositivo = grafico;

	_gerenciadorCena  = _dispositivo->getSceneManager();   // Cria o gerenciador de cena
	_gerenciadorVideo = _dispositivo->getVideoDriver();    // Cria o driver para o v�deo
	_gerenciadorHud   = _dispositivo->getGUIEnvironment(); // Cria o gerenciador de menu

	_totalLoading = /*NUMCENARIOS*8 +*/ NUMMENUHUDS + NUM2DOBJS + NUM3DPERS*2 + NUM3DITENS*2;// + NUMPROPS*2;
}

bool CGameData::isDataLoaded()
{
	return _gameLoaded;
}

void CGameData::loadStage(int stage)
{

	
	switch (stage) // Est�gios de carregamento do jogo
	{

	case 0: // Carrega malhas dos personagens 3D
		for(int i=0; i<NUM3DPERS; i++)
		{			
			dataGeometryChars[i] = _gerenciadorCena->getMesh(pathCharsModels[i]);
			_dataLoaded++;
			porcentagem = _dataLoaded/_totalLoading*100.00f;
		}	          
		break;

	case 1: // Carrega malhas dos itens 3D
		for(int i=0; i<NUM3DITENS; i++)
		{
			dataGeometryItens[i] = _gerenciadorCena->getMesh(pathItensModels[i]);
			_dataLoaded++;
			porcentagem = _dataLoaded/_totalLoading*100.00f;
		}	          
		break;
/*
	case 2: // Carrega malhas dos props 3D
		for(int i=0; i<NUMPROPS; i++)
		{
			dataGeometryProps[i] = _gerenciadorCena->getMesh(modelPropFile[i]);
			_dataLoaded++;
			porcentagem = _dataLoaded/_totalLoading*100.0f;
		}	          
		break;*/

	case 2: // Carrega texturas dos personagens 3D
		for(int i=0; i<NUM3DPERS; i++)
		{
			dataTxChars[i] = _gerenciadorVideo->getTexture(pathTextureModels[i]);
			_dataLoaded++;
			porcentagem = _dataLoaded/_totalLoading*100.00f;
		}	          
		break;

	case 3: // Carrega texturas dos itens 3D
		for(int i=0; i<NUM3DITENS; i++)
		{
			dataTxItens[i] = _gerenciadorVideo->getTexture(pathTextureItens[i]);
			_dataLoaded++;
			porcentagem = _dataLoaded/_totalLoading*100.00f;
		}	          
		break;
/*
	case 5: // Carrega texturas dos props 3D
		for(int i=0; i<NUMPROPS; i++)
		{
			dataTxProps[i] = _gerenciadorVideo->getTexture(texturePropFile[i]);
			_dataLoaded++;
			porcentagem = _dataLoaded/_totalLoading*100.0f;
		}	          
		break;*/

	case 4: // Carrega texturas dos Huds
		for(int i=0; i<NUM2DOBJS; i++)
		{
			dataTx2DItens[i] = _gerenciadorVideo->getTexture(pathTexture2D[i]);
			_dataLoaded++;
			porcentagem = _dataLoaded/_totalLoading*100.00f;
		}	          
		break;

	case 5: // Carrega as demais texturas dos Huds
		for(int i=0; i<NUMMENUHUDS; i++)
		{
			dataTxHuds[i] = _gerenciadorVideo->getTexture(pathTextureHud[i]);
			_dataLoaded++;
			porcentagem = _dataLoaded/_totalLoading*100.00f;
		}

		_gameLoaded = true;

		break;
	};

	cout << "\n" << porcentagem << endl;
}