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
#include <math.h>

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
const int NUM2DOBJS = 39;  // Número de objetos 2D no jogo
const int NUMMENUHUDS = 3; // Número de huds nos menus
const int NUMMUSICAS = 4;  // Número de músicas do jogo

// Irrlicht

const E_DRIVER_TYPE defDriver = EDT_OPENGL/*EDT_DIRECT3D9*/;
const dimension2d <s32> defDimension = dimension2d <s32>( 1024, 768 );
const u8 defBits = 32;
const bool defFullScreen = true;
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
enum TypeReturn 
{
	ERRO_CONTINUE, 
	ERRO_SAIR, 
	SUCESSO, 
	PING_REQUEST,
	FINAL_PACOTES
};

// Menu
enum TypeMenuID 
{
	MN_ABERTURA, 
	MN_LOGIN, 
	MN_SELECAOPERSONAGEM, 
	MN_CRIACAOPERSONAGEM, 
	MN_JOGO,
	MN_CREDITOS, 
	MN_COUNT, 
	MN_SAIDA, 
	MN_ERRO
};

enum TypeLoadStage 
{
	LS_PERSONAGENS, 
	LS_ITENS, 
	LS_TXPERSONAGENS, 
	LS_TXITENS, 
	LS_HUDITENS, 
	LS_HUDS, 
	LS_COUNT
};

enum TypeMenuFlag 
{
	HUDUPDATED, 
	OBJSELECTED, 
	INVENTARIOON, 
	CHATON, 
	STATUSON, 
	MAPAON, 
	TRADEON, 
	EQUIPON, 
	SHOPON, 
	BOLSAON, 
	ALERTON, 
	CONFIGON, 
	FLAG_COUNT
};

enum TypeFontSize 
{
	FONT_PEQUENA, 
	FONT_GRANDE, 
	FONT_COUNT
};

enum TypeMenuSCene 
{
	MC_LOGIN, 
	MC_SELECAO, 
	MC_CRIACAO, 
	MC_COUNT
};

enum TypeMenuMusic 
{
	MM_LOGIN, 
	MM_SELECAO, 
	MM_CRIACAO, 
	MM_JOGO, 
	MM_COUNT
};

enum TypeMenuSfx 
{
	MFX_BOTAO, 
	MFX_OPENWINDOW, 
	MFX_CLOSEWINDOW, 
	MFX_SLIDEBAR, 
	MFX_CASH, 
	MFX_PICKUP, 
	MFX_COUNT
};

enum TypeCutScene 
{
	CS_ABERTURA, 
	CS_CREDITOS, 
	CS_TRANSICAO, 
	CS_COUNT
};

enum TypeHudSkin 
{
	HS_NONE, 
	HS_PADRAO, 
	HS_ARANHA, 
	HS_BESOURO, 
	HS_ESCORPIAO, 
	HS_LOUVADEUS, 
	HS_VESPA, 
	HS_COUNT 
};


// Cenario
enum TypeMoon
{
	MOON_OBLIVION,
	MOON_TYPHOONA,
	MOON_MABILOG,
	MOON_ABGRUNDI,
	MOON_RESPLANDORA,
	MOON_SAMARA,
	MOON_COUNT
};

enum TypeTxScenes 
{
	TXCENA_0, 
	TXCENA_1, 
	TXCENA_2, 
	TXCENA_3, 
	TXCENA_4, 
	TXCENA_5, 
	TXCENA_6, 
	TXCENA_7, 
	TXCENA_BUMP, 
	TXCENA_COUNT
};

enum TypeGameScene 
{
	GAMESCENE_00, 
	GAMESCENE_01, 
	GAMESCENE_02, 
	GAMESCENE_03, 
	GAMESCENE_04, 
	GAMESCENE_05, 
	GAMESCENE_06, 
	GAMESCENE_07, 
	GAMESCENE_08, 
	GAMESCENE_09, 
	GAMESCENE_COUNT
};

enum TypeParticle 
{
	P_FOGO
};


// Personagem
enum TypePersonagemSelecao 
{
	S_ARANHA, 
	S_BESOURO, 
	S_ESCORPIAO, 
	S_LOUVADEUS, 
	S_VESPA, 
	S_COUNT
};

enum TypeRaceChars 
{
	NONERACE, 
	ALLRACE, 
	ARANHA, 
	BESOURO, 
	ESCORPIAO, 
	LOUVADEUS, 
	VESPA, 
	CUPIM, 
	FORMIGA, 
	BARBEIRO, 
	BARATA, 
	TATUBOLINHA, 
	LIBELULA, 
	PERCEVEJO, 
	ABELHA, 
	LAGARTIXA, 
	CALANGO, 
	SAPO, 
	JOANINHA, 
	CAMALEAO
};

enum TypeClassChars 
{
	NONECLASS, 
	ALLCLASS, 
	JOGADOR, 
	SOLDADO,
	LIDER, 
	VENDEDOR, 
	MAE, 
	FILHOTE
};

enum TypeModelos 
{
	M_NONE, 
	M_ARANHA_LIDER, 
	M_ARANHA_JOGADOR, 
	M_ARANHA_SOLDADO, 
	M_ARANHA_VENDEDOR, 
	M_ARANHA_MAE, 
	M_ARANHA_FILHOTE, 
	M_BESOURO_LIDER, 
	M_BESOURO_JOGADOR, 
	M_BESOURO_SOLDADO, 
	M_BESOURO_VENDEDOR, 
	M_BESOURO_MAE, 
	M_BESOURO_FILHOTE, 
	M_ESCORPIAO_LIDER, 
	M_ESCORPIAO_JOGADOR, 
	M_ESCORPIAO_SOLDADO, 
	M_ESCORPIAO_VENDEDOR, 
	M_ESCORPIAO_MAE, 
	M_ESCORPIAO_FILHOTE, 
	M_LOUVADEUS_LIDER, 
	M_LOUVADEUS_JOGADOR, 
	M_LOUVADEUS_SOLDADO, 
	M_LOUVADEUS_VENDEDOR, 
	M_LOUVADEUS_MAE, 
	M_LOUVADEUS_FILHOTE, 
	M_VESPA_LIDER, 
	M_VESPA_JOGADOR, 
	M_VESPA_SOLDADO, 
	M_VESPA_VENDEDOR, 
	M_VESPA_MAE, 
	M_VESPA_FILHOTE, 
	M_CUPIM, 
	M_FORMIGA, 
	M_BARBEIRO, 
	M_BARATA, 
	M_TATUBOLINHA, 
	M_LIBELULA, 
	M_PERCEVEJO, 
	M_ABELHA, 
	M_LAGARTIXA, 
	M_CALANGO, 
	M_SAPO, 
	M_JOANINHA, 
	M_CAMALEAO, 
	M_TANDAN
};

enum TypeBuff
{
	BUFF_NORMAL,
	BUFF_DESESPERO,
	BUFF_VENENO,
	BUFF_DADIVA,
	BUFF_BERSERKER,
	BUFF_STRIKE,
	BUFF_BACKSTAB,
	BUFF_LENTO,
	BUFF_PIERCESHOT,
	BUFF_STUN,
	BUFF_ATORDOADO,
	BUFF_ESCUDO,
	BUFF_CHI,
	BUFF_INVISIVEL,
	BUFF_MOON_TYPHOONA,
	BUFF_MOON_MABILOG,
	BUFF_MOON_ABGRUNDI,
	BUFF_MOON_RESPLANDORA,
	BUFF_MOON_SAMARA,
	BUFF_COUNT
};

// Item
enum TypeItens 
{
	I_NONE, 
	I_BUZINA, 
	I_VARINHA, 
	I_SOCO, 
	I_BAZUCA, 
	I_MARTELO_GUERRA, 
	I_METRALHADORA, 
	I_MARTELO_CONAN, 
	I_KATANA, 
	I_LANÇADOR_DARDOS, 
	I_MACHADO, 
	I_PALITO_FOSFORO, 
	I_VASSOURA, 
	I_PU_DAO, 
	I_ESPINGARDA, 
	I_MAMONA, 
	I_ESTILINGUE, 
	I_CARTOLA, 
	I_TENIS, 
	I_ELMO_HERCULES, 
	I_ELMO_BARBARO, 
	I_OCULOS_ESCUROS, 
	I_GORRO, 
	I_CHACHI, 
	I_CHAPEU_PALHA, 
	I_OCULOS_AVIADOR, 
	I_MASCARA_GAS, 
	I_PASSAPORTE, 
	I_POLPA_FORMIGA, 
	I_POLPA_CUPIM, 
	I_POLPA_BARATA, 
	I_POLPA_TATU, 
	I_ASA_LIBELULA, 
	I_PERFUME_PERCEVEJO, 
	I_MEL_ABELHA, 
	I_TESOURA_BARBEIRO, 
	I_RABO_CALANGO, 
	I_OVO_LAGARTIXA, 
	I_LINGUA_SAPO, 
	I_LINGUA_CAMALEAO
};

enum TypeBtnHuds 
{ 
	H_NONE, 
	H_BUZINA, 
	H_VARINHA, 
	H_SOCO, 
	H_BAZUCA, 
	H_MARTELO_GUERRA, 
	H_METRALHADORA, 
	H_MARTELO_CONAN, 
	H_KATANA, 
	H_LANÇADOR_DARDOS, 
	H_MACHADO, 
	H_PALITO_FOSFORO, 
	H_VASSOURA, 
	H_PU_DAO, 
	H_ESPINGARDA, 
	H_MAMONA, 
	H_ESTILINGUE, 
	H_CARTOLA, 
	H_TENIS, 
	H_ELMO_HERCULES, 
	H_ELMO_BARBARO, 
	H_OCULOS_ESCUROS, 
	H_GORRO, 
	H_CHACHI, 
	H_CHAPEU_PALHA, 
	H_OCULOS_AVIADOR, 
	H_MASCARA_GAS, 
	H_PASSAPORTE, 
	H_POLPA_FORMIGA, 
	H_POLPA_CUPIM, 
	H_POLPA_BARATA, 
	H_POLPA_TATU, 
	H_ASA_LIBELULA, 
	H_PERFUME_PERCEVEJO, 
	H_MEL_ABELHA, 
	H_TESOURA_BARBEIRO, 
	H_RABO_CALANGO, 
	H_OVO_LAGARTIXA, 
	H_LINGUA_SAPO, 
	H_LINGUA_CAMALEAO,
	H_CONECTAR,
	H_CRIAR,
	H_REMOVER,
	H_JOGAR,
	H_MEONMAP,
	H_LEFT,
	H_RIGHT,
	H_LEFT_MINI,
	H_RIGHT_MINI,
	H_DROP,
	H_COMPRAR,
	H_VENDER,
	H_ROLETA,
	H_CADEADO,
	H_EQUIP,
	H_MOLDURA,
	H_SEMENTE,
	H_MOON_HUD,
	H_MOON_NONE,
	H_MOON_ARANHA,
	H_MOON_BESOURO,
	H_MOON_ESCORPIAO,
	H_MOON_LOUVA,
	H_MOON_VESPA,
	H_CLOSE_WINDOW,
	H_INVENTARIO,
	H_TRADE,
	H_SHOP,
	H_ALERT,
	H_STATUS,
	H_CONFIG,
	H_EXIT,
	H_PEACEMODE,
	H_WARMODE,	
	H_QUEST_NONE,
	H_QUEST_OPENED,
	H_QUEST_CLOSED,
	H_ROLETA_MASK,
	H_FACE_NONE,
	H_FACE_ARANHA,
	H_FACE_BESOURO,
	H_FACE_ESCORPIAO,
	H_FACE_LOUVA,
	H_FACE_VESPA,
	H_FACE_BESOURO_LIDER,
	H_FACE_BESOURO_GUARDA,
	H_FACE_BESOURO_VENDEDOR,
	H_FACE_VESPA_LIDER,
	H_FACE_VESPA_GUARDA,
	H_FACE_VESPA_VENDEDOR,
	H_FACE_FORMIGA,
	H_FACE_CUPIM,
	H_FACE_SAPO,
	H_FACE_CAMALEAO,
	H_FACE_BARBEIRO,
	H_FACE_JOANINHA,
	H_FACE_CALANGO,
	H_FACE_LAGARTIXA,
	H_FACE_TANDAN,
	H_ROLETA_POWER1_ARANHA,
	H_ROLETA_POWER2_ARANHA,
	H_ROLETA_POWER3_ARANHA,
	H_ROLETA_POWER1_BESOURO,
	H_ROLETA_POWER2_BESOURO,
	H_ROLETA_POWER3_BESOURO,
	H_ROLETA_POWER1_ESCORPIAO,
	H_ROLETA_POWER2_ESCORPIAO,
	H_ROLETA_POWER3_ESCORPIAO,
	H_ROLETA_POWER1_LOUVA,
	H_ROLETA_POWER2_LOUVA,
	H_ROLETA_POWER3_LOUVA,
	H_ROLETA_POWER1_VESPA,
	H_ROLETA_POWER2_VESPA,
	H_ROLETA_POWER3_VESPA,
	H_ROLETA_POLPA_FORMIGA, 
	H_ROLETA_POLPA_CUPIM, 
	H_ROLETA_POLPA_BARATA, 
	H_ROLETA_POLPA_TATU,
	H_COUNT
};

enum TypeDirecao 
{
	D_LEFT, 
	D_SOUTH, 
	D_DOWN, 
	D_EAST, 
	D_RIGHT, 
	D_NORTH, 
	D_UP, 
	D_WEST
};

enum TypeAnimState
{
	PARADO,
	SAUDACAO,
	CORRENDO,
	ATAQUE1,
	ATAQUE2,
	ATAQUE3,
	ATAQUE4,
	PODER1,
	PODER2,
	PODER3,
	BUFF_BOM,
	BUFF_RUIM,
	APANHANDO, 
	MORRENDO
};