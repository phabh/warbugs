#include <irrlicht.h>
#include "CGUITexturedSkin.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#pragma comment(lib, "Irrlicht.lib")


IrrlichtDevice *device = 0;
s32 cnt = 0;
IGUIListBox* listbox = 0;


/*
The Event Receiver is not only capable of getting keyboard and
mouse input events, but also events of the graphical user interface 
(gui). There are events for almost everything: Button click, 
Listbox selection change, events that say that a element was hovered
and so on. To be able to react to some of these events, we create 
an event receiver. 
We only react to gui events, and if it's such an event, we get the
id of the caller (the gui element which caused the event) and get 
the pointer to the gui environment.
*/
class MyEventReceiver : public IEventReceiver
{
public:
	virtual bool OnEvent(const SEvent& event)
	{
		if (event.EventType == EET_GUI_EVENT)
		{
			s32 id = event.GUIEvent.Caller->getID();
			IGUIEnvironment* env = device->getGUIEnvironment();

			switch(event.GUIEvent.EventType)
			{

	
			case EGET_SCROLL_BAR_CHANGED:
				if (id == 104)
				{
					s32 pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
					
					for (s32 i=0; i<EGDC_COUNT ; ++i)
					{
						SColor col = env->getSkin()->getColor((EGUI_DEFAULT_COLOR)i);
						col.setAlpha(pos);
						env->getSkin()->setColor((EGUI_DEFAULT_COLOR)i, col);
					}
					
				}
				break;


			case EGET_BUTTON_CLICKED:

				if (id == 101)
				{
					device->closeDevice();
					return true;
				}

				if (id == 102)
				{
					listbox->addItem(L"Window created");
					cnt += 30;
					if (cnt > 200) 
						cnt = 0;

					IGUIWindow* window = env->addWindow(
						rect<s32>(100 + cnt, 100 + cnt, 300 + cnt, 200 + cnt), 
						false, // modal?
						L"Test window");

					env->addStaticText(L"Please close me",  
						rect<s32>(35,35,140,50),
						true, // border?
						false, // wordwrap?
						window);

					return true;
				}

				if (id == 103)
				{
					listbox->addItem(L"File open");
					env->addFileOpenDialog(L"Please choose a file.");
					return true;
				}

				break;
			}
		}
		else if (event.EventType == EET_MOUSE_INPUT_EVENT &&
		         event.MouseInput.Event==EMIE_RMOUSE_LEFT_UP)
		{
			IGUIEnvironment* env = device->getGUIEnvironment();
		    IGUIContextMenu * pMenu = env->addContextMenu(rect<s32>
		        (event.MouseInput.X,event.MouseInput.Y,event.MouseInput.X+40,event.MouseInput.Y+40));
		    pMenu->addItem(L"Eins");
		    pMenu->addSeparator();
			pMenu->addItem(L"Zwei");
			pMenu->addItem(L"Drei");
			pMenu->addItem(L"Vier");
			pMenu->addItem(L"Funf");
		}

		return false;
	}
};


/*
Ok, now for the more interesting part. First, create the 
Irrlicht device. As in some examples before, we ask the user which
driver he wants to use for this example:
*/
int main()
{
	device = createDevice(video::EDT_OPENGL, core::dimension2d<s32>(640, 480));

	if (device == 0)
		return 1; // could not create selected driver.

	/* The creation was successful, now we set the event receiver and
		store pointers to the driver and to the gui environment. */

	MyEventReceiver receiver;
	device->setEventReceiver(&receiver);
	device->setWindowCaption(L"Irrlicht Engine - User Interface Demo");

	video::IVideoDriver* driver = device->getVideoDriver();
	IGUIEnvironment* env = device->getGUIEnvironment();

	/*
	We add three buttons. The first one closes the engine. The second
	creates a window and the third opens a file open dialog. The third
	parameter is the id of the button, with which we can easily identify
	the button in the event receiver.
	*/	

	env->addButton(rect<s32>(10,210,100,240), 0, 101, L"Quit");
	env->addButton(rect<s32>(10,250,100,290), 0, 102, L"New Window");
	env->addButton(rect<s32>(10,300,100,340), 0, 103, L"File Open");

	/*
	To make the font a little bit nicer, we load an external font
	and set it as new font in the skin. An at last, we create a 
	nice Irrlicht Engine logo in the top left corner.
	*/
	IGUISkin* skin = env->getSkin();
	CGUITexturedSkin * pNewSkin = new CGUITexturedSkin(env, device->getFileSystem());
	pNewSkin->setSkin( "guiskin.xml" );
	env->setSkin(pNewSkin);
	pNewSkin->drop();
	IGUIFont* font = env->getFont("fonthaettenschweiler.bmp");
	if (font)
		pNewSkin->setFont(font, EGDF_DEFAULT);
/*
	IGUIImage* img = env->addImage(
		driver->getTexture("irrlichtlogoalpha2.tga"),
		position2d<int>(500,350));*/

	// create menu
	gui::IGUIContextMenu* menu = env->addMenu();
	menu->addItem(L"File", -1, true, true);
	menu->addItem(L"View", -1, true, true);
	menu->addItem(L"Help", -1, true, true);

	gui::IGUIContextMenu* submenu;
	submenu = menu->getSubMenu(0);
	submenu->addItem(L"Open Model File...", 100);
	submenu->addSeparator();
	submenu->addItem(L"Quit", 200);

	submenu = menu->getSubMenu(1);
	submenu->addItem(L"toggle sky box visibility", 300);
	submenu->addItem(L"toggle model debug information", 400);
	submenu->addItem(L"model material", -1, true, true );

	submenu = submenu->getSubMenu(2);
	submenu->addItem(L"Solid", 610);
	submenu->addItem(L"Transparent", 620);
	submenu->addItem(L"Reflection", 630);

	submenu = menu->getSubMenu(2);
	submenu->addItem(L"About", 500);

	/*
	Now, we add a static text and a scrollbar, which modifies the
	transparency of all gui elements. We set the maximum value of
	the scrollbar to 255, because that's the maximal value for 
	a color value.
	Then we create an other static text and a list box.
	*/
	env->addStaticText(L"Transparent Control:", rect<s32>(350,120,550,140), true);
	IGUIScrollBar* scrollbar = env->addScrollBar(true, rect<s32>(350, 145, 550, 160), 0, 104);
	scrollbar->setMax(255);

	// set scrollbar position to alpha value of an arbitrary element
	scrollbar->setPos(env->getSkin()->getColor((EGUI_DEFAULT_COLOR)0).getAlpha());

	env->addStaticText(L"Logging ListBox:", rect<s32>(50,80,250,100), true);
	listbox = env->addListBox(rect<s32>(50, 110, 250, 180));
	env->addEditBox(L"Editable Text", rect<s32>(350, 80, 550, 100));

	env->addCheckBox( true, rect<s32>(10,360,30,380));
	env->addStaticText(L"Check Box", rect<s32>(35,360,100,380), false, false);
	IGUIComboBox * pCombo = env->addComboBox( rect<s32>(10,400,100,420));
	pCombo->addItem(L"Some");
	pCombo->addItem(L"Combo");
	pCombo->addItem(L"Text");

	IGUIToolBar * bar = env->addToolBar();
	video::ITexture* image = driver->getTexture("open.bmp");
	driver->makeColorKeyTexture(image, core::position2d<s32>(0,0));
	bar->addButton(1102, 0, 0, image, 0, false, true);
	image = driver->getTexture("help.bmp");
	driver->makeColorKeyTexture(image, core::position2d<s32>(0,0));
	bar->addButton(1103, 0, 0, image, 0, false, true);
	image = driver->getTexture("tools.bmp");
	driver->makeColorKeyTexture(image, core::position2d<s32>(0,0));
	bar->addButton(1104, 0, 0, image, 0, false, true);

	//env->addColorSelectDialog(L"color",false);
	//env->addFileOpenDialog(L"file",false);
	//env->addMessageBox(L"MB",L"MB",false);
	//env->addMeshViewer(rect<s32>(150,300,200,350));
	//env->addTab(rect<s32>(150,350,200,400));

	IGUITabControl * pTC = env->addTabControl(rect<s32>(150,300,300,450));
	pTC->addTab(L"1"); pTC->addTab(L"2"); pTC->addTab(L"3");

	//That's all, we only have to draw everything.
	while(device->run() && driver && device->isWindowActive())
	{
		driver->beginScene(true, true, SColor(0,200,200,200));
		env->drawAll();
		driver->endScene();
	}

	device->drop();
	return 0;
}
