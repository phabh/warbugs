#ifndef _DSVT_H_
#define _DSVT_H_

//!  Video Texture class
/*!
dsvt-0.6.5
 Video texture library for irrlicht and non irrlicht use. Based on DirectShow.

 Header file for Nor-Irrlicht use.

    Author: vi-wer

*/



//!  LONGLONG define
/*!
*/
#ifndef LONGLONG
	#define LONGLONG long long
#endif

//!  dsvt version
/*!
*/
#define DSVT_VERSION    "6.5-Beta"


//! Video format enumeration
/*! Describes color format data. */
enum E_FORMAT{
    RGB_8,  /**<  8 Bit */
    RGB_555, /**< 16 Bit, 5 Bit every color */
    RGB_565, /**< 16 Bit, 5 Bit for green color */
    RGB_24, /**< 24 Bit, 8 Bit every color */
    RGB_32, /**< 32 Bit, 8 Bit every color, first 8 Bit unused */
    ARGB_32, /**< 32 Bit with Alpha, 8 Bit every color and alpha channel */
};

//! dsvt namespace
/*!
*/
namespace dsvt
{


    //! Capture device class
	/*!
    */
    class /*__declspec(dllimport)*/ ICaptureDevice
    {
        public:
            //! Constructor
		    /*!

			*/
            ICaptureDevice();

            //! Destructor
		    /*!

			*/
            virtual ~ICaptureDevice();

            //! Get Next Device
		    /*!
                Returns pointer to next Capture device or NULL if none exist
			*/
            virtual ICaptureDevice *getNext();

            //! Enumerate capture devices
		    /*!
                Returns pointer to first capture device or NULL if none exist.
                Last Device in the list is not used.
			*/
            static ICaptureDevice *enumDevices();
    };


    //! Frame data struct
	/*!
        Retrieves data used by callback functions
	*/
    struct SFrameData
    {
        //! Buffer pointer
        /*!
            Video buffer.
        */
        char *pBuffer;      // frame buffer data

        //! Color format
        /*!
            E_FORMAT color type used in pBuffer.
        */
        E_FORMAT iColorFormat;   //Color Format

        //! Buffer size
        /*!
            Video buffer size in bytes.
        */
        long iSize;     //Number of Bytes

        //! Video width
        /*!

        */
        int iWidth;

        //! Video height
        /*!

        */
        int iHeight;

        //! Average time per frame
        /*!
            Information only. Get frame per second by 1000/iTimePerFrame.
        */
        int iTimePerFrame;

        //! User data
        /*!

        */
        void *userData;
    };



    //! Irrlicht video texture class
	/*!
        Video texture class
	*/
    class /*__declspec(dllimport)*/ IVideoTextureBase
    {
        public:
			//! Constructor
		    /*!

			*/
            IVideoTextureBase();

			//! Destructor
		    /*!

			*/
            virtual ~IVideoTextureBase();



			//! Creates Video texture
			/*!
				Does not create an Irrlicht texture. Loads a media to buffer that can be accessed by a callback function.
			      \param file File Name
			      \return Pointer to a Video Texture or NULL if failed
			    */
            static IVideoTextureBase* createVideoTexture( const char* file,E_FORMAT fmt = RGB_24, char *version = DSVT_VERSION);



			//! Creates Video texture
			/*!
				Does not create an Irrlicht texture. Opens a capture device that can be accessed by a callback function.
			      \param cap Capture Device ID.
			      \return Pointer to a Video Texture or NULL if failed
			    */
            static IVideoTextureBase* createCaptureTexture( ICaptureDevice *cap = NULL,E_FORMAT fmt = RGB_32, char *version = DSVT_VERSION);

			//! Returns first texture that was created
			/*!
			      \return Pointer to a Video Texture or NULL if none exist.
			    */
            static IVideoTextureBase* getFirstTexture();

            //! Returns next texture from list
			/*!
			      \return Pointer to a Video Texture or NULL if none exist.
            */
            IVideoTextureBase* getNextTexture();


			//! Sets Callback Function
			/*!
			      Set Callback function.
				Create a callback function as follow.
				void callback( SFrameData& data)

				setCallback( callback );

				Don't use with Irrlicht texture.
            */
            virtual void setCallback( void (*call) (SFrameData& data), void* userData = 0);

			//! Remove Video texture
			/*!
			      Video texture can't be used anymore.
				  Irrlicht texture that was returned by getTexture will not be removed.
			    */
            virtual void drop();

			//! Update Video texture
			/*!
			      Should be called as often as necessary.
                    Also when using callback function.
            */
            virtual bool update();

			//! Play media
			/*!

			    */
            virtual void play();

			//! Stop media
			/*!

			    */
            virtual void stop();

			//! Pause media
			/*!

			    */
            virtual void pause();

			//! Set media position
			/*!
				Set media position in seconds.
			    */
            virtual void setPosition(LONGLONG position);

			//! Set media position
			/*!
				Set media position as frame.
			    */
            virtual void setFrame( LONGLONG position );

			//! Get media position
			/*!
				Returns media position in 1ms.
			    */
            virtual LONGLONG getPosition(); // 1ms

			//! Enable loop mode
			/*!

			    */
            virtual void setLoop(bool enable=true);

			//! Get play state
			/*!
				Returns true if media is playing
			    */
            virtual bool isPlaying();

			//! Get loop mode
			/*!
			    */
            virtual bool isLooping();

            //! Get Volume
			/*!
				Returns volume in percentages (0-100)
			    */
            inline virtual long getVolume();

			//! Set Volume
			/*!
				Set volume in percentages (0-100)
			    */
            inline virtual void setVolume(long vol);

            //! Get Format
			/*!
				returns color format
			    */
            virtual E_FORMAT getFormat();

            //! Get Width
			/*!
				\return video width
            */
            int getWidth();

            //! Get Height
			/*!
				\return video height
            */
            int getHeight();

            //! Set User data
			/*!
            */
            void setUserData( void *userdata);

            //! Get Userdata
			/*!
				\return void pointer to data.
            */
            void *getUserData( );
    };

}


#endif // _DSVT_H_
