#ifndef __Setup__
#define __Setup__

//-----------------------------------------------------------------------------------------
// Includes genéricos

#include <windows.h>
#include <iostream>
#include <fstream>
#include <string.h>
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
#pragma comment(lib, "dsvt.lib")

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
const int NUMFLAGSMENU = 20;
const int NUMFXHUD = 10;

const int NUMCENARIOS = 10; // Número de cenários no jogo
const int NUMPROPS = 50; // Número de props do jogo (arvore, templos, flores, etc..)

const int NUMRACES = 20; // Número de raças disponíveis no jogo
const int NUMCLASSES = 8; // Número de classes para cada raça

const int NUM3DITENS = 26; // Número de itens 3D no jogo
const int NUM3DPERS = 44; // Número de personagens 3D no jogo
const int NUM2DOBJS = 38; // Número de objetos 2D no jogo
const int NUMMENUHUDS = 3; // Número de huds nos menus


//-----------------------------------------------------------------------------------------
// Enumerators

enum menuID {ABERTURA, LOGIN, CONFIGURACAO, SELECAOPERSONAGEM, CRIACAOPERSONAGEM, JOGO, CREDITOS, SAIDA, ERRO};

enum tipoLua {LUANULL, LUABESOURO, LUAVESPA, LUAESCORPIAO, LUAARANHA, LUALOUVAADEUS};

enum TypeRaceChars {NONERACE, ALLRACE, ARANHA, BESOURO, ESCORPIAO, LOUVADEUS, VESPA, CUPIM, FORMIGA, BARBEIRO, BARATA, TATUBOLINHA, LIBELULA, PERCEVEJO, ABELHA, LAGARTIXA, CALANGO, SAPO, JOANINHA, CAMALEAO};

enum TypeClassChars {NONECLASS, ALLCLASS, JOGADOR, SOLDADO, LIDER, VENDEDOR, MAE, FILHOTE};

enum TypeTxScenes {TXCENA0, TXCENA1, TXCENA2, TXCENA3, TXCENA4, TXCENA5, TXCENA6, TXCENA7, HEIGHTMAP};

enum TypeModelos {M_ARANHA_LIDER, M_ARANHA_JOGADOR, M_ARANHA_SOLDADO, M_ARANHA_VENDEDOR, M_ARANHA_MAE, M_ARANHA_FILHOTE, M_BESOURO_LIDER, M_BESOURO_JOGADOR, M_BESOURO_SOLDADO, M_BESOURO_VENDEDOR, M_BESOURO_MAE, M_BESOURO_FILHOTE, M_ESCORPIAO_LIDER, M_ESCORPIAO_JOGADOR, M_ESCORPIAO_SOLDADO, M_ESCORPIAO_VENDEDOR, M_ESCORPIAO_MAE, M_ESCORPIAO_FILHOTE, M_LOUVADEUS_LIDER, M_LOUVADEUS_JOGADOR, M_LOUVADEUS_SOLDADO, M_LOUVADEUS_VENDEDOR, M_LOUVADEUS_MAE, M_LOUVADEUS_FILHOTE, M_VESPA_LIDER, M_VESPA_JOGADOR, M_VESPA_SOLDADO, M_VESPA_VENDEDOR, M_VESPA_MAE, M_VESPA_FILHOTE, M_CUPIM, M_FORMIGA, M_BARBEIRO, M_BARATA, M_TATUBOLINHA, M_LIBELULA, M_PERCEVEJO, M_ABELHA, M_LAGARTIXA, M_CALANGO, M_SAPO, M_JOANINHA, M_CAMALEAO, M_TANDAN};
    
enum TypeItens {I_BUZINA, I_VARINHA, I_SOCO, I_BAZUCA, I_MARTELO_GUERRA, I_METRALHADORA, I_MARTELO_CONAN, I_KATANA, I_LANÇADOR_DARDOS, I_MACHADO, I_PALITO_FOSFORO, I_VASSOURA, I_PU_DAO, I_ESPINGARDA, I_MAMONA, I_ESTILINGUE, I_CARTOLA, I_TENIS, I_ELMO_HERCULES, I_ELMO_BARBARO, I_OCULOS_ESCUROS, I_GORRO, I_CACETETE, I_CHAPEU_PALHA, I_OCULOS_AVIADOR, I_MASCARA_GAS, I_PASSAPORTE, I_POLPA_FORMIGA, I_POLPA_CUPIM, I_POLPA_BARATA, I_POLPA_TATU, I_ASA_LIBELULA, I_PERFUME_PERCEVEJO, I_MEL_ABELHA, I_PATA_BARBEIRO, I_RABO_CALANGO, I_OVO_LAGARTIXA, I_LINGUA_SAPO, I_LINGUA_CAMALEAO};

enum TypeHuds { H_MINIMAPAON, H_MINIMAPAOFF, H_SEMENTE };

#endif;