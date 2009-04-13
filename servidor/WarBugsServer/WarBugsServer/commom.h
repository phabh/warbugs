#ifndef _COMMOM_H
#define _COMMOM_H

/*
	Inclusão das classes de lógica do jogo
*/
#include "dreamSock.h"
#include "logica\CPersonagemJogador.cpp"


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
	EXIT_CENARIO
};

#define FRAMES_HISTORIC 64
#define PORT 30003

/*
	Estrutura comum no Cliente e Servidor para armazenamento dos players que estão jogando
*/
struct CDataPlayer
{
	CPersonagemJogador   _frame[FRAMES_HISTORIC];
	dreamClient        * _netPlayer;
	CPersonagemJogador   _currentFrame;
	CPersonagemJogador   _lastFrame;

	int					 _index;

	CDataPlayer        * _next;
} CDataPlayer;
#endif