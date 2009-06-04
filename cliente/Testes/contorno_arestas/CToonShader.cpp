#include "CToonShader.h"

//-----------------------------------------------------------------------------------------

CToonShader::CToonShader( IrrlichtDevice *device, ILightSceneNode *light ) 
{
	_dispositivo = device;
	_gerVideo = _dispositivo->getVideoDriver();
	_gerCena = _dispositivo->getSceneManager();
	
	_luz = light;

	//_lightPosition = light->getAbsolutePosition();

	_camera = _gerCena->getActiveCamera();
}

//-----------------------------------------------------------------------------------------

CToonShader::~CToonShader()
{
}

//-----------------------------------------------------------------------------------------

void CToonShader::apply(ISceneNode/*IAnimatedMeshSceneNode*/ *modelo, c8 *textura)
{
	modelo->setMaterialFlag( EMF_NORMALIZE_NORMALS, true );

	modelo->getMaterial(0).setTexture(0, _gerVideo->getTexture(textura));
	modelo->getMaterial(0).setTexture(1, _gerVideo->getTexture("layercell.png"));
	modelo->getMaterial(0).TextureLayer[1].BilinearFilter = false;

	IGPUProgrammingServices* gpu = _gerVideo->getGPUProgrammingServices();

	s32 toonMaterial = gpu->addHighLevelShaderMaterialFromFiles(
		"cellshader.fx", "vertexMain", EVST_VS_2_0,
		"cellshader.fx", "pixelMain", EPST_PS_2_0, this);

	modelo->getMaterial(0).MaterialType = (E_MATERIAL_TYPE)toonMaterial;
}

//-----------------------------------------------------------------------------------------

void CToonShader::OnSetConstants(IMaterialRendererServices* servicos, s32 dados)
{
	matrix4 world = _gerVideo->getTransform(ETS_WORLD);

	matrix4 invWorld;
	world.getInverse(invWorld);

	vector3df lightPosOS;

	invWorld.transformVect(lightPosOS, _luz->getAbsolutePosition()/*_lightPosition*/);
	servicos->setVertexShaderConstant("mLightPos", &lightPosOS.X, 3);

	vector3df camPosOS;

	invWorld.transformVect(camPosOS, _camera->getAbsolutePosition());
	servicos->setVertexShaderConstant("mCamPos", &camPosOS.X, 3);

	matrix4 wvp = _gerVideo->getTransform(ETS_PROJECTION);
	wvp *= _gerVideo->getTransform(ETS_VIEW);
	wvp *= world;

	servicos->setVertexShaderConstant("mWorldViewProj", wvp.pointer(), 16);
}

//-----------------------------------------------------------------------------------------
