#pragma once

#include <IGUISkin.h>
#include <irrString.h>

using namespace irr;
using namespace io;
using namespace gui;
using namespace core;
using namespace video;

namespace irr
{
	namespace video
	{
		class IVideoDriver;
		class ITexture;
	}

	namespace gui
	{
		struct SImageGUIElementStyle
		{
			struct SBorder
			{
				s32 Top, Left, Bottom, Right;
				SBorder() : Top(0), Left(0), Bottom(0), Right(0) {}
			};

			SBorder SrcBorder;
			SBorder DstBorder;
			ITexture* Texture;
			SColor Color;

			SImageGUIElementStyle() : Texture(0), Color(255,255,255,255) {}
		};

		struct SImageGUISkinConfig
		{
			SImageGUIElementStyle SunkenPane, Window, Button, ButtonPressed, ProgressBar, ProgressBarFilled, CheckBox;
		};

		class CHudImageSkin : public IGUISkin
		{

		public:

			CHudImageSkin( IVideoDriver* videoDriver, IGUISkin* fallbackSkin );

			virtual ~CHudImageSkin();

			void loadConfig( const SImageGUISkinConfig& config );
			virtual void drawHorizontalProgressBar( IGUIElement* element, const core::rect<s32>& rectangle, const core::rect<s32>* clip, f32 filledRatio, SColor fillColor );
			virtual SColor getColor(EGUI_DEFAULT_COLOR color) const;
			virtual void setColor(EGUI_DEFAULT_COLOR which, SColor newColor);
			virtual s32 getSize(EGUI_DEFAULT_SIZE size) const;
			virtual const wchar_t* getDefaultText(EGUI_DEFAULT_TEXT text) const;
			virtual void setDefaultText(EGUI_DEFAULT_TEXT which, const wchar_t* newText);
			virtual void setSize(EGUI_DEFAULT_SIZE which, s32 size);
			virtual IGUIFont* getFont(EGUI_DEFAULT_FONT which=EGDF_DEFAULT) const;
			virtual void setFont(IGUIFont* font, EGUI_DEFAULT_FONT which=EGDF_DEFAULT);
			virtual IGUISpriteBank* getSpriteBank() const;
			virtual void setSpriteBank(IGUISpriteBank* bank);
			virtual u32 getIcon(EGUI_DEFAULT_ICON icon) const;
			virtual void setIcon(EGUI_DEFAULT_ICON icon, u32 index);
			virtual void draw3DButtonPaneStandard(IGUIElement* element, const core::rect<s32>& rect, const core::rect<s32>* clip=0);
			virtual void draw3DButtonPanePressed(IGUIElement* element, const core::rect<s32>& rect, const core::rect<s32>* clip=0);
			virtual void draw3DSunkenPane(IGUIElement* element, SColor bgcolor, bool flat, bool fillBackGround, const core::rect<s32>& rect, const core::rect<s32>* clip=0);
			virtual core::rect<s32> draw3DWindowBackground(IGUIElement* element, bool drawTitleBar, SColor titleBarColor, const core::rect<s32>& rect, const core::rect<s32>* clip=0);
			virtual void draw3DMenuPane(IGUIElement* element, const core::rect<s32>& rect, const core::rect<s32>* clip=0);
			virtual void draw3DToolBar(IGUIElement* element, const core::rect<s32>& rect, const core::rect<s32>* clip=0);
			virtual void draw3DTabButton(IGUIElement* element, bool active, const core::rect<s32>& rect, const core::rect<s32>* clip=0, gui::EGUI_ALIGNMENT alignment=EGUIA_UPPERLEFT);
			virtual void draw3DTabBody(IGUIElement* element, bool border, bool background, const core::rect<s32>& rect, const core::rect<s32>* clip=0, s32 tabHeight=-1, gui::EGUI_ALIGNMENT alignment=EGUIA_UPPERLEFT );
			virtual void drawIcon(IGUIElement* element, EGUI_DEFAULT_ICON icon, const core::position2di position, u32 starttime=0, u32 currenttime=0, bool loop=false, const core::rect<s32>* clip=0);
			virtual void draw2DRectangle(IGUIElement* element, const SColor &color, const core::rect<s32>& pos, const core::rect<s32>* clip = 0);
			virtual EGUI_SKIN_TYPE getType() const { return EGST_UNKNOWN; }

		private:

			void drawElementStyle( const SImageGUIElementStyle& elem, const core::rect<s32>& rect, const core::rect<s32>* clip, SColor* color=0 );
			IVideoDriver* VideoDriver;
			IGUISkin* FallbackSkin;
			SImageGUISkinConfig Config;
		};
	}
}