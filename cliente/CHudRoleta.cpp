#ifndef __CHudRoleta__
#define __CHudRoleta__

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace video;
using namespace gui;
using namespace scene;

class CHudRoleta : public IGUIElement
{
	private:

		SMeshBuffer CorpoMesh; 
		SMeshBuffer PonteiroMesh; 
		matrix4 Matrix; 
		float _angAlvo,
			  _angAtual;


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
	 
		CHudRoleta(rect<s32> rect, IGUIEnvironment* env, IGUIElement* parent, ITexture* txCorpo, ITexture* txPonteiro) : gui::IGUIElement(EGUIET_ELEMENT, env, parent, -1, rect) 
		{ 
		   setupQuadMesh( CorpoMesh, 1.0f ); 
		   setupQuadMesh( PonteiroMesh, 1.0f );

		   CorpoMesh.getMaterial().setTexture(0, txCorpo);  
		   PonteiroMesh.getMaterial().setTexture(0, txPonteiro);

		   _angAlvo = _angAtual = 0;
		} 

		//------------------------------------------------------------------------------ 

		void move(f32 i)
		{
			if(_angAlvo == _angAtual)
			{
				if(i > 0)
					_angAlvo+=60;
				
				else if(i < 0)
					_angAlvo-=60;	
			}
		}

		//------------------------------------------------------------------------------ 

		void update() 
		{ 
			
			if(_angAlvo > _angAtual)
			{
				_angAtual++;
				Matrix.makeIdentity(); 
				Matrix.setRotationDegrees(vector3df(0, 0, _angAtual)); 
				
			}
			else if(_angAlvo < _angAtual)
			{
				_angAtual--;
				Matrix.makeIdentity(); 
				Matrix.setRotationDegrees(vector3df(0, 0, _angAtual)); 
				
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

			driver->setTransform(ETS_WORLD, Matrix); 

			// Desenha corpo da bussola 
			driver->setMaterial(CorpoMesh.Material); 
			driver->drawMeshBuffer(&CorpoMesh); 

			driver->setTransform(ETS_WORLD, matrix4()); 

			// Desenha ponteiro da bussola
			driver->setMaterial(PonteiroMesh.Material); 
			driver->drawMeshBuffer(&PonteiroMesh); 

			// Restaurar a matriz da viewport 
			driver->setTransform(ETS_VIEW, oldViewMat); 

			// Restaurar a matriz de projeção
			driver->setTransform(ETS_PROJECTION, oldProjMat); 

			// Restaurar a ViewPort 
			driver->setViewPort(oldViewPort); 
		}
};

#endif;