#ifndef _COMMOM_H
#define _COMMOM_H

/*
	Variaveis que ser�o comuns no cliente e servidor
**/

#ifndef _WARBUGS_LOG_
#define _WARBUGS_LOG_


/* Para Funcionar o Log no server*/
ref class WarBugsLog
{
public:
	static  System::Windows::Forms::ListBox^ _log;
};


#endif

/*Identificador de Mensagens*/
enum TYPE_MESSAGE 
{
	DISCONNECT = 0,
	PING,
	END_FRAME,
	//MENSAGENS RECEBIDAS
	LOGIN_OK = 33, // se o login foi OK
	LOGIN_FAIL, //se o login falhou por algum motivo
	SHOW_PERSONAGENS, //QTD PERSONAGENS QUE O JOGADOR POSSUI, E OS PERSONAGENS
	CREATE_PLAYER_OK, //o player foi criado com sucesso
	CREATE_PLAYER_FAIL, //n�o foi poss�vel criar o player
	DELETE_PLAYER_OK,	
	DELETE_PLAYER_FAIL,
	PLAY_FAIL,
	ENTER_CENARIO,//id cenario, POSICAO X, POSICAO Z, qtd Inimigos, qtdNPC, qtdVendedores, qtdPersonagensJogadores, qtdBolsa
	ADD_PERSONAGEM, //atributos do outros persoangens NPC, Jogadores
	ADD_BOLSA,//id bolsa, POSICAO X, POSICAO Z, estado bolsa
	UPDATE_POSITION, //ID PERSONAGEM, POSICAO X, POSICAO Z
	UPDATE_ESTADO, //IDPERSONAGEM, ESTADO
	UPDATE_ATACK, //ID PERSONAGEM, ID ALVO, ID ATAQUE
	OPENED_BOLSA, //ID BOLSA, ITENS DA BOLSA -1 se n�o houver nada
	CLOSED_BOLSA, //ID BOLSA
	UPDATE_EQUIP, //ID PERSONAGEM, ID ARMA, ID ARMADURA
	SHOW_DAMAGE, //ID PERSONAGEM , DANO
	CHAT, // MENSAGEM
	REMOVE_ITEM,  //ID ITEM, QTD DINHEIRO
	ADD_ITEM, //id do item, qtd dinheiro
	PRICE_ITEM, //ID ITEM, PRECO
	CHANGE_BUFFS, //ID BUFF, ESTADO
	CHANGE_MONEY, //quantidade
	CHANGE_BONUS, //HABILIDADES PRIMARIAS E SECUNDARIAS DO JOGADOR EM ORDEM ALFABETICA
	UPDATE_PVPPNIVEL,  //ID PERSONAGEM, PONTOS VIDA, PONTOS PODER, NIVEL, PP_MAX, PV_MAX
	UPDATE_DIRVEL, //ID PERSONAGEM, DIRECAO, VELOCIDADE
	ADD_QUEST, //ID QUEST, QUANTIDADE DE ITENS QUE TENHO QUE OBTER
	UPDATE_QUEST, //ID QUEST, QUANTIDADE QUE CONSEGUI, QUANTIDADE DE ITENS QUE TENHO QUE OBTER
	QUEST_OK, //IDQUEST, PARABENS
	UPDATE_BOLSA, // ATUALIZA BOLSA DO PERSONAGEM 9 IDS
	SHOW_SHOP, //ID ITENS[30], PRECO [30]
	UPDATE_XP, //XP, XP_MAX
	SHOT, //IDSHOT, POSICAO X E POSICAO Z INICIAL, E ID ALVO
	REMOVE_PERSONAGEM, //ID PERSONAGEM
	UPDATE_LEVEL,//NIVEL, QTD PONTOS DISTRIBUIR HABILIDADES PRIMARIAS, QTD PONTOS SKILL(PODER)
	REMOVE_BOLSA, // ID BOLSA

	//ENVIADAS
	LOGIN_REQUEST, //LOGIN, SENHA
	PERSONAGENS_REQUEST, //ID PESSOA
	CREATE_PERSONAGEM, //ID RACA, NOME
	DELETE_PERSONAGEM,
	PLAY, //ID PERSONAGEM
	SEND_POSITION, //ID PERSONAGEM, POSICAO X, POSICAO Z
	SEND_ESTADO, //IDPERSONAGEM, ESTADO
	SEND_ATACK, //ID PERSONAGEM, ID ALVO, ID ATAQUE, POSICAO X E POSICAO Z ALVO CH�O //PODE SER PODER OU ATAQUE NORMAL
	OPEN_BOLSA, //ID PERSONAGEM, ID BOLSA
	CLOSE_BOLSA, //ID BOLSA
	SEND_EQUIP, //ID PERSONAGEM, ID ARMA, ID ARMADURA
	SEND_TARGET, //ID PERSONAGEM, ID ALVO
	USE_ITEM, //IDPERSONAGEM, IDITEM
	DROP_ITEM, //IDPERSONAGEM, IDITEM
	SEND_MESSAGE, //ID PERSONAGEMDESTINO, MENSAGEM
	SEND_ITEM,  //ID PERSONAGEM, ID ITEM, DINHEIRO
	GET_ITEM_BOLSA, //ID PERSONAGEM, ID BOLSA, ID ITEM
	INSERT_ITEM_BOLSA, //ID BOLSA, ID ITEM
	START_SHOT, //ID PERSONAGEM, ID ALVO, IDSHOT, POSICAO X E POSICAO Z INICIAL
	REQUEST_FULL_STATUS, //ID PERSONAGEM
	SEND_BONUS_POINTS, //ID PERSONAGEM,VETOR EM ORDEM ALFABETICA COM QTD PONTOS DA HABILIDADE PRIMARIA USADA E A QUANTIDADE DE PONTOS DE SKILL(PODER)[PODER1,PODER2,PODER3]
	ACCEPT_QUEST, // ID PERSONAGEM, ID QUEST
	START_SHOP, //ID PERSONAGEM, ID NPC VENDEDOR
	BUY_ITEM, //IDPERSONAGEM, IDNPC VENDEDOR, ID ITEM
	REQUEST_PRICE_ITEM, //ID PERSONAGEM, ID NPCVENDEDOR, ID ITEM
	SELL_ITEM, //IDPERSOANGEM, ID NPCVENDEDOR, ID ITEM, PRECO
	TRADE_REQUEST, //ID PERSONAGEM, ID FREGUES
	TRADE_REQUEST_ACCEPTED, //ID PERSONAGEM, ID FREGUES
	TRADE_REQUEST_REFUSED, //ID PERSONAGEM, ID FREGUES
	TRADE_CHANGED, //ID PERSONAGEM, ID FREGUES, idItemPersonagem, idItemFregues, qtdDinheiroPersonagem, qtdDinheiroFregues
	TRADE_ACCEPTED, //ID PERSONAGEM
	TRADE_REFUSED, //ID PERSONAGEM, ID FREGUES
	TRADE_CONCLUDE //ID PERSONAGEM, ID FREGUES
};

#define PORT 30003
#define NUMCONNECTIONS 54
#define NUMPERSONAGEMJOGADOR 2

#endif