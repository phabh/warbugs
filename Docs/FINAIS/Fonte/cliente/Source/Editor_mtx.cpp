/*#include <irrlicht.h>
#include <iostream>

using namespace irr;
using namespace scene;
using namespace video;
using namespace core;

#pragma comment(lib, "Irrlicht.lib")*/

#include "PathSetup.h"
#include "CArquivoMatrizes.cpp"
#include "CGerEventos.h"


class CSampleSceneNode : public scene::ISceneNode
{
	aabbox3d<f32> box;
	S3DVertex Vertices[4];
	SMaterial Material;

public:

	CSampleSceneNode(ISceneNode* parent, ISceneManager* mgr, s32 id, vector3df p1, vector3df p2, vector3df p3, vector3df p4 ) : ISceneNode(parent, mgr, id)
	{
		Material.Wireframe = false;
		Material.Lighting = false;

		Vertices[0]  = S3DVertex(p1.X, p1.Y, p1.Z,  1, 1,-1, SColor(255,255,255,255), 1, 0);
		Vertices[1]  = S3DVertex(p2.X, p2.Y, p2.Z,  1, 1, 1, SColor(255,255,255,255), 0, 0);
		Vertices[2]  = S3DVertex(p3.X, p3.Y, p3.Z, -1, 1, 1, SColor(255,255,255,255), 0, 1);
		Vertices[3]  = S3DVertex(p4.X, p4.Y, p4.Z, -1, 1,-1, SColor(255,255,255,255), 1, 1);

	}


	virtual void OnRegisterSceneNode()
	{
		if (IsVisible)
			SceneManager->registerNodeForRendering(this);

		ISceneNode::OnRegisterSceneNode();
	}

	virtual void render()
	{
		u16 indices[6] = { 3,1,0,   3,2,1 };

		video::IVideoDriver* driver = SceneManager->getVideoDriver();
		driver->setMaterial(Material);
		driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);

		driver->drawIndexedTriangleList(&Vertices[0], 4, &indices[0], 2); 
	}

	virtual const aabbox3d<f32>& getBoundingBox() const 
	{
		
		return box;
	}

	virtual u32 getMaterialCount() const
	{
		return 1;
	}

	virtual SMaterial& getMaterial(u32 i)
	{
		return Material;
	}   
};



int main()
{
	int idCenario = 0;
	
	int quadId;

	vector3df p1, p2, p3, p4;

	SMatrix mtxCenario; 

	CArquivoMatrizes *_fileMtx = new CArquivoMatrizes();

	CSampleSceneNode *myQuad[2500];

	CGerEventos eventos;

	IrrlichtDevice *device =  createDevice(EDT_OPENGL, dimension2d<s32>(800, 600), 16, false,false,false, &eventos);

	device->setWindowCaption(L"Editor de matrizes - Warbugs");

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();

	

	smgr->addCameraSceneNodeFPS();
	//smgr->addCameraSceneNode(0, vector3df(0,100,0), vector3df(0,0,0));

	smgr->loadScene(pathCenario[idCenario]);
	mtxCenario = _fileMtx->getMatrix(idCenario);

	ITerrainSceneNode *sceneTerrain = (ITerrainSceneNode*)smgr->getSceneNodeFromType(ESNT_TERRAIN, 0);
	ITriangleSelector *sceneTris = smgr->createTerrainTriangleSelector(sceneTerrain, 0);
	sceneTerrain->setTriangleSelector(sceneTris);

	for(int i=0; i<50; i++) // z
	{
		for(int j=0; j<50;j++) // x
		{
			//if(
			//{
				p1.X = 10.0;
				p1.Y = 1.0;
				p1.Z = 0.0;

				p2.X = 10.0;
				p2.Y = 1.0;
				p2.Z = 500.0;

				p3.X = 0.0;
				p3.Y = 1.0;
				p3.Z = 500.0;

				p4.X = 0.0;
				p4.Y = 1.0;
				p4.Z = 0.0;

				quadId = j + (i * 10);
				myQuad[quadId] = new CSampleSceneNode(smgr->getRootSceneNode(), smgr, quadId, p1, p2, p3, p4);
			//}
		}
	}

	while(device->run())
	{
		driver->beginScene(true, true, SColor(0,100,100,100));

		smgr->drawAll();

		driver->endScene();
	}

	device->drop();

	return 0;
} 