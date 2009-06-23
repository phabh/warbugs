#pragma once

/*
* Classe CGerEventos
*
* Autor: Eduardo Fantini
*
* Objetivo: Encapsular os eventos de GUI da Irrlicht 1.5
*
* Ultima alteração: 26/02/2009
*
*/

#include "irrlicht.h"

using namespace irr;
using namespace core;
using namespace gui;
using namespace io;
using namespace std;

#define NUMBER_OF_KEYS KEY_KEY_CODES_COUNT
#define NUMBER_OF_MOUSE_BUTTONS 3
#define NUMBER_OF_GUI_ELEMENTS 24

const int ENDFRAME_DOUBLECLICK = 10; // Intervalo máximo de frames para capturar um double-click

enum buttonState
{
	BS_UP,
	BS_DOWN,
	BS_PRESSED,
	BS_RELEASED
};

enum mouseButton
{
	MBLEFT,
	MBMIDDLE,
	MBRIGHT
};

enum mouseButtonState
{
	MBS_UP,
	MBS_DOWN,
	MBS_PRESSED,
	MBS_RELEASED,
};

struct mouseInformation 
{
	s32 x, y, lx, ly, cx, cy;
	f32 wheelPos, lwheelPos;
};

struct mouseDoubleClick  
{ 
	s32 cx, cy; 
};

// Enumeration de estados para os eventos de interface
enum ElementStatus 
{ 
	OK, 
	NOK
};

// Enumeration de estados do ouvinte de eventos
enum ProcessEventState 
{ 
	STARTED, 
	ENDED 
};


class CGerEventos : public IEventReceiver
{
	public:

		CGerEventos();
		~CGerEventos();
		
		// Métodos de Interface:
		bool getEventCallerByElement(EGUI_EVENT_TYPE guiEventType);
		int getEventCallerOfMenuByID();
		int getEventCallerByID();

		// Métodos de Teclado:
		bool isKeyUp(EKEY_CODE key);
		bool isKeyDown(EKEY_CODE key);
		bool isKeyPressed(EKEY_CODE key);
		bool isKeyReleased(EKEY_CODE key);
    
		// Métodos do Mouse:
		bool isMouseButtonUp(mouseButton mb);
		bool isMouseButtonDown(mouseButton mb);
		bool isMouseButtonPressed(mouseButton mb);
		bool isMouseButtonReleased(mouseButton mb);
		bool isMouseButtonDoubleClicked(mouseButton mb);
		bool mouseMoved();
		int getDeltaMousePosX();
		int getDeltaMousePosY();
		position2d<s32> getMousePosition();

		inline int getMouseX() { return MouseData.x; }
		inline int getMouseY() { return MouseData.y; }
		inline int getLastMouseX() { return MouseData.lx; }
		inline int getLastMouseY() { return MouseData.ly; }
		inline u32 getClickedMouseX() { return MouseData.cx; }
		inline u32 getClickedMouseY() { return MouseData.cy; }
		inline f32 getMouseWheelPosition() { return MouseData.wheelPos; }
		inline f32 getLastMouseWheelPosition() { return MouseData.lwheelPos; }
		
		inline f32 getDeltaMouseWheelPosition()
		{
		   f32 a = MouseData.wheelPos - MouseData.lwheelPos;
		   return a;
		}

		inline s32 getDeltaMouseX()
		{
		   s32 a = MouseData.x - MouseData.lx;
		   return (s32)(a < 0 ? -a : a);
		}

		inline s32 getDeltaMouseY()
		{
		   s32 a = MouseData.y - MouseData.ly;
		   return (s32)(a < 0 ? -a : a);
		}

		// Métodos do Ouvinte de eventos:	
		void startEventProcess();
		bool wheelMoved();
		void endEventProcess();		
		
		// Método de interpretação do evento disparado
		bool OnEvent(const SEvent& event);

	protected:

		buttonState Keys[NUMBER_OF_KEYS];
		mouseButtonState Mouse[NUMBER_OF_MOUSE_BUTTONS];
		ElementStatus elementStatus[NUMBER_OF_GUI_ELEMENTS];
		mouseInformation MouseData;
		ProcessEventState procesState;

		mouseDoubleClick MouseDbClickData;
	    
		IGUIContextMenu* menu;
		s32 menuItemSelectedID;
		s32 generalCallerID;

		int deltaMouseX;
		int deltaMouseY;
	    
		bool mouseHasMoved;
		bool wheelHasMoved;

		bool mouseLeftDbClick;
		bool mouseRightDbClick;
		bool mouseMiddleDbClick;

		int frameCountLfDbClick;
		int frameCountMdDbClick;
		int frameCountRgDbClick;
};
