#ifndef _COMMOM_H
#define _COMMOM_H

/*
	Inclusão das classes de lógica do jogo
*/
#include "dreamSock.h"
#include "logica\CPersonagemJogador.cpp"
#include "CDataBase.h"
#include <vcclr.h>


/*
	Variaveis que serão comuns no cliente e servidor
**/

/*Identificador de Mensagens*/
/*Começa do Zero ta bom!*/
enum TYPE_MESSAGE 
{
	LOGIN,
	CREATE_PLAYER,
	SELECT_PLAYER,
	ENTER_CENARIO,
	MOVE_PLAYER,
	MESSAGE_TOALL,
	MESSAGE_TO_PLAYER,
	SELECT_TARGET,
	DESELECT_TARGET,
	DO_ATACK,
	DO_POWER,
	EQUIP_ITEM,
	USE_ITEM,
	TRADE_REQUEST,
	DO_TRADE_ITEM,
	PICK_ITEM,
	PLAYER_DIE,
	PLAYER_GET_DAMAGE,
	PLAYER_CONNECTED,
	PLAYER_EXIT,
	ADD_PLAYER,
	REMOVE_PLAYER,
	EXIT_CENARIO,
//FALHAS
	LOGIN_FAIL,
	CREATE_PLAYER_FAIL,
	SELECT_PLAYER_FAIL,
	CHAT
};

#define FRAMES_HISTORIC 64
#define PORT 30003

/*Transforma a porra do tipo string do windows em coisa de macho!*/
char * toChar(System::String^ str)
{
	char * target;

	pin_ptr<const wchar_t> wch = PtrToStringChars( str );

	int len = (( str->Length+1) * 2);

	target = new char[ len ];
				
	wcstombs( target, wch, len );

	return target;
}


#ifndef _CNETWORKPLAYER_
#define _CNETWORKPLAYER_
/*
	Estrutura comum no Cliente e Servidor para armazenamento dos players que estão jogando
*/
class CNetWorkPlayer
{
	/*
- Vetor de flags (estados, buffs?)
- Posição x,y
- ID da animação corrente
- ID da arma equipada
- ID da armadura equipada
- PV
- PM
- Nivel de experiência
- Nome
- ID
- ID do modelo3D
- Direção ( 0 a 359º)*/
public:
	bool			_buffs[5];

	int				_posX;	
	int				_posY;

	int				_idAnimation;
	int				_idModel;

	int				_idWeapon;
	int				_idArmor;

	int				_pv;
	int				_pm;
	int				_xp;

	char			* _nome;

	int				_direcao;

	int				_id;


	

	dreamClient     * _netPlayer;

	CNetWorkPlayer      * _next;

};

#endif  /*_CNETPLAYER_*/

#endif