#include "CCoreServer.h"
#include "CDataManager.h"

CCoreServer::CCoreServer(CDataBase *db, int fps)
{
	if(db == NULL)
		return;

	_db = db;

	_dataManager = new CDataManager(_db);

	//seta os fps dos servidor
	_fps = fps;

	System::String^ texto = L"Inicializando o Server...";
	WarBugsLog::_log->Items->Add(texto);

	initialize();
	initializeNetwork();
}


void CCoreServer::initialize()
{
	_playersList = new CPlayerList();


	_cenarioList = _dataManager->getListCenario();
}

void CCoreServer::initializeNetwork()
{
	_networkServer = new CBugSocketServer(PORT, NUMCONNECTIONS, NonBlockingSocket);
}

CPlayerList * CCoreServer::getPlayers()
{
	return _playersList;
}


void CCoreServer::readPackets()
{
	char data[1400];
	CBugMessage mesRecebida;// = new CBugMessage();
	mesRecebida.init(data,sizeof(data));

	int tipoMensagem;

	CBugSocket * newConnection = _networkServer->Accept();

	if(newConnection != NULL)
	{
		if(_playersList->size() < NUMCONNECTIONS)
		{
			CJogador * newJogador = new CJogador();
			newJogador->setSocket(newConnection);
			_playersList->addJogador(newJogador);
		}
		
	}

	for(int indexJogador = 0; indexJogador < _playersList->size(); indexJogador++)
	{

		//recebe a mensagem do socket 
		_playersList->getElementAt(indexJogador)->getSocket()->ReceiveLine(mesRecebida);
		tipoMensagem = 0;

		mesRecebida.beginReading();
		tipoMensagem = mesRecebida.readByte();	
		

		switch(tipoMensagem)
		{
		
				case LOGIN_REQUEST: //LOGIN, SENHA
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						char login[15];
						char senha[15];

						strcpy(login,mesRecebida.readString());
						strcpy(senha,mesRecebida.readString());
						
						CJogador *  tempJogador = new CJogador();

						//se fez login
						if(_dataManager->doLogin(login,senha,tempJogador))
						{
							sendMessage(false,_playersList->getElementAt(indexJogador)->getSocket(),(int)LOGIN);
							tempJogador->setSocket(_playersList->getElementAt(indexJogador)->getSocket());
							_playersList->removeJogadorByPosition(indexJogador);
							_playersList->addJogador(tempJogador);
						}
						else
						{
							sendMessage(false,_playersList->getElementAt(indexJogador)->getSocket(),(int)LOGIN_FAIL);
						}

						break;
					}
				case REQUEST_PERSONAGENS:  //ID PESSOA
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int idJogador = mesRecebida.readLong();
						
						CPeopleList * tempList = &_dataManager->getPersonagemJogador(idJogador);

						if(tempList != NULL)
						{
							sendMessage(false,_playersList->getElementAt(indexJogador)->getSocket(),(int)SHOW_PERSONAGENS,tempList->size(),tempList);
						}
						else
						{
							sendMessage(false,_playersList->getElementAt(indexJogador)->getSocket(),(int)SHOW_PERSONAGENS,0);
						}

						break;
					}
				case CREATE_PERSONAGEM: //ID RACA, NOME
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idJogador = mesRecebida.readLong();
						int    idRaca	 = mesRecebida.readLong();
						char * nome		 = mesRecebida.readString();
						
						CPeopleList * tempList = &_dataManager->getPersonagem((int)JOGADOR,idRaca,true);

						if(tempList == NULL)
						{
							sendMessage(false,_playersList->getElementAt(indexJogador)->getSocket(),(int)CREATE_PLAYER_FAIL);
						}
						else
						{
								((CPersonagemJogador *)tempList->getElementAt(0))->setName(nome);

								//_cenarioList->addPlayer(tempJogador);

								_playersList->getElementAt(indexJogador)->setCharacter((CPersonagemJogador *)tempList->getElementAt(0));
	
								_dataManager->insertPersonagem(tempList->getElementAt(0));

								//insert em personagens do novo personagem e insert em personagem_jogador da vinculação de 1 com o outro;
						}

						break;
					}
				case PLAY: //ID PERSONAGEM
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem = mesRecebida.readLong();		

						break;
					}
				case SEND_POSITION: //ID PERSONAGEM, POSICAO X, POSICAO Z
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem = mesRecebida.readLong();
						float  posX = mesRecebida.readFloat();
						float  posZ = mesRecebida.readFloat();

						_playersList->getElementAt(indexJogador)->getCharacter()->setPosition(posX,posZ);

						break;
					}
				case SEND_ESTADO: //IDPERSONAGEM, ESTADO
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem = mesRecebida.readLong();
						int    estado       = mesRecebida.readLong();

						_playersList->getElementAt(indexJogador)->getCharacter()->setState((EstadoPersonagem)estado);

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

						CPersonagem * tempPersonagem = _playersList->getElementAt(indexJogador)->getScene()->getPlayer(idAlvo);
						
						if(tempPersonagem ==NULL)
							CPersonagem * tempPersonagem = _playersList->getElementAt(indexJogador)->getScene()->getMonster(idAlvo);
							

						if(tempPersonagem != NULL)

						_playersList->getElementAt(indexJogador)->getCharacter()->setTarget(tempPersonagem);
						_playersList->getElementAt(indexJogador)->getCharacter()->attack();

						/*
							posX e posZ não vi função para eles
						*/

						break;
					}
				case SEND_ITEM:  //ID PERSONAGEM, ID ITEM, DINHEIRO
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem = mesRecebida.readLong();
						int    idItem       = mesRecebida.readLong();
						int    dinheiro     = mesRecebida.readLong();

						

						break;
					}
				case USE_ITEM: //IDPERSONAGEM, IDITEM
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem = mesRecebida.readLong();
						int    idItem       = mesRecebida.readLong();

						CItem * tempItem = _playersList->getElementAt(indexJogador)->getCharacter()->getBolsa()->getItem(idItem);

						_playersList->getElementAt(indexJogador)->getCharacter()->useItem(tempItem);

						break;
					}
				case DROP_ITEM: //IDPERSONAGEM, IDITEM
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem = mesRecebida.readLong();
						int    idItem       = mesRecebida.readLong();

						CItem * tempItem = _playersList->getElementAt(indexJogador)->getCharacter()->getBolsa()->getItem(idItem);
						CBolsa * tempBolsa = new CBolsa();
						tempBolsa->addItem(tempItem);

//						_playersList->getElementAt(indexJogador)->getScene()->addBag(tempBolsa);

						break;
					}
				case OPEN_BOLSA: //ID PERSONAGEM, ID BOLSA
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem	= mesRecebida.readLong();
						int    idBolsa		= mesRecebida.readLong();

						_playersList->getElementAt(indexJogador)->getScene()->getBag(idBolsa);

						break;
					}
				case CLOSE_BOLSA: //ID BOLSA
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idBolsa		= mesRecebida.readLong();


						break;
					}
				case GET_ITEM_BOLSA: //ID PERSONAGEM, ID BOLSA, ID ITEM
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem	= mesRecebida.readLong();
						int    idBolsa		= mesRecebida.readLong();
						int    idItem		= mesRecebida.readLong();


						break;
					}
				case INSERT_ITEM_BOLSA: //ID BOLSA, ID ITEM
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idBolsa		= mesRecebida.readLong();
						int    idItem		= mesRecebida.readLong();


						break;
					}
				case EQUIP_ITEM: //ID PERSONAGEM, ID ARMA, ID ARMADURA
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem	= mesRecebida.readLong();
						int    idArma		= mesRecebida.readLong();
						int    idArmadura	= mesRecebida.readLong();


						break;
					}
				case SET_TARGET: //ID PERSONAGEM, ID ALVO
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem	= mesRecebida.readLong();
						int    idAlvo		= mesRecebida.readLong();


						break;
					}
				case SEND_MESSAGE: //ID DESTINO, MENSAGEM
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						//-1 para todos
						int    idPersonagem	= mesRecebida.readLong();
						char * mensagem     = mesRecebida.readString();


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


						break;
					}
				case REQUEST_FULL_STATUS: //ID PERSONAGEM
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem	= mesRecebida.readLong();


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


						break;
					}
				case ACCEPT_QUEST: // ID PERSONAGEM, ID QUEST
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem	= mesRecebida.readLong();
						int    idQuest		= mesRecebida.readLong();


						break;
					}
				case START_SHOP: //ID PERSONAGEM, ID NPC VENDEDOR
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem	= mesRecebida.readLong();
						int    idNPC		= mesRecebida.readLong();


						break;
					}
				case BUY_ITEM: //IDPERSONAGEM, IDNPC VENDEDOR, ID ITEM
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem	= mesRecebida.readLong();
						int    idNPC		= mesRecebida.readLong();
						int    idItem		= mesRecebida.readLong();


						break;
					}
				case REQUEST_PRICE_ITEM: //ID PERSONAGEM, ID NPCVENDEDOR, ID ITEM
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem	= mesRecebida.readLong();
						int    idNPC		= mesRecebida.readLong();
						int    idItem		= mesRecebida.readLong();


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

						
						
						break;
					}	
				case TRADE_REQUEST: //ID PERSONAGEM, ID FREGUES
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int idPersonagem1 = mesRecebida.readLong();
						int idPersonagem2 = mesRecebida.readLong();
						
						//CPersonagemJogador * tempPers = _playersList->getElementAt(indexJogador)->getScene()->


						//sendMessage(false,_playersList->getJogador(idJogador)->getSocket(),(int)TRADE_REQUEST,idPersonagem2);

						break;
					}
				case TRADE_REQUEST_ACCEPTED: //ID PERSONAGEM, ID FREGUES
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						break;
					}
				case TRADE_REQUEST_REFUSED: //ID PERSONAGEM, ID FREGUES
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						break;
					}
				case TRADE_CHANGED: //ID PERSONAGEM, ID FREGUES, idItemPersonagem, idItemFregues, qtdDinheiroPersonagem, qtdDinheiroFregues
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						break;
					}
				case TRADE_ACCEPTED: //ID PERSONAGEM
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						break;
					}
				case TRADE_REFUSED: //ID PERSONAGEM, ID FREGUES
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						break;
					}
				case TRADE_CONCLUDE: //ID PERSONAGEM, ID FREGUES
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						break;
					}		
		}//fim switch
	
	}

}

void CCoreServer::sendMessage(bool toAll, CBugSocket * destino, CBugMessage * mes)
{

	if(toAll)
	{
		CPlayerList * cList;
		cList = _playersList;

		for(int index = 0; index < cList->size(); index++)
		{
			cList->getElementAt(index)->getSocket()->SendLine(*mes);
		}
	}
	else
	{
		destino->SendLine(*mes);
	}		
}



void CCoreServer::sendMessage(bool toAll, CBugSocket * destino, int idMensagem, int i1, float f1, float f2)
{
	char data[1400];
	CBugMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);
	mes.writeLong(i1);
	mes.writeFloat(f1);
	mes.writeFloat(f2);

	sendMessage(toAll, destino, &mes);
}

void CCoreServer::sendMessage(bool toAll, CBugSocket * destino, int idMensagem, CPersonagem * p1)
{
/*	char data[1400];
	CBugMessage mes;
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

/*
	Manda os personagens que o jogador possui
*/
void CCoreServer::sendMessage(bool toAll, CBugSocket * destino, int idMensagem, int i1, CPeopleList * p1)
{
	char data[1400];
	CBugMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);

	mes.writeLong(i1);

	for(int j = 0; j < i1; j++)
	{
		CPersonagemJogador * personagem = (CPersonagemJogador *)p1->getElementAt(j);

		mes.writeLong(personagem->getID());
		mes.writeString(personagem->getName());
		mes.writeLong(personagem->getLevel());

		mes.writeLong(personagem->getAGI());
		mes.writeLong(personagem->getDES());
		mes.writeLong(personagem->getFOR());
		mes.writeLong(personagem->getINS());
		mes.writeLong(personagem->getRES());

		mes.writeLong(personagem->getStats()->getAttackRate());
		mes.writeLong(personagem->getStats()->getChargeTime());
		mes.writeLong(personagem->getStats()->getDefense());
		mes.writeLong(personagem->getStats()->getMeleeAttack());
		mes.writeLong(personagem->getStats()->getMeleeDamage());
		mes.writeLong(personagem->getStats()->getRangedAttack());
		mes.writeLong(personagem->getStats()->getRangedDamage());

		mes.writeLong(personagem->getModel());
		mes.writeLong(personagem->get3DTexture());
	}

	sendMessage(toAll, destino, &mes);
	
}


void CCoreServer::sendMessage(bool toAll, CBugSocket * destino, int idMensagem, int i1, int i2, float f1, float f2)
{
	char data[1400];
	CBugMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);

	mes.writeLong(i1);
	mes.writeLong(i2);
	mes.writeFloat(f1);
	mes.writeFloat(f2);

	sendMessage(toAll, destino, &mes);
}

void CCoreServer::sendMessage(bool toAll, CBugSocket * destino, int idMensagem, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9, int i10)
{
	char data[1400];
	CBugMessage mes;
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

void CCoreServer::sendMessage(bool toAll, CBugSocket * destino, int idMensagem, int i1)
{
	char data[1400];
	CBugMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);

	mes.writeLong(i1);

	sendMessage(toAll, destino, &mes);
}

void CCoreServer::sendMessage(bool toAll, CBugSocket * destino, int idMensagem, int i1, int i2)
{
	char data[1400];
	CBugMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);

	mes.writeLong(i1);
	mes.writeLong(i2);

	sendMessage(toAll, destino, &mes);
}

void CCoreServer::sendMessage(bool toAll, CBugSocket * destino, int idMensagem, int i1, int i2, int i3)
{
	char data[1400];
	CBugMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);

	mes.writeLong(i1);
	mes.writeLong(i2);
	mes.writeLong(i3);

	sendMessage(toAll, destino, &mes);
}

void CCoreServer::sendMessage(bool toAll, CBugSocket * destino, int idMensagem)
{ 
	char data[1400];
	CBugMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);

	sendMessage(toAll, destino, &mes);
}

void CCoreServer::sendMessage(bool toAll, CBugSocket * destino, int idMensagem, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9)
{
	char data[1400];
	CBugMessage mes;
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

void CCoreServer::sendMessage(bool toAll, CBugSocket * destino, int idMensagem, int i1, int i2, int i3, int i4, int i5, int i6)
{
	char data[1400];
	CBugMessage mes;
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

void CCoreServer::sendMessage(bool toAll, CBugSocket * destino, int idMensagem, char * mensagem)
{
	char data[1400];
	CBugMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);

	mes.writeString(mensagem);

	sendMessage(toAll, destino, &mes);
}

void CCoreServer::sendMessage(bool toAll, CBugSocket * destino, int idMensagem, int v1[30], int v2[30])
{
	char data[1400];
	CBugMessage mes;
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
