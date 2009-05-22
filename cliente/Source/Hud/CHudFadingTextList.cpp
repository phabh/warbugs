#pragma once

#include "Setup.h"

class CHudFadingTextList 
{ 

public: 

	int m_nItems; 
	IGUIStaticText * *m_texts; 
   
	CHudFadingTextList(){}

   void start(IGUIEnvironment * gui, IGUIFont * font, rect<s32> const & totalSize, u8 initialAlpha = 255, u8 finalAlpha = 64, bool scrollDown = true) 
   { 
	   

      if(!gui || !font) 
         return; 

      s32 itemHeight = font->getDimension(L"A").Height; 
	  m_nItems = (int)(totalSize.LowerRightCorner.Y - totalSize.UpperLeftCorner.Y) / itemHeight; 
      

      m_texts = (IGUIStaticText * *)malloc(sizeof(IGUIStaticText *) * m_nItems); 

      f32 currentAlpha = (f32)initialAlpha; 
      f32 stepAlpha = (currentAlpha - finalAlpha) / (m_nItems - 1); 

      for(int item = 0; item < m_nItems; ++item) 
      { 
         m_texts[item] = gui->addStaticText(L"", totalSize); 
         m_texts[item]->setOverrideFont(font); 
         m_texts[item]->enableOverrideColor(true); 

            s32 topOfLine = 0; 

         if(scrollDown) 
            topOfLine = totalSize.UpperLeftCorner.Y + (itemHeight * item); 
         else 
            topOfLine = totalSize.LowerRightCorner.Y - (itemHeight * (item + 1)); 

         m_texts[item]->setRelativePosition(rect<s32>(totalSize.UpperLeftCorner.X, 
                                          topOfLine, 
                                          totalSize.LowerRightCorner.X, 
                                          topOfLine + itemHeight)); 

         m_texts[item]->setOverrideColor(SColor((s8)currentAlpha, 255, 255, 255)); 
         currentAlpha -= stepAlpha; 
      } 
   } 

   virtual ~CHudFadingTextList() 
   { 
      free(m_texts); 
      m_texts = 0; 
   } 

   void addText(wchar_t const * text, SColor const & colour = SColor(255, 255, 255, 255)) 
   { 
 
      for(int item = m_nItems - 1; item > 0; --item) 
      { 
         m_texts[item]->setText(m_texts[item - 1]->getText()); 
         SColor movedColour(m_texts[item - 1]->getOverrideColor()); 
         movedColour.setAlpha(m_texts[item ]->getOverrideColor().getAlpha()); 
         m_texts[item]->setOverrideColor(movedColour); 
      } 

      SColor newColour(colour); 
      newColour.setAlpha(m_texts[0]->getOverrideColor().getAlpha()); 
      m_texts[0]->setOverrideColor(newColour); 
      m_texts[0]->setText(text); 

   } 
}; 
