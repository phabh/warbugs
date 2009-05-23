#include "CGameCore.h"

//-----------------------------------------------------------------------------------------------------------------

CGameCore::CGameCore(int &startInit)
{
	startInit = SUCESSO;

	CArquivoConfig *gameCfg = new CArquivoConfig();

	TypeCfg cfg = gameCfg->loadConfig();

	/*
	RECT desktop; // Faz uma referência para a tela do desktop   
	const HWND hDesktop = GetDesktopWindow(); // Captura a dimensão da tela 
	GetWindowRect(hDesktop, &desktop);  */ 

	cfg.parametrosVideo.WindowSize.Width = 1024;//desktop.right;
	cfg.parametrosVideo.WindowSize.Height = 768;//desktop.bottom;
	cfg.parametrosVideo.Fullscreen = false;

	_dispositivoGrafico = createDevice(EDT_DIRECT3D9, 
		cfg.parametrosVideo.WindowSize, 
		cfg.parametrosVideo.Bits, 
		cfg.parametrosVideo.Fullscreen, 
		cfg.parametrosVideo.Stencilbuffer, 
		cfg.parametrosVideo.Vsync, 									
		&_gerenciadorEventos);

	if(!_dispositivoGrafico)
	{
		cout << "\nERRO 0x00: Falha ao inicializar o dispositivo grafico.";
		startInit = ERRO;
	}

	if(startInit == SUCESSO)
	{
		_dispositivoAudio = createIrrKlangDevice();

		if(!_dispositivoAudio)
		{
			cout << "\nERRO 0x01: Falha ao inicializar o dispositivo de audio.";
			startInit = ERRO;
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::drop()
{
	_dispositivoGrafico->drop(); // Deleta o dispositivo grafico da memória
	_dispositivoAudio->drop();   // Deleta o dispositivo de audio da memória
}

//-----------------------------------------------------------------------------------------------------------------

IrrlichtDevice* CGameCore::getGraphicDevice()
{
	return this->_dispositivoGrafico;
}

//-----------------------------------------------------------------------------------------------------------------

ISoundEngine* CGameCore::getSoundDevice()
{
	return this->_dispositivoAudio;
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::loadGameData()
{
	_Data = new CGameData(_dispositivoGrafico);

	int estagio = 0; // estágio de loading

	while(estagio < 6) // Carrega elementos do jogo
	{
		_Data->loadStage(estagio);
		estagio++;
	}
}

//--------------------------------------------------------------------------------------

void CGameCore::conectar(const std::string& host, int port)
{
	_netClient = new CBugSocketClient(host, port);

	_msgToSend.init(_dataSend, PACKAGESIZE);
	_msgToReceive.init(_dataReceive, PACKAGESIZE);
}

//-----------------------------------------------------------------------------------------------------------------

void CGameCore::enviarPacote(char *s)
{
	_msgToSend.writeString(s);
	_netClient->SendLine(_msgToSend);
}

//-----------------------------------------------------------------------------------------------------------------

CBugMessage* CGameCore::receberPacote()
{
	//return _netClient->ReceiveLine();
}

//--------------------------------------------------------------------------------------
