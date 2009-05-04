#include "CCoreServer.h"
#include "CDataManager.h"

CCoreServer::CCoreServer(CDataBase *db, int fps)
{
	if(db != NULL)
		return;

	_db = db;

	//seta os fps dos servidor
	_fps = fps;

	System::String^ texto = L"Inicializando o Server...";
	WarBugsLog::_log->Items->Add(texto);
	initialize();
}


void CCoreServer::initialize(){}

void CCoreServer::initializeNetwork()
{
	
	_networkServer = new dreamServer();

	_networkServer->initialize("",PORT);

}


void CCoreServer::readPackets()
{
	char data[1400];

	dreamMessage mesRecebida;
	mesRecebida.init(data,sizeof(data));

	sockaddr     player;

	int tipoMensagem;

	int retorno;

	while(retorno = _networkServer->getPacket(mesRecebida._data, &player) != 0)
	{
		mesRecebida.beginReading();

		tipoMensagem = mesRecebida.readByte();	
		

		switch(tipoMensagem)
		{
		
				case LOGIN_REQUEST: //LOGIN, SENHA
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						char * login = mesRecebida.readString();
						char * senha = mesRecebida.readString();
						
						//para saber para quem enviar a mensagem de volta, dentro da classe de jogador possui essa variavel
						sockaddr enderecoIPJogador = player;

						break;
					}
				case REQUEST_PERSONAGENS:  //ID PESSOA
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int idJogador = mesRecebida.readLong();
						
						//para saber para quem enviar a mensagem de volta, dentro da classe de jogador possui essa variavel
						sockaddr enderecoIPJogador = player;

						break;
					}
				case CREATE_PERSONAGEM: //ID RACA, NOME
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idRaca = mesRecebida.readLong();
						char * nome   = mesRecebida.readString();
						
						//para saber para quem enviar a mensagem de volta, dentro da classe de jogador possui essa variavel
						sockaddr enderecoIPJogador = player;

						break;
					}
				case PLAY: //ID PERSONAGEM
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem = mesRecebida.readLong();		

						//para saber para quem enviar a mensagem de volta, dentro da classe de jogador possui essa variavel
						sockaddr enderecoIPJogador = player;

						break;
					}
				case SEND_POSITION: //ID PERSONAGEM, POSICAO X, POSICAO Z
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem = mesRecebida.readLong();
						float  posX = mesRecebida.readFloat();
						float  posZ = mesRecebida.readFloat();

						//para saber para quem enviar a mensagem de volta, dentro da classe de jogador possui essa variavel
						sockaddr enderecoIPJogador = player;

						break;
					}
				case SEND_ESTADO: //IDPERSONAGEM, ESTADO
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem = mesRecebida.readLong();
						int    estado       = mesRecebida.readLong();

						//para saber para quem enviar a mensagem de volta, dentro da classe de jogador possui essa variavel
						sockaddr enderecoIPJogador = player;

						break;
					}
				case SEND_ATACK: //ID PERSONAGEM, ID ALVO, ID ATAQUE, POSICAO X E POSICAO Z ALVO CHÃO //PODE SER PODER OU ATAQUE NORMAL
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem = mesRecebida.readLong();
						int    idAlvo       = mesRecebida.readLong();
						int    idAtaque     = mesRecebida.readLong();
						float  posX         = mesRecebida.readFloat();
						float  posZ         = mesRecebida.readFloat();

						//para saber para quem enviar a mensagem de volta, dentro da classe de jogador possui essa variavel
						sockaddr enderecoIPJogador = player;

						break;
					}
				case SEND_ITEM:  //ID PERSONAGEM, ID ITEM, DINHEIRO
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem = mesRecebida.readLong();
						int    idItem       = mesRecebida.readLong();
						int    dinheiro     = mesRecebida.readLong();

						//para saber para quem enviar a mensagem de volta, dentro da classe de jogador possui essa variavel
						sockaddr enderecoIPJogador = player;

						break;
					}
				case USE_ITEM: //IDPERSONAGEM, IDITEM
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem = mesRecebida.readLong();
						int    idItem       = mesRecebida.readLong();

						//para saber para quem enviar a mensagem de volta, dentro da classe de jogador possui essa variavel
						sockaddr enderecoIPJogador = player;

						break;
					}
				case DROP_ITEM: //IDPERSONAGEM, IDITEM
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem = mesRecebida.readLong();
						int    idItem       = mesRecebida.readLong();

						//para saber para quem enviar a mensagem de volta, dentro da classe de jogador possui essa variavel
						sockaddr enderecoIPJogador = player;

						break;
					}
				case ACCEPT_TRADE: //ID PERSONAGEM, ID FREGUES, ID ITEM MEU, DINHEIRO MEU, ID ITEM FREGUES, DINHEIRO FREGUES
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem			= mesRecebida.readLong();
						int    idFregues			= mesRecebida.readLong();
						int    idItemPersonagem		= mesRecebida.readLong();
						int    dinheiroPersonagem	= mesRecebida.readLong();
						int    idItemFregues		= mesRecebida.readLong();
						int    dinheiroFregues		= mesRecebida.readLong();

						//para saber para quem enviar a mensagem de volta, dentro da classe de jogador possui essa variavel
						sockaddr enderecoIPJogador = player;

						break;
					}
				case OPEN_BOLSA: //ID PERSONAGEM, ID BOLSA
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem	= mesRecebida.readLong();
						int    idBolsa		= mesRecebida.readLong();

						//para saber para quem enviar a mensagem de volta, dentro da classe de jogador possui essa variavel
						sockaddr enderecoIPJogador = player;

						break;
					}
				case CLOSE_BOLSA: //ID BOLSA
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idBolsa		= mesRecebida.readLong();

						//para saber para quem enviar a mensagem de volta, dentro da classe de jogador possui essa variavel
						sockaddr enderecoIPJogador = player;

						break;
					}
				case GET_ITEM_BOLSA: //ID PERSONAGEM, ID BOLSA, ID ITEM
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem	= mesRecebida.readLong();
						int    idBolsa		= mesRecebida.readLong();
						int    idItem		= mesRecebida.readLong();

						//para saber para quem enviar a mensagem de volta, dentro da classe de jogador possui essa variavel
						sockaddr enderecoIPJogador = player;

						break;
					}
				case INSERT_ITEM_BOLSA: //ID BOLSA, ID ITEM
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idBolsa		= mesRecebida.readLong();
						int    idItem		= mesRecebida.readLong();

						//para saber para quem enviar a mensagem de volta, dentro da classe de jogador possui essa variavel
						sockaddr enderecoIPJogador = player;

						break;
					}
				case TRADE_CANCEL: //ID PERSONAGEM, ID FREGUES
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem	= mesRecebida.readLong();
						int    idFregues	= mesRecebida.readLong();

						//para saber para quem enviar a mensagem de volta, dentro da classe de jogador possui essa variavel
						sockaddr enderecoIPJogador = player;

						break;
					}
				case EQUIP_ITEM: //ID PERSONAGEM, ID ARMA, ID ARMADURA
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem	= mesRecebida.readLong();
						int    idArma		= mesRecebida.readLong();
						int    idArmadura	= mesRecebida.readLong();

						//para saber para quem enviar a mensagem de volta, dentro da classe de jogador possui essa variavel
						sockaddr enderecoIPJogador = player;

						break;
					}
				case SET_TARGET: //ID PERSONAGEM, ID ALVO
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem	= mesRecebida.readLong();
						int    idAlvo		= mesRecebida.readLong();

						//para saber para quem enviar a mensagem de volta, dentro da classe de jogador possui essa variavel
						sockaddr enderecoIPJogador = player;

						break;
					}
				case START_TRADE: //ID PERSONAGEM, ID FREGUES
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem	= mesRecebida.readLong();
						int    idFregues	= mesRecebida.readLong();

						//para saber para quem enviar a mensagem de volta, dentro da classe de jogador possui essa variavel
						sockaddr enderecoIPJogador = player;

						break;
					}
				case SEND_MESSAGE: //ID DESTINO, MENSAGEM
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						//-1 para todos
						int    idPersonagem	= mesRecebida.readLong();
						char * mensagem     = mesRecebida.readString();

						//para saber para quem enviar a mensagem de volta, dentro da classe de jogador possui essa variavel
						sockaddr enderecoIPJogador = player;

						break;
					}
				case START_SHOT: //ID PERSONAGEM, ID ALVO, IDSHOT, POSICAO X E POSICAO Z INICIAL
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem	= mesRecebida.readLong();
						int    idAlvo		= mesRecebida.readLong();
						int    idShot		= mesRecebida.readLong();
						float  posX			= mesRecebida.readFloat();
						float  posZ			= mesRecebida.readFloat();

						//para saber para quem enviar a mensagem de volta, dentro da classe de jogador possui essa variavel
						sockaddr enderecoIPJogador = player;

						break;
					}
				case REQUEST_FULL_STATUS: //ID PERSONAGEM
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem	= mesRecebida.readLong();

						//para saber para quem enviar a mensagem de volta, dentro da classe de jogador possui essa variavel
						sockaddr enderecoIPJogador = player;

						break;
					}
				case SEND_BONUS_POINTS: //ID PERSONAGEM,VETOR EM ORDEM ALFABETICA COM QTD PONTOS DA HABILIDADE PRIMARIA USADA E A QUANTIDADE DE PONTOS DE SKILL(PODER)[PODER1,PODER2,PODER3]
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem	= mesRecebida.readLong();
						int    agilidade	= mesRecebida.readLong();
						int    destreza		= mesRecebida.readLong();
						int    forca		= mesRecebida.readLong();
						int    instinto		= mesRecebida.readLong();
						int    resistencia  = mesRecebida.readLong();
						int    poder1		= mesRecebida.readLong();
						int    poder2		= mesRecebida.readLong();
						int    poder3		= mesRecebida.readLong();

						//para saber para quem enviar a mensagem de volta, dentro da classe de jogador possui essa variavel
						sockaddr enderecoIPJogador = player;

						break;
					}
				case ACCEPT_QUEST: // ID PERSONAGEM, ID QUEST
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem	= mesRecebida.readLong();
						int    idQuest		= mesRecebida.readLong();

						//para saber para quem enviar a mensagem de volta, dentro da classe de jogador possui essa variavel
						sockaddr enderecoIPJogador = player;

						break;
					}
				case START_SHOP: //ID PERSONAGEM, ID NPC VENDEDOR
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem	= mesRecebida.readLong();
						int    idNPC		= mesRecebida.readLong();

						//para saber para quem enviar a mensagem de volta, dentro da classe de jogador possui essa variavel
						sockaddr enderecoIPJogador = player;

						break;
					}
				case BUY_ITEM: //IDPERSONAGEM, IDNPC VENDEDOR, ID ITEM
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem	= mesRecebida.readLong();
						int    idNPC		= mesRecebida.readLong();
						int    idItem		= mesRecebida.readLong();

						//para saber para quem enviar a mensagem de volta, dentro da classe de jogador possui essa variavel
						sockaddr enderecoIPJogador = player;

						break;
					}
				case REQUEST_PRICE_ITEM: //ID PERSONAGEM, ID NPCVENDEDOR, ID ITEM
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem	= mesRecebida.readLong();
						int    idNPC		= mesRecebida.readLong();
						int    idItem		= mesRecebida.readLong();

						//para saber para quem enviar a mensagem de volta, dentro da classe de jogador possui essa variavel
						sockaddr enderecoIPJogador = player;

						break;
					}
				case SELL_ITEM: //IDPERSOANGEM, ID NPCVENDEDOR, ID ITEM, PRECO
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem	= mesRecebida.readLong();
						int    idNPC		= mesRecebida.readLong();
						int    idItem		= mesRecebida.readLong();
						int    preco		= mesRecebida.readLong();

						//para saber para quem enviar a mensagem de volta, dentro da classe de jogador possui essa variavel
						sockaddr enderecoIPJogador = player;

						break;
					}	
		
		}//fim switch

	}//fim while

}

void CCoreServer::sendMessage(bool toAll, sockaddr * destino, dreamMessage * mes)
{
	dreamClient * cList;
	cList = _networkServer->getClientList();

	if(toAll)
	{
		for(;cList != NULL; cList = cList->_next)
		{
			cList->sendPacket(mes);
		}
	}
	else
	{
		SOCKET temp = cList->getSocket();
		cList = NULL;

		cList = (dreamClient *) calloc(1, sizeof(dreamClient));
		cList->setSocket(temp);
		cList->setSocketAddress(destino);
		cList->setConnectionState(DREAMSOCK_CONNECTED);
		cList->setOutgoingSequence(1);
		cList->setIncomingSequence(0);
		cList->setIncomingAcknowledged(0);
		cList->setIndex(0);
		cList->setName("temp");
		cList->_next = NULL;

		cList->sendPacket(mes);

		cList = NULL;
	}		
}



void CCoreServer::sendMessage(bool toAll, sockaddr * destino, int idMensagem, int i1, float f1, float f2)
{
	char data[1400];
	dreamMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);
	mes.writeLong(i1);
	mes.writeFloat(f1);
	mes.writeFloat(f2);

	sendMessage(toAll, destino, &mes);
}

void CCoreServer::sendMessage(bool toAll, sockaddr * destino, int idMensagem, CPersonagem * p1)
{
/*	char data[1400];
	dreamMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);

	mes.writeLong(p1->getID());
	//mes.writeString(p1->getNome());
	mes.writeFloat(p1->getPosition()->x);
	mes.writeFloat(p1->getPosition()->y);
	//mes.writeLong(p1);
	//mes.writeLong(p1.getPP());
	//mes.writeLong(p1->);
	//mes.writeLong(p1.getPVMax());
	//mes.writeLong(p1.getPPMax());

	
	//	AKI VAI TER QUE PREENCHER OS BUFFS CONFORME FOR, OLHA AE EDER
	
	short   buff;	

	bool    buffer[15]  = p1.getBuff();

	for(int i = 0; i < 14; i--)
	{
		buff = (short)(buffer[i] & pow(2,i));
	}

	mes.writeShort(buff);

	
	//	END BUFF
	

	mes.writeLong(p1.getEstado());
	mes.writeLong(p1.getRaca());
	mes.writeLong(p1.getTipoPersonagem());
	mes.writeLong(p1.getIdArma());
	mes.writeLong(p1.getIdArmadura());
	mes.writeFloat(p1.getDirecao());
	mes.writeFloat(p1.getVelocidade());

	sendMessage(toAll, destino, &mes);
	*/
}

void CCoreServer::sendMessage(bool toAll, sockaddr * destino, int idMensagem, int i1, int i2, float f1, float f2)
{
	char data[1400];
	dreamMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);

	mes.writeLong(i1);
	mes.writeLong(i2);
	mes.writeFloat(f1);
	mes.writeFloat(f2);

	sendMessage(toAll, destino, &mes);
}

void CCoreServer::sendMessage(bool toAll, sockaddr * destino, int idMensagem, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9, int i10)
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
	mes.writeLong(i10);

	sendMessage(toAll, destino, &mes);
}

void CCoreServer::sendMessage(bool toAll, sockaddr * destino, int idMensagem, int i1)
{
	char data[1400];
	dreamMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);

	mes.writeLong(i1);

	sendMessage(toAll, destino, &mes);
}

void CCoreServer::sendMessage(bool toAll, sockaddr * destino, int idMensagem, int i1, int i2)
{
	char data[1400];
	dreamMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);

	mes.writeLong(i1);
	mes.writeLong(i2);

	sendMessage(toAll, destino, &mes);
}

void CCoreServer::sendMessage(bool toAll, sockaddr * destino, int idMensagem, int i1, int i2, int i3)
{
	char data[1400];
	dreamMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);

	mes.writeLong(i1);
	mes.writeLong(i2);
	mes.writeLong(i3);

	sendMessage(toAll, destino, &mes);
}

void CCoreServer::sendMessage(bool toAll, sockaddr * destino, int idMensagem)
{ 
	char data[1400];
	dreamMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);

	sendMessage(toAll, destino, &mes);
}

void CCoreServer::sendMessage(bool toAll, sockaddr * destino, int idMensagem, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9)
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
	
	sendMessage(toAll, destino, &mes);
}

void CCoreServer::sendMessage(bool toAll, sockaddr * destino, int idMensagem, int i1, int i2, int i3, int i4, int i5, int i6)
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

	sendMessage(toAll, destino, &mes);
}

void CCoreServer::sendMessage(bool toAll, sockaddr * destino, int idMensagem, char * mensagem)
{
	char data[1400];
	dreamMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);

	mes.writeString(mensagem);

	sendMessage(toAll, destino, &mes);
}

void CCoreServer::sendMessage(bool toAll, sockaddr * destino, int idMensagem, int v1[30], int v2[30])
{
	char data[1400];
	dreamMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);

	for(int i = 0; i < 30; i++)
	{
		mes.writeLong(v1[i]);
	}

	for(int i = 0; i < 30; i++)
	{
		mes.writeLong(v2[i]);
	}

	sendMessage(toAll, destino, &mes);
}
