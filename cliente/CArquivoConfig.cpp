#pragma once

#include "Setup.h"

struct TypeCfgAudio
{
	ik_f32 volumeMusica,
		   volumeEfeitos;
};

struct TypeCfg
{
	SIrrlichtCreationParameters parametrosVideo;
	TypeCfgAudio parametrosAudio;
};

class CArquivoConfig
{

private:

	TypeCfg _configuracao;

public:

	CArquivoConfig(){}

	void setParameters( TypeCfg parametros)
	{
		_configuracao = parametros;
	}

	TypeCfg loadConfig()
	{
		ifstream load("config.dat");
		load.read( (char *)&_configuracao, sizeof(_configuracao));
		return (_configuracao);
	}

	void saveConfig()
	{
		ofstream save("config.dat");
		save.write( (char *)&_configuracao, sizeof(_configuracao));
	}

	void reset()
	{
		_configuracao.parametrosVideo.DriverType = EDT_DIRECT3D9;
		_configuracao.parametrosVideo.WindowSize = dimension2d <s32>( 800, 600 );
		_configuracao.parametrosVideo.Bits = 32;
		_configuracao.parametrosVideo.Fullscreen = false;
		_configuracao.parametrosVideo.Stencilbuffer = true;
		_configuracao.parametrosVideo.Vsync = true;
		_configuracao.parametrosVideo.AntiAlias = true;
		_configuracao.parametrosVideo.EventReceiver = 0;
		_configuracao.parametrosVideo.WithAlphaChannel = true;
		_configuracao.parametrosVideo.HighPrecisionFPU = false;
		_configuracao.parametrosVideo.IgnoreInput = false;
		_configuracao.parametrosVideo.WindowId = 0;
		_configuracao.parametrosVideo.ZBufferBits = 16;

		_configuracao.parametrosAudio.volumeEfeitos = 1.0;
		_configuracao.parametrosAudio.volumeMusica = 1.0;

		saveConfig();
	}

	
};
