#include "CGerEventos.h"

CGerEventos::CGerEventos()
{
	// Construtor

	for(u32 i = 0; i < NUMBER_OF_KEYS; i++)
		Keys[i] = BS_UP;

	for(u32 i = 0; i < NUMBER_OF_MOUSE_BUTTONS; i++)
		Mouse[i] = MBS_UP;

	MouseData.x = MouseData.y = MouseData.lx = MouseData.ly = MouseData.cx = MouseData.cy = 0;
	MouseData.wheelPos = MouseData.lwheelPos = 0;
	MouseDbClickData.cx = MouseDbClickData.cy = -1; // Fantini

	deltaMouseX = deltaMouseY = 0;

	frameCountLfDbClick = frameCountMdDbClick = frameCountRgDbClick = ENDFRAME_DOUBLECLICK;

	mouseHasMoved = false; 
	wheelHasMoved = false;

	mouseLeftDbClick = mouseRightDbClick = mouseMiddleDbClick = false;

	generalCallerID = menuItemSelectedID = 0;

	menu = NULL;

	elementStatus[EGET_SPINBOX_CHANGED] = 				
	elementStatus[EGET_ELEMENT_CLOSED] = 
	elementStatus[EGET_ELEMENT_FOCUS_LOST] = 
	elementStatus[EGET_ELEMENT_FOCUSED] = 
	elementStatus[EGET_ELEMENT_HOVERED] = 
	elementStatus[EGET_ELEMENT_LEFT] =		 
	elementStatus[EGET_BUTTON_CLICKED] = 
	elementStatus[EGET_SCROLL_BAR_CHANGED] = 
	elementStatus[EGET_CHECKBOX_CHANGED] =
	elementStatus[EGET_LISTBOX_CHANGED] = 
	elementStatus[EGET_LISTBOX_SELECTED_AGAIN] = 
	elementStatus[EGET_FILE_SELECTED] = 
	elementStatus[EGET_FILE_CHOOSE_DIALOG_CANCELLED] =
	elementStatus[EGET_MESSAGEBOX_YES] = 
	elementStatus[EGET_MESSAGEBOX_NO] = 
	elementStatus[EGET_MESSAGEBOX_OK] = 
	elementStatus[EGET_MESSAGEBOX_CANCEL] = 
	elementStatus[EGET_EDITBOX_ENTER] = 
	elementStatus[EGET_TAB_CHANGED] = 
	elementStatus[EGET_TABLE_CHANGED] = 
	elementStatus[EGET_TABLE_HEADER_CHANGED] = 
	elementStatus[EGET_TABLE_SELECTED_AGAIN] = 
	elementStatus[EGET_MENU_ITEM_SELECTED] = 
	elementStatus[EGET_COMBO_BOX_CHANGED] = NOK; // Setar o status de todos os eventos como falso		
}

CGerEventos::~CGerEventos()
{
	// Destrutor
} 

// M�todos de Interface:
bool CGerEventos::getEventCallerByElement(EGUI_EVENT_TYPE guiEventType)
{
	if(elementStatus[guiEventType] == OK)
		return true;
	return false;
}

int CGerEventos::getEventCallerOfMenuByID() 
{ 
	return menuItemSelectedID; 
}

int CGerEventos::getEventCallerByID() 
{ 
	return generalCallerID; 
}


// M�todos de Teclado:
bool CGerEventos::isKeyUp(EKEY_CODE key)
{
	if (Keys[key] == BS_UP)
		return true;
	return false;
}


bool CGerEventos::isKeyDown(EKEY_CODE key)
{
	if (Keys[key] == BS_DOWN)
		return true;
	return false;
}

bool CGerEventos::isKeyPressed(EKEY_CODE key)
{
	if(Keys[key] == BS_PRESSED)
		return true;
	return false;
}

bool CGerEventos::isKeyReleased(EKEY_CODE key)
{
	if(Keys[key] == BS_RELEASED)
		return true;
	return false;
}

// M�todos do Mouse:
bool CGerEventos::isMouseButtonUp(mouseButton mb)
{
	if (Mouse[mb] == MBS_UP)
		return true;
	return false;
}

bool CGerEventos::isMouseButtonDown(mouseButton mb)
{
	if (Mouse[mb] == MBS_DOWN)
		return true;
	return false;
}

bool CGerEventos::isMouseButtonPressed(mouseButton mb)
{
	if (Mouse[mb] == MBS_PRESSED)
		return true;
	return false;
}

bool CGerEventos::isMouseButtonDoubleClicked(mouseButton mb)
{
	switch (mb)
	{

	case MBLEFT:

		if(mouseLeftDbClick)
		{
			mouseLeftDbClick = false;
			MouseDbClickData.cx = MouseDbClickData.cy = -1;
			return true;
		}
		break;

	case MBMIDDLE:

		if(mouseMiddleDbClick)
		{
			mouseMiddleDbClick = false;
			MouseDbClickData.cx = MouseDbClickData.cy = -1;
			return true;
		}
		break;

	case MBRIGHT:

		if(mouseRightDbClick)
		{
			mouseRightDbClick = false;	
			MouseDbClickData.cx = MouseDbClickData.cy = -1;
			return true;
		}
		break;
	};

	return false;
}

bool CGerEventos::isMouseButtonReleased(mouseButton mb)
{
	if (Mouse[mb] == MBS_RELEASED)
		return true;
	return false;
}

bool CGerEventos::mouseMoved()
{
	if(mouseHasMoved)
	{
		mouseHasMoved = false;
		return true;
	}
	return false;
}

int CGerEventos::getDeltaMousePosX() 
{ 
	return deltaMouseX; 
}

int CGerEventos::getDeltaMousePosY() 
{ 
	return deltaMouseY; 
}

position2d<s32> CGerEventos::getMousePosition()
{
	return position2d<s32>(MouseData.x, MouseData.y); 
}

// M�todos do Ouvinte de eventos:
void CGerEventos::startEventProcess()
{
	// Iniciar escuta

	procesState = STARTED;

	for(int i = 0; i < KEY_KEY_CODES_COUNT; i++)
	{
		if(Keys[i] == BS_RELEASED)
			Keys[i] = BS_UP;

		if(Keys[i] == BS_PRESSED)
			Keys[i] = BS_DOWN;
	}

	for(int i = 0; i < NUMBER_OF_MOUSE_BUTTONS; i++)
	{
		if(Mouse[i] == MBS_RELEASED)
			Mouse[i] = MBS_UP;

		if(Mouse[i] == MBS_PRESSED)
			Mouse[i] = MBS_DOWN;
	}

	elementStatus[EGET_SPINBOX_CHANGED] =
	elementStatus[EGET_ELEMENT_CLOSED] = 
	elementStatus[EGET_ELEMENT_FOCUS_LOST] = 
	elementStatus[EGET_ELEMENT_FOCUSED] = 
	elementStatus[EGET_ELEMENT_HOVERED] = 
	elementStatus[EGET_ELEMENT_LEFT] =		 
	elementStatus[EGET_BUTTON_CLICKED] = 
	elementStatus[EGET_SCROLL_BAR_CHANGED] = 
	elementStatus[EGET_CHECKBOX_CHANGED] =
	elementStatus[EGET_LISTBOX_CHANGED] = 
	elementStatus[EGET_LISTBOX_SELECTED_AGAIN] = 
	elementStatus[EGET_FILE_SELECTED] = 
	elementStatus[EGET_FILE_CHOOSE_DIALOG_CANCELLED] =
	elementStatus[EGET_MESSAGEBOX_YES] = 
	elementStatus[EGET_MESSAGEBOX_NO] = 
	elementStatus[EGET_MESSAGEBOX_OK] = 
	elementStatus[EGET_MESSAGEBOX_CANCEL] = 
	elementStatus[EGET_EDITBOX_ENTER] = 
	elementStatus[EGET_TAB_CHANGED] = 
	elementStatus[EGET_TABLE_CHANGED] = 
	elementStatus[EGET_TABLE_HEADER_CHANGED] = 
	elementStatus[EGET_TABLE_SELECTED_AGAIN] = 
	elementStatus[EGET_MENU_ITEM_SELECTED] =
	elementStatus[EGET_MENU_ITEM_SELECTED] = 
	elementStatus[EGET_COMBO_BOX_CHANGED] = NOK; // Setar o status de todos os eventos como falso
}

bool CGerEventos::wheelMoved()
{
	if(wheelHasMoved)
	{
		wheelHasMoved = false;
		return true;
	}
	return false;
}

void CGerEventos::endEventProcess() 
{ 
	// Finalizar escuta
	procesState = ENDED; 

	// incrementa contador de frames para double click
	if(frameCountLfDbClick < ENDFRAME_DOUBLECLICK)
		frameCountLfDbClick++;

	//if(frameCountMdDbClick < ENDFRAME_DOUBLECLICK)
	//	frameCountMdDbClick++;

	//if(frameCountRgDbClick < ENDFRAME_DOUBLECLICK)
	//	frameCountRgDbClick++;
}

// M�todo de interpreta��o do evento disparado
bool CGerEventos::OnEvent(const SEvent& event)
{

	switch (event.EventType) 
	{

	// Eventos de Teclado:
	case EET_KEY_INPUT_EVENT: 
		{
			if(procesState == STARTED)
			{
				if(event.KeyInput.PressedDown)
				{
					if(Keys[event.KeyInput.Key] != BS_DOWN)
						Keys[event.KeyInput.Key] = BS_PRESSED;
					else
						Keys[event.KeyInput.Key] = BS_DOWN;
					break;
				}      
				else
				{
					if(Keys[event.KeyInput.Key] != BS_UP)   
						Keys[event.KeyInput.Key] = BS_RELEASED;
					else
						Keys[event.KeyInput.Key] = BS_UP;
					break;
				}
			}
		}
		break;

		
	// Eventos do Mouse:
	case EET_MOUSE_INPUT_EVENT: 
		{
			switch(event.MouseInput.Event)
			{
			case EMIE_MOUSE_MOVED: // Movimento do mouse
				{
					deltaMouseX = event.MouseInput.X - MouseData.lx;
					deltaMouseY = event.MouseInput.Y - MouseData.ly;

					MouseData.lx = MouseData.x;
					MouseData.ly = MouseData.y;

					MouseData.x = event.MouseInput.X;
					MouseData.y = event.MouseInput.Y;

					mouseHasMoved = true;

					break;
				}

			case EMIE_MOUSE_WHEEL: // Movimento do scroll
				{
					wheelHasMoved = true;
					MouseData.lwheelPos = MouseData.wheelPos;
					MouseData.wheelPos += event.MouseInput.Wheel;

					break;
				}

			case EMIE_LMOUSE_PRESSED_DOWN: // Bot�o esquerdo pressionado
				{
					if(Mouse[MBLEFT] == MBS_UP || Mouse[MBLEFT] == MBS_RELEASED)
					{
						if( MouseDbClickData.cx == event.MouseInput.X &&
							MouseDbClickData.cy == event.MouseInput.Y )
						{
							if(frameCountLfDbClick < ENDFRAME_DOUBLECLICK)
							{
								MouseDbClickData.cx = MouseDbClickData.cy = -1;
								mouseLeftDbClick = true;
							}
						}
						else
						{
							MouseDbClickData.cx = event.MouseInput.X;
							MouseDbClickData.cy = event.MouseInput.Y;
							mouseLeftDbClick = false;
						}

						frameCountLfDbClick = 0;
						Mouse[MBLEFT] = MBS_PRESSED;
					}
					else
					{
						Mouse[MBLEFT] = MBS_DOWN;
					}

					break;
				}

			case EMIE_LMOUSE_LEFT_UP: // Bot�o esquerdo liberado
				{
					if(Mouse[MBLEFT] != MBS_UP)
					{
						Mouse[MBLEFT] = MBS_RELEASED;
						MouseData.cx = event.MouseInput.X;
						MouseData.cy = event.MouseInput.Y;
					}

					break;
				}

			case EMIE_MMOUSE_PRESSED_DOWN: // Bot�o do meio pressionado
				{
					if(Mouse[MBMIDDLE] == MBS_UP || Mouse[MBMIDDLE] == MBS_RELEASED)
						Mouse[MBMIDDLE] = MBS_PRESSED;
					else
						Mouse[MBMIDDLE] = MBS_DOWN;

					break;
				}

			case EMIE_MMOUSE_LEFT_UP: // Bot�o do meio liberado
				{
					if (Mouse[MBMIDDLE] != MBS_UP)
					{
						Mouse[MBMIDDLE] = MBS_RELEASED;
						MouseData.cx = event.MouseInput.X;
						MouseData.cy = event.MouseInput.Y;
					}

					break;
				}

			case EMIE_RMOUSE_PRESSED_DOWN: // Bot�o direito pressionado
				{
					if (Mouse[MBRIGHT] == MBS_UP || Mouse[MBRIGHT] == MBS_RELEASED)
						Mouse[MBRIGHT] = MBS_PRESSED;
					else
						Mouse[MBRIGHT] = MBS_DOWN;

					break;
				}

			case EMIE_RMOUSE_LEFT_UP: // Bot�o direito liberado
				{
					if(Mouse[MBRIGHT] != MBS_UP)
					{
						Mouse[MBRIGHT] = MBS_RELEASED;
						MouseData.cx = event.MouseInput.X;
						MouseData.cy = event.MouseInput.Y;
					}

					break;
				}

			default:
				break;
			}
		}
		break;

	// Eventos de Interface:
	case EET_GUI_EVENT:
		{
			generalCallerID = event.GUIEvent.Caller->getID();

			switch(event.GUIEvent.EventType)
			{
			case EGET_SPINBOX_CHANGED:
			case EGET_ELEMENT_CLOSED:
			case EGET_ELEMENT_FOCUS_LOST:
			case EGET_ELEMENT_FOCUSED:
			case EGET_ELEMENT_HOVERED:
			case EGET_ELEMENT_LEFT:
			case EGET_BUTTON_CLICKED:
			case EGET_SCROLL_BAR_CHANGED:
			case EGET_CHECKBOX_CHANGED:
			case EGET_LISTBOX_CHANGED:
			case EGET_LISTBOX_SELECTED_AGAIN:
			case EGET_FILE_SELECTED:
			case EGET_FILE_CHOOSE_DIALOG_CANCELLED:
			case EGET_MESSAGEBOX_YES:
			case EGET_MESSAGEBOX_NO:
			case EGET_MESSAGEBOX_OK:
			case EGET_MESSAGEBOX_CANCEL:
			case EGET_EDITBOX_ENTER:
			case EGET_TAB_CHANGED:
			case EGET_TABLE_CHANGED: 
			case EGET_TABLE_HEADER_CHANGED: 
			case EGET_TABLE_SELECTED_AGAIN:
			case EGET_COMBO_BOX_CHANGED:

				elementStatus[event.GUIEvent.EventType] = OK; // atualiza status do evento disparado

				break;

			case EGET_MENU_ITEM_SELECTED:
				elementStatus[EGET_MENU_ITEM_SELECTED] = OK;
				menu = (IGUIContextMenu*)event.GUIEvent.Caller; 
				menuItemSelectedID = menu->getItemCommandId(menu->getSelectedItem());
				break;
			}
		}
	default:
		break;
	}	
	return false;
}
