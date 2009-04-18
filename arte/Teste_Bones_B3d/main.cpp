#include "irrlicht.h" 

using namespace irr; 
using namespace core; 
using namespace scene; 
using namespace video; 
using namespace io; 
using namespace gui; 

IrrlichtDevice *device; 
IAnimatedMeshSceneNode *modelo; 

#pragma comment (lib,"irrlicht.lib") 

class MyEventReceiver : public IEventReceiver 
{ 

public: 

	bool OnEvent(const SEvent& event) 
	{ 
	   if (event.EventType == EET_KEY_INPUT_EVENT) 
	   { 
		  vector3df currot; 
		  switch(event.KeyInput.Key) 
		  { 
		  case KEY_KEY_A: 
			 currot = modelo->getRotation(); 
			 currot.Y-=5; 
			 modelo->setRotation(currot); 
			 break; 

		 case KEY_KEY_W: 
			 currot = modelo->getPosition(); 
			 currot.X-=10; 
			 modelo->setPosition(currot); 
			 break; 

		 case KEY_KEY_S: 
			 currot = modelo->getPosition(); 
			 currot.X+=10; 
			 modelo->setPosition(currot); 
			 break; 

		  case KEY_KEY_D: 
			 currot = modelo->getRotation(); 
			 currot.Y+=5; 
			 modelo->setRotation(currot); 
			 break; 

		  case KEY_ESCAPE: 
			 device->closeDevice(); 
			 break; 
		  } 
	   } 
	   return false; 
	} 
}; 

int main(int argc, char* argv[]) 
{ 
   IVideoDriver* driver; 
   ISceneManager* smgr; 
   IGUIEnvironment* guienv; 
   ICameraSceneNode *cam; 
   u32 lasttick; 
   int lastFPS = -1; 

   MyEventReceiver event; 

   device = createDevice(EDT_DIRECT3D9, dimension2d<s32>(640, 480), 16, false, true, false,&event); 

   driver = device->getVideoDriver(); 
   smgr = device->getSceneManager(); 

   cam = smgr->addCameraSceneNodeFPS(); 
   cam->setPosition(vector3df(0, 50, 0)); 

   lasttick = 0; 

   IAnimatedMeshSceneNode *head,*lhand; 
   IBoneSceneNode *jHead, *jlHand; 
  
   modelo = smgr->addAnimatedMeshSceneNode(smgr->getMesh("besouro2.b3d")); 
   modelo->setMaterialFlag(EMF_LIGHTING, false);
   modelo->setMaterialTexture(0, driver->getTexture("besouro1.jpg"));

   head = smgr->addAnimatedMeshSceneNode(smgr->getMesh("capacete.b3d"));
   head->setMaterialFlag(EMF_LIGHTING, false);
   head->setMaterialTexture(0, driver->getTexture("hercules.jpg"));

   lhand = smgr->addAnimatedMeshSceneNode(smgr->getMesh("martelo.b3d"));
   lhand->setMaterialFlag(EMF_LIGHTING, false);
   lhand->setMaterialTexture(0, driver->getTexture("martelo.jpg"));

   jHead = modelo->getJointNode("visao"); 
   jlHand = modelo->getJointNode("mao_L"); 

   jHead->addChild(head); 
   jlHand->addChild(lhand); 

   modelo->setAnimationSpeed(30); // 30 fps

   while (device->run()) 
   { 
      driver->beginScene(true, true, SColor(0,220,220,255)); 

      smgr->drawAll(); 

      driver->endScene(); 

      int fps = driver->getFPS(); 
      if (lastFPS != fps) 
      { 
         wchar_t tmp[1024]; 
         swprintf(tmp, 1024, L"Juntas b3d [fps:%d] [triangulos:%d]", 
            fps, driver->getPrimitiveCountDrawn()); 
         device->setWindowCaption(tmp); 
         lastFPS = fps; 
      } 
   } 

   device->drop(); 
   return 0; 
}