#include <iostream>
#include <dreamMessage.h>
#include <dreamServer.h>

using namespace std;

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
	OPENED_BOLSA, //ID BOLSA, ITENS DA BOLSA -1 se não houver nada
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
	TRADE_OK, //FECHA A JANELA DE TROCA E ADICIONA OU RETIRA ITEM NO INVENTÁRIO
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
	CREATE_PERSONAGEM, //IDPESSOA, ID RACA, NOME
	PLAY, //ID PERSONAGEM
	SEND_POSITION, //ID PERSONAGEM, POSICAO X, POSICAO Z
	SEND_ESTADO, //IDPERSONAGEM, ESTADO
	SEND_ATACK, //ID PERSONAGEM, ID ALVO, ID ATAQUE, POSICAO X E POSICAO Z ALVO CHÃO //PODE SER PODER OU ATAQUE NORMAL
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

int main()
{
	char	dadosRec[1400];
	char	memoria[1400];
	char *	tipoMes;

	sockaddr from;

	dreamServer * _server = new dreamServer();
	_server->initialize("",8767);

	dreamMessage mes;
	mes.init(dadosRec,sizeof(dadosRec));

	int retorno = 0;

	system("cls");

	while(true)
	{
		cout<<"Teste do Cliente WarBugs\n";

		while(retorno = _server->getPacket(mes._data, &from) != 0)
		{
			mes.beginReading();

			int tipo = mes.readByte();


			switch(tipo)
			{
				case LOGIN_REQUEST: //LOGIN, SENHA
					{
						tipoMes = "LOGIN_REQUEST";
						break;
					}
				case REQUEST_PERSONAGENS:  //ID PESSOA
					{
						tipoMes = "REQUEST_PERSONAGENS";
						break;
					}
				case CREATE_PERSONAGEM: //ID RACA, NOME
					{
						tipoMes = "CREATE_PERSONAGEM";
						break;
					}
				case PLAY: //ID PERSONAGEM
					{
						tipoMes = "PLAY";
						break;
					}
				case SEND_POSITION: //ID PERSONAGEM, POSICAO X, POSICAO Z
					{
						tipoMes = "SEND_POSITION";
						break;
					}
				case SEND_ESTADO: //IDPERSONAGEM, ESTADO
					{
						tipoMes = "SEND_ESTADO";
						break;
					}
				case SEND_ATACK: //ID PERSONAGEM, ID ALVO, ID ATAQUE, POSICAO X E POSICAO Z ALVO CHÃO //PODE SER PODER OU ATAQUE NORMAL
					{
						tipoMes = "SEND_ATACK";
						break;
					}
				case SEND_ITEM:  //ID PERSONAGEM, ID ITEM, DINHEIRO
					{
						tipoMes = "SEND_ITEM";
						break;
					}
				case USE_ITEM: //IDPERSONAGEM, IDITEM
					{
						tipoMes = "USE_ITEM";
						break;
					}
				case DROP_ITEM: //IDPERSONAGEM, IDITEM
					{
						tipoMes = "DROP_ITEM";
						break;
					}
				case ACCEPT_TRADE: //ID PERSONAGEM, ID FREGUES, ID ITEM MEU, DINHEIRO MEU, ID ITEM FREGUES, DINHEIRO FREGUES
					{
						tipoMes = "ACCEPT_TRADE";
						break;
					}
				case OPEN_BOLSA: //ID PERSONAGEM, ID BOLSA
					{
						tipoMes = "OPEN_BOLSA";
						break;
					}
				case CLOSE_BOLSA: //ID BOLSA
					{
						tipoMes = "CLOSE_BOLSA";
						break;
					}
				case GET_ITEM_BOLSA: //ID PERSONAGEM, ID BOLSA, ID ITEM
					{
						tipoMes = "GET_ITEM_BOLSA";
						break;
					}
				case INSERT_ITEM_BOLSA: //ID BOLSA, ID ITEM
					{
						tipoMes = "INSERT_ITEM_BOLSA";
						break;
					}
				case TRADE_CANCEL: //ID PERSONAGEM, ID FREGUES
					{
						tipoMes = "TRADE_CANCEL";
						break;
					}
				case EQUIP_ITEM: //ID PERSONAGEM, ID ARMA, ID ARMADURA
					{
						tipoMes = "EQUIP_ITEM";
						break;
					}
				case SET_TARGET: //ID PERSONAGEM, ID ALVO
					{
						tipoMes = "SET_TARGET";
						break;
					}
				case START_TRADE: //ID PERSONAGEM, ID FREGUES
					{
						tipoMes = "START_TRADE";
						break;
					}
				case SEND_MESSAGE: //ID DESTINO, MENSAGEM
					{
						tipoMes = "SEND_MESSAGE";
						break;
					}
				case START_SHOT: //ID PERSONAGEM, ID ALVO, IDSHOT, POSICAO X E POSICAO Z INICIAL
					{
						tipoMes = "START_SHOT";
						break;
					}
				case REQUEST_FULL_STATUS: //ID PERSONAGEM
					{
						tipoMes = "REQUEST_FULL_STATUS";
						break;
					}
				case SEND_BONUS_POINTS: //ID PERSONAGEM,VETOR EM ORDEM ALFABETICA COM QTD PONTOS DA HABILIDADE PRIMARIA USADA E A QUANTIDADE DE PONTOS DE SKILL(PODER)[PODER1,PODER2,PODER3]
					{
						tipoMes = "SEND_BONUS_POINTS";
						break;
					}
				case ACCEPT_QUEST: // ID PERSONAGEM, ID QUEST
					{
						tipoMes = "ACCEPT_QUEST";
						break;
					}
				case START_SHOP: //ID PERSONAGEM, ID NPC VENDEDOR
					{
						tipoMes = "START_SHOP";
						break;
					}
				case BUY_ITEM: //IDPERSONAGEM, IDNPC VENDEDOR, ID ITEM
					{
						tipoMes = "BUY_ITEM";
						break;
					}
				case REQUEST_PRICE_ITEM: //ID PERSONAGEM, ID NPCVENDEDOR, ID ITEM
					{
						tipoMes = "REQUEST_PRICE_ITEM";
						break;
					}
				case SELL_ITEM: //IDPERSOANGEM, ID NPCVENDEDOR, ID ITEM, PRECO
					{
						tipoMes = "SELL_ITEM";
						break;
					}
			}

			strcpy(&memoria,mes._data);
		}	

		cout<<"\n"<<"Recebido do Client: "<<tipoMes<<" - "<<memoria;
		system("cls");
	}

}