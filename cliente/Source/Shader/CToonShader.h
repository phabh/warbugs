#pragma once

#include "GameSetup.h"

class CToonShader : public IShaderConstantSetCallBack
{

private:

	ICameraSceneNode *_camera;
	IVideoDriver *_gerVideo;
	ISceneManager *_gerCena;
	IrrlichtDevice *_dispositivo;
	vector3df _lightPosition;

public:

	CToonShader(IrrlichtDevice *device, ILightSceneNode *light);
	~CToonShader();
	void apply(ISceneNode/*IAnimatedMeshSceneNode*/ *modelo, c8 *textura);
	/*virtual */
	void OnSetConstants(IMaterialRendererServices* servicos, s32 dados);
};