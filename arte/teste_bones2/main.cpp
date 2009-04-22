#include "irrlicht.h" 

using namespace irr; 
using namespace core; 
using namespace scene; 
using namespace video; 
using namespace io; 
using namespace gui; 

IrrlichtDevice *device; 
IAnimatedMeshSceneNode *modelo; 
IAnimatedMeshSceneNode *modelo1; 
IAnimatedMeshSceneNode *modelo2; 

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
   cam->setPosition(vector3df(0, 0, -50)); 

   lasttick = 0; 

   IAnimatedMeshSceneNode *head,*lhand, *head1; 
   IBoneSceneNode *jHead, *jlHand, *jHead1; 
  
   // Besouro 
   modelo = smgr->addAnimatedMeshSceneNode(smgr->getMesh("besouro6.b3d")); 
   modelo->setMaterialFlag(EMF_LIGHTING, false);
   modelo->setMaterialTexture(0, driver->getTexture("besouro1.jpg"));
   modelo->setPosition(vector3df(0.f,0.f,0.f));

   head = smgr->addAnimatedMeshSceneNode(smgr->getMesh("capacete2.b3d"));
   //head->setRotation(vector3df(90.f,180.f,0.f));
  // head->setPosition(vector3df(0.f,-0.5f,0.f));
   head->setMaterialFlag(EMF_LIGHTING, false);
   head->setMaterialTexture(0, driver->getTexture("hercules.jpg"));

  lhand = smgr->addAnimatedMeshSceneNode(smgr->getMesh("martelo4.b3d"));
   lhand->setMaterialFlag(EMF_LIGHTING, false);
   lhand->setMaterialTexture(0, driver->getTexture("martelo.jpg"));
  // lhand->setPosition(vector3df(1.5f,-2.2f,-1.f));
   lhand->setRotation(vector3df(90.f,-90.f,0.f));

 // Louva-Deus
   modelo1 = smgr->addAnimatedMeshSceneNode(smgr->getMesh("louva.b3d")); 
   modelo1->setMaterialFlag(EMF_LIGHTING, false);
   modelo1->setMaterialTexture(0, driver->getTexture("louva.jpg"));
   modelo1->setPosition(vector3df(10.f,0.f,0.f));

   head1 = smgr->addAnimatedMeshSceneNode(smgr->getMesh("chapeu.b3d"));
   head1->setRotation(vector3df(-110.f,0.f,0.f));
   head1->setPosition(vector3df(0.f,-1.f,0.5f));
   head1->setMaterialFlag(EMF_LIGHTING, false);
   //head1->setMaterialTexture(0, driver->getTexture("hercules.jpg"));

   // joints besouro
   jHead = modelo->getJointNode("visao"); 
   jlHand = modelo->getJointNode("mao_L"); 
   
   // joints louva
   jHead1 = modelo1->getJointNode("visao");

   // parents Besouro
   jHead->addChild(head); 
   jlHand->addChild(lhand); 

 //   parents Louva
   jHead1->addChild(head1); 

   // lagarto
  
   modelo2 = smgr->addAnimatedMeshSceneNode(smgr->getMesh("lagarto.b3d")); 
   modelo2->setMaterialFlag(EMF_LIGHTING, false);
   modelo2->setMaterialTexture(0, driver->getTexture("lagarto1.jpg"));
   modelo2->setPosition(vector3df(-10.f,10.f,0.f));

   modelo->setAnimationSpeed(30); // 30 fps
   modelo1->setAnimationSpeed(30);
   modelo2->setAnimationSpeed(30);

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