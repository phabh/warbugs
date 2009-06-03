#include "CHudProgressBar.h"
#include <IGUIEnvironment.h>
#include "CHudImageSkin.h"
#include <IGUIFont.h>

namespace irr
{
	namespace gui
	{

		CHudProgressBar::CHudProgressBar( IGUIElement* parent, IGUIEnvironment* environment, const core::rect<s32>& rectangle, s32 id )
			: IGUIElement( EGUIET_ELEMENT, environment, parent, id, rectangle )
		{
			FilledRatio = 0.0f;
			FillColor = video::SColor(255,255,0,0);
			AutomaticTextFormat = L"%0.0f %%"; // 0.1 = decimal
		}

		void CHudProgressBar::setAutomaticText( const wchar_t* text )
		{
			AutomaticTextFormat = text? text:L"";
			if ( AutomaticTextFormat != L"" )
			{
				wchar_t* buffer = new wchar_t[ AutomaticTextFormat.size() + 10 ];
				swprintf( buffer, AutomaticTextFormat.size() + 10, AutomaticTextFormat.c_str(), 100*FilledRatio );
				Text = buffer;
				delete buffer;
			}
		}

		void CHudProgressBar::setFillColor( video::SColor fill )
		{
			FillColor = fill;
		}

		video::SColor CHudProgressBar::getFillColor() const
		{
			return FillColor;
		}

		void CHudProgressBar::setProgress( f32 progress )
		{
			FilledRatio = progress;
			if ( AutomaticTextFormat != L"" )
			{
				wchar_t* buffer = new wchar_t[ AutomaticTextFormat.size() + 10 ];
				swprintf( buffer, AutomaticTextFormat.size() + 10, AutomaticTextFormat.c_str(), 100*FilledRatio );
				Text = buffer;
				delete buffer;
			}
		}

		f32 CHudProgressBar::getProgress() const
		{
			return FilledRatio;
		}

		void CHudProgressBar::draw()
		{
			CHudImageSkin* skin = static_cast<CHudImageSkin*>( Environment->getSkin() );

			skin->drawHorizontalProgressBar( this, AbsoluteRect, &AbsoluteClippingRect, FilledRatio, FillColor );

			// Draw text in center
			skin->getFont(EGDF_DEFAULT)->draw( Text.c_str(), AbsoluteRect, skin->getColor(EGDC_BUTTON_TEXT), true, true, &AbsoluteClippingRect );
		}

	}
}