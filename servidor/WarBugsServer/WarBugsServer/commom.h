#ifndef _COMMOM_H
#define _COMMOM_H

/*
	Inclus�o das classes de l�gica do jogo
*/
#include <dreamSock.h>
#include <dreamServer.h>
#include <dreamClient.h>
#include <dreamMessage.h>
#include <CPersonagemJogador.h>
#include <CJogador.h>
#include <CCenario.h>
#include <CTimer.cpp>
#include <CInimigo.h>
#include <CHabilidadesSecundarias.h>
#include "CDataBase.h"
#include <vcclr.h>


/*
	Variaveis que ser�o comuns no cliente e servidor
**/


/* Para Funcionar o Log no server*/
ref class WarBugsLog
{
public:
	static  System::Windows::Forms::ListBox^ _log;
};



/*Identificador de Mensagens*/
enum TYPE_MESSAGE 
{
	//MENSAGENS RECEBIDAS
	LOGIN = 33,
	SHOW_PERSONAGENS, //QTD PERSONAGENS QUE O JOGADOR POSSUI, E OS PERSONAGENS
	ENTER_CENARIO,//id cenario, POSICAO X, POSICAO Z
	MOVE_PLAYER, //id jogador, POSICAO X, POSICAO Z
	ADD_PERSONAGEM, //atributos do outros persoangens NPC, Jogadores
	ADD_BOLSA,//id bolsa, POSICAO X, POSICAO Z, estado bolsa
	OPENED_BOLSA, //ID BOLSA, ITENS DA BOLSA -1 se n�o houver nada
	CLOSED_BOLSA, //ID BOLSA
	CHANGE_BUFFS, //ID BUFF, ESTADO
	SET_ESTADO, //ID PERSONAGEM, ESTADO, ULTIMO ESTADO
	SHOW_DAMAGE, //ID PERSONAGEM , DANO
	RECEIVE_ITEM, //id do item, qtd dinheiro
	REMOVE_ITEM,  //ID ITEM, QTD DINHEIRO
	PRICE_ITEM, //ID ITEM, PRECO
	CHANGE_MONEY, //quantidade
	TRADE_REQUEST, //ID JOGADOR ABRE A JANELA DE TROCA
	SHOW_TRADE_ITEM, //ID ITEM, QTD DINEHIRO, ID JOGADOR
	TRADE_OK, //FECHA A JANELA DE TROCA E ADICIONA OU RETIRA ITEM NO INVENT�RIO
	TRADE_CANCELED,//FECHA A JANELA DE TROCA 
	CHANGE_BONUS, //HABILIDADES PRIMARIAS E SECUNDARIAS DO JOGADOR EM ORDEM ALFABETICA
	UPDATE_PVPPNIVEL,  //ID PERSONAGEM, PONTOS VIDA, PONTOS PODER, NIVEL, PP_MAX, PV_MAX
	UPDATE_EQUIP, //ID PERSONAGEM, ID ARMA, ID ARMADURA
	UPDATE_DIRVEL, //ID PERSONAGEM, DIRECAO, VELOCIDADE
	ADD_QUEST, //ID QUEST, QUANTIDADE DE ITENS QUE TENHO QUE OBTER
	UPDATE_QUEST, //ID QUEST, QUANTIDADE QUE CONSEGUI, QUANTIDADE DE ITENS QUE TENHO QUE OBTER
	QUEST_OK, //IDQUEST, PARABENS
	CHAT, // MENSAGEM
	UPDATE_BOLSA, // ATUALIZA BOLSA DO PERSONAGEM 9 IDS
	SHOW_SHOP, //ID ITENS[30], PRECO [30]
	UPDATE_XP, //XP, XP_MAX
	SHOT, //IDSHOT, POSICAO X E POSICAO Z INICIAL, E ID ALVO
	REMOVE_PERSONAGEM, //ID PERSONAGEM
	UPDATE_LEVEL,//NIVEL, QTD PONTOS DISTRIBUIR HABILIDADES PRIMARIAS, QTD PONTOS SKILL(PODER)

	//ENVIADAS
	LOGIN_REQUEST, //LOGIN, SENHA
	REQUEST_PERSONAGENS, //ID PESSOA
	CREATE_PERSONAGEM, //ID RACA, NOME
	PLAY, //ID PERSONAGEM
	SEND_POSITION, //ID PERSONAGEM, POSICAO X, POSICAO Z
	SEND_ESTADO, //IDPERSONAGEM, ESTADO
	SEND_ATACK, //ID PERSONAGEM, ID ALVO, ID ATAQUE, POSICAO X E POSICAO Z ALVO CH�O //PODE SER PODER OU ATAQUE NORMAL
	SEND_ITEM,  //ID PERSONAGEM, ID ITEM, DINHEIRO
	USE_ITEM, //IDPERSONAGEM, IDITEM
	DROP_ITEM, //IDPERSONAGEM, IDITEM
	ACCEPT_TRADE, //ID PERSONAGEM, ID FREGUES, ID ITEM MEU, DINHEIRO MEU, ID ITEM FREGUES, DINHEIRO FREGUES
	OPEN_BOLSA, //ID PERSONAGEM, ID BOLSA
	CLOSE_BOLSA, //ID BOLSA
	GET_ITEM_BOLSA, //ID PERSONAGEM, ID BOLSA, ID ITEM
	INSERT_ITEM_BOLSA, //ID BOLSA, ID ITEM
	TRADE_CANCEL, //ID PERSONAGEM, ID FREGUES
	EQUIP_ITEM, //ID PERSONAGEM, ID ARMA, ID ARMADURA
	SET_TARGET, //ID PERSONAGEM, ID ALVO
	START_TRADE, //ID PERSONAGEM, ID FREGUES
	SEND_MESSAGE, //ID DESTINO, MENSAGEM
	START_SHOT, //ID PERSONAGEM, ID ALVO, IDSHOT, POSICAO X E POSICAO Z INICIAL
	REQUEST_FULL_STATUS, //ID PERSONAGEM
	SEND_BONUS_POINTS, //ID PERSONAGEM,VETOR EM ORDEM ALFABETICA COM QTD PONTOS DA HABILIDADE PRIMARIA USADA E A QUANTIDADE DE PONTOS DE SKILL(PODER)[PODER1,PODER2,PODER3]
	ACCEPT_QUEST, // ID PERSONAGEM, ID QUEST
	START_SHOP, //ID PERSONAGEM, ID NPC VENDEDOR
	BUY_ITEM, //IDPERSONAGEM, IDNPC VENDEDOR, ID ITEM
	REQUEST_PRICE_ITEM, //ID PERSONAGEM, ID NPCVENDEDOR, ID ITEM
	SELL_ITEM, //IDPERSOANGEM, ID NPCVENDEDOR, ID ITEM, PRECO
	UPDATE_ALL, //ATUALIZA O PERSONAGEM COMPLETO

//FALHAS
	LOGIN_FAIL,
	CREATE_PLAYER_FAIL,
	SELECT_PLAYER_FAIL
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


#endif