#pragma once

#include "GameSetup.h"

class CHudMiniMapa 
{ 

public: 

	stringw update(ISceneManager* smgr, IVideoDriver* video, dimension2d<s32> dimMapa, position2d<s32> posMapa, dimension2d<s32> dimTerreno) 
	{ 
		array <ISceneNode *> allC, allD; 
		float scale = 1; 
		stringw tmp(L"Minimapa [");

		smgr->getSceneNodesFromType( ESNT_ANIMATED_MESH, allD); 

		for(u32 i = 0; i < allD.size(); i++)
		{ 
			video->draw2DRectangle(SColor(255,128,0,0), rect<s32>( 
								   (s32)posMapa.X + (s32)(allD[i]->getPosition().X / dimTerreno.Width*dimMapa.Width)-2, 
								   (s32)posMapa.Y + (s32)(allD[i]->getPosition().Z / dimTerreno.Height*dimMapa.Height)-2, 
								   (s32)posMapa.X + (s32)(allD[i]->getPosition().X / dimTerreno.Width*dimMapa.Width) +2, 
								   (s32)posMapa.Y + (s32)(allD[i]->getPosition().Z / dimTerreno.Height*dimMapa.Height)+2) 
								   );

			tmp += allD[i]->getPosition().X; 
			tmp += " ; "; 
			tmp += allD[i]->getPosition().Y; 
			tmp += " ; "; 
			tmp += allD[i]->getPosition().Z; 
		}
		return tmp; 
	} 
}; 
