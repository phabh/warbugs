#pragma once

#include "irrlicht.h" 

using namespace irr; 
using namespace core; 
using namespace scene; 
using namespace video; 
using namespace io; 
using namespace gui; 

class CToonShader : public IShaderConstantSetCallBack
{

private:

	ICameraSceneNode *_camera;
	IVideoDriver *_gerVideo;
	ISceneManager *_gerCena;
	IrrlichtDevice *_dispositivo;
	ILightSceneNode *_luz;
	//vector3df _lightPosition;

public:

	CToonShader(IrrlichtDevice *device, ILightSceneNode *light);
	~CToonShader();
	void apply(ISceneNode/*IAnimatedMeshSceneNode*/ *modelo, c8 *textura);
	void OnSetConstants(IMaterialRendererServices* servicos, s32 dados);
};