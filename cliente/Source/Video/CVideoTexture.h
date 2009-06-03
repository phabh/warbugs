#pragma once

//!  class CVideoTexture
/*!
\Biblioteca para inserir texturas de vídeo na engine Irrlicht 1.5.
\Link com a biblioteca DSVT.H criada por Vi-Wer.
\Autor: Eduardo Fantini
*/

#include <irrlicht.h>
#include "dsvt.h"

using namespace irr; 
using namespace core; 
using namespace scene; 
using namespace video; 
using namespace io; 

class CVideoTexture
{

public:

	//! Construtor 1
	/*!
	\Construtor vazio.
	*/
	CVideoTexture();

	//! Constructor 2
	/*!
	\param1: dispositivo irrlicht (IrrlichtDevice*)
	\param2: textura estática (ITexture*)
	*/
	CVideoTexture( IrrlichtDevice *device, ITexture *texture);

	//! Construtor 3
	/*!
	\param1: dispositivo irrlicht (IrrlichtDevice*)
	\param2: nome do arquivo de vídeo (const char*)
	\param3: retorno de sucesso (boolean)
	*/
	CVideoTexture( IrrlichtDevice *device, const char* file, bool& bSuccess);

	//! Construtor 4
	/*!
	\param1: dispositivo irrlicht (IrrlichtDevice*)
	\param2: dispositivo de captura (dsvt::ICaptureDevice*)
	\param3: retorno de sucesso (boolean)
	*/
	CVideoTexture( IrrlichtDevice *device, dsvt::ICaptureDevice *cap , bool& bSuccess);

	//! Destrutor
	virtual ~CVideoTexture();

	//! Cria textura de vídeo para Irrlicht
	/*!
	\param device Irrlicht device
	\param file File Name
	\return Pointer to a Video Texture or NULL if failed
	*/
	static CVideoTexture* createVideoTexture( IrrlichtDevice *device ,const char* file);

	//! Creates Irrlicht Capture texture
	/*!
	Opens Capture device and renders it's content to a texture.
	\param device Irrlicht device
	\param cap Capture Device ID.Not Implemented
	\return Pointer to a Video Texture or NULL if failed
	*/
	static CVideoTexture* createCaptureTexture( IrrlichtDevice *device , dsvt::ICaptureDevice *cap = NULL);

	//! Returns Irrlicht texture pointer
	/*!
	\return Pointer to an Irrlicht Texture.
	*/
	virtual ITexture *getTexture();

	//! Remove Video texture
	/*!
	Video texture can't be used anymore.
	Irrlicht texture that was returned by getTexture will not be removed.
	*/
	virtual void drop()
	{
		delete this;
	}

	//! Update Video texture
	/*!
	Should be called as often as necessary.
	Also when using callback function.
	*/
	virtual bool update()
	{
		bool bReturn = false;
		if( m_dshow_player )
			bReturn = m_dshow_player->update();

		if( m_device->getVideoDriver()->getDriverType() != EDT_OPENGL && bReturn)
			m_pTempTexture->regenerateMipMapLevels();

		return bReturn;
	}

	//! play
	/*!
	\Inicia a exibição do vídeo.
	*/
	virtual void play()
	{
		if( m_dshow_player )
			m_dshow_player->play();
	}

	//! stop
	/*!
	\Para a exibição do vídeo.
	*/
	virtual void stop()
	{
		if( m_dshow_player )
			m_dshow_player->stop();
	}

	//! Pause
	/*!
	\Pausa a exibição do vídeo.
	*/
	virtual void pause()
	{
		if( m_dshow_player )
			m_dshow_player->pause();
	}

	//! SetPosition
	/*!
	\Determina a posição de exibição do vídeo em segundos.
	*/
	virtual void setPosition(LONGLONG position)
	{
		if( m_dshow_player )
			m_dshow_player->setPosition(position);
	}

	//! setFrame
	/*!
	\Define a posição de exibição do vídeo em frames.
	*/
	virtual void setFrame( LONGLONG position )
	{
		if( m_dshow_player )
			m_dshow_player->setFrame( position );
	}

	//! getPosition()
	/*!
	\Retorna a posição atual de exibição do vídeo em milisegundos.
	*/
	virtual LONGLONG getPosition()
	{
		if( m_dshow_player )
			return m_dshow_player->getPosition();

		return 0;
	}

	//! setLoop
	/*!
	\param1: ativar loop no vídeo? (true[default] ou false).
	*/
	virtual void setLoop(bool enable=true)
	{
		if( m_dshow_player )
			m_dshow_player->setLoop(enable);
	}

	//! isPlaying
	/*!
	\Retorna 'true' se o vídeo estiver tocando ou 'false' no caso contrário.
	*/
	virtual bool isPlaying()
	{
		if( m_dshow_player )
			return m_dshow_player->isPlaying();

		return true;
	}

	//! isLooping
	/*!
	\Retorna 'true' se o vídeo estiver em loop ou 'false' no caso contrário.
	*/
	virtual bool isLooping()
	{
		if( m_dshow_player )
			return m_dshow_player->isLooping();

		return true;
	}

	//! GetVolume
	/*!
	\Retorna o volume (0 a 100)%.
	*/
	inline virtual long getVolume()
	{
		if( m_dshow_player )
			return m_dshow_player->getVolume();
		return 0;
	}

	//! SetVolume
	/*!
	\Define o volume (0 a 100)%.
	*/
	inline virtual void setVolume(long vol)
	{
		if( m_dshow_player )
			m_dshow_player->setVolume(vol);
	}

	//! PlayCutscene
	/*!
	\Toca o vídeo carregado em tela cheia.
	\Retorna 'false' se o dispositivo da Irrlicht for fechado. Neste caso, finalize a aplicação imediatamente.
	*/
	virtual bool playCutscene();

	//! drawBackbround
	/*!
	\Exibe o vídeo como tela de fundo.
	*/
	virtual bool drawBackground( );

	//! getSize
	/*!
	\Retorna a dimensão 2D da textura
	*/
	dimension2d<s32> getSize()
	{
		if( m_pTempTexture )
			return m_pTempTexture->getSize();

		return dimension2d<s32>(0,0);
	}

	//! getBufferSize
	/*!
	\Retorna o tamanho, em bytes, do buffer de textura utilizado.
	*/
	u32 getBufferSize()
	{
		return m_copy_buffer_size;
	}

private:

	//! Dispositivo da Irrlicht
	IrrlichtDevice *m_device;

	//! Buffer de textura
	ITexture *m_pTempTexture;

	//! Tipo da textura
	bool m_bStaticTexture;

	//! Formato de cores da textura
	ECOLOR_FORMAT m_color_format;

	//! Objeto de IVideoTextureBase (DirectShow Player)
	dsvt::IVideoTextureBase *m_dshow_player;

	//! Tamanho do buffer de vídeo em bytes
	u32 m_video_buffer_size;

	//! Cópia do buffer de vídeo
	u32 m_copy_buffer_size;

protected:

	// Conversões a partir do formato RGB_32
	static void RGB_32_To_A8R8G8B8(dsvt::SFrameData& data);
	static void RGB_32_To_A1R5G5B5(dsvt::SFrameData& data);
	static void RGB_32_To_R5G6B5(dsvt::SFrameData& data);
	static void RGB_32_To_R8G8B8(dsvt::SFrameData& data);

	// Conversões a partir do formato RGB_24
	static void RGB_24_To_A8R8G8B8(dsvt::SFrameData& data);
	static void RGB_24_To_A1R5G5B5(dsvt::SFrameData& data);
	static void RGB_24_To_R5G6B5(dsvt::SFrameData& data);
	static void RGB_24_To_R8G8B8(dsvt::SFrameData& data);

	// Conversões a partir do formato RGB_565
	static void RGB_565_To_A8R8G8B8(dsvt::SFrameData& data);
	static void RGB_565_To_A1R5G5B5(dsvt::SFrameData& data);
	static void RGB_565_To_R5G6B5(dsvt::SFrameData& data);
	static void RGB_565_To_R8G8B8(dsvt::SFrameData& data);

	// Conversões do formato RGB_555 (não suportado) para formato válido RGB_565
	static void RGB_555_To_A8R8G8B8(dsvt::SFrameData& data);
	static void RGB_555_To_A1R5G5B5(dsvt::SFrameData& data);
	static void RGB_555_To_R5G6B5(dsvt::SFrameData& data);
	static void RGB_555_To_R8G8B8(dsvt::SFrameData& data);

	// Conversões do formato RGB_8 (não suportado) para formato válido
	static void RGB_8_To_A8R8G8B8(dsvt::SFrameData& data);
	static void RGB_8_To_A1R5G5B5(dsvt::SFrameData& data);
	static void RGB_8_To_R5G6B5(dsvt::SFrameData& data);
	static void RGB_8_To_R8G8B8(dsvt::SFrameData& data);
};