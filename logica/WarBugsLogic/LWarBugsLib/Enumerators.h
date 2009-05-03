#pragma once
#ifndef _ENUMS
#define _ENUMS
// ------------------------------------------------------------------------------------------------------------
//Enumerador para retornar o tipo da classe
enum TipoClasse{
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
enum Raca {NENHUMA, BESOURO, ARANHA, LOUVADEUS, ESCORPIAO, VESPA, TODAS};
// ------------------------------------------------------------------------------------------------------------
//#ifndef _SATRIB
//#define _SATRIB
enum Atrib {NENHUM, PV, PM, FOR, DES, AGI, RES, INS, ATTACKMELEE, ATTACKRANGED, DAMAGEMELEE, DAMAGERANGED, DEFESA};
//#endif
// ------------------------------------------------------------------------------------------------------------
enum TipoBuff{NORMAL, DESESPERO, VENENO, DADIVA, BERSERKER, STRIKE, BACKSTAB, LENTO, STUN, ATORDOADO};
// ------------------------------------------------------------------------------------------------------------
enum EstadoItem{NAMOCHILA, NOCHAO, EQUIPADO, USADO};
// ------------------------------------------------------------------------------------------------------------
enum TipoItem{USO, ARMA, ARMADURA, QUEST, SCROLL, LSCROLL};
// ------------------------------------------------------------------------------------------------------------
enum EstadoPersonagem{
	PARADO,
	ANDANDO
};
// ------------------------------------------------------------------------------------------------------------
enum Direcoes {NORTE, SUL, LESTE, OESTE};
// ------------------------------------------------------------------------------------------------------------
enum TipoPoder {SK_BERSERK_TORNADO, SK_ARIETE, SK_STRIKE};
// ------------------------------------------------------------------------------------------------------------
/*DEFINES*/
#ifndef MAXSTATS
#define MAXSTATS 5
#endif
// ------------------------------------------------------------------------------------------------------------
#define FPS 8
// ------------------------------------------------------------------------------------------------------------
#define MAXFRIENDS 10
// ------------------------------------------------------------------------------------------------------------
#define MAXPARTYSIZE 4
// ------------------------------------------------------------------------------------------------------------
#ifndef MAXSTATS
#define MAXSTATS 5
#endif
// ------------------------------------------------------------------------------------------------------------
#define MAXITENS 10
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
	int x;
	int y;
};
// ------------------------------------------------------------------------------------------------------------
#endif