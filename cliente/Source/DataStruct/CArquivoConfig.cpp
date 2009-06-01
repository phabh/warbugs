#pragma once

#include "GameSetup.h"
#include "PathSetup.h"

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
		ifstream load(pathConfig);
		load.read( (char *)&_configuracao, sizeof(_configuracao));
		return (_configuracao);
	}

	void saveConfig()
	{
		ofstream save(pathConfig);
		save.write( (char *)&_configuracao, sizeof(_configuracao));
	}

	void reset()
	{
		_configuracao.parametrosVideo.DriverType       = defDriver;
		_configuracao.parametrosVideo.WindowSize       = defDimension;
		_configuracao.parametrosVideo.Bits             = defBits;
		_configuracao.parametrosVideo.Fullscreen       = defFullScreen;
		_configuracao.parametrosVideo.Stencilbuffer    = defStencilBuffer;
		_configuracao.parametrosVideo.Vsync            = defVsync;
		_configuracao.parametrosVideo.AntiAlias        = defAntiAlias;
		_configuracao.parametrosVideo.EventReceiver    = NULL;
		_configuracao.parametrosVideo.WithAlphaChannel = defAlphaChannel;
		_configuracao.parametrosVideo.HighPrecisionFPU = defHiPrecisionFpu;
		_configuracao.parametrosVideo.IgnoreInput      = defIgnoreInput;
		_configuracao.parametrosVideo.WindowId         = NULL;
		_configuracao.parametrosVideo.ZBufferBits      = defZBufferBits;

		_configuracao.parametrosAudio.volumeEfeitos = defSFXVol;
		_configuracao.parametrosAudio.volumeMusica = defMusicVol;

		saveConfig();
	}
};
