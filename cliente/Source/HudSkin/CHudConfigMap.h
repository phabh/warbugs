#pragma once

#include "irrMap.h"
#include "irrString.h"
#include "irrTypes.h"
#include "vector2d.h"
#include "vector3d.h"

using namespace irr;
using namespace core;

class CHudConfigMap
{

public:

    stringc getConfig( const stringc& name );
    s32 getConfigAsInt( const stringc& name );
    f32 getConfigAsFloat( const stringc& name );
    vector2df getConfigAsVector2df( const stringc& name );
    vector3df getConfigAsVector3df( const stringc& name );
    bool hasConfig( const stringc& name );
    void setConfig( const stringc& name, const stringc& value );

private:

    map<stringc, stringc> Map;
};