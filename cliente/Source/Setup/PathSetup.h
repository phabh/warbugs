#pragma once

#include "Setup.h"
/*
//-----------------------------------------------------------------------------------------
// Caminhos de diretórios

static c8 *pathSfxs     = "recursos/audio/sfx/";
static c8 *pathHuds     = "recursos/huds/";
static c8 *pathFonts    = "recursos/fonts/";
static c8 *pathModels   = "recursos/modelos/";
static c8 *pathMusics   = "recursos/audio/";
static c8 *pathScenes   = "recursos/cenas/";
static c8 *pathShaders  = "recursos/shaders/";
static c8 *pathTextures = "recursos/texturas/";
static c8 *pathVideos   = "recursos/videos/";*/

//-----------------------------------------------------------------------------------------
// Caminhos de arquivos específicos

static c8 *pathMatrizSetup = "recursos/data/mtxadj.dat";
static c8 *pathConfig = "recursos/data/config.dat";

static c8 *pathVideoAbertura = "recursos/videos/abertura.wmv";
static c8 *pathVideoCreditos = "recursos/videos/creditos.wmv";

static c8 *pathArquivoCena[NUMMENUCENA] = {
"",
"recursos/cenas/login.irr",
"recursos/cenas/selecao.irr",
"recursos/cenas/criacao.irr" };

//-----------------------------------------------------------------------------------------
// Nomes de arquivos

static c8 *modelCharFile[NUM3DPERS]={ // Modelos 3D de todos os personagens do jogo
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
"recursos/modelos/p3d_tandan.b3d" };

static c8 *textureCharFile[NUM3DPERS]={ // Texturas de todos os personagens 3D do jogo
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
"recursos/texturas/tx3d_tandan.png" };

static c8 *modelItemFile[NUM3DITENS]={ // Modelos 3D de todos os itens do jogo
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
"recursos/modelos/i3d_mascara_gas.b3d" };

static c8 *textureItemFile[NUM3DITENS]={ // Texturas de todos os itens 3d do jogo
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
"recursos/texturas/tx3d_mascara_gas.png" };

static c8 *texture2DFile[NUM2DOBJS]={ // Texturas de todos os objetos 2d do jogo
"recursos/texturas/huds/tx2d_buzina.png",
"recursos/texturas/huds/tx2d_varinha.png",
"recursos/texturas/huds/tx2d_soco.png",
"recursos/texturas/huds/tx2d_bazuca.png",
"recursos/texturas/huds/tx2d_martelo_guerra.png",
"recursos/texturas/huds/tx2d_metralhadora.png",
"recursos/texturas/huds/tx2d_martelo_conan.png",
"recursos/texturas/huds/tx2d_katana.png",
"recursos/texturas/huds/tx2d_lançador_dardos.png",
"recursos/texturas/huds/tx2d_machado.png",
"recursos/texturas/huds/tx2d_palito_fosforo.png",
"recursos/texturas/huds/tx2d_vassoura.png",
"recursos/texturas/huds/tx2d_pu_dao.png",
"recursos/texturas/huds/tx2d_espingarda.png",
"recursos/texturas/huds/tx2d_mamona.png",
"recursos/texturas/huds/tx2d_estilingue.png",
"recursos/texturas/huds/tx2d_cartola.png",
"recursos/texturas/huds/tx2d_tenis.png",
"recursos/texturas/huds/tx2d_elmo_hercules.png",
"recursos/texturas/huds/tx2d_elmo_barbaro.png",
"recursos/texturas/huds/tx2d_oculos_escuros.png",
"recursos/texturas/huds/tx2d_gorro.png",
"recursos/texturas/huds/tx2d_cacetete.png",
"recursos/texturas/huds/tx2d_chapeu_palha.png",
"recursos/texturas/huds/tx2d_oculos_aviador.png",
"recursos/texturas/huds/tx2d_mascara_gas.png",
"recursos/texturas/huds/tx2d_passaporte.png",
"recursos/texturas/huds/tx2d_polpa_formiga.png",
"recursos/texturas/huds/tx2d_polpa_cupim.png",
"recursos/texturas/huds/tx2d_polpa_barata.png",
"recursos/texturas/huds/tx2d_polpa_tatu.png",
"recursos/texturas/huds/tx2d_asa_libelula.png",
"recursos/texturas/huds/tx2d_perfume_percevejo.png",
"recursos/texturas/huds/tx2d_pata_barbeiro.png",
"recursos/texturas/huds/tx2d_rabo_calango.png",
"recursos/texturas/huds/tx2d_ovo_lagartixa.png",
"recursos/texturas/huds/tx2d_lingua_sapo.png",
"recursos/texturas/huds/tx2d_lingua_camaleao.png" };

static c8 *textureHudFile[NUMMENUHUDS]={ // Texturas de todos os huds dos menus
"recursos/texturas/huds/tx2d_minimapa1on.png", 
"recursos/texturas/huds/tx2d_minimapa1off.png", 
"recursos/texturas/huds/tx2d_semente.png" };