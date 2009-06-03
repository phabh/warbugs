#pragma once

#include <IGUIElement.h>
#include <SColor.h>

namespace irr
{
	namespace gui
	{

		using namespace core;
		using namespace video;

		class CHudProgressBar : public IGUIElement
		{

		public:

			CHudProgressBar( IGUIElement* parent, IGUIEnvironment* environment, const rect<s32>& rectangle, s32 id=-1 );

			//! Atualizar automaticamente o texto da barra de progresso.
			//! Enviando NULL ou uma string vazia como parâmetro format, desabilita o texto automático.
			void setAutomaticText( const wchar_t* format );
			void setFillColor( SColor fill );
			SColor getFillColor() const;
			void setProgress( f32 progress );
			f32 getProgress() const;
			virtual void draw();

		private:

			SColor FillColor;
			f32 FilledRatio;
			stringw AutomaticTextFormat;
		};
	}
}