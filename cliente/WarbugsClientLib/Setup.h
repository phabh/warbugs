#pragma once

//-----------------------------------------------------------------------------------------
// Includes genéricos

#include <windows.h>
#include <iostream>
#include <fstream>
#include "irrlicht.h"
#include "irrklang.h"

//-----------------------------------------------------------------------------------------
// Namespaces

using namespace std; 
using namespace irr; 
using namespace core; 
using namespace scene; 
using namespace video; 
using namespace io; 
using namespace gui;
using namespace irrklang;

//-----------------------------------------------------------------------------------------
// Inclusão de libs

#pragma comment(lib, "Irrlicht.lib")
#pragma comment(lib, "irrKlang.lib")

//-----------------------------------------------------------------------------------------
// Constantes

const int MAXPORTAIS = 4;
const int MAPMAXLIN  = 50;
const int MAPMAXCOL  = 50;
const int BOLSAMAXITENS = 9;
const int INVENTARIOMAXITENS = 12;
const int RACASMAX = 5;
const int NUMPODERES = 3;
const int NUMROLETAOPCOES = 6;
const int MAXITENSVENDEDOR = 30;
const int NUMBUFFERS = 15;
const int LARGURABUSCA = 10;
const int AREABUSCA = LARGURABUSCA*LARGURABUSCA;
const int NUMFLAGSMENU = 12;
const int NUMFXHUD = 10;

//-----------------------------------------------------------------------------------------
// Enumerators

enum menuID {ABERTURA, LOGIN, CONFIGURACAO, SELECAOPERSONAGEM, CRIACAOPERSONAGEM, JOGO, CREDITOS, SAIDA, ERRO};
enum tipoLua {LUANULL, LUABESOURO, LUAVESPA, LUAESCORPIAO, LUAARANHA, LUALOUVAADEUS};