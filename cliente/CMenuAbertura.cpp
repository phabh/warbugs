#pragma once

#include "CMenu.h"
#include "IVideoTexture.h"

#define eu reinterpret_cast<CMenuAbertura*>(lParam)

class CMenuAbertura : public CMenu
{
	
private:

	IVideoTexture *_video;

	CRITICAL_SECTION m_cs; // Objeto de Sessão Crítica
	HANDLE hThrd[2]; // Cria referências para as threads
	DWORD IDThread1, IDThread2; // Variáveis para guardar os IDs das threads
	
	
	
	void graphicsDrawAddOn() {}

	void updateHuds() 
	{
		_flags[HUDCHANGED] = false;
	}

	void readCommands()	{}

	void updateGraphics() 
	{
		_video = IVideoTexture::createVideoTexture(_dispositivo, "recursos/videos/video.wmv");
		_video->setVolume(100);
		_video->playCutscene();
		_video->drop();

		_nextID = LOGIN;
	}

	void runIrrlicht()
	{
		//updateHuds();

		while(_dispositivo->run())
		{
			//if (_dispositivo->isWindowActive())
			//{
				EnterCriticalSection(&m_cs);
				_gerenciadorEventos->endEventProcess(); // Desativa a escuta de eventos para desenhar.
			
				_gerenciadorVideo->beginScene(true, true, SColor(255, 0, 0, 0));
					_gerenciadorCena->drawAll(); 
					_gerenciadorHud->drawAll();
					graphicsDrawAddOn();
				_gerenciadorVideo->endScene();

				readCommands();

				updateGraphics();

				if(_flags[HUDCHANGED])
					updateHuds();

				if(_nextID != _myID)
				{
					break;
				}

				_gerenciadorEventos->startEventProcess(); // Ativa a escuta de eventos.
				LeaveCriticalSection(&m_cs);
				_temPacote = true;
			//}
		}

		_gerenciadorAudio->stopAllSounds();
		ExitThread(IDThread2);
		//return _nextID;
	}

	void readPackets()
	{
		while(_nextID == _myID)
		{
			if(_temPacote)
			{
				EnterCriticalSection(&m_cs); 
					cout << "\nLeu pacotes0.\n";
				LeaveCriticalSection(&m_cs);
				_temPacote = false;
			}
		}			
	}

	static DWORD WINAPI ThreadIrrlicht(LPVOID lParam)
	{
		reinterpret_cast<CMenuAbertura*>(lParam)->runIrrlicht();
		return 0;
	}

	static DWORD WINAPI ThreadReadPackets(LPVOID lParam)
	{
		reinterpret_cast<CMenuAbertura*>(lParam)->readPackets();
		return 0;
	}

public:

	CMenuAbertura(){}
	
	bool start(IrrlichtDevice *grafico, ISoundEngine *audio)
	{
		_temPacote = false;
		_gameCfg = new CArquivoConfig();
		TypeCfg cfg = _gameCfg->loadConfig();

	    _dispositivo = grafico;
		_gerenciadorEventos = (CGerEventos*)_dispositivo->getEventReceiver();

		_gerenciadorAudio = audio;
		_gerenciadorAudio->removeAllSoundSources();

		_myID = _nextID = ABERTURA;


		_dispositivo->setWindowCaption(L"Warbugs - BETA Version 0.1");

		_gerenciadorCena = _dispositivo->getSceneManager();   // Cria o gerenciador de cena
		_gerenciadorVideo = _dispositivo->getVideoDriver();   // Cria o driver para o vídeo
		_gerenciadorHud = _dispositivo->getGUIEnvironment();  // Cria o gerenciador de menu

        _flags[HUDCHANGED] = true;
/*
		_video = IVideoTexture::createVideoTexture(_dispositivo, "recursos/videos/video.wmv");
		_video->setVolume(100);
		_video->playCutscene();
		_video->drop();

		_nextID = LOGIN;*/

		return (true);
	}

	menuID run()
	{
		
		//HANDLE hThrd[2]; // Cria referências para as threads
		//DWORD IDThread1, IDThread2; // Variáveis para guardar os IDs das threads
			
		InitializeCriticalSection(&m_cs); // Inicializar sessão crítica

		// Criar threads usando a função CreateThread
		hThrd[0] = CreateThread(NULL, 0, /*(LPTHREAD_START_ROUTINE)*/ &ThreadIrrlicht, this/*(LPVOID)NULL*/, 0, &IDThread1);       
		hThrd[1] = CreateThread(NULL, 0, /*(LPTHREAD_START_ROUTINE)*/ &ThreadReadPackets, this/*(LPVOID)NULL*/, 0, &IDThread2); 
		
		WaitForMultipleObjects(2, hThrd, TRUE, INFINITE); // Esperar a execução da thread principal (tempo infinito)

		DeleteCriticalSection(&m_cs); // Deletar a sessão crítica

		return _nextID;
	}
};

