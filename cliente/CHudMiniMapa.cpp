#ifndef __CHudMiniMapa__
#define __CHudMiniMapa__

#include <irrlicht.h> 

using namespace irr; 
using namespace scene; 
using namespace video; 
using namespace core; 

class CHudMiniMapa 
{ 

public: 

	stringw update(ISceneManager* smgr, IVideoDriver* video, dimension2d<s32> dimMapa, position2d<s32> posMapa, dimension2d<s32> dimTerreno) 
	{ 
		array <ISceneNode *> allC, allD; 
		ISceneNode* node; 
		float scale = 1; 
		stringw tmp(L"Minimapa [");

		smgr->getSceneNodesFromType( ESNT_ANIMATED_MESH, allD); 

		for(int i = 0; i < allD.size(); i++)
		{ 
			video->draw2DRectangle(SColor(255,128,0,0), rect<s32>( 
								   posMapa.X + (allD[i]->getPosition().X / dimTerreno.Width*dimMapa.Width)-2, 
								   posMapa.Y + (allD[i]->getPosition().Z / dimTerreno.Height*dimMapa.Height)-2, 
								   posMapa.X + (allD[i]->getPosition().X / dimTerreno.Width*dimMapa.Width) +2, 
								   posMapa.Y + (allD[i]->getPosition().Z / dimTerreno.Height*dimMapa.Height)+2) 
								   );

			tmp += allD[i]->getPosition().X; 
			tmp += " ; "; 
			tmp += allD[i]->getPosition().Y; 
			tmp += " ; "; 
			tmp += allD[i]->getPosition().Z; 
		}
/*
		smgr->getSceneNodesFromType(ESNT_MESH, allC); 

		for(int i = 0; i < allC.size(); i++)
		{ 
			video->draw2DRectangle(SColor(255,0,0,0),rect<s32>( 
								   posMapa.X + (allC[i]->getPosition().X / dimTerreno.Width*dimMapa.Width)-2, 
								   posMapa.Y + (allC[i]->getPosition().Z / dimTerreno.Height*dimMapa.Height)-2, 
								   posMapa.X + (allC[i]->getPosition().X / dimTerreno.Width*dimMapa.Width) +2, 
								   posMapa.Y + (allC[i]->getPosition().Z / dimTerreno.Height*dimMapa.Height)+2) 
								   ); 
		} */
		return tmp; 
	} 

}; 

#endif;