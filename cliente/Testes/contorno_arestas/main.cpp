
#include "CToonShader.h"

#pragma comment (lib,"irrlicht.lib") 

using namespace irr; 
using namespace core; 
using namespace scene; 
using namespace video; 
using namespace io; 
using namespace gui; 

IrrlichtDevice *device; 
IAnimatedMeshSceneNode *modelo; 
IAnimatedMeshSceneNode *modelo1; 
IAnimatedMeshSceneNode *modelos[100]; /*
									  IAnimatedMeshSceneNode *modelo3; 
									  IAnimatedMeshSceneNode *modelo4; 
									  IAnimatedMeshSceneNode *modelo5; */
ILightSceneNode *_luz;
CToonShader *_toonShader; 

SMaterial mblack;
	


void addContorno(ISceneNode* oNode, f32 fThickness = 3, SColor cColor = SColor(255,0,0,0))
{
	if(!oNode) 
		return;

	SMaterial tmat[MATERIAL_MAX_TEXTURES],
		lmat;

	lmat.DiffuseColor = lmat.SpecularColor = lmat.AmbientColor = lmat.EmissiveColor = cColor;
	lmat.Lighting = true;
	lmat.Wireframe = true;
	lmat.Thickness = fThickness;
	lmat.FrontfaceCulling = true;
	lmat.BackfaceCulling = false;

	for(u32 i=0; i<oNode->getMaterialCount(); i++)
	{
		tmat[i] = oNode->getMaterial(i);
		oNode->getMaterial(i) = lmat;
	}

	oNode->render();

	for(u32 i=0; i<oNode->getMaterialCount(); i++)
		oNode->getMaterial(i) = tmat[i];
}

void MapearMundo(ISceneNode* node) 
{ 
  if (node->getType() == ESNT_MESH || node->getType() == ESNT_ANIMATED_MESH )
  {

	  if( node->getAutomaticCulling() != EAC_OFF)
			addContorno(node);

  }  
  list<ISceneNode*>::ConstIterator begin = node->getChildren().begin(); 
  list<ISceneNode*>::ConstIterator end   = node->getChildren().end(); 

  for (; begin != end; ++begin) 
    MapearMundo(*begin); 
} 

void trocaMat( ISceneNode* oNode, f32 fThickness)
{
	SMaterial guarda[MATERIAL_MAX_TEXTURES];

	for(u32 i=0; i<oNode->getMaterialCount(); i++)
	{
		guarda[i] = oNode->getMaterial(i);
		oNode->getMaterial(i) = mblack;
	}

	oNode->render();

	for(u32 i=0; i<oNode->getMaterialCount(); i++)
		oNode->getMaterial(i) = guarda[i];
}



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

	device = createDevice(::EDT_OPENGL/*::EDT_DIRECT3D9*/, dimension2d<s32>(640, 480), 16, false, true, false,&event); 

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
	head1->setMaterialTexture(0, driver->getTexture("hercules.jpg"));

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

	for(int i=0; i<100; i++)
	{

		//modelos[i] = smgr->addAnimatedMeshSceneNode(smgr->getMesh("lagarto.b3d")); 
		//modelos[i]->setMaterialFlag(EMF_LIGHTING, false);
		//modelos[i]->setMaterialTexture(0, driver->getTexture("lagarto1.jpg"));
		modelos[i] = smgr->addAnimatedMeshSceneNode(smgr->getMesh("besouro6.b3d")); 
	modelos[i]->setMaterialFlag(EMF_LIGHTING, false);
	modelos[i]->setMaterialTexture(0, driver->getTexture("besouro1.jpg"));

		modelos[i]->setPosition(vector3df(i*-10.0,10.f,0.f));
		modelos[i]->setAnimationSpeed(30);
	}
	/*
	modelo3 = smgr->addAnimatedMeshSceneNode(smgr->getMesh("lagarto.b3d")); 
	//modelo3->setMaterialFlag(EMF_LIGHTING, false);
	modelo3->setMaterialTexture(0, driver->getTexture("lagarto1.jpg"));
	modelo3->setPosition(vector3df(-40.f,10.f,0.f));

	modelo4 = smgr->addAnimatedMeshSceneNode(smgr->getMesh("lagarto.b3d")); 
	//modelo4->setMaterialFlag(EMF_LIGHTING, false);
	modelo4->setMaterialTexture(0, driver->getTexture("lagarto1.jpg"));
	modelo4->setPosition(vector3df(-50.f,10.f,0.f));

	modelo5 = smgr->addAnimatedMeshSceneNode(smgr->getMesh("lagarto.b3d")); 
	//modelo5->setMaterialFlag(EMF_LIGHTING, false);
	modelo5->setMaterialTexture(0, driver->getTexture("lagarto1.jpg"));
	modelo5->setPosition(vector3df(-30.f,10.f,0.f));

	*/
	modelo->setAnimationSpeed(30); // 30 fps
	modelo1->setAnimationSpeed(30);
	/*	modelo2->setAnimationSpeed(30);
	modelo3->setAnimationSpeed(30);
	modelo4->setAnimationSpeed(30);
	modelo5->setAnimationSpeed(30);*/

	_luz = smgr->addLightSceneNode(0, vector3df(0,0,0), SColorf(1.0f, 0.6f, 0.7f, 1.0f), 100);

	_luz->setParent(cam);
	//	_toonShader = new CToonShader(device, _luz);
	/*
	_toonShader->apply(modelo, "besouro1.jpg" );
	_toonShader->apply(modelo1, "louva.jpg");
	_toonShader->apply(modelo2, "lagarto1.jpg");
	_toonShader->apply(modelo3, "lagarto1.jpg");
	_toonShader->apply(modelo4, "lagarto1.jpg");
	_toonShader->apply(modelo5, "lagarto1.jpg" );
	_toonShader->apply(lhand, "martelo.jpg" );
	_toonShader->apply(head, "hercules.jpg" );
	_toonShader->apply(head1, "hercules.jpg");

	*/

	smgr->loadScene("recursos/cenas/jogo.irr");

	cam->setFarValue(300);



	mblack.DiffuseColor = mblack.SpecularColor = mblack.AmbientColor = mblack.EmissiveColor = SColor(255,0,0,0);
	mblack.Lighting = true;
	mblack.Wireframe = true;
	mblack.Thickness = 2;
	mblack.FrontfaceCulling = true;
	mblack.BackfaceCulling = false;

	mblack.setFlag(::E_MATERIAL_FLAG::EMF_NORMALIZE_NORMALS, true);

	while (device->run()) 
	{ 
		driver->beginScene(true, true, SColor(0,220,220,255)); 

		smgr->drawAll(); 

		MapearMundo( smgr->getRootSceneNode() );
/*
		if( modelo->getAutomaticCulling() != EAC_OFF)
			addContorno(modelo);
		if( modelo1->getAutomaticCulling() != EAC_OFF)
			addContorno(modelo1);
		if( modelo2->getAutomaticCulling() != EAC_OFF)
		addContorno(modelo2);
		if( modelo3->getAutomaticCulling() != EAC_OFF)
		addContorno(modelo3);
		if( modelo4->getAutomaticCulling() != EAC_OFF)
		addContorno(modelo4);
		if( modelo5->getAutomaticCulling() != EAC_OFF)
		addContorno(modelo5);
		if( lhand->getAutomaticCulling() != EAC_OFF)
		addContorno(lhand);
		if( head->getAutomaticCulling() != EAC_OFF)
		addContorno(head);
		if( head1->getAutomaticCulling() != EAC_OFF)
		addContorno(head1);

		for(int i=0; i<100; i++)
		{
			if( modelos[i]->getAutomaticCulling() != EAC_OFF)
				addContorno(modelos[i], 2);
		}

*/

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