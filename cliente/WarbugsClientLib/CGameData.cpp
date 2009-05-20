#include "CGameData.h"

CGameData::CGameData()
{
}

void CGameData::start(IrrlichtDevice *grafico)
{
	porcentagem = 0.0f;
	_dataLoaded = 0.0f;

	_dispositivo = grafico;
	_gerenciadorCena = _dispositivo->getSceneManager();   // Cria o gerenciador de cena
	_gerenciadorVideo = _dispositivo->getVideoDriver();   // Cria o driver para o vídeo
	_gerenciadorHud = _dispositivo->getGUIEnvironment(); // Cria o gerenciador de menu

	_totalLoading = /*NUMCENARIOS*8 +*/ NUMMENUHUDS + NUM2DOBJS + NUM3DPERS*2 + NUM3DITENS*2;// + NUMPROPS*2;

}

void CGameData::loadGameData(int stage)
{
	switch (stage) // Estágios de carregamento do jogo
	{

	case 0: // Carrega malhas dos personagens 3D
		for(int i=0; i<NUM3DPERS; i++)
		{			
			dataGeometryChars[i] = _gerenciadorCena->getMesh(modelCharFile[i]);
			_dataLoaded++;
			porcentagem = _dataLoaded/_totalLoading*100.0f;
		}	          
		break;

	case 1: // Carrega malhas dos itens 3D
		for(int i=0; i<NUM3DITENS; i++)
		{
			dataGeometryItens[i] = _gerenciadorCena->getMesh(modelItemFile[i]);
			_dataLoaded++;
			porcentagem = _dataLoaded/_totalLoading*100.0f;
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
			dataTxChars[i] = _gerenciadorVideo->getTexture(textureCharFile[i]);
			_dataLoaded++;
			porcentagem = _dataLoaded/_totalLoading*100.0f;
		}	          
		break;

	case 3: // Carrega texturas dos itens 3D
		for(int i=0; i<NUM3DITENS; i++)
		{
			dataTxItens[i] = _gerenciadorVideo->getTexture(textureItemFile[i]);
			_dataLoaded++;
			porcentagem = _dataLoaded/_totalLoading*100.0f;
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
			dataTx2DItens[i] = _gerenciadorVideo->getTexture(texture2DFile[i]);
			_dataLoaded++;
			porcentagem = _dataLoaded/_totalLoading*100.0f;
		}	          
		break;

	case 5: // Carrega as demais texturas dos Huds
		for(int i=0; i<NUMMENUHUDS; i++)
		{
			dataTxHuds[i] = _gerenciadorVideo->getTexture(textureHudFile[i]);
			_dataLoaded++;
			porcentagem = _dataLoaded/_totalLoading*100.0f;
		}	          
		break;
	};

	cout << "\n" << porcentagem << endl;
}

//--------------------------------------------------------------------------------------
// Métodos Network

void CGameData::conectar(const std::string& host, int port)
{
	gameNetClient = new CBugSocketClient(host, port);

	msgToSend.init(dataSend, PACKAGESIZE);
	msgToReceive.init(dataReceive, PACKAGESIZE);
}

void CGameData::enviarPacote(char *s)
{
	msgToSend.writeString(s);
	gameNetClient->SendLine(msgToSend);
}

CBugMessage *CGameData::receberPacote()
{
	return gameNetClient->ReceiveLine();
}

//--------------------------------------------------------------------------------------
