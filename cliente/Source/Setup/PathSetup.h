#pragma once

#include "GameSetup.h"

//-----------------------------------------------------------------------------------------
// Caminhos de arquivos específicos

static c8 *pathMatrizSetup = "recursos/data/mtxall.dat";
static c8 *pathConfig = "recursos/data/config.dat";

static c8 *pathHudSkin[HS_COUNT] =
{
	"recursos/skins/guiskin0.cfg",
	"recursos/skins/guiskin0.cfg",
	"recursos/skins/guiskin0.cfg",
	"recursos/skins/guiskin0.cfg",
	"recursos/skins/guiskin0.cfg",
	"recursos/skins/guiskin0.cfg",
	"recursos/skins/guiskin0.cfg"
};

static c8 *pathArquivoCena[NUMMENUCENA] = 
{
	"recursos/cenas/login.irr",
	"recursos/cenas/selecao.irr",
	"recursos/cenas/criacao.irr" 
};

static c8 *pathCutScene[CS_COUNT] =
{
	"recursos/videos/abertura.wmv",
	"recursos/videos/creditos.wmv",
	"recursos/videos/logo.wmv"
};

static c8 *pathCenario[NUMCENARIOS] = 
{
	"recursos/cenas/jogo.irr",
	"recursos/cenas/jogo.irr",
	"recursos/cenas/jogo.irr",
	"recursos/cenas/jogo.irr",
	"recursos/cenas/jogo.irr",
	"recursos/cenas/jogo.irr",
	"recursos/cenas/jogo.irr",
	"recursos/cenas/jogo.irr",
	"recursos/cenas/jogo.irr",
	"recursos/cenas/jogo.irr",
};

static c8 *pathBackgroundSound[NUMMUSICAS] =
{
	"recursos/audio/bgsnd_login.ogg",
	"recursos/audio/bgsnd_selecao.ogg",
	"recursos/audio/bgsnd_criacao.ogg",
	"recursos/audio/bgsnd_jogo.ogg"
};

static c8 *pathFonts[NUMHUDFONTS] = 
{
	"recursos/fonts/mplus8.xml",
	"recursos/fonts/mplus12.xml" 
};

static c8 *pathParticleImage[NUMPARTICLETYPES] =
{
	"recursos/texturas/particulas/fire.bmp"
};
//-----------------------------------------------------------------------------------------
// Nomes de arquivos

static c8 *pathMtxCharsModels[NUMRACES][NUMCLASSES] =
{
// NONECLASS, ALLCLASS, JOGADOR, SOLDADO, LIDER, VENDEDOR, MAE, FILHOTE
{"", "", "", "", "", "", "", "" }, // NONERACE
{"", "", "", "", "", "", "", "" }, // ALLRACE
{"", "", "recursos/modelos/p3d_aranha_jogador.b3d", "recursos/modelos/p3d_aranha_soldado.b3d", "recursos/modelos/p3d_aranha_lider.b3d", "recursos/modelos/p3d_aranha_vendedor.b3d", "recursos/modelos/p3d_aranha_mae.b3d", "recursos/modelos/p3d_aranha_filhote.b3d"}, // ARANHA
{"", "", "recursos/modelos/p3d_besouro_jogador.b3d", "recursos/modelos/p3d_besouro_soldado.b3d",  "recursos/modelos/p3d_besouro_lider.b3d", "recursos/modelos/p3d_besouro_vendedor.b3d", "recursos/modelos/p3d_besouro_mae.b3d", "recursos/modelos/p3d_besouro_filhote.b3d"}, // BESOURO
{"", "", "recursos/modelos/p3d_escorpiao_jogador.b3d", "recursos/modelos/p3d_escorpiao_soldado.b3d", "recursos/modelos/p3d_escorpiao_lider.b3d", "recursos/modelos/p3d_escorpiao_vendedor.b3d", "recursos/modelos/p3d_escorpiao_mae.b3d", "recursos/modelos/p3d_escorpiao_filhote.b3d"},  // ESCORPIAO
{"", "", "recursos/modelos/p3d_louvadeus_jogador.b3d", "recursos/modelos/p3d_louvadeus_soldado.b3d", "recursos/modelos/p3d_louvadeus_lider.b3d", "recursos/modelos/p3d_louvadeus_vendedor.b3d", "recursos/modelos/p3d_louvadeus_mae.b3d", "recursos/modelos/p3d_louvadeus_filhote.b3d"},  // LOUVADEUS
{"", "", "recursos/modelos/p3d_vespa_jogador.b3d", "recursos/modelos/p3d_vespa_soldado.b3d", "recursos/modelos/p3d_vespa_lider.b3d", "recursos/modelos/p3d_vespa_vendedor.b3d", "recursos/modelos/p3d_vespa_mae.b3d", "recursos/modelos/p3d_vespa_filhote.b3d"}, // VESPA
{"", "", "", "recursos/modelos/p3d_cupim.b3d", "", "", "", ""}, // CUPIM
{"", "", "", "recursos/modelos/p3d_formiga.b3d", "recursos/modelos/p3d_tandan.b3d", "", "", ""}, // FORMIGA
{"", "", "", "recursos/modelos/p3d_barbeiro.b3d", "", "", "", ""}, // BARBEIRO
{"", "", "", "recursos/modelos/p3d_barata.b3d", "", "", "", ""}, // BARATA
{"", "", "", "recursos/modelos/p3d_tatubolinha.b3d", "", "", "", ""}, // TATU_BOLINHA
{"", "", "", "recursos/modelos/p3d_libelula.b3d", "", "", "", ""}, // LIBELULA
{"", "", "", "recursos/modelos/p3d_percevejo.b3d", "", "", "", ""}, // PERCEVEJO
{"", "", "", "recursos/modelos/p3d_abelha.b3d", "", "", "", ""}, // ABELHA
{"", "", "", "recursos/modelos/p3d_lagartixa.b3d", "", "", "", ""}, // LAGARTIXA
{"", "", "", "recursos/modelos/p3d_calango.b3d", "", "", "", ""}, // CALANGO
{"", "", "", "recursos/modelos/p3d_sapo.b3d", "", "", "", ""}, // SAPO
{"", "", "", "recursos/modelos/p3d_joaninha.b3d", "", "", "", ""}, // JOANINHA
{"", "", "", "recursos/modelos/p3d_camaleao.b3d", "", "", "", ""} // CAMALEAO
};

static c8 *pathMtxCharsTextures[NUMRACES][NUMCLASSES] =
{
// NONECLASS, ALLCLASS, JOGADOR, SOLDADO, LIDER, VENDEDOR, MAE, FILHOTE
{"", "", "", "", "", "", "", "" }, // NONERACE
{"", "", "", "", "", "", "", "" }, // ALLRACE
{"", "", "recursos/modelos/tx3d_aranha_jogador.png", "recursos/modelos/tx3d_aranha_soldado.png", "recursos/modelos/tx3d_aranha_lider.png", "recursos/modelos/tx3d_aranha_vendedor.png", "recursos/modelos/tx3d_aranha_mae.png", "recursos/modelos/tx3d_aranha_filhote.png"}, // ARANHA
{"", "", "recursos/modelos/tx3d_besouro_jogador.png", "recursos/modelos/tx3d_besouro_soldado.png",  "recursos/modelos/tx3d_besouro_lider.png", "recursos/modelos/tx3d_besouro_vendedor.png", "recursos/modelos/tx3d_besouro_mae.png", "recursos/modelos/tx3d_besouro_filhote.png"}, // BESOURO
{"", "", "recursos/modelos/tx3d_escorpiao_jogador.png", "recursos/modelos/tx3d_escorpiao_soldado.png", "recursos/modelos/tx3d_escorpiao_lider.png", "recursos/modelos/tx3d_escorpiao_vendedor.png", "recursos/modelos/tx3d_escorpiao_mae.png", "recursos/modelos/tx3d_escorpiao_filhote.png"},  // ESCORPIAO
{"", "", "recursos/modelos/tx3d_louvadeus_jogador.png", "recursos/modelos/tx3d_louvadeus_soldado.png", "recursos/modelos/tx3d_louvadeus_lider.png", "recursos/modelos/tx3d_louvadeus_vendedor.png", "recursos/modelos/tx3d_louvadeus_mae.png", "recursos/modelos/tx3d_louvadeus_filhote.png"},  // LOUVADEUS
{"", "", "recursos/modelos/tx3d_vespa_jogador.png", "recursos/modelos/tx3d_vespa_soldado.png", "recursos/modelos/tx3d_vespa_lider.png", "recursos/modelos/tx3d_vespa_vendedor.png", "recursos/modelos/tx3d_vespa_mae.png", "recursos/modelos/tx3d_vespa_filhote.png"}, // VESPA
{"", "", "", "recursos/modelos/tx3d_cupim.png", "", "", "", ""}, // CUPIM
{"", "", "", "recursos/modelos/tx3d_formiga.png", "recursos/modelos/tx3d_tandan.png", "", "", ""}, // FORMIGA
{"", "", "", "recursos/modelos/tx3d_barbeiro.png", "", "", "", ""}, // BARBEIRO
{"", "", "", "recursos/modelos/tx3d_barata.png", "", "", "", ""}, // BARATA
{"", "", "", "recursos/modelos/tx3d_tatubolinha.png", "", "", "", ""}, // TATU_BOLINHA
{"", "", "", "recursos/modelos/tx3d_libelula.png", "", "", "", ""}, // LIBELULA
{"", "", "", "recursos/modelos/tx3d_percevejo.png", "", "", "", ""}, // PERCEVEJO
{"", "", "", "recursos/modelos/tx3d_abelha.png", "", "", "", ""}, // ABELHA
{"", "", "", "recursos/modelos/tx3d_lagartixa.png", "", "", "", ""}, // LAGARTIXA
{"", "", "", "recursos/modelos/tx3d_calango.png", "", "", "", ""}, // CALANGO
{"", "", "", "recursos/modelos/tx3d_sapo.png", "", "", "", ""}, // SAPO
{"", "", "", "recursos/modelos/tx3d_joaninha.png", "", "", "", ""}, // JOANINHA
{"", "", "", "recursos/modelos/tx3d_camaleao.png", "", "", "", ""} // CAMALEAO
};

static c8 *pathCharsModels[NUM3DPERS]=
{ // Modelos 3D de todos os personagens do jogo
	"recursos/modelos/p3d_aranha_lider.b3d", 
	"recursos/modelos/p3d_aranha_jogador.b3d", 
	"recursos/modelos/p3d_aranha_soldado.b3d", 
	"recursos/modelos/p3d_aranha_vendedor.b3d", 
	"recursos/modelos/p3d_aranha_mae.b3d", 
	"recursos/modelos/p3d_aranha_filhote.b3d", 
	"recursos/modelos/p3d_besouro_lider.b3d", 
	"recursos/modelos/p3d_besouro_jogador.b3d", 
	"recursos/modelos/p3d_besouro_soldado.b3d", 
	"recursos/modelos/p3d_besouro_vendedor.b3d", 
	"recursos/modelos/p3d_besouro_mae.b3d", 
	"recursos/modelos/p3d_besouro_filhote.b3d", 
	"recursos/modelos/p3d_escorpiao_lider.b3d", 
	"recursos/modelos/p3d_escorpiao_jogador.b3d", 
	"recursos/modelos/p3d_escorpiao_soldado.b3d", 
	"recursos/modelos/p3d_escorpiao_vendedor.b3d", 
	"recursos/modelos/p3d_escorpiao_mae.b3d", 
	"recursos/modelos/p3d_escorpiao_filhote.b3d", 
	"recursos/modelos/p3d_louvadeus_lider.b3d", 
	"recursos/modelos/p3d_louvadeus_jogador.b3d", 
	"recursos/modelos/p3d_louvadeus_soldado.b3d", 
	"recursos/modelos/p3d_louvadeus_vendedor.b3d", 
	"recursos/modelos/p3d_louvadeus_mae.b3d", 
	"recursos/modelos/p3d_louvadeus_filhote.b3d", 
	"recursos/modelos/p3d_vespa_lider.b3d", 
	"recursos/modelos/p3d_vespa_jogador.b3d", 
	"recursos/modelos/p3d_vespa_soldado.b3d", 
	"recursos/modelos/p3d_vespa_vendedor.b3d", 
	"recursos/modelos/p3d_vespa_mae.b3d", 
	"recursos/modelos/p3d_vespa_filhote.b3d", 
	"recursos/modelos/p3d_cupim.b3d", 
	"recursos/modelos/p3d_formiga.b3d", 
	"recursos/modelos/p3d_barbeiro.b3d", 
	"recursos/modelos/p3d_barata.b3d", 
	"recursos/modelos/p3d_tatubolinha.b3d", 
	"recursos/modelos/p3d_libelula.b3d", 
	"recursos/modelos/p3d_percevejo.b3d", 
	"recursos/modelos/p3d_abelha.b3d", 
	"recursos/modelos/p3d_lagartixa.b3d", 
	"recursos/modelos/p3d_calango.b3d", 
	"recursos/modelos/p3d_sapo.b3d", 
	"recursos/modelos/p3d_joaninha.b3d", 
	"recursos/modelos/p3d_camaleao.b3d", 
	"recursos/modelos/p3d_tandan.b3d" 
};

static c8 *pathTextureModels[NUM3DPERS]=
{ // Texturas de todos os personagens 3D do jogo
	"recursos/texturas/tx3d_aranha_lider.png", 
	"recursos/texturas/tx3d_aranha_jogador.png", 
	"recursos/texturas/tx3d_aranha_soldado.png", 
	"recursos/texturas/tx3d_aranha_vendedor.png", 
	"recursos/texturas/tx3d_aranha_mae.png", 
	"recursos/texturas/tx3d_aranha_filhote.png", 
	"recursos/texturas/tx3d_besouro_lider.png", 
	"recursos/texturas/tx3d_besouro_jogador.png", 
	"recursos/texturas/tx3d_besouro_soldado.png", 
	"recursos/texturas/tx3d_besouro_vendedor.png", 
	"recursos/texturas/tx3d_besouro_mae.png", 
	"recursos/texturas/tx3d_besouro_filhote.png", 
	"recursos/texturas/tx3d_escorpiao_lider.png", 
	"recursos/texturas/tx3d_escorpiao_jogador.png", 
	"recursos/texturas/tx3d_escorpiao_soldado.png", 
	"recursos/texturas/tx3d_escorpiao_vendedor.png", 
	"recursos/texturas/tx3d_escorpiao_mae.png", 
	"recursos/texturas/tx3d_escorpiao_filhote.png", 
	"recursos/texturas/tx3d_louvadeus_lider.png", 
	"recursos/texturas/tx3d_louvadeus_jogador.png", 
	"recursos/texturas/tx3d_louvadeus_soldado.png", 
	"recursos/texturas/tx3d_louvadeus_vendedor.png", 
	"recursos/texturas/tx3d_louvadeus_mae.png", 
	"recursos/texturas/tx3d_louvadeus_filhote.png", 
	"recursos/texturas/tx3d_vespa_lider.png", 
	"recursos/texturas/tx3d_vespa_jogador.png", 
	"recursos/texturas/tx3d_vespa_soldado.png", 
	"recursos/texturas/tx3d_vespa_vendedor.png", 
	"recursos/texturas/tx3d_vespa_mae.png", 
	"recursos/texturas/tx3d_vespa_filhote.png", 
	"recursos/texturas/tx3d_cupim.png", 
	"recursos/texturas/tx3d_formiga.png", 
	"recursos/texturas/tx3d_barbeiro.png", 
	"recursos/texturas/tx3d_barata.png", 
	"recursos/texturas/tx3d_tatubolinha.png", 
	"recursos/texturas/tx3d_libelula.png", 
	"recursos/texturas/tx3d_percevejo.png", 
	"recursos/texturas/tx3d_abelha.png", 
	"recursos/texturas/tx3d_lagartixa.png", 
	"recursos/texturas/tx3d_calango.png", 
	"recursos/texturas/tx3d_sapo.png", 
	"recursos/texturas/tx3d_joaninha.png", 
	"recursos/texturas/tx3d_camaleao.png", 
	"recursos/texturas/tx3d_tandan.png" 
};

static c8 *pathItensModels[NUM3DITENS]=
{ // Modelos 3D de todos os itens do jogo
	"recursos/modelos/i3d_buzina.b3d",
	"recursos/modelos/i3d_varinha.b3d",
	"recursos/modelos/i3d_soco.b3d",
	"recursos/modelos/i3d_bazuca.b3d",
	"recursos/modelos/i3d_martelo_guerra.b3d",
	"recursos/modelos/i3d_metralhadora.b3d",
	"recursos/modelos/i3d_martelo_conan.b3d",
	"recursos/modelos/i3d_katana.b3d",
	"recursos/modelos/i3d_lançador_dardos.b3d",
	"recursos/modelos/i3d_machado.b3d",
	"recursos/modelos/i3d_palito_fosforo.b3d",
	"recursos/modelos/i3d_vassoura.b3d",
	"recursos/modelos/i3d_pu_dao.b3d",
	"recursos/modelos/i3d_espingarda.b3d",
	"recursos/modelos/i3d_mamona.b3d",
	"recursos/modelos/i3d_estilingue.b3d",
	"recursos/modelos/i3d_cartola.b3d",
	"recursos/modelos/i3d_tenis.b3d",
	"recursos/modelos/i3d_elmo_hercules.b3d",
	"recursos/modelos/i3d_elmo_barbaro.b3d",
	"recursos/modelos/i3d_oculos_escuros.b3d",
	"recursos/modelos/i3d_gorro.b3d",
	"recursos/modelos/i3d_cacetete.b3d",
	"recursos/modelos/i3d_chapeu_palha.b3d",
	"recursos/modelos/i3d_oculos_aviador.b3d",
	"recursos/modelos/i3d_mascara_gas.b3d" 
};

static c8 *pathTextureItens[NUM3DITENS]=
{ // Texturas de todos os itens 3d do jogo
	"recursos/texturas/tx3d_buzina.png",
	"recursos/texturas/tx3d_varinha.png",
	"recursos/texturas/tx3d_soco.png",
	"recursos/texturas/tx3d_bazuca.png",
	"recursos/texturas/tx3d_martelo_guerra.png",
	"recursos/texturas/tx3d_metralhadora.png",
	"recursos/texturas/tx3d_martelo_conan.png",
	"recursos/texturas/tx3d_katana.png",
	"recursos/texturas/tx3d_lançador_dardos.png",
	"recursos/texturas/tx3d_machado.png",
	"recursos/texturas/tx3d_palito_fosforo.png",
	"recursos/texturas/tx3d_vassoura.png",
	"recursos/texturas/tx3d_pu_dao.png",
	"recursos/texturas/tx3d_espingarda.png",
	"recursos/texturas/tx3d_mamona.png",
	"recursos/texturas/tx3d_estilingue.png",
	"recursos/texturas/tx3d_cartola.png",
	"recursos/texturas/tx3d_tenis.png",
	"recursos/texturas/tx3d_elmo_hercules.png",
	"recursos/texturas/tx3d_elmo_barbaro.png",
	"recursos/texturas/tx3d_oculos_escuros.png",
	"recursos/texturas/tx3d_gorro.png",
	"recursos/texturas/tx3d_cacetete.png",
	"recursos/texturas/tx3d_chapeu_palha.png",
	"recursos/texturas/tx3d_oculos_aviador.png",
	"recursos/texturas/tx3d_mascara_gas.png" 
};

static c8 *pathTexture2D[NUM2DOBJS]=
{ // Texturas de todos os objetos 2d do jogo
	"recursos/huds/tx2d_buzina.png",
	"recursos/huds/tx2d_varinha.png",
	"recursos/huds/tx2d_soco.png",
	"recursos/huds/tx2d_bazuca.png",
	"recursos/huds/tx2d_martelo_guerra.png",
	"recursos/huds/tx2d_metralhadora.png",
	"recursos/huds/tx2d_martelo_conan.png",
	"recursos/huds/tx2d_katana.png",
	"recursos/huds/tx2d_lançador_dardos.png",
	"recursos/huds/tx2d_machado.png",
	"recursos/huds/tx2d_palito_fosforo.png",
	"recursos/huds/tx2d_vassoura.png",
	"recursos/huds/tx2d_pu_dao.png",
	"recursos/huds/tx2d_espingarda.png",
	"recursos/huds/tx2d_mamona.png",
	"recursos/huds/tx2d_estilingue.png",
	"recursos/huds/tx2d_cartola.png",
	"recursos/huds/tx2d_tenis.png",
	"recursos/huds/tx2d_elmo_hercules.png",
	"recursos/huds/tx2d_elmo_barbaro.png",
	"recursos/huds/tx2d_oculos_escuros.png",
	"recursos/huds/tx2d_gorro.png",
	"recursos/huds/tx2d_cacetete.png",
	"recursos/huds/tx2d_chapeu_palha.png",
	"recursos/huds/tx2d_oculos_aviador.png",
	"recursos/huds/tx2d_mascara_gas.png",
	"recursos/huds/tx2d_passaporte.png",
	"recursos/huds/tx2d_polpa_formiga.png",
	"recursos/huds/tx2d_polpa_cupim.png",
	"recursos/huds/tx2d_polpa_barata.png",
	"recursos/huds/tx2d_polpa_tatu.png",
	"recursos/huds/tx2d_asa_libelula.png",
	"recursos/huds/tx2d_perfume_percevejo.png",
	"recursos/huds/tx2d_pata_barbeiro.png",
	"recursos/huds/tx2d_rabo_calango.png",
	"recursos/huds/tx2d_ovo_lagartixa.png",
	"recursos/huds/tx2d_lingua_sapo.png",
	"recursos/huds/tx2d_lingua_camaleao.png" 
};

static c8 *pathTextureHud[NUMMENUHUDS]=
{ // Texturas de todos os huds dos menus
	"recursos/huds/tx2d_minimapa1on.png", 
	"recursos/huds/tx2d_minimapa1off.png", 
	"recursos/huds/tx2d_semente.png" 
};

static c8 *pathPropsModels[NUMPROPS]=
{ // Modelos 3d dos objetos estáticos do cenário
	"recursos/modelos/prop3d_arvore.3ds",
	"recursos/modelos/prop3d_arvore2.3ds",
	"recursos/modelos/prop3d_skydome.3ds",
	"recursos/modelos/prop3d_coluna.3ds",
	"recursos/modelos/prop3d_cactus.3ds"
};

static c8 *pathTextureProps[NUMPROPS]=
{ // Modelos 3d dos objetos estáticos do cenário
	"recursos/texturas/prop3d_arvore.png",
	"recursos/texturas/prop3d_arvore2.png",
	"recursos/texturas/prop3d_skydome.png",
	"recursos/texturas/prop3d_coluna.png",
	"recursos/texturas/prop3d_cactus.png"
};