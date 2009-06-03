#include "CHudImageSkin.h"
#include "IVideoDriver.h"
#include "ITexture.h"
#include "rect.h"

using namespace irr;
using namespace io;
using namespace gui;
using namespace core;
using namespace video;

namespace irr
{
	//! Workaround for a bug in IVideoDriver::draw2DImage( ITexture* tex, rect<s32> dstRect, rect<s32> srcRect, rect<s32>* clip, SColor* colors, bool alpha )
	//! It modifies dstRect and srcRect so the resulting dstRect is entirely inside the clipping rect.
	//! srcRect is scaled so the same part of the image is displayed.
	//! Returns false if dstRect is entirely outside clip, or true if at least some of it is inside.
	inline bool clipRects( rect<s32>& dstRect, rect<s32>& srcRect, const rect<s32>& clip )
	{
		// Clip left side
		if ( dstRect.UpperLeftCorner.X < clip.UpperLeftCorner.X )
		{
			s32 w = clip.UpperLeftCorner.X - dstRect.UpperLeftCorner.X;

			f32 percentRemoved = (f32)w / (f32)dstRect.getWidth();

			dstRect.UpperLeftCorner.X = clip.UpperLeftCorner.X;

			srcRect.UpperLeftCorner.X += (s32)(percentRemoved * srcRect.getWidth());
		}

		// Clip top side
		if ( dstRect.UpperLeftCorner.Y < clip.UpperLeftCorner.Y )
		{
			s32 w = clip.UpperLeftCorner.Y - dstRect.UpperLeftCorner.Y;

			f32 percentRemoved = (f32)w / (f32)dstRect.getHeight();

			dstRect.UpperLeftCorner.Y = clip.UpperLeftCorner.Y;

			srcRect.UpperLeftCorner.Y += (s32)(percentRemoved * srcRect.getHeight());
		}

		// Clip right side
		if ( dstRect.LowerRightCorner.X > clip.LowerRightCorner.X )
		{
			s32 w = dstRect.LowerRightCorner.X - clip.LowerRightCorner.X;

			f32 percentRemoved = (f32)w / (f32)dstRect.getWidth();

			dstRect.LowerRightCorner.X = clip.LowerRightCorner.X;

			srcRect.LowerRightCorner.X -= (s32)(percentRemoved * srcRect.getWidth());
		}

		// Clip bottom side
		if ( dstRect.LowerRightCorner.Y > clip.LowerRightCorner.Y )
		{
			s32 w = dstRect.LowerRightCorner.Y - clip.LowerRightCorner.Y;

			f32 percentRemoved = (f32)w / (f32)dstRect.getHeight();

			dstRect.LowerRightCorner.Y = clip.LowerRightCorner.Y;

			srcRect.LowerRightCorner.Y -= (s32)(percentRemoved * srcRect.getHeight());
		}

		return ( dstRect.getWidth() > 0 && dstRect.getHeight() > 0 );
	}

	namespace gui
	{

		CHudImageSkin::CHudImageSkin( IVideoDriver* driver, IGUISkin* fallbackSkin )
		{
			VideoDriver = driver;
			FallbackSkin = fallbackSkin;
			FallbackSkin->grab();
		}

		CHudImageSkin::~CHudImageSkin()
		{
			FallbackSkin->drop();
		}

		void CHudImageSkin::loadConfig( const SImageGUISkinConfig& config )
		{
			Config = config;
		}

		SColor CHudImageSkin::getColor(EGUI_DEFAULT_COLOR color) const
		{
			if ( color == EGDC_ACTIVE_CAPTION || color == EGDC_INACTIVE_CAPTION || color == EGDC_TOOLTIP )
			{
				return SColor(255,0,0,0);
			}
			return FallbackSkin->getColor(color);
		}

		void CHudImageSkin::setColor( EGUI_DEFAULT_COLOR which, SColor newColor )
		{
			FallbackSkin->setColor(which, newColor);
		}

		s32 CHudImageSkin::getSize(EGUI_DEFAULT_SIZE size) const
		{
			return FallbackSkin->getSize(size);
		}

		const wchar_t* CHudImageSkin::getDefaultText(EGUI_DEFAULT_TEXT text) const
		{
			return FallbackSkin->getDefaultText(text);
		}

		void CHudImageSkin::setDefaultText(EGUI_DEFAULT_TEXT which, const wchar_t* newText)
		{
			FallbackSkin->setDefaultText(which, newText);
		}


		void CHudImageSkin::setSize(EGUI_DEFAULT_SIZE which, s32 size)
		{
			FallbackSkin->setSize(which, size);
		}

		IGUIFont* CHudImageSkin::getFont(EGUI_DEFAULT_FONT defaultFont) const
		{
			return FallbackSkin->getFont(defaultFont);
		}

		void CHudImageSkin::setFont(IGUIFont* font, EGUI_DEFAULT_FONT defaultFont)
		{
			FallbackSkin->setFont(font, defaultFont);
		}

		IGUISpriteBank* CHudImageSkin::getSpriteBank() const
		{
			return FallbackSkin->getSpriteBank();
		}

		void CHudImageSkin::setSpriteBank( IGUISpriteBank* bank )
		{
			FallbackSkin->setSpriteBank(bank);
		}

		u32 CHudImageSkin::getIcon( EGUI_DEFAULT_ICON icon ) const
		{
			return FallbackSkin->getIcon(icon);
		}

		void CHudImageSkin::setIcon( EGUI_DEFAULT_ICON icon, u32 index )
		{
			FallbackSkin->setIcon(icon, index);
		}

		void CHudImageSkin::draw3DButtonPaneStandard( IGUIElement* element, const rect<s32>& rect, const core::rect<s32>* clip )
		{
			if ( !Config.Button.Texture )
			{
				FallbackSkin->draw3DButtonPaneStandard( element, rect, clip );
				return;
			}

			drawElementStyle( Config.Button, rect, clip );
		}

		void CHudImageSkin::draw3DButtonPanePressed( IGUIElement* element, const core::rect<s32>& rect, const core::rect<s32>* clip )
		{
			if ( !Config.Button.Texture )
			{
				FallbackSkin->draw3DButtonPanePressed( element, rect, clip );
				return;
			}

			drawElementStyle( Config.ButtonPressed, rect, clip );
		}

		void CHudImageSkin::draw3DSunkenPane(IGUIElement* element, SColor bgcolor, bool flat, bool fillBackGround, const core::rect<s32>& rect, const core::rect<s32>* clip)
		{
			if ( !Config.SunkenPane.Texture )
			{
				FallbackSkin->draw3DSunkenPane(element, bgcolor, flat, fillBackGround, rect, clip);
				return;
			}
			drawElementStyle( Config.SunkenPane, rect, clip );
		}

		core::rect<s32> CHudImageSkin::draw3DWindowBackground(IGUIElement* element, bool drawTitleBar, SColor titleBarColor, const core::rect<s32>& rect, const core::rect<s32>* clip)
		{
			if ( !Config.Window.Texture )
			{
				return FallbackSkin->draw3DWindowBackground(element, drawTitleBar, titleBarColor, rect, clip );
			}
			drawElementStyle( Config.Window, rect, clip );

			return core::rect<s32>( rect.UpperLeftCorner.X+Config.Window.DstBorder.Left, rect.UpperLeftCorner.Y, rect.LowerRightCorner.X-Config.Window.DstBorder.Right, rect.UpperLeftCorner.Y+Config.Window.DstBorder.Top );
		}

		void CHudImageSkin::draw3DMenuPane(IGUIElement* element, const core::rect<s32>& rect, const core::rect<s32>* clip)
		{
			FallbackSkin->draw3DMenuPane(element,rect,clip);
		}

		void CHudImageSkin::draw3DToolBar(IGUIElement* element, const core::rect<s32>& rect, const core::rect<s32>* clip)
		{
			FallbackSkin->draw3DToolBar(element,rect,clip);
		}

		void CHudImageSkin::draw3DTabButton(IGUIElement* element, bool active, const core::rect<s32>& rect, const core::rect<s32>* clip, gui::EGUI_ALIGNMENT alignment)
		{
			FallbackSkin->draw3DTabButton(element, active, rect, clip);
		}

		void CHudImageSkin::draw3DTabBody(IGUIElement* element, bool border, bool background, const core::rect<s32>& rect, const core::rect<s32>* clip, s32 tabHeight, gui::EGUI_ALIGNMENT alignment )
		{
			FallbackSkin->draw3DTabBody(element, border, background, rect, clip);
		}

		void CHudImageSkin::drawIcon(IGUIElement* element, EGUI_DEFAULT_ICON icon, const core::position2di position, u32 starttime, u32 currenttime, bool loop, const core::rect<s32>* clip)
		{
			FallbackSkin->drawIcon(element,icon,position,starttime,currenttime,loop,clip);
		}

		void CHudImageSkin::drawHorizontalProgressBar( IGUIElement* element, const core::rect<s32>& rectangle, const core::rect<s32>* clip, f32 filledRatio, SColor fillColor )
		{
			if ( !Config.ProgressBar.Texture || !Config.ProgressBarFilled.Texture )
			{
				return;
			}

			// Draw empty progress bar
			drawElementStyle( Config.ProgressBar, rectangle, clip );

			// Draw filled progress bar on top
			if ( filledRatio < 0.0f )
				filledRatio = 0.0f;
			else
				if ( filledRatio > 1.0f )
					filledRatio = 1.0f;

			if ( filledRatio > 0.0f )
			{
				s32 filledPixels = (s32)( filledRatio * rectangle.getSize().Width );
				s32 height = rectangle.getSize().Height;

				core::rect<s32> clipRect = clip? *clip:rectangle;
				if ( filledPixels < height )
				{
					if ( clipRect.LowerRightCorner.X > rectangle.UpperLeftCorner.X + filledPixels )
						clipRect.LowerRightCorner.X = rectangle.UpperLeftCorner.X + filledPixels;

					filledPixels = height;
				}

				core::rect<s32> filledRect = core::rect<s32>( 
					rectangle.UpperLeftCorner.X, 
					rectangle.UpperLeftCorner.Y, 
					rectangle.UpperLeftCorner.X + filledPixels, 
					rectangle.LowerRightCorner.Y );

				drawElementStyle( Config.ProgressBarFilled, filledRect, &clipRect, &fillColor );
			}
		}

		void CHudImageSkin::drawElementStyle( const SImageGUIElementStyle& elem, const core::rect<s32>& rect, const core::rect<s32>* clip, SColor* pcolor  )
		{
			core::rect<s32> srcRect;
			core::rect<s32> dstRect;
			core::dimension2di tsize = elem.Texture->getSize();
			ITexture* texture = elem.Texture;

			SColor color = elem.Color;
			
			if ( pcolor )
				color = *pcolor;

			SColor faceColor = getColor(EGDC_3D_FACE);
			color.setRed( (u8)(color.getRed() * faceColor.getRed() / 255) );
			color.setGreen( (u8)(color.getGreen() * faceColor.getGreen() / 255) );
			color.setBlue( (u8)(color.getBlue() * faceColor.getBlue() / 255) );
			color.setAlpha( (u8)(color.getAlpha() * faceColor.getAlpha() / 255 ) );

			SColor colors [4] = { color, color, color, color };

			core::dimension2di dstSize = rect.getSize();

			// Scale the border if there is insufficient room
			SImageGUIElementStyle::SBorder dst = elem.DstBorder;
			f32 scale = 1.0f;
			
			if ( dstSize.Width < dst.Left + dst.Right )
			{
				scale = dstSize.Width / (f32)( dst.Left + dst.Right );
			}

			if ( dstSize.Height < dst.Top + dst.Bottom )
			{
				f32 x = dstSize.Height / (f32)( dst.Top + dst.Bottom );
				
				if ( x < scale )
				{
					scale = x;
				}
			}

			if ( scale < 1.0f )
			{
				dst.Left = (s32)( dst.Left * scale );
				dst.Right = (s32)( dst.Right * scale );
				dst.Top = (s32)( dst.Top * scale );
				dst.Bottom = (s32)( dst.Bottom * scale );
			}

			const SImageGUIElementStyle::SBorder& src = elem.SrcBorder;

			// Draw the top left corner
			srcRect = core::rect<s32>( 0, 0, src.Left, src.Top );
			dstRect = core::rect<s32>( rect.UpperLeftCorner.X, rect.UpperLeftCorner.Y, rect.UpperLeftCorner.X+dst.Left, rect.UpperLeftCorner.Y+dst.Top );
			
			if ( !clip || clipRects( dstRect, srcRect, *clip ) )
				VideoDriver->draw2DImage( texture, dstRect, srcRect, clip, colors, true );

			// Draw the top right corner
			srcRect = core::rect<s32>( tsize.Width-src.Right, 0, tsize.Width, src.Top );
			dstRect = core::rect<s32>( rect.LowerRightCorner.X-dst.Right, rect.UpperLeftCorner.Y, rect.LowerRightCorner.X, rect.UpperLeftCorner.Y+dst.Top );
			
			if ( !clip || clipRects( dstRect, srcRect, *clip ) )
				VideoDriver->draw2DImage( texture, dstRect, srcRect, clip, colors, true );

			// Draw the top border
			srcRect = core::rect<s32>( src.Left, 0, tsize.Width-src.Right, src.Top );
			dstRect = core::rect<s32>( rect.UpperLeftCorner.X+dst.Left, rect.UpperLeftCorner.Y, rect.LowerRightCorner.X-dst.Right, rect.UpperLeftCorner.Y+dst.Top );
			
			if ( !clip || clipRects( dstRect, srcRect, *clip ) )
				VideoDriver->draw2DImage( texture, dstRect, srcRect, clip, colors, true );

			// Draw the left border
			srcRect = core::rect<s32>( 0, src.Top, src.Left, tsize.Height-src.Bottom );
			dstRect = core::rect<s32>( rect.UpperLeftCorner.X, rect.UpperLeftCorner.Y+dst.Top, rect.UpperLeftCorner.X+dst.Left, rect.LowerRightCorner.Y-dst.Bottom );
			
			if ( !clip || clipRects( dstRect, srcRect, *clip ) )
				VideoDriver->draw2DImage( texture, dstRect, srcRect, clip, colors, true );

			// Draw the right border
			srcRect = core::rect<s32>( tsize.Width-src.Right, src.Top, tsize.Width, tsize.Height-src.Bottom );
			dstRect = core::rect<s32>( rect.LowerRightCorner.X-dst.Right, rect.UpperLeftCorner.Y+dst.Top, rect.LowerRightCorner.X, rect.LowerRightCorner.Y-dst.Bottom );
			
			if ( !clip || clipRects( dstRect, srcRect, *clip ) )
				VideoDriver->draw2DImage( texture, dstRect, srcRect, clip, colors, true );

			// Draw the middle section
			srcRect = core::rect<s32>( src.Left, src.Top, tsize.Width-src.Right, tsize.Height-src.Bottom );
			dstRect = core::rect<s32>( rect.UpperLeftCorner.X+dst.Left, rect.UpperLeftCorner.Y+dst.Top, rect.LowerRightCorner.X-dst.Right, rect.LowerRightCorner.Y-dst.Bottom );
			
			if ( !clip || clipRects( dstRect, srcRect, *clip ) )
				VideoDriver->draw2DImage( texture, dstRect, srcRect, clip, colors, true );

			// Draw the bottom left corner
			srcRect = core::rect<s32>( 0, tsize.Height-src.Bottom, src.Left, tsize.Height );
			dstRect = core::rect<s32>( rect.UpperLeftCorner.X, rect.LowerRightCorner.Y-dst.Bottom, rect.UpperLeftCorner.X+dst.Left, rect.LowerRightCorner.Y );
			
			if ( !clip || clipRects( dstRect, srcRect, *clip ) )
				VideoDriver->draw2DImage( texture, dstRect, srcRect, clip, colors, true );

			// Draw the bottom right corner
			srcRect = core::rect<s32>( tsize.Width-src.Right, tsize.Height-src.Bottom, tsize.Width, tsize.Height );
			dstRect = core::rect<s32>( rect.LowerRightCorner.X-dst.Right, rect.LowerRightCorner.Y-dst.Bottom, rect.LowerRightCorner.X, rect.LowerRightCorner.Y );
			
			if ( !clip || clipRects( dstRect, srcRect, *clip ) )
				VideoDriver->draw2DImage( texture, dstRect, srcRect, clip, colors, true );

			// Draw the bottom border
			srcRect = core::rect<s32>( src.Left, tsize.Height-src.Bottom, tsize.Width-src.Right, tsize.Height );
			dstRect = core::rect<s32>( rect.UpperLeftCorner.X+dst.Left, rect.LowerRightCorner.Y-dst.Bottom, rect.LowerRightCorner.X-dst.Right, rect.LowerRightCorner.Y );
			
			if ( !clip || clipRects( dstRect, srcRect, *clip ) )
				VideoDriver->draw2DImage( texture, dstRect, srcRect, clip, colors, true );
		}

		void CHudImageSkin::draw2DRectangle(IGUIElement* element, const SColor &color, const core::rect<s32>& pos, const core::rect<s32>* clip)
		{
			FallbackSkin->draw2DRectangle(element, color, pos, clip);
		}
	}
}