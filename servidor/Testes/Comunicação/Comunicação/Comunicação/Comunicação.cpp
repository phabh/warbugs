// Comunicação.cpp : Defines the entry point for the console application.
//

#include <dreamMessage.h>
#include <dreamClient.h>

dreamClient * _networkClient;

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
	CREATE_PERSONAGEM, //ID RACA, NOME
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

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}


/*
	LOGIN
	ler pacotes vindos do servidor na parte de login
*/
void lerPacotes()
{
	char data[1400];
	sockaddr from;

	dreamMessage mesRec;
	mesRec.init(data,sizeof(data));

	int retorno;

	while(retorno = _networkClient->getPacket(mesRec._data, &from) != 0)
	{
		mesRec.beginReading();
		
		int tipoMesssage = mesRec.readByte();

		switch(tipoMessage)
		{
			case LOGIN:
				{
					/*
						OK Logado
						Muda para a tela de seleção de personagens
					*/
					break;
				}

			case LOGIN_FAIL:
				{
					/*
						FALHA no login
						aparece a mensagem e volta para a tela de login
					*/
				}
		
		
		}//fim switch

	}//fim while


}

/*
	SELECAO DE PERSONAGENS
	ler pacotes vindos do servidor na parte de selecao de personagens
*/
void lerPacotes()
{
	char data[1400];
	sockaddr from;

	dreamMessage mesRec;
	mesRec.init(data,sizeof(data));

	int retorno;

	while(retorno = _networkClient->getPacket(mesRec._data, &from) != 0)
	{
		mesRec.beginReading();
		
		int tipoMesssage = mesRec.readByte();

		switch(tipoMessage)
		{
			case SHOW_PERSONAGENS:
				{
					/*
						quantidade de personagens a selecionar
						personagens selecionaveis
					*/
					int qtdPersonagens = mesRec.readLong();

					if(qtdPersoangens > 0)
					{
						for(int i = 0; i < qtdPersonagens; i++)
						{
							//Monta os objetos dos personagens a selecionar						
						}						
					}
					break;
				}

			case SELECT_PLAYER_FAIL:
				{
					_networkClient->sendDisconnect();
					/*
						Houve uma falha no servidor
						manda uma messagem de desconexão
						aparece a mensagem e volta para a tela de login
					*/
				}
		
		
		}//fim switch

	}//fim while


}

/*
	CRIA PLAYER
	ler pacotes vindos do servidor na parte de criacao de personagens
*/
void lerPacotes()
{
	char data[1400];
	sockaddr from;

	dreamMessage mesRec;
	mesRec.init(data,sizeof(data));

	int retorno;

	while(retorno = _networkClient->getPacket(mesRec._data, &from) != 0)
	{
		mesRec.beginReading();
		
		int tipoMesssage = mesRec.readByte();

		switch(tipoMessage)
		{
			case CREATE_PLAYER:
				{
					/*
						manda os personagens base das 5 raças para que o jogador
						possa escolher
					*/

					//quantidade raças
					int qtdRacas = mesRec.readLong();

					if(qtdRacas > 0)
					{
						for(int i = 0; i < qtdRacas; i++)
						{
							//Monta os objetos dos personagens criaveis
						}						
					}
					break;
				}

			case CREATE_PLAYER_FAIL:
				{
					_networkClient->sendDisconnect();
					/*
						Houve uma falha no servidor
						manda uma messagem de desconexão
						aparece a mensagem e volta para a tela de login
					*/
				}
		
		
		}//fim switch

	}//fim while


}

/*
	JOGO
	ler pacotes vindos do servidor na parte de JOGO
*/
void lerPacotes()
{
	char data[1400];
	sockaddr from;

	dreamMessage mesRec;
	mesRec.init(data,sizeof(data));

	int retorno;

	while(retorno = _networkClient->getPacket(mesRec._data, &from) != 0)
	{
		mesRec.beginReading();
		
		int tipoMesssage = mesRec.readByte();

		switch(tipoMessage)
		{
			//MENSAGENS RECEBIDAS
			case ENTER_CENARIO://id cenario, minha posicao
				{
					mesRec.beginReading();
					mesRec.readByte();

					int   idCenario = mesRec.readLong();
					float posX      = mesRec.readFloat();
					float posZ      = mesRec.readFloat();

					break;
				}
			case MOVE_PLAYER: //id jogador, posicao absoluta
				{
					mesRec.beginReading();
					mesRec.readByte();

					int   idPersonagem = mesRec.readLong();
					float posX         = mesRec.readFloat();
					float posZ         = mesRec.readFloat();

					break;
				}
			case ADD_PERSONAGEM: //atributos do outros persoangens NPC, Jogadores
				{
					mesRec.beginReading();
					mesRec.readByte();

					int     idPersonagem   = mesRec.readLong();
					char *  nomePersonagem = mesRec.readString();
					float   posX           = mesRec.readFloat();
					float   posZ           = mesRec.readFloat();
					int     pontosVida     = mesRec.readLong();
					int     pontosPoder    = mesRec.readLong();
					int     nivel          = mesRec.readLong();
					int     pvMax          = mesRec.readLong();
					int     ppMax          = mesRec.readLong();

					short   buff           = mesRec.readShort();

					bool    buffer[15];

					for(int i = 0; i < 14; i--)
					{
						buffer[i] = (bool)buff & pow(2,i);
					}

					int     estado         = mesRec.readLong();
					int     raca           = mesRec.readLong();
					int     tipoPersonagem = mesRec.readLong();
					int     idArma         = mesRec.readLong();
					int     idArmadura     = mesRec.readLong();
					float   direcao        = mesRec.readFloat();
					float   velocidade     = mesRec.readFloat();

					break;
				}
			case ADD_BOLSA://id bolsa, posicao absoluta, estado bolsa
				{
					mesRec.beginReading();
					mesRec.readByte();

					int     idBolsa        = mesRec.readLong();
					float   posX           = mesRec.readFloat();
					float   posZ           = mesRec.readFloat();
					int     estadoBolsa    = mesRec.readLong();

					break;
				}
			case OPENED_BOLSA: //ID BOLSA, ITENS DA BOLSA
				{
					mesRec.beginReading();
					mesRec.readByte();

					int     idBolsa        = mesRec.readLong();
					
					int     itensBolsa[9];

					for(int i = 0; i < 9; i++)
					{
						itensBolsa[i]	   = mesRec.readLong();
					}

					break;
				}
			case CLOSED_BOLSA: //ID BOLSA
				{
					mesRec.beginReading();
					mesRec.readByte();

					int     idBolsa        = mesRec.readLong();


					break;
				}
			case CHANGE_BUFFS: //ID BUFF, ESTADO
				{
					mesRec.beginReading();
					mesRec.readByte();

					int     idBuff        = mesRec.readLong();
					int     estado        = mesRec.readLong();

					break;
				}
			case SET_ESTADO: //ID PERSONAGEM, ESTADO, ULTIMO ESTADO
				{
					mesRec.beginReading();
					mesRec.readByte();

					int     idPersonagem  = mesRec.readLong();
					int     estado		  = mesRec.readLong();
					int     ultimoEstado  = mesRec.readLong();

					break;
				}
			case SHOW_DAMAGE: //ID PERSONAGEM , DANO
				{
					mesRec.beginReading();
					mesRec.readByte();

					int     idPersonagem  = mesRec.readLong();
					int     dano		  = mesRec.readLong();

					break;
				}
			case RECEIVE_ITEM: //id do item, qtd dinheiro
				{
					mesRec.beginReading();
					mesRec.readByte();

					int     idItem	          = mesRec.readLong();
					int     qtdDinheiro		  = mesRec.readLong();

					break;
				}
			case REMOVE_ITEM:  //ID ITEM, QTD DINHEIRO
				{
					mesRec.beginReading();
					mesRec.readByte();

					int     idItem	          = mesRec.readLong();
					int     qtdDinheiro		  = mesRec.readLong();

					break;
				}
			case PRICE_ITEM: //ID ITEM, PRECO
				{
					mesRec.beginReading();
					mesRec.readByte();

					int     idItem	          = mesRec.readLong();
					int     preco			  = mesRec.readLong();

					break;
				}
			case CHANGE_MONEY: //quantidade
				{
					mesRec.beginReading();
					mesRec.readByte();

					int     qtdDinheiro		  = mesRec.readLong();

					break;
				}
			case TRADE_REQUEST: //ID JOGADOR ABRE A JANELA DE TROCA
				{
					mesRec.beginReading();
					mesRec.readByte();

					int     idPersonagem      = mesRec.readLong();

					break;
				}
			case SHOW_TRADE_ITEM: //ID ITEM, QTD DINEHIRO, ID JOGADOR
				{
					mesRec.beginReading();
					mesRec.readByte();

					int     idItem	          = mesRec.readLong();
					int     qtdDinheiro		  = mesRec.readLong();
					int     idPersonagem      = mesRec.readLong();

					break;
				}
			case TRADE_OK: //FECHA A JANELA DE TROCA E ADICIONA OU RETIRA ITEM NO INVENTÁRIO
				{
					mesRec.beginReading();
					mesRec.readByte();

					break;
				}
			case TRADE_CANCELED://FECHA A JANELA DE TROCA 
				{
					mesRec.beginReading();
					mesRec.readByte();

					break;
				}
			case CHANGE_BONUS: //HABILIDADES PRIMARIAS E SECUNDARIAS DO JOGADOR
				{
					mesRec.beginReading();
					mesRec.readByte();

					int     agilidade    = mesRec.readLong();
					int     destreza     = mesRec.readLong();
					int     forca        = mesRec.readLong();
					int     instinto     = mesRec.readLong();
					int     resistencia  = mesRec.readLong();

					int		alcance      = mesRec.readLong();
					int		ataque       = mesRec.readLong();
					int		defesa       = mesRec.readLong();
					int		taxaAtaque   = mesRec.readLong();
					

					break;
				}
			case UPDATE_PVPPNIVEL:  //ID PERSONAGEM, PONTOS VIDA, PONTOS PODER, NIVEL, PP_MAX, PV_MAX
				{
					mesRec.beginReading();
					mesRec.readByte();

					int     idPersonagem = mesRec.readLong();
					int     pontosVida   = mesRec.readLong();
					int     pontosPoder  = mesRec.readLong();
					int     nivel        = mesRec.readLong();
					int     pv_max       = mesRec.readLong();
					int     pp_max       = mesRec.readLong();

					break;
				}
			case UPDATE_EQUIP: //ID PERSONAGEM, ID ARMA, ID ARMADURA
				{
					mesRec.beginReading();
					mesRec.readByte();

					int     idPersonagem = mesRec.readLong();
					int     pontosVida   = mesRec.readLong();
					int     pontosPoder  = mesRec.readLong();

					break;
				}
			case UPDATE_DIRVEL: //ID PERSONAGEM, DIRECAO, VELOCIDADE
				{
					mesRec.beginReading();
					mesRec.readByte();

					int     idPersonagem = mesRec.readLong();
					float   direcao      = mesRec.readFloat();
					float   velocidade   = mesRec.readFloat();

					break;
				}
			case ADD_QUEST: //ID QUEST, QUANTIDADE DE ITENS QUE TENHO QUE OBTER
				{
					mesRec.beginReading();
					mesRec.readByte();

					int     idQuest         = mesRec.readLong();
					int     qtdTotalItens   = mesRec.readLong();

					break;
				}
			case UPDATE_QUEST: //ID QUEST, QUANTIDADE QUE CONSEGUI, QUANTIDADE DE ITENS QUE TENHO QUE OBTER
				{
					mesRec.beginReading();
					mesRec.readByte();

					int     idQuest       = mesRec.readLong();
					int     qtdAtualItens = mesRec.readLong();
					int     qtdTotal      = mesRec.readLong();

					break;
				}
			case QUEST_OK: //IDQUEST, PARABENS
				{
					mesRec.beginReading();
					mesRec.readByte();

					int     idQuest       = mesRec.readLong();

					break;
				}
			case CHAT: // MENSAGEM
				{
					mesRec.beginReading();
					mesRec.readByte();

					char *  mensagem_chat = mesRec.readString();

					break;
				}
			case UPDATE_BOLSA: // ATUALIZA BOLSA DO PERSONAGEM 9 IDS
				{
					mesRec.beginReading();
					mesRec.readByte();

					int itensBolsa[9];

					for(int i = 0; i < 9; i++)
					{
						itensBolsa[i] = mesRec.readLong();
					}

					break;
				}
			case SHOW_SHOP: //ID ITENS[30], PRECO [30]
				{
					mesRec.beginReading();
					mesRec.readByte();

					int itensVendedor[30];
					int precoItens[30];

					for(int i = 0; i < 2; i++)
					{
						for(int j = 0; j < 30; j++)						
						{
							if(i == 0)
							{
								itensVendedor[j] = mesRec.readLong();
							}
							else
							if(i == 1)
							{
								precoItens[j]   = mesRec.readLong();
							}
						}
					}
					
					break;
				}
			case UPDATE_XP: //XP, XP_MAX
				{
					mesRec.beginReading();
					mesRec.readByte();

					int xp = mesRec.readLong();
					int xp_Max = mesRec.readLong();

					break;
				}
			case SHOT: //IDSHOT, POSICAO INICIAL, E ID ALVO
				{
					mesRec.beginReading();
					mesRec.readByte();

					int   idShot = mesRec.readLong();
					float posX   = mesRec.readFloat();
					float posZ   = mesRec.readFloat();
					int   idAlvo = mesRec.readLong();

					break;
				}
			case REMOVE_PERSONAGEM: //ID PERSONAGEM
				{
					mesRec.beginReading();
					mesRec.readByte();

					int idPersonagem = mesRec.readLong();

					break;
				}
			case UPDATE_LEVEL: //NIVEL, QTD PONTOS DISTRIBUIR HABILIDADES PRIMARIAS, QTD PONTOS SKILL(PODER)			
				{
					mesRec.beginReading();
					mesRec.readByte();

					int nivel				= mesRec.readLong();
					int qtdPontosPrimarias	= mesRec.readLong();
					int qtdPontosPoder		= mesRec.readLong();

					break;
				}
		
		}//fim switch

	}//fim while
}




/*

	FUNÇÕES DO CLIENTE

*/
	void sendMessage(dreamMessage * mes)
	{
		_networkClient->sendPacket(mes);
	}

	void sendMessage(int idMensagem, int i1)
	{
		char data[1400];

		dreamMessage mes;
		mes.init(data,sizeof(data));

		mes.writeByte(idMensagem);

		mes.writeLong(i1);

		sendMessage(&mes);
	}


	void sendMessage(int idMensagem, int i1, int i2)
	{
		char data[1400];

		dreamMessage mes;
		mes.init(data,sizeof(data));

		mes.writeByte(idMensagem);

		mes.writeLong(i1);
		mes.writeLong(i2);

		sendMessage(&mes);	
	
	}
	void sendMessage(int idMensagem, int i1, int i2, int i3)
	{
		char data[1400];

		dreamMessage mes;
		mes.init(data,sizeof(data));

		mes.writeByte(idMensagem);

		mes.writeLong(i1);
		mes.writeLong(i2);
		mes.writeLong(i3);

		sendMessage(&mes);
	}

	void sendMessage(int idMensagem, int i1, int i2, int i3, int i4)
	{
		char data[1400];

		dreamMessage mes;
		mes.init(data,sizeof(data));

		mes.writeByte(idMensagem);

		mes.writeLong(i1);
		mes.writeLong(i2);
		mes.writeLong(i3);
		mes.writeLong(i4);

		sendMessage(&mes);
	}

	void sendMessage(int idMensagem, int i1, int i2, int i3, int i4, int i5, int i6)
	{
		char data[1400];

		dreamMessage mes;
		mes.init(data,sizeof(data));

		mes.writeByte(idMensagem);

		mes.writeLong(i1);
		mes.writeLong(i2);
		mes.writeLong(i3);
		mes.writeLong(i4);
		mes.writeLong(i5);
		mes.writeLong(i6);

		sendMessage(&mes);
	}

	void sendMessage(int idMensagem, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9)
	{
		char data[1400];

		dreamMessage mes;
		mes.init(data,sizeof(data));

		mes.writeByte(idMensagem);

		mes.writeLong(i1);
		mes.writeLong(i2);
		mes.writeLong(i3);
		mes.writeLong(i4);
		mes.writeLong(i5);
		mes.writeLong(i6);
		mes.writeLong(i7);
		mes.writeLong(i8);
		mes.writeLong(i9);

		sendMessage(&mes);
	}

	void sendMessage(int idMensagem, int i1, char * s1)
	{
		char data[1400];

		dreamMessage mes;
		mes.init(data,sizeof(data));

		mes.writeByte(idMensagem);

		mes.writeLong(i1);
		mes.writeString(s1);

		sendMessage(&mes);
	}

	void sendMessage(int idMensagem, int i1, float f1, float f2)
	{
		char data[1400];

		dreamMessage mes;
		mes.init(data,sizeof(data));

		mes.writeByte(idMensagem);

		mes.writeLong(i1);
		mes.writeFloat(f1);
		mes.writeFloat(f2);

		sendMessage(&mes);
	}

	void sendMessage(int idMensagem, int i1, int i2, int i3, float f1, float f2)
	{
		char data[1400];

		dreamMessage mes;
		mes.init(data,sizeof(data));

		mes.writeByte(idMensagem);

		mes.writeLong(i1);
		mes.writeLong(i2);
		mes.writeLong(i3);
		mes.writeFloat(f1);
		mes.writeFloat(f2);


		sendMessage(&mes);
	}

	void sendMessage(int idMensagem, char * s1, char * s2)
	{
		char data[1400];

		dreamMessage mes;
		mes.init(data,sizeof(data));

		mes.writeByte(idMensagem);

		mes.writeString(s1);
		mes.writeString(s2);

		sendMessage(&mes);
	}


