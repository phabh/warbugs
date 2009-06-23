#pragma once

#include "GameSetup.h"

class CHudRoleta : public IGUIElement
{

private:

	SMeshBuffer mascara, 
		slot1,
		slot2,
		slot3,
		slot4,
		slot5,
		slot6,
		target;

	matrix4 Matrix[6]; 

	float _angAlvo,
		_angAtual;

	//------------------------------------------------------------------------------ 

	void setupQuadMesh( SMeshBuffer &mesh, f32 f32Width ) 
	{ 
		f32 f32HalfWidth = f32Width/2.0f; 
		mesh.Vertices.set_used(4); 
		mesh.Indices .set_used(6); 

		SColor white(255, 255, 255, 255); 

		mesh.Vertices[0] = S3DVertex(-f32HalfWidth, -f32HalfWidth, 0.f, 0.f, 0.f, 1.f, white, 0.f, 1.f); 
		mesh.Vertices[1] = S3DVertex(-f32HalfWidth,  f32HalfWidth, 0.f, 0.f, 0.f, 1.f, white, 0.f, 0.f); 
		mesh.Vertices[2] = S3DVertex( f32HalfWidth,  f32HalfWidth, 0.f, 0.f, 0.f, 1.f, white, 1.f, 0.f); 
		mesh.Vertices[3] = S3DVertex( f32HalfWidth, -f32HalfWidth, 0.f, 0.f, 0.f, 1.f, white, 1.f, 1.f); 

		mesh.Indices[0] = 0; 
		mesh.Indices[1] = 1; 
		mesh.Indices[2] = 2; 
		mesh.Indices[3] = 2; 
		mesh.Indices[4] = 3; 
		mesh.Indices[5] = 0; 

		mesh.getMaterial().Lighting = false; 
		mesh.getMaterial().MaterialType = EMT_TRANSPARENT_ALPHA_CHANNEL; 
	} 

public:

	//------------------------------------------------------------------------------ 

	CHudRoleta(rect<s32> rect, IGUIEnvironment* env, IGUIElement* parent, ITexture* tx_mascara, 
		ITexture* tx_slot1, ITexture* tx_slot2, ITexture* tx_slot3, ITexture* tx_slot4, 
		ITexture* tx_slot5, ITexture* tx_slot6,	ITexture* tx_target)
		: gui::IGUIElement(EGUIET_ELEMENT, env, parent, -1, rect) 
	{ 	
		setupQuadMesh( mascara, 1.5f ); 
		setupQuadMesh( slot1, 1.5f );
		setupQuadMesh( slot2, 1.5f );
		setupQuadMesh( slot3, 1.5f );
		setupQuadMesh( slot4, 1.5f );
		setupQuadMesh( slot5, 1.5f );
		setupQuadMesh( slot6, 1.5f );
		setupQuadMesh( target, 0.5f );

		mascara.getMaterial().setTexture(0, tx_mascara);  
		slot1.getMaterial().setTexture(0, tx_slot1);
		slot2.getMaterial().setTexture(0, tx_slot2);
		slot3.getMaterial().setTexture(0, tx_slot3);
		slot4.getMaterial().setTexture(0, tx_slot4);
		slot5.getMaterial().setTexture(0, tx_slot5);
		slot6.getMaterial().setTexture(0, tx_slot6);
		target.getMaterial().setTexture(0, tx_target);

		_angAlvo = _angAtual = 0;

		for(int i=0; i<6; i++)
		{
			Matrix[i].makeIdentity(); 
			Matrix[i].setRotationDegrees(vector3df(0, 0, i*60 )); 
		}
	} 

	//------------------------------------------------------------------------------ 

	void changeAllTextures(ITexture* tx_mascara, ITexture* tx_slot1, ITexture* tx_slot2, 
		ITexture* tx_slot3, ITexture* tx_slot4, ITexture* tx_slot5, ITexture* tx_slot6, 
		ITexture* tx_target)
	{

		mascara.getMaterial().setTexture(0, tx_mascara);
		slot1.getMaterial().setTexture(0, tx_slot1);
		slot2.getMaterial().setTexture(0, tx_slot2);
		slot3.getMaterial().setTexture(0, tx_slot3);
		slot4.getMaterial().setTexture(0, tx_slot4);
		slot5.getMaterial().setTexture(0, tx_slot5);
		slot6.getMaterial().setTexture(0, tx_slot6); 
		target.getMaterial().setTexture(0, tx_target);
	}

	//------------------------------------------------------------------------------ 

	void changeTextureIndex(int index, ITexture *new_texture)
	{
		switch(index)
		{

		case 0:
			mascara.getMaterial().setTexture(0, new_texture);  
			break;

		case 1:
			slot1.getMaterial().setTexture(0, new_texture); 
			break;

		case 2:
			slot2.getMaterial().setTexture(0, new_texture); 
			break;

		case 3:
			slot3.getMaterial().setTexture(0, new_texture); 
			break;

		case 4:
			slot4.getMaterial().setTexture(0, new_texture); 
			break;

		case 5:
			slot5.getMaterial().setTexture(0, new_texture); 
			break;

		case 6:
			slot6.getMaterial().setTexture(0, new_texture); 
			break;

		case 7:
			target.getMaterial().setTexture(0, new_texture); 
			break;

		};
	}

	//------------------------------------------------------------------------------ 

	void move(f32 i)
	{
		if(_angAlvo == _angAtual)
		{
			if(i > 0)
				_angAlvo += 60;

			else if(i < 0)
				_angAlvo -= 60;	
		}
	}

	//------------------------------------------------------------------------------ 

	void update() 
	{ 

		if(_angAlvo > _angAtual)
		{
			_angAtual+=10;

			for(int i=0; i<6; i++)
			{
				Matrix[i].makeIdentity(); 
				Matrix[i].setRotationDegrees(vector3df(0, 0, (_angAtual + i*60) )); 
			}
		}
		else if(_angAlvo < _angAtual)
		{
			_angAtual-=10;

			for(int i=0; i<6; i++)
			{
				Matrix[i].makeIdentity(); 
				Matrix[i].setRotationDegrees(vector3df(0, 0, (_angAtual + i*60) )); 
			}
		}
	} 

	//------------------------------------------------------------------------------ 

	void draw() 
	{ 
		IVideoDriver* driver = Environment->getVideoDriver(); 

		if (! (driver && IsVisible)) 
			return; 

		rect<s32> oldViewPort = driver->getViewPort(); 
		driver->setViewPort(getAbsolutePosition()); 

		// Limpa matriz de projeção 
		matrix4 oldProjMat = driver->getTransform(ETS_PROJECTION); 
		driver->setTransform(ETS_PROJECTION, matrix4()); 

		// Limpa matriz da viewport 
		matrix4 oldViewMat = driver->getTransform(ETS_VIEW); 
		driver->setTransform(ETS_VIEW, matrix4()); 

		// estático
		driver->setTransform(ETS_WORLD, matrix4()); 

		driver->setMaterial(mascara.Material); 
		driver->drawMeshBuffer(&mascara);

		// rotaciona
		driver->setTransform(ETS_WORLD, Matrix[0]); 
		driver->setMaterial(slot1.Material); 
		driver->drawMeshBuffer(&slot1); 

		driver->setTransform(ETS_WORLD, Matrix[1]); 
		driver->setMaterial(slot2.Material); 
		driver->drawMeshBuffer(&slot2); 

		driver->setTransform(ETS_WORLD, Matrix[2]); 
		driver->setMaterial(slot3.Material); 
		driver->drawMeshBuffer(&slot3); 

		driver->setTransform(ETS_WORLD, Matrix[3]); 
		driver->setMaterial(slot4.Material); 
		driver->drawMeshBuffer(&slot4); 

		driver->setTransform(ETS_WORLD, Matrix[4]); 
		driver->setMaterial(slot5.Material); 
		driver->drawMeshBuffer(&slot5); 

		driver->setTransform(ETS_WORLD, Matrix[5]); 
		driver->setMaterial(slot6.Material); 
		driver->drawMeshBuffer(&slot6); 

		// estático
		driver->setTransform(ETS_WORLD, matrix4()); 

		driver->setMaterial(target.Material); 
		driver->drawMeshBuffer(&target); 

		// Restaurar a matriz da viewport 
		driver->setTransform(ETS_VIEW, oldViewMat); 

		// Restaurar a matriz de projeção
		driver->setTransform(ETS_PROJECTION, oldProjMat); 

		// Restaurar a ViewPort 
		driver->setViewPort(oldViewPort); 
	}
};
