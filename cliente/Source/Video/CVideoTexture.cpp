#pragma once

#include "CVideoTexture.h"
#include "dsvt.h"
#include <irrlicht.h>

using namespace irr;
using namespace video;
using namespace dsvt;

CVideoTexture::CVideoTexture()
{
    m_device = 0;

    m_pTempTexture = 0;

    m_bStaticTexture = true;

    m_dshow_player = 0;

    m_color_format = ECF_A8R8G8B8;

    m_video_buffer_size = 0;

    m_copy_buffer_size = 0;
}

CVideoTexture::CVideoTexture( IrrlichtDevice *device,ITexture *texture)
{
    m_device = device;

    m_pTempTexture = texture;

    m_color_format = ECF_A8R8G8B8;

    m_dshow_player = 0;

    m_bStaticTexture = true;

    m_video_buffer_size = 0;

    m_copy_buffer_size = 0;
}

CVideoTexture::CVideoTexture( IrrlichtDevice *device, const char* file, bool& bSuccess)
{
    m_device = device;

    m_pTempTexture = 0;

    m_color_format = ECF_A8R8G8B8;

    m_bStaticTexture = false;

    m_dshow_player = dsvt::IVideoTextureBase::createVideoTexture( file, RGB_32 );

    if( !m_dshow_player )
    {
        bSuccess = false;
        return;
    }

    m_video_buffer_size = m_dshow_player->getWidth() * m_dshow_player->getHeight() * 4 /* RGB_32*/;
    m_copy_buffer_size = m_video_buffer_size;

    m_pTempTexture = device->getVideoDriver()->addTexture(dimension2d<s32>( m_dshow_player->getWidth(),
                                                        m_dshow_player->getHeight()),
                                                        "target",ECF_A8R8G8B8);

    if( !m_pTempTexture )
    {
        bSuccess = false;
        return;
    }

    dimension2d<s32> size = m_pTempTexture->getSize();
    u32 texture_size = size.Height * size.Width;

    m_pTempTexture->grab();

    m_color_format = m_pTempTexture->getColorFormat();

    switch( m_color_format )
    {
        case ECF_A1R5G5B5:
        case ECF_R5G6B5:
            texture_size *= 2;
        break;

        case ECF_R8G8B8:
            texture_size *= 3;
        break;

        case ECF_A8R8G8B8:
            texture_size *= 4;
        break;
    }

    if( texture_size < m_copy_buffer_size)
        m_copy_buffer_size = texture_size;

    switch( m_dshow_player->getFormat() )
    {
        case RGB_8:
            switch( m_color_format )
            {
                case ECF_A1R5G5B5:
                    m_dshow_player->setCallback( RGB_8_To_A1R5G5B5, this );
                break;

                case ECF_R5G6B5:
                    m_dshow_player->setCallback( RGB_8_To_R5G6B5, this );
                break;

                case ECF_R8G8B8:
                    m_dshow_player->setCallback( RGB_8_To_R8G8B8, this );
                break;

                case ECF_A8R8G8B8:
                    m_dshow_player->setCallback( RGB_8_To_A8R8G8B8, this );
                break;
            }
        break;

        case RGB_555:
            switch( m_color_format )
            {
                case ECF_A1R5G5B5:
                    m_dshow_player->setCallback( RGB_555_To_A1R5G5B5, this );
                break;

                case ECF_R5G6B5:
                    m_dshow_player->setCallback( RGB_555_To_R5G6B5, this );
                break;

                case ECF_R8G8B8:
                    m_dshow_player->setCallback( RGB_555_To_R8G8B8, this );
                break;

                case ECF_A8R8G8B8:
                    m_dshow_player->setCallback( RGB_555_To_A8R8G8B8, this );
                break;
            }
        break;

        case RGB_565:
            switch( m_color_format )
            {
                case ECF_A1R5G5B5:
                    m_dshow_player->setCallback( RGB_565_To_A1R5G5B5, this );
                break;

                case ECF_R5G6B5:
                    m_dshow_player->setCallback( RGB_565_To_R5G6B5, this );
                break;

                case ECF_R8G8B8:
                    m_dshow_player->setCallback( RGB_565_To_R8G8B8, this );
                break;

                case ECF_A8R8G8B8:
                    m_dshow_player->setCallback( RGB_565_To_A8R8G8B8, this );
                break;
            }
        break;

        case RGB_24:
            switch( m_color_format )
            {
                case ECF_A1R5G5B5:
                    m_dshow_player->setCallback( RGB_24_To_A1R5G5B5, this );
                break;

                case ECF_R5G6B5:
                    m_dshow_player->setCallback( RGB_24_To_R5G6B5, this );
                break;

                case ECF_R8G8B8:
                    m_dshow_player->setCallback( RGB_24_To_R8G8B8, this );
                break;

                case ECF_A8R8G8B8:
                    m_dshow_player->setCallback( RGB_24_To_A8R8G8B8, this );
                break;
            }
        break;

        case RGB_32:
        case ARGB_32:
            switch( m_color_format )
            {
                case ECF_A1R5G5B5:
                    m_dshow_player->setCallback( RGB_32_To_A1R5G5B5, this );
                break;

                case ECF_R5G6B5:
                    m_dshow_player->setCallback( RGB_32_To_R5G6B5, this );
                break;

                case ECF_R8G8B8:
                    m_dshow_player->setCallback( RGB_32_To_R8G8B8, this );
                break;

                case ECF_A8R8G8B8:
                    m_dshow_player->setCallback( RGB_32_To_A8R8G8B8, this );
                break;
            }
        break;
    }
}

CVideoTexture::CVideoTexture( IrrlichtDevice *device, dsvt::ICaptureDevice *cap, bool& bSuccess)
{
    m_device = device;

    m_pTempTexture = 0;

    m_color_format = ECF_A8R8G8B8;

    m_bStaticTexture = false;

    m_dshow_player = dsvt::IVideoTextureBase::createCaptureTexture( cap, RGB_32 );

    if( !m_dshow_player )
    {
        bSuccess = false;
        return;
    }

    m_video_buffer_size = m_dshow_player->getWidth() * m_dshow_player->getHeight() * 4 /* RGB_32*/;
    m_copy_buffer_size = m_video_buffer_size;

    m_pTempTexture = device->getVideoDriver()->addTexture(core::dimension2d<s32>( m_dshow_player->getWidth(),
                                                        m_dshow_player->getHeight()),
                                                        "target",ECF_A8R8G8B8);

    if( !m_pTempTexture )
    {
        bSuccess = false;
        return;
    }

    dimension2d<s32> size = m_pTempTexture->getSize();
    u32 texture_size = size.Height * size.Width;

    m_pTempTexture->grab();

    m_color_format = m_pTempTexture->getColorFormat();

    switch( m_color_format )
    {
        case ECF_A1R5G5B5:
        case ECF_R5G6B5:
            texture_size *= 2;
        break;

        case ECF_R8G8B8:
            texture_size *= 3;
        break;

        case ECF_A8R8G8B8:
            texture_size *= 4;
        break;
    }

    if( texture_size < m_copy_buffer_size)
        m_copy_buffer_size = texture_size;

    switch( m_dshow_player->getFormat() )
    {
        case RGB_8:
            switch( m_color_format )
            {
                case ECF_A1R5G5B5:
                    m_dshow_player->setCallback( RGB_8_To_A1R5G5B5, this );
                break;

                case ECF_R5G6B5:
                    m_dshow_player->setCallback( RGB_8_To_R5G6B5, this );
                break;

                case ECF_R8G8B8:
                    m_dshow_player->setCallback( RGB_8_To_R8G8B8, this );
                break;

                case ECF_A8R8G8B8:
                    m_dshow_player->setCallback( RGB_8_To_A8R8G8B8, this );
                break;
            }
        break;

        case RGB_555:
            switch( m_color_format )
            {
                case ECF_A1R5G5B5:
                    m_dshow_player->setCallback( RGB_555_To_A1R5G5B5, this );
                break;

                case ECF_R5G6B5:
                    m_dshow_player->setCallback( RGB_555_To_R5G6B5, this );
                break;

                case ECF_R8G8B8:
                    m_dshow_player->setCallback( RGB_555_To_R8G8B8, this );
                break;

                case ECF_A8R8G8B8:
                    m_dshow_player->setCallback( RGB_555_To_A8R8G8B8, this );
                break;
            }
        break;

        case RGB_565:
            switch( m_color_format )
            {
                case ECF_A1R5G5B5:
                    m_dshow_player->setCallback( RGB_565_To_A1R5G5B5, this );
                break;

                case ECF_R5G6B5:
                    m_dshow_player->setCallback( RGB_565_To_R5G6B5, this );
                break;

                case ECF_R8G8B8:
                    m_dshow_player->setCallback( RGB_565_To_R8G8B8, this );
                break;

                case ECF_A8R8G8B8:
                    m_dshow_player->setCallback( RGB_565_To_A8R8G8B8, this );
                break;
            }
        break;

        case RGB_24:
            switch( m_color_format )
            {
                case ECF_A1R5G5B5:
                    m_dshow_player->setCallback( RGB_24_To_A1R5G5B5, this );
                break;

                case ECF_R5G6B5:
                    m_dshow_player->setCallback( RGB_24_To_R5G6B5, this );
                break;

                case ECF_R8G8B8:
                    m_dshow_player->setCallback( RGB_24_To_R8G8B8, this );
                break;

                case ECF_A8R8G8B8:
                    m_dshow_player->setCallback( RGB_24_To_A8R8G8B8, this );
                break;
            }
        break;

        case RGB_32:
        case ARGB_32:
            switch( m_color_format )
            {
                case ECF_A1R5G5B5:
                    m_dshow_player->setCallback( RGB_32_To_A1R5G5B5, this );
                break;

                case ECF_R5G6B5:
                    m_dshow_player->setCallback( RGB_32_To_R5G6B5, this );
                break;

                case ECF_R8G8B8:
                    m_dshow_player->setCallback( RGB_32_To_R8G8B8, this );
                break;

                case ECF_A8R8G8B8:
                    m_dshow_player->setCallback( RGB_32_To_A8R8G8B8, this );
                break;
            }
        break;
    }
}

CVideoTexture::~CVideoTexture()
{
    if( m_dshow_player )
        m_dshow_player->drop();

    m_device = 0;

    if( m_pTempTexture && !m_bStaticTexture)
        m_pTempTexture->drop();

    m_pTempTexture = 0;
}


CVideoTexture* CVideoTexture::createVideoTexture( IrrlichtDevice *device, const char* file)
{
    if( !device)
    {
        return 0;
    }

    if( !device->getFileSystem()->existFile( file ))
    {
        printf("erro: arquivo nao existe: %s%s",file,"\n");

        return 0;
    }

    IVideoDriver *driver = device->getVideoDriver();

    ITexture *stTex = driver->getTexture( file );

    CVideoTexture *tmpTexture = 0;

    if( stTex )
    {
        tmpTexture = new CVideoTexture(device, stTex);

        if( !tmpTexture )
            return 0;

        printf( "textura estatica criada: %s%s",file,"\n");
    }
    else  
    {

        E_DRIVER_TYPE drvtp = device->getVideoDriver()->getDriverType();
        if( drvtp == EDT_SOFTWARE || drvtp == EDT_BURNINGSVIDEO || drvtp==EDT_NULL)
        {
            return 0;
        }

        bool bSuccess = true;
        tmpTexture = new CVideoTexture(device, file,bSuccess);

        if( !bSuccess )
        {
            tmpTexture->drop();
            return 0;
        }

        printf( "textura dinamica criada: %s%s",file,"\n");
    }

    return tmpTexture;
}

CVideoTexture* CVideoTexture::createCaptureTexture( IrrlichtDevice *device , dsvt::ICaptureDevice *cap )
{
    if( !device)
    {
        return 0;
    }

    // Test device
    E_DRIVER_TYPE drvtp = device->getVideoDriver()->getDriverType();
    if( drvtp == EDT_SOFTWARE || drvtp == EDT_BURNINGSVIDEO || drvtp==EDT_NULL)
    {
        return 0;
    }

    bool bSuccess = true;
    CVideoTexture *tmpTexture = 0;
    tmpTexture = new CVideoTexture(device, cap ,bSuccess);

    if( !bSuccess )
    {
        tmpTexture->drop();
        return 0;
    }

    printf( "textura de captura criada\n");

    return tmpTexture;
}

bool CVideoTexture::playCutscene( void )
{
    stop();
    setPosition(0);

    bool bLoopMode = isLooping();
    setLoop(false);

    IVideoDriver *drv = m_device->getVideoDriver();
    rect<s32> viewport = drv->getViewPort();

    class VideoEventReceiver : public irr::IEventReceiver
    {
        public:
            bool bQuit;

            virtual bool OnEvent( const SEvent& event )
            {
				if ( event.EventType == EET_KEY_INPUT_EVENT && event.KeyInput.Key == KEY_ESCAPE)
                    bQuit = true;

                return false;
            }
    };

    IEventReceiver *oldEvent = m_device->getEventReceiver();
    VideoEventReceiver myEventReceiver;
    myEventReceiver.bQuit = false;
    m_device->setEventReceiver(&myEventReceiver);

    play();

    bool bIrrlichtRun = true;

    while( (bIrrlichtRun = m_device->run()) && !myEventReceiver.bQuit)
    {
        update();

        drv->beginScene(true,true,video::SColor(255,0,0,0));

            drawBackground();

        drv->endScene();

        if( !isPlaying() )
        {
            myEventReceiver.bQuit = true;
        }
    }

    if( bIrrlichtRun )
        m_device->setEventReceiver(oldEvent);

    setLoop(bLoopMode);

    return bIrrlichtRun;
}

bool CVideoTexture::drawBackground( )
{
    IVideoDriver *drv = m_device->getVideoDriver();
    dimension2d<s32> ssize = drv->getCurrentRenderTargetSize();
    dimension2d<s32> tsize = getSize();

    drv->draw2DImage(m_pTempTexture, rect<s32>(0, 0, ssize.Width, ssize.Height),
                rect<s32>(0, 0, tsize.Width, tsize.Height));

    return false;
}

ITexture *CVideoTexture::getTexture()
{
    return m_pTempTexture;
}

void CVideoTexture::RGB_32_To_A8R8G8B8( SFrameData& data )
{
    CVideoTexture *texBase = reinterpret_cast<CVideoTexture*>(data.userData);
    if( !texBase )
        return;

    ITexture *tex = texBase->getTexture();
    if(!tex)
        return;

    s32 *video_buffer = reinterpret_cast<s32*>(data.pBuffer);
    s32 *texture_buffer = reinterpret_cast<s32*>(tex->lock());

    if( !texture_buffer )
    {
        printf("falha no lock\n");
        return;
    }

    u32 pitch = texBase->getBufferSize()/4;
    video_buffer += pitch;
    s32 *old_vbuffer = video_buffer;

    for( u32 i=0;i<(u32)data.iHeight;i++)
    {
        video_buffer -= data.iWidth;
        old_vbuffer = video_buffer;

        for( u32 x=0;x<(u32)data.iWidth;x++)
        {
            *texture_buffer = *video_buffer;
            texture_buffer++;
            video_buffer++;
        }

        video_buffer = old_vbuffer;
    }

    tex->unlock();
}

void CVideoTexture::RGB_32_To_A1R5G5B5(dsvt::SFrameData& data)
{
    CVideoTexture *texBase = reinterpret_cast<CVideoTexture*>(data.userData);
    if( !texBase )
        return;

    ITexture *tex = texBase->getTexture();
    if(!tex)
        return;

    s32 *video_buffer = reinterpret_cast<s32*>(data.pBuffer);
    s16 *texture_buffer = reinterpret_cast<s16*>(tex->lock());

    if( !texture_buffer )
    {
        printf("falha no lock\n");
        return;
    }

    u32 pitch = texBase->getBufferSize()/4;
    video_buffer += pitch;
    s32 *old_vbuffer = video_buffer;

    for( int i=0;i<data.iHeight;i++)
    {
        video_buffer -= data.iWidth;
        old_vbuffer = video_buffer;

        for( int x=0;x<data.iWidth;x++)
        {
            *texture_buffer = ( (video_buffer[0]) & 0xFF000000) >> 16|
                                ( (video_buffer[0]) & 0x00FF0000) >> 9 |
                                ( (video_buffer[0]) & 0x0000FF00) >> 6 |
                                ( (video_buffer[0]) & 0x000000FF) >> 3;
            texture_buffer++;
            video_buffer++;
        }

        video_buffer = old_vbuffer;
    }

    tex->unlock();
}

void CVideoTexture::RGB_32_To_R5G6B5(dsvt::SFrameData& data)
{
    CVideoTexture *texBase = reinterpret_cast<CVideoTexture*>(data.userData);
    if( !texBase )
        return;

    ITexture *tex = texBase->getTexture();
    if(!tex)
        return;

    s32 *video_buffer = reinterpret_cast<s32*>(data.pBuffer);
    s16 *texture_buffer = reinterpret_cast<s16*>(tex->lock());

    if( !texture_buffer )
    {
        printf("falha no lock\n");
        return;
    }

    u32 pitch = texBase->getBufferSize()/4;
    video_buffer += pitch;
    s32 *old_vbuffer = video_buffer;

    for( int i=0;i<data.iHeight;i++)
    {
        video_buffer -= data.iWidth;
        old_vbuffer = video_buffer;

        for( int x=0;x<data.iWidth;x++)
        {
            *texture_buffer =   ( (video_buffer[0]) & 0x00F80000) >> 8 |
                                ( (video_buffer[0]) & 0x0000FC00) >> 6 |
                                ( (video_buffer[0]) & 0x000000FF) >> 3;
            texture_buffer++;
            video_buffer++;
        }

        video_buffer = old_vbuffer;
    }

    tex->unlock();
}

void CVideoTexture::RGB_32_To_R8G8B8(dsvt::SFrameData& data)
{
    CVideoTexture *texBase = reinterpret_cast<CVideoTexture*>(data.userData);
    if( !texBase )
        return;

    ITexture *tex = texBase->getTexture();
    if(!tex)
        return;

    s8 *video_buffer = reinterpret_cast<s8*>(data.pBuffer);
    s8 *texture_buffer = reinterpret_cast<s8*>(tex->lock());

    if( !texture_buffer )
    {
        printf("falha no lock\n");
        return;
    }

    u32 pitch = texBase->getBufferSize();
    video_buffer += pitch;
    s8 *old_vbuffer = video_buffer;

    for( int i=0;i<data.iHeight;i++)
    {
        video_buffer -= data.iWidth;
        old_vbuffer = video_buffer;

        for( int x=0;x<data.iWidth;x++)
        {
            texture_buffer[0] = video_buffer[0];
            texture_buffer[1] = video_buffer[1];
            texture_buffer[2] = video_buffer[2];

            texture_buffer+=3;
            video_buffer+=4;
        }

        video_buffer = old_vbuffer;
    }

    tex->unlock();
}

void CVideoTexture::RGB_24_To_A8R8G8B8(dsvt::SFrameData& data)
{
    CVideoTexture *texBase = reinterpret_cast<CVideoTexture*>(data.userData);
    if( !texBase )
        return;

    ITexture *tex = texBase->getTexture();
    if(!tex)
        return;

    s8 *video_buffer = reinterpret_cast<s8*>(data.pBuffer);
    s8 *texture_buffer = reinterpret_cast<s8*>(tex->lock());

    if( !texture_buffer )
    {
        printf("falha no lock\n");
        return;
    }

    int pitch = texBase->getBufferSize()/4;

    video_buffer += pitch*3;

    s8 *old_vbuffer = video_buffer;

    for( int i=0;i<data.iHeight;i++)
    {
        video_buffer -= data.iWidth*3;
        old_vbuffer = video_buffer;

        for( int x=0;x<data.iWidth;x++)
        {
            texture_buffer[3] =  0xFF;
            texture_buffer[2] = video_buffer[2];
            texture_buffer[1] = video_buffer[1];
            texture_buffer[0] = video_buffer[0];

            texture_buffer+=4;
            video_buffer+=3;
        }

        video_buffer = old_vbuffer;
    }

    tex->unlock();
}

void CVideoTexture::RGB_24_To_A1R5G5B5(dsvt::SFrameData& data)
{
    printf( "24to16\n");
}

void CVideoTexture::RGB_24_To_R5G6B5(dsvt::SFrameData& data)
{
    CVideoTexture *texBase = reinterpret_cast<CVideoTexture*>(data.userData);
    if( !texBase )
        return;

    ITexture *tex = texBase->getTexture();
    if(!tex)
        return;

    s8 *video_buffer = reinterpret_cast<s8*>(data.pBuffer);
    s16 *texture_buffer = reinterpret_cast<s16*>(tex->lock());

    if( !texture_buffer )
    {
        printf("falha no lock\n");
        return;
    }

    u32 pitch = texBase->getBufferSize();
    video_buffer += pitch;
    s8 *old_vbuffer = video_buffer;

    for( int i=0;i<data.iHeight;i++)
    {
        video_buffer -= data.iWidth;
        old_vbuffer = video_buffer;

        for( int x=0;x<data.iWidth;x++)
        {
            *texture_buffer =   ( (video_buffer[2]) >> 3) << 11 |
                                ( (video_buffer[1]) >> 2) >> 5 |
                                ( (video_buffer[0]) >> 3);

            texture_buffer++;
            video_buffer+=3;
        }

        video_buffer = old_vbuffer;
    }

    tex->unlock();
}

void CVideoTexture::RGB_24_To_R8G8B8(dsvt::SFrameData& data)
{
    CVideoTexture *texBase = reinterpret_cast<CVideoTexture*>(data.userData);
    if( !texBase )
        return;

    ITexture *tex = texBase->getTexture();
    if(!tex)
        return;

    char *video_buffer = reinterpret_cast<char*>(data.pBuffer);
    char *texture_buffer = reinterpret_cast<char*>(tex->lock());

    if( !texture_buffer )
    {
        printf("falha no lock\n");
        return;
    }

    int pitch = texBase->getBufferSize();
    video_buffer += pitch;
    char *old_vbuffer = video_buffer;

    for( int i=0;i<data.iHeight;i++)
    {
        video_buffer -= data.iWidth*3;
        old_vbuffer = video_buffer;

        for( int x=0;x<data.iWidth*3;x++)
        {
            *texture_buffer = *video_buffer;
            texture_buffer++;
            video_buffer++;
        }

        video_buffer = old_vbuffer;
    }

    tex->unlock();
}

void CVideoTexture::RGB_565_To_A8R8G8B8(dsvt::SFrameData& data)
{
    CVideoTexture *texBase = reinterpret_cast<CVideoTexture*>(data.userData);
    if( !texBase )
        return;

    ITexture *tex = texBase->getTexture();
    if(!tex)
        return;

    s16 *video_buffer = reinterpret_cast<s16*>(data.pBuffer);
    s32 *texture_buffer = reinterpret_cast<s32*>(tex->lock());

    if( !texture_buffer )
    {
        printf("falha no lock\n");
        return;
    }

    int pitch = texBase->getBufferSize()/4;
    video_buffer += pitch;
    s16 *old_vbuffer = video_buffer;

    for( int i=0;i<data.iHeight;i++)
    {
        video_buffer -= data.iWidth;
        old_vbuffer = video_buffer;

        for( int x=0;x<data.iWidth;x++)
        {
            *texture_buffer = 0xFF000000 |
                            ((*video_buffer) & 0x1F000) << 8 |
                            ((*video_buffer) & 0x07E0) << 5 |
                            ((*video_buffer) & 0x001F) << 3;

            texture_buffer++;
            video_buffer++;
        }

        video_buffer = old_vbuffer;
    }

    tex->unlock();
}

void CVideoTexture::RGB_565_To_A1R5G5B5(dsvt::SFrameData& data)
{
    printf( "16to16\n");
}

void CVideoTexture::RGB_565_To_R5G6B5(dsvt::SFrameData& data)
{
    printf( "16to16\n");
}

void CVideoTexture::RGB_565_To_R8G8B8(dsvt::SFrameData& data)
{
    printf( "16to24\n");
}

void CVideoTexture::RGB_555_To_A8R8G8B8(dsvt::SFrameData& data)
{
    printf( "16to32\n");
}

void CVideoTexture::RGB_555_To_A1R5G5B5(dsvt::SFrameData& data)
{
    printf( "16to16\n");
}

void CVideoTexture::RGB_555_To_R5G6B5(dsvt::SFrameData& data)
{
    printf( "16to16\n");
}

void CVideoTexture::RGB_555_To_R8G8B8(dsvt::SFrameData& data)
{
    printf( "16to24\n");
}

void CVideoTexture::RGB_8_To_A8R8G8B8(dsvt::SFrameData& data)
{
    printf( "8to32\n");
}

void CVideoTexture::RGB_8_To_A1R5G5B5(dsvt::SFrameData& data)
{
    printf( "8to16\n");
}

void CVideoTexture::RGB_8_To_R5G6B5(dsvt::SFrameData& data)
{
    printf( "8to16\n");
}

void CVideoTexture::RGB_8_To_R8G8B8(dsvt::SFrameData& data)
{
    printf( "8to24\n");
}