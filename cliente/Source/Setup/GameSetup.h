#pragma once

//-----------------------------------------------------------------------------------------
// Includes genéricos
//-----------------------------------------------------------------------------------------

#include <WinSock2.h> // Sempre antes do Windows.h
#include <windows.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

#include "irrlicht.h"
#include "irrklang.h"

//-----------------------------------------------------------------------------------------
// Namespaces
//-----------------------------------------------------------------------------------------

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
//-----------------------------------------------------------------------------------------

#pragma comment(lib, "Irrlicht.lib")
#pragma comment(lib, "irrKlang.lib")
#pragma comment(lib, "dsvt.lib")

//-----------------------------------------------------------------------------------------
// Constantes
//-----------------------------------------------------------------------------------------

// Cenario
const int MAXPORTAIS = 4;    // Número de portais por cenário
const int MAPMAXLIN  = 50;   // Número máximo de linhas por cenário
const int MAPMAXCOL  = 50;   // Número máximo de colunas por cenário
const int TAMQUADRANTE = 44; // Tamanho de cada quadrante em pixels
const int NUMCENARIOS = 10;  // Número de cenários no jogo
const int NUMPROPS = 50; // Número de props do jogo (arvore, templos, flores, etc..)
const int NUMPARTICLETYPES = 1; // Número de tipos de partículas (fogo, fumaça,...)

// Bolsa
const int BOLSAMAXITENS = 9; // Número máximo de itens na bolsa de um personagem
const int BOLSA_ID_OFFSET = 1000000; // para nao colidir com id de personagens no nó de cena

// Personagens
const int INVENTARIOMAXITENS = 12; // Número máximo de itens no inventário
const int RACASMAX = 5;    // Número máximo de raças jogáveis
const int NUMRACES = 20;   // Número de raças disponíveis no jogo
const int NUMCLASSES = 8;  // Número de classes para cada raça
const int NUMPODERES = 3;  // Número de poderes de cada personagem
const int NUMBUFFERS = 15; // Número de buffs de cada personagem
const int MAXITENSVENDEDOR = 30; // Número máximo de itens do vendedor

// Menu
const int NUMMENUCENA = 3; // número de menus com cenas irr a carregar
const int MAXSLOTPERSONAGEM = 2; // número máximo de slots de personagem de um jogador

// Hud
const int NUMROLETAOPCOES = 6; // número de opções na roleta
const int NUMSFXHUD = 10;      // efeitos sonoros do HUD
const int NUMFLAGSMENU = 20;   // número de flags de menu
const int NUMHUDFONTS = 2;     // número de fonts no menu

// Pathfinding
const int LARGURABUSCA = 10; // largura de busca 10 quadrantes
const int AREABUSCA = LARGURABUSCA*LARGURABUSCA; // área de busca 10x10 quadrantes

// Game Data
const int NUM3DITENS = 26; // Número de itens 3D no jogo
const int NUM3DPERS = 44;  // Número de personagens 3D no jogo
const int NUM2DOBJS = 38;  // Número de objetos 2D no jogo
const int NUMMENUHUDS = 3; // Número de huds nos menus
const int NUMMUSICAS = 4;  // Número de músicas do jogo

// Irrlicht

const E_DRIVER_TYPE defDriver = EDT_DIRECT3D9;
const dimension2d <s32> defDimension = dimension2d <s32>( 1024, 768 );
const u8 defBits = 32;
const bool defFullScreen = false;
const bool defStencilBuffer = true;
const bool defVsync = true;
const bool defAntiAlias = true;
const bool defAlphaChannel = true;
const bool defHiPrecisionFpu = false;
const bool defIgnoreInput = false;
const u8 defZBufferBits = 16;

// IrrKlang

const f32 defSFXVol = 1.0;
const f32 defMusicVol = 1.0;

//-----------------------------------------------------------------------------------------
// Enumerators
//-----------------------------------------------------------------------------------------

// Inicialização
enum TypeReturn {ERRO, SUCESSO};


// Menu
enum TypeMenuID {MN_ABERTURA, MN_LOGIN, MN_SELECAOPERSONAGEM, MN_CRIACAOPERSONAGEM, MN_JOGO, MN_CREDITOS, MN_COUNT, MN_SAIDA, MN_ERRO};

enum TypeMenuFlag {HUDUPDATED, OBJSELECTED, INVENTARIOON, CHATON, STATUSON, MAPAON, TRADEON, EQUIPON, SHOPON, BOLSAON, ALERTON, CONFIGON, FLAG_COUNT};

enum TypeFontSize {FONT_PEQUENA, FONT_GRANDE, FONT_COUNT};

enum TypeMenuSCene {MC_LOGIN, MC_SELECAO, MC_CRIACAO, MC_COUNT};

enum TypeMenuMusic {MM_LOGIN, MM_SELECAO, MM_CRIACAO, MM_JOGO, MM_COUNT};

enum TypeMenuSfx {MFX_BOTAO, MFX_OPENWINDOW, MFX_CLOSEWINDOW, MFX_SLIDEBAR, MFX_CASH, MFX_PICKUP, MFX_COUNT};

enum TypeCutScene {CS_ABERTURA, CS_CREDITOS, CS_TRANSICAO, CS_COUNT};

enum TypeHudSkin {HS_NONE, HS_PADRAO, HS_ARANHA, HS_BESOURO, HS_ESCORPIAO, HS_LOUVADEUS, HS_VESPA, HS_COUNT };


// Cenario
enum TypeMoon {LUANULL, LUABESOURO, LUAVESPA, LUAESCORPIAO, LUAARANHA, LUALOUVAADEUS, LUA_COUNT};

enum TypeTxScenes {TXCENA_0, TXCENA_1, TXCENA_2, TXCENA_3, TXCENA_4, TXCENA_5, TXCENA_6, TXCENA_7, TXCENA_BUMP, TXCENA_COUNT};

enum TypeGameScene {GAMESCENE_01, GAMESCENE_02, GAMESCENE_03, GAMESCENE_04, GAMESCENE_05, GAMESCENE_06, GAMESCENE_07, GAMESCENE_08, GAMESCENE_09, GAMESCENE_10};

enum TypeParticle {P_FOGO};


// Personagem
enum TypePersonagemSelecao {S_ARANHA, S_BESOURO, S_ESCORPIAO, S_LOUVADEUS, S_VESPA, S_COUNT};

enum TypeRaceChars {NONERACE, ALLRACE, ARANHA, BESOURO, ESCORPIAO, LOUVADEUS, VESPA, CUPIM, FORMIGA, BARBEIRO, BARATA, TATUBOLINHA, LIBELULA, PERCEVEJO, ABELHA, LAGARTIXA, CALANGO, SAPO, JOANINHA, CAMALEAO};

enum TypeClassChars {NONECLASS, ALLCLASS, JOGADOR, SOLDADO, LIDER, VENDEDOR, MAE, FILHOTE};

enum TypeModelos {M_NONE, M_ARANHA_LIDER, M_ARANHA_JOGADOR, M_ARANHA_SOLDADO, M_ARANHA_VENDEDOR, M_ARANHA_MAE, M_ARANHA_FILHOTE, M_BESOURO_LIDER, M_BESOURO_JOGADOR, M_BESOURO_SOLDADO, M_BESOURO_VENDEDOR, M_BESOURO_MAE, M_BESOURO_FILHOTE, M_ESCORPIAO_LIDER, M_ESCORPIAO_JOGADOR, M_ESCORPIAO_SOLDADO, M_ESCORPIAO_VENDEDOR, M_ESCORPIAO_MAE, M_ESCORPIAO_FILHOTE, M_LOUVADEUS_LIDER, M_LOUVADEUS_JOGADOR, M_LOUVADEUS_SOLDADO, M_LOUVADEUS_VENDEDOR, M_LOUVADEUS_MAE, M_LOUVADEUS_FILHOTE, M_VESPA_LIDER, M_VESPA_JOGADOR, M_VESPA_SOLDADO, M_VESPA_VENDEDOR, M_VESPA_MAE, M_VESPA_FILHOTE, M_CUPIM, M_FORMIGA, M_BARBEIRO, M_BARATA, M_TATUBOLINHA, M_LIBELULA, M_PERCEVEJO, M_ABELHA, M_LAGARTIXA, M_CALANGO, M_SAPO, M_JOANINHA, M_CAMALEAO, M_TANDAN};
    

// Item
enum TypeItens {I_NONE, I_BUZINA, I_VARINHA, I_SOCO, I_BAZUCA, I_MARTELO_GUERRA, I_METRALHADORA, I_MARTELO_CONAN, I_KATANA, I_LANÇADOR_DARDOS, I_MACHADO, I_PALITO_FOSFORO, I_VASSOURA, I_PU_DAO, I_ESPINGARDA, I_MAMONA, I_ESTILINGUE, I_CARTOLA, I_TENIS, I_ELMO_HERCULES, I_ELMO_BARBARO, I_OCULOS_ESCUROS, I_GORRO, I_CHACHI, I_CHAPEU_PALHA, I_OCULOS_AVIADOR, I_MASCARA_GAS, I_PASSAPORTE, I_POLPA_FORMIGA, I_POLPA_CUPIM, I_POLPA_BARATA, I_POLPA_TATU, I_ASA_LIBELULA, I_PERFUME_PERCEVEJO, I_MEL_ABELHA, I_TESOURA_BARBEIRO, I_RABO_CALANGO, I_OVO_LAGARTIXA, I_LINGUA_SAPO, I_LINGUA_CAMALEAO};

enum TypeHuds { H_MINIMAPAON, H_MINIMAPAOFF, H_SEMENTE };

enum TypeDirecao {D_NONE, D_LEFT, D_SOUTH, D_DOWN, D_EAST, D_RIGHT, D_NORTH, D_UP, D_WEST};