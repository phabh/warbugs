#ifndef IVIDEOTEXTURE_H_INCLUDED
#define IVIDEOTEXTURE_H_INCLUDED

//!  Video Texture class
/*!
dsvt-0.6.5
 Video texture library for irrlicht and non-irrlicht use. Based on DirectShow.

Header file for Irrlicht use.

    Author: vi-wer
*/


#include <irrlicht.h>
#include "dsvt.h"

using namespace irr; 
using namespace core; 
using namespace scene; 
using namespace video; 
using namespace io; 
using namespace gui;
//! irr namespace
/*!
*/

//namespace irr
//{

//! video namespace
/*!
*/
//namespace video
//{

    //! Irrlicht video texture class
	/*!
        Video texture class.

        Include IVideoTexture.h for Irrlicht use. Callback functions can be used
        but not with createTexture methods that need an Irrlicht device.

        Include dsvt.h for non Irrlicht use. Callback method only.
	*/
    class IVideoTexture
    {
        public:
			//! Constructor 1
		    /*!
                Simple Constructor
			*/
			IVideoTexture();

			//! Constructor 2
		    /*!
                Static texture constructor
			*/
            IVideoTexture( IrrlichtDevice *device,ITexture *texture);

            //! Constructor 3
		    /*!
                Video texture constructor
			*/
            IVideoTexture( IrrlichtDevice *device, const char* file,bool& bSuccess);

            //! Constructor 4
		    /*!
                Capture device constructor
			*/
            IVideoTexture( IrrlichtDevice *device, dsvt::ICaptureDevice *cap ,bool& bSuccess);

			//! Destructor
		    /*!

			*/
            virtual ~IVideoTexture();


			//! Creates Irrlicht Video texture
			/*!
			      \param device Irrlicht device
			      \param file File Name
			      \return Pointer to a Video Texture or NULL if failed
			    */
            static IVideoTexture* createVideoTexture( IrrlichtDevice *device ,const char* file);



			//! Creates Irrlicht Capture texture
			/*!
				Opens Capture device and renders it's content to a texture.
				\param device Irrlicht device
				\param cap Capture Device ID.Not Implemented
			      \return Pointer to a Video Texture or NULL if failed
			    */
            static IVideoTexture* createCaptureTexture( IrrlichtDevice *device , dsvt::ICaptureDevice *cap = NULL);



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

                if( m_device->getVideoDriver()->getDriverType() != video::EDT_OPENGL && bReturn)
                    m_pTempTexture->regenerateMipMapLevels();

                return bReturn;
            }


			//! Play media
			/*!

			    */
            virtual void play()
            {
                if( m_dshow_player )
                    m_dshow_player->play();
            }



			//! Stop media
			/*!

			    */
            virtual void stop()
            {
                if( m_dshow_player )
                    m_dshow_player->stop();
            }


			//! Pause media
			/*!

			    */
            virtual void pause()
            {
                if( m_dshow_player )
                    m_dshow_player->pause();
            }



			//! Set media position
			/*!
				Set media position in seconds.
			    */
            virtual void setPosition(LONGLONG position)
            {
                if( m_dshow_player )
                    m_dshow_player->setPosition(position);
            }



			//! Set media position
			/*!
				Set media position as frame.
			    */
            virtual void setFrame( LONGLONG position )
            {
                if( m_dshow_player )
                    m_dshow_player->setFrame( position );
            }



			//! Get media position
			/*!
				Returns media position in 1ms.
			    */
            virtual LONGLONG getPosition() // 1ms
            {
                if( m_dshow_player )
                    return m_dshow_player->getPosition();

                return 0;
            }



			//! Enable loop mode
			/*!

			    */
            virtual void setLoop(bool enable=true)
            {
                if( m_dshow_player )
                    m_dshow_player->setLoop(enable);
            }



			//! Get play state
			/*!
				Returns true if media is playing
			    */
            virtual bool isPlaying()
            {
                if( m_dshow_player )
                    return m_dshow_player->isPlaying();

                return true;
            }



			//! Get loop mode
			/*!
			    */
            virtual bool isLooping()
            {
                if( m_dshow_player )
                    return m_dshow_player->isLooping();

                return true;
            }



            //! Get Volume
			/*!
				Returns volume in percentages (0-100)
			    */
            inline virtual long getVolume()
            {
                if( m_dshow_player )
                    return m_dshow_player->getVolume();
                return 0;
            }



			//! Set Volume
			/*!
				Set volume in percentages (0-100)
			    */
            inline virtual void setVolume(long vol)
            {
                if( m_dshow_player )
                    m_dshow_player->setVolume(vol);
            }



			//! Play Video texture fullscreen as FMV Sequence
			/*!
			      Plays loaded media as fullscreen Video (Viewport size).

				 \return Returns false value if Irrlicht Device was closed. Immediatly close your programm or it will crash.

			      Irrlicht Texture mode only.
			    */
            virtual bool playCutscene( );



			//! Draw texture as backbround
			/*!
				Viewport size used.

				Irrlicht Texture mode only.
			    */
            virtual bool drawBackground( );


            //! getSize
			/*!

				\return Returns texture dimension.
            */
            core::dimension2d<s32> getSize()
            {
                if( m_pTempTexture )
                    return m_pTempTexture->getSize();

                return core::dimension2d<s32>(0,0);
            }



            //! getBufferSize
			/*!

				\return Returns useable texture buffer size in bytes.
            */
            u32 getBufferSize()
            {
                return m_copy_buffer_size;
            }


        private:
            //! Irrlicht device
			/*!
            */
            IrrlichtDevice *m_device;

            //! Texture buffer
			/*!
            */
            ITexture *m_pTempTexture;

            //! Texture type
			/*!
            */
            bool m_bStaticTexture;

            //! Texture color format
			/*!
            */
            irr::video::ECOLOR_FORMAT m_color_format;

            //! Texture color format
			/*!
            */
            dsvt::IVideoTextureBase *m_dshow_player;

            //! Video Buffer size
            /*!
                Buffer size in bytes
            */
            u32 m_video_buffer_size;

            //! Copy Buffer size
            /*!
                Buffer size in bytes
            */
            u32 m_copy_buffer_size;

        protected:
            //! RGB_32 conversion
            static void RGB_32_To_A8R8G8B8(dsvt::SFrameData& data);
            //! RGB_32 conversion
            static void RGB_32_To_A1R5G5B5(dsvt::SFrameData& data);
            //! RGB_32 conversion
            static void RGB_32_To_R5G6B5(dsvt::SFrameData& data);
            //! RGB_32 conversion
            static void RGB_32_To_R8G8B8(dsvt::SFrameData& data);

            //! RGB_24 conversion
            static void RGB_24_To_A8R8G8B8(dsvt::SFrameData& data);
            //! RGB_24 conversion
            static void RGB_24_To_A1R5G5B5(dsvt::SFrameData& data);
            //! RGB_24 conversion
            static void RGB_24_To_R5G6B5(dsvt::SFrameData& data);
            //! RGB_24 conversion
            static void RGB_24_To_R8G8B8(dsvt::SFrameData& data);

            //! RGB_565 conversion
            static void RGB_565_To_A8R8G8B8(dsvt::SFrameData& data);
            //! RGB_565 conversion
            static void RGB_565_To_A1R5G5B5(dsvt::SFrameData& data);
            //! RGB_565 conversion
            static void RGB_565_To_R5G6B5(dsvt::SFrameData& data);
            //! RGB_565 conversion
            static void RGB_565_To_R8G8B8(dsvt::SFrameData& data);

            //! RGB_555 conversion not supported, use RGB_565 instead
            static void RGB_555_To_A8R8G8B8(dsvt::SFrameData& data);
            //! RGB_555 conversion not supported, use RGB_565 instead
            static void RGB_555_To_A1R5G5B5(dsvt::SFrameData& data);
            //! RGB_555 conversion not supported, use RGB_565 instead
            static void RGB_555_To_R5G6B5(dsvt::SFrameData& data);
            //! RGB_555 conversion not supported, use RGB_565 instead
            static void RGB_555_To_R8G8B8(dsvt::SFrameData& data);

            //! RGB_8 conversion not supported
            static void RGB_8_To_A8R8G8B8(dsvt::SFrameData& data);
            //! RGB_8 conversion not supported
            static void RGB_8_To_A1R5G5B5(dsvt::SFrameData& data);
            //! RGB_8 conversion not supported
            static void RGB_8_To_R5G6B5(dsvt::SFrameData& data);
            //! RGB_8 conversion not supported
            static void RGB_8_To_R8G8B8(dsvt::SFrameData& data);
    };

//}
//}

//#include "ivideotexture.cpp"

#endif // IVIDEOTEXTURE_H_INCLUDED
