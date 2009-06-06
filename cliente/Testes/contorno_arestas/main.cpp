
#include "CToonShader.h"

#pragma comment (lib,"irrlicht.lib") 

using namespace irr; 
using namespace core; 
using namespace scene; 
using namespace video; 
using namespace io; 
using namespace gui; 

IrrlichtDevice *device; 
IVideoDriver* driver; 
	ISceneManager* smgr; 
	IGUIEnvironment* guienv; 
	ICameraSceneNode *cam; 
	IAnimatedMesh *mod1, *mod2;
	::ITexture *tx1, *tx2;

IAnimatedMeshSceneNode *modelo; 
IAnimatedMeshSceneNode *modelo1; 
IAnimatedMeshSceneNode *modelos[100];

IAnimatedMeshSceneNode *md1, *md2; 

/*
									  IAnimatedMeshSceneNode *modelo3; 
									  IAnimatedMeshSceneNode *modelo4; 
									  IAnimatedMeshSceneNode *modelo5; */
ILightSceneNode *_luz;
CToonShader *_toonShader; 

SMaterial mblack;


	
	
float getDist(vector3df v1, vector3df v2)
{
	float dx = abs(v1.X - v2.X);
	float dz = abs(v1.Z - v2.Z);

	return ::sqrt(dx*dx + dz*dz);

}

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
	//lmat.setFlag(EMF_FOG_ENABLE, true);

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
	if (node->getType() == ESNT_MESH || node->getType() == ESNT_ANIMATED_MESH  /*|| node->getType() == ESNT_TERRAIN*/ )
  {
	  if(node->getID() >= 10)
	  {
	  IAnimatedMeshSceneNode* no = (IAnimatedMeshSceneNode*)node;

	  if( getDist(no->getAbsolutePosition(), cam->getAbsolutePosition()) > 300)
	  {		
		  no->setVisible(false);/*
		  no->setMesh(mod2);
		  no->setMaterialFlag(EMF_LIGHTING, false);
		  no->setMaterialTexture(0, tx2);
		  no->setAnimationSpeed(30);*/
	  }
	  else
	  {
		  no->setVisible(true);/*
		  no->setMesh(mod1);
		  no->setMaterialFlag(EMF_LIGHTING, false);
		  no->setMaterialTexture(0, tx1);
		  no->setAnimationSpeed(30);*/
	  }
	  }
	  
	  if( node->getAutomaticCulling() != EAC_OFF && node->isVisible())
	  {
			addContorno(node);
/*
			video::SMaterial m;
m.Lighting = false;
driver->setMaterial(m);

// this is an object aligned bounding box. it should be a pretty tight fit.
core::aabbox3df box(node->getBoundingBox());

// to draw a box that is in object coordinates...
driver->setTransform(ETS_WORLD, node->getAbsoluteTransformation());
driver->draw3DBox(box, SColor(255, 0, 255, 0));

// this is a world aligned bounding box. it may be bigger than the
// object space bounding box, but the edges of the box will be aligned
// with the world coordinate system.
node->getAbsoluteTransformation().transformBoxEx(box);

// to draw a box that is in world coordinates...
driver->setTransform(video::ETS_WORLD, core::matrix4());
driver->draw3DBox(box, video::SColor(255, 0, 0, 255)); */
	  }
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
	

	u32 lasttick; 
	int lastFPS = -1; 

	::ILightSceneNode *_luz;

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

	mod1 = smgr->getMesh("lagarto.b3d");
	mod2 = smgr->getMesh("besouro6.b3d");

	tx1 = driver->getTexture("lagarto1.jpg");
	tx2 =driver->getTexture("besouro1.jpg");
/*
	md1 = smgr->addAnimatedMeshSceneNode(mod1); 
	md1->setMaterialFlag(EMF_LIGHTING, false);
	md1->setMaterialTexture(0, tx1);
	md1->setAnimationSpeed(30);

	md2 = smgr->addAnimatedMeshSceneNode(mod2); 
	md2->setMaterialFlag(EMF_LIGHTING, false);
	md2->setMaterialTexture(0, tx2);
	md2->setAnimationSpeed(30);*/

	for(int i=0; i<100; i++)
	{

		//modelos[i] = smgr->addAnimatedMeshSceneNode(smgr->getMesh("lagarto.b3d")); 
	modelos[i] = smgr->addAnimatedMeshSceneNode(mod1); 
	modelos[i]->setMaterialFlag(EMF_FOG_ENABLE, true);
	//modelos[i]->setMaterialType(::EMT_SOLID);
		modelos[i]->setMaterialFlag(EMF_LIGHTING, false);
	modelos[i]->setMaterialTexture(0, tx1);
		//modelos[i] = smgr->addAnimatedMeshSceneNode(smgr->getMesh("besouro6.b3d")); 
	//modelos[i]->setMaterialFlag(EMF_LIGHTING, false);
	//modelos[i]->setMaterialTexture(0, driver->getTexture("besouro1.jpg"));

		modelos[i]->setPosition(vector3df(i*-20.0,10.f,0.f));
		modelos[i]->setAnimationSpeed(30);
		modelos[i]->setID(i+10);
	}

	driver->setFog(video::SColor(255,/*138,125,81*/255,255,255), true, /*250*/100, 300, 0, true);
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

	cam->setFarValue(1000);

	mblack.DiffuseColor = mblack.SpecularColor = mblack.AmbientColor = mblack.EmissiveColor = SColor(255,0,0,0);
	mblack.Lighting = true;
	mblack.Wireframe = true;
	mblack.Thickness = 2;
	mblack.FrontfaceCulling = true;
	mblack.BackfaceCulling = false;

	mblack.setFlag(::E_MATERIAL_FLAG::EMF_NORMALIZE_NORMALS, true);


	_luz = smgr->addLightSceneNode(cam, vector3df(0,10000,0), SColorf(0.5, 0.5, 1.0, 1.0), 10000);

	while (device->run()) 
	{ 
		driver->beginScene(true, true, SColor(255,255,255,255)); 

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