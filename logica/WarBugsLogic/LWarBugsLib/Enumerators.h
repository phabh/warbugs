#pragma once
#ifndef _ENUMS
#define _ENUMS
// ------------------------------------------------------------------------------------------------------------
//Enumerador para retornar o tipo da classe
enum TipoClasse	
{
	COBJECT,
	C3DOBJECT,
	CLOGICOBJECT,
	CDOUBLELIST,
	CITEM,
	CCONSUMABLEITEM,
	CWEAPON,
	CARMOR,
	CSCROLL,
	CATRIBUTO,
	CHABILIDADES,
	CHABILIDADESSECUNDARIAS,
	CLEALDADE
};
// ------------------------------------------------------------------------------------------------------------
//Enumerador para retornar a raça do personagem
enum Raca 
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
// ------------------------------------------------------------------------------------------------------------
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
// ------------------------------------------------------------------------------------------------------------
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
// ------------------------------------------------------------------------------------------------------------
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
	I_LANCADOR_DARDOS, 
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
// ------------------------------------------------------------------------------------------------------------
//#ifndef _SATRIB
//#define _SATRIB
enum Atrib 
{
	NENHUM, 
	PV, 
	PM, 
	FOR, 
	DES, 
	AGI, 
	RES, 
	INS, 
	ATTACKMELEE, 
	ATTACKRANGED, 
	DAMAGEMELEE, 
	DAMAGERANGED, 
	DEFESA
};
//#endif
// ------------------------------------------------------------------------------------------------------------
enum TipoBuff
{
	NORMAL, 
	DESESPERO, 
	VENENO, 
	DADIVA, 
	BERSERKER, 
	STRIKE, 
	BACKSTAB, 
	LENTO, 
	STUN, 
	ATORDOADO
};
// ------------------------------------------------------------------------------------------------------------
enum EstadoItem
{
	NAMOCHILA, 
	NOCHAO, 
	EQUIPADO, 
	USADO
};
// ------------------------------------------------------------------------------------------------------------
enum TipoItem
{
	USO, 
	ARMA, 
	ARMADURA, 
	QUEST, 
	SCROLL, 
	LSCROLL
};
// ------------------------------------------------------------------------------------------------------------
enum EstadoPersonagem
{
	E_PARADO,
	E_ANDANDO,
	E_ARIETE,
	E_BERSERK,
	E_STRIKE,
	E_MORTO,
	E_FALANDO
};
// ------------------------------------------------------------------------------------------------------------
enum Direcoes 
{
	NORTE, 
	SUL, 
	LESTE, 
	OESTE
};
// ------------------------------------------------------------------------------------------------------------
enum TipoPoder 
{
	SK_BERSERK_TORNADO, 
	SK_ARIETE, 
	SK_STRIKE,
	SK_STEAL,
	SK_BREAK,
	SK_STINK_GAS,
	SK_LIGHT_SPEED,
	SK_ATOMIC_EXPLOSION
};
// ------------------------------------------------------------------------------------------------------------
enum QuestState
{
	Q_CLOSED,
	Q_OPEN,
	Q_FINISHED
};
// ------------------------------------------------------------------------------------------------------------

/*DEFINES*/
#ifndef MAXSTATS
#define MAXSTATS 5
#endif
// ------------------------------------------------------------------------------------------------------------
#define FPS 30
// ------------------------------------------------------------------------------------------------------------
#define MAXFRIENDS 10
// ------------------------------------------------------------------------------------------------------------
#define MAXPARTYSIZE 4
// ------------------------------------------------------------------------------------------------------------
#ifndef MAXSTATS
#define MAXSTATS 5
#endif
// ------------------------------------------------------------------------------------------------------------
#define MAXITENS 9
#define MAXITEMTYPES 40
// ------------------------------------------------------------------------------------------------------------
#define MAXSKILLNUMBER 3
// ------------------------------------------------------------------------------------------------------------
#define ENEMYRESPAWNTIME FPS * 10
// ------------------------------------------------------------------------------------------------------------
#define QUADRANTESIZE 10
// ------------------------------------------------------------------------------------------------------------
#define BASEXPVALUE 100
#define XPREDUCTIONFACTOR 2
// ------------------------------------------------------------------------------------------------------------
//Struct pra listas
template<class A>
struct SCelula
{
	A *valor;
	SCelula *prev;
	SCelula *next;
};
// ------------------------------------------------------------------------------------------------------------
struct Ponto
{
	float x;
	float z;

	Ponto()
	{
		x = 0.0f;
		z = 0.0f;
	}
	Ponto(float x, float z)
	{
		this->x = x;
		this->z = z;
	}
};
// ------------------------------------------------------------------------------------------------------------
#endif