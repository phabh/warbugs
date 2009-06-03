#include "CHudConfigMap.h"

stringc CHudConfigMap::getConfig( const stringc& name )
{
	map<stringc, stringc>::Node* node = Map.find(name);

	if ( node == 0 )
		return stringc();

	return node->getValue();
}

s32 CHudConfigMap::getConfigAsInt( const stringc& name )
{
	stringc cfg = getConfig(name);

	if ( cfg.size() == 0 )
		return 0;

	s32 x = 0;
	sscanf( cfg.c_str(), "%d", &x );

	return x;
}

f32 CHudConfigMap::getConfigAsFloat( const stringc& name )
{
	stringc cfg = getConfig(name);

	if ( cfg.size() == 0 )
		return 0;

	f32 x = 0.0f;
	sscanf( cfg.c_str(), "%f", &x );

	return x;
}


vector2df CHudConfigMap::getConfigAsVector2df( const stringc& name )
{
	stringc cfg = getConfig(name);

	if ( cfg.size() == 0 )
		return vector2df(0,0);

	vector2df vec;

	sscanf( cfg.c_str(), "%f , %f", &vec.X, &vec.Y );

	return vec;
}

vector3df CHudConfigMap::getConfigAsVector3df( const stringc& name )
{
	stringc cfg = getConfig(name);

	if ( cfg.size() == 0 )
		return vector3df(0,0,0);

	vector3df vec;

	sscanf( cfg.c_str(), "%f , %f , %f", &vec.X, &vec.Y, &vec.Z );

	return vec;
}

bool CHudConfigMap::hasConfig( const stringc& name )
{
	map<stringc,stringc>::Node* node = Map.find(name);

	return ( node != 0 );
}

void CHudConfigMap::setConfig( const stringc& name, const stringc& value )
{
	Map.set(name,value);
}