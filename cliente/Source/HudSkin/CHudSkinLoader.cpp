#include "IFileSystem.h"
#include "IReadFile.h"
#include "IVideoDriver.h"
#include "CHudSkinLoader.h"
#include "CHudConfigMap.h"
#include "CHudConfigReader.h"

namespace irr
{

	stringc GetContextPathFromFilename( const stringc& filename )
	{
		stringc path;
		s32 i=filename.size()-1;
		while ( i >= 0 && filename[i] != '/' )
		{
			i--;
		}
		path = filename.subString( 0, i+1 );
		return path;
	}

	CHudConfigMap* LoadConfigFromFile( IFileSystem* fileSystem, const stringc& filename )
	{
		IReadFile* file = fileSystem->createAndOpenFile( filename.c_str() );

		if ( !file )
			return 0;

		CHudConfigMap* map = new CHudConfigMap();

		CHudConfigReader reader;
		reader.loadReadFile(file);

		file->drop();

		while ( reader.nextConfig() )
		{
			stringc name = reader.getConfigName();
			stringc value = reader.getConfigValue();

			map->setConfig(name,value);
		}

		return map;
	}

	static void ParseGUIElementStyle( IVideoDriver* driver, CHudConfigMap* cfg, SImageGUIElementStyle& elem, const stringc& name, const stringc& context )
	{
		stringc s = cfg->getConfig(name + ".SrcBorder");
		sscanf( s.c_str(), "%d , %d , %d , %d", &elem.SrcBorder.Top, &elem.SrcBorder.Left, &elem.SrcBorder.Bottom, &elem.SrcBorder.Right );

		s = cfg->getConfig(name + ".DstBorder");
		sscanf( s.c_str(), "%d , %d , %d , %d", &elem.DstBorder.Top, &elem.DstBorder.Left, &elem.DstBorder.Bottom, &elem.DstBorder.Right );

		s = cfg->getConfig(name + ".Texture");
		elem.Texture = driver->getTexture((context + s).c_str());

		s = cfg->getConfig(name + ".Color");

		if ( s != "" )
		{
			s32 a,r,g,b;
			sscanf( s.c_str(), "%d , %d , %d , %d", &a, &r, &g, &b );
			elem.Color = SColor(a,r,g,b);
		}
	}

	SImageGUISkinConfig LoadGUISkinFromFile( IFileSystem* fileSystem, IVideoDriver* driver, const stringc& filename )
	{
		SImageGUISkinConfig skin;

		CHudConfigMap* cfg = LoadConfigFromFile(fileSystem, filename);
		if ( !cfg )
			return skin;

		stringc context = GetContextPathFromFilename(filename);

		ParseGUIElementStyle( driver, cfg, skin.Button, "Button", context );
		ParseGUIElementStyle( driver, cfg, skin.ButtonPressed, "ButtonPressed", context );
		ParseGUIElementStyle( driver, cfg, skin.SunkenPane, "SunkenPane", context );
		ParseGUIElementStyle( driver, cfg, skin.Window, "Window", context );
		ParseGUIElementStyle( driver, cfg, skin.ProgressBar, "ProgressBar", context );
		ParseGUIElementStyle( driver, cfg, skin.ProgressBarFilled, "ProgressBarFilled", context );
		ParseGUIElementStyle( driver, cfg, skin.CheckBox, "CheckBox", context );

		delete cfg;

		return skin;
	}
}