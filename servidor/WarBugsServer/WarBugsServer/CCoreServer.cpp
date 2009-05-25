#include "CCoreServer.h"
#include "CDataManager.h"
#include <math.h>

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

	_buffer = gcnew CBufferFrame();

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
						
						CJogador * tempJogador = new CJogador;

						//se fez login
						if(_dataManager->doLogin(login,senha,*tempJogador))
						{
							sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)LOGIN_OK);
							tempJogador->setSocket(_playersList->getElementAt(indexJogador)->getSocket());
							_playersList->removeJogadorByPosition(indexJogador);
							_playersList->addJogador(tempJogador);
						}
						else
						{
							sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)LOGIN_FAIL);
						}

						//sendMessagesFrame(_playersList);

						break;
					}
				case PERSONAGENS_REQUEST:  //ID PESSOA
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int idJogador = mesRecebida.readLong();
						
						CPeopleList * tempList = &_dataManager->getPersonagemJogador(idJogador);

						if(tempList != NULL)
						{
							sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)SHOW_PERSONAGENS,tempList->size(),tempList);
						}
						else
						{
							sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)SHOW_PERSONAGENS,0);
						}

						break;
					}
				case CREATE_PERSONAGEM: //ID RACA, NOME
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idJogador = mesRecebida.readLong();
						int    idRaca	 = mesRecebida.readLong();
						char   nome[15];
						strcpy(nome,mesRecebida.readString());
						
						CPeopleList * tempList = &_dataManager->getPersonagem((int)JOGADOR,idRaca,true);

						if(tempList == NULL)
						{
							sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)CREATE_PLAYER_FAIL);
						}
						else
						{
								((CPersonagemJogador *)tempList->getElementAt(0))->setName(nome);

								//_cenarioList->addPlayer(tempJogador);

								_playersList->getElementAt(indexJogador)->setCharacter((CPersonagemJogador *)tempList->getElementAt(0));
	
								_dataManager->insertPersonagemJogador(((CPersonagemJogador *)tempList->getElementAt(0)));

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
				case SEND_EQUIP: //ID PERSONAGEM, ID ARMA, ID ARMADURA
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem	= mesRecebida.readLong();
						int    idArma		= mesRecebida.readLong();
						int    idArmadura	= mesRecebida.readLong();


						break;
					}
				case SEND_TARGET: //ID PERSONAGEM, ID ALVO
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

void CCoreServer::sendMessage(bool toAll, int idCenario, CBugSocket * destino, CBugMessage & mes)
{
	CFrame ^ frame = gcnew CFrame(toAll, destino, mes, idCenario);

	_buffer->Add(frame);
}



void CCoreServer::sendMessage(bool toAll, int idCenario, CBugSocket * destino, int idMensagem, int i1, float f1, float f2)
{
	char data[1400];
	CBugMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);
	mes.writeLong(i1);
	mes.writeFloat(f1);
	mes.writeFloat(f2);

	sendMessage(toAll, idCenario, destino, mes);
}

void CCoreServer::sendMessage(bool toAll, int idCenario, CBugSocket * destino,  int idMensagem, TypeClassChars tipoPersonagem, CPersonagem  * p1)
{
	char data[1400];
	CBugMessage mes;
	mes.init(data,sizeof(data));

	int idArmor		= -1;
	int idWeapon	= -1;

	int tipoClasse	= (int)tipoPersonagem;
	int race		= (int)p1->getRace();
	char * nome;	

	switch(p1->getRace())
	{
		case ARANHA:
				switch(tipoPersonagem)
				{
					case SOLDADO:	nome = "Soldado Aranha";	break;
					case FILHOTE:	nome = "Filhote Aranha";	break;
					case VENDEDOR:	nome = "Vendedor Aranha";	break;
					case LIDER:		nome = "Deena Balaath";		break;
					case MAE:		nome = "Deena Balaath";		break;
					case JOGADOR:	nome = ((CPersonagemJogador *)p1)->getName();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->armadura->getID();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->arma->getID();
						break;
				}
			break;
		case BESOURO:		
				switch(tipoPersonagem)
				{
					case SOLDADO:	nome = "Soldado Besouro";	break;
					case FILHOTE:	nome = "Filhote Besouro";	break;
					case VENDEDOR:	nome = "Vendedor Besouro";	break;
					case LIDER:		nome = "Líder Besouro";		break;
					case MAE:		nome = "Mãe Besouro";		break;
					case JOGADOR:	nome = ((CPersonagemJogador *)p1)->getName();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->armadura->getID();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->arma->getID();
						break;
				}
			break;
		case ESCORPIAO:
				switch(tipoPersonagem)
				{
					case SOLDADO:	nome = "Soldado Escorpião";	break;
					case FILHOTE:	nome = "Filhote Escorpião";	break;
					case VENDEDOR:	nome = "Vendedor Escorpião";	break;
					case LIDER:		nome = "Líder Escorpião";		break;
					case MAE:		nome = "Mãe Escorpião";		break;
					case JOGADOR:	nome = ((CPersonagemJogador *)p1)->getName();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->armadura->getID();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->arma->getID();
						break;
				}
				break;
		case LOUVADEUS:
				switch(tipoPersonagem)
				{
					case SOLDADO:	nome = "Soldado Louva-a-Deus";	break;
					case FILHOTE:	nome = "Filhote Louva-a-Deus";	break;
					case VENDEDOR:	nome = "Vendedor Louva-a-Deus";	break;
					case LIDER:		nome = "Líder Louva-a-Deus";		break;
					case MAE:		nome = "Mãe Louva-a-Deus";		break;
					case JOGADOR:	nome = ((CPersonagemJogador *)p1)->getName();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->armadura->getID();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->arma->getID();
						break;
				}
				break;
		case VESPA:
				switch(tipoPersonagem)
				{
					case SOLDADO:	nome = "Soldado Vespa";	break;
					case FILHOTE:	nome = "Filhote Vespa";	break;
					case VENDEDOR:	nome = "Vendedor Vespa";	break;
					case LIDER:		nome = "Líder Vespa";		break;
					case MAE:		nome = "Mãe Vespa";		break;
					case JOGADOR:	nome = ((CPersonagemJogador *)p1)->getName();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->armadura->getID();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->arma->getID();
						break;
				}
				break;
		case ABELHA:
				switch(tipoPersonagem)
				{
					case SOLDADO:	nome = "Soldado Abelha";	break;
					case FILHOTE:	nome = "Filhote Abelha";	break;
					case VENDEDOR:	nome = "Vendedor Abelha";	break;
					case LIDER:		nome = "Líder Abelha";		break;
					case MAE:		nome = "Mãe Abelha";		break;
					case JOGADOR:	nome = ((CPersonagemJogador *)p1)->getName();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->armadura->getID();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->arma->getID();
						break;
				}
				break;
		case BARATA:
				switch(tipoPersonagem)
				{
					case SOLDADO:	nome = "Soldado Barata";	break;
					case FILHOTE:	nome = "Filhote Barata";	break;
					case VENDEDOR:	nome = "Vendedor Barata";	break;
					case LIDER:		nome = "Líder Barata";		break;
					case MAE:		nome = "Mãe Barata";		break;
					case JOGADOR:	nome = ((CPersonagemJogador *)p1)->getName();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->armadura->getID();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->arma->getID();
						break;
				}
				break;
		case BARBEIRO:
				switch(tipoPersonagem)
				{
					case SOLDADO:	nome = "Soldado Barbeiro";	break;
					case FILHOTE:	nome = "Filhote Barbeiro";	break;
					case VENDEDOR:	nome = "Vendedor Barbeiro";	break;
					case LIDER:		nome = "Líder Barbeiro";	break;
					case MAE:		nome = "Mãe Barbeiro";		break;
					case JOGADOR:	nome = ((CPersonagemJogador *)p1)->getName();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->armadura->getID();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->arma->getID();
						break;
				}
				break;
		case CALANGO:
				switch(tipoPersonagem)
				{
					case SOLDADO:	nome = "Soldado Calango";	break;
					case FILHOTE:	nome = "Filhote Calango";	break;
					case VENDEDOR:	nome = "Vendedor Calango";	break;
					case LIDER:		nome = "Líder Calango";		break;
					case MAE:		nome = "Mãe Calango";		break;
					case JOGADOR:	nome = ((CPersonagemJogador *)p1)->getName();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->armadura->getID();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->arma->getID();
						break;
				}
				break;
		case CAMALEAO:
				switch(tipoPersonagem)
				{
					case SOLDADO:	nome = "Soldado Camaleão";	break;
					case FILHOTE:	nome = "Filhote Camaleão";	break;
					case VENDEDOR:	nome = "Vendedor Camaleão";	break;
					case LIDER:		nome = "Líder Camaleão";		break;
					case MAE:		nome = "Mãe Camaleão";		break;
					case JOGADOR:	nome = ((CPersonagemJogador *)p1)->getName();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->armadura->getID();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->arma->getID();
						break;
				}
				break;
		case CUPIM:
				switch(tipoPersonagem)
				{
					case SOLDADO:	nome = "Soldado Cupim";	break;
					case FILHOTE:	nome = "Filhote Cupim";	break;
					case VENDEDOR:	nome = "Vendedor Cupim";	break;
					case LIDER:		nome = "Líder Cupim";		break;
					case MAE:		nome = "Mãe Cupim";		break;
					case JOGADOR:	nome = ((CPersonagemJogador *)p1)->getName();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->armadura->getID();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->arma->getID();
						break;
				}
				break;
		case FORMIGA:
				switch(tipoPersonagem)
				{
					case SOLDADO:	nome = "Soldado Formiga";	break;
					case FILHOTE:	nome = "Filhote Formiga";	break;
					case VENDEDOR:	nome = "Vendedor Formiga";	break;
					case LIDER:		nome = "Líder Formiga";		break;
					case MAE:		nome = "Mãe Formiga";		break;
					case JOGADOR:	nome = ((CPersonagemJogador *)p1)->getName();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->armadura->getID();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->arma->getID();
						break;
				}
				break;
		case JOANINHA:
				switch(tipoPersonagem)
				{
					case SOLDADO:	nome = "Soldado Joaninha";	break;
					case FILHOTE:	nome = "Filhote Joaninha";	break;
					case VENDEDOR:	nome = "Vendedor Joaninha";	break;
					case LIDER:		nome = "Líder Joaninha";	break;
					case MAE:		nome = "Mãe Joaninha";		break;
					case JOGADOR:	nome = ((CPersonagemJogador *)p1)->getName();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->armadura->getID();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->arma->getID();
						break;
				}
				break;
		case LAGARTIXA:
				switch(tipoPersonagem)
				{
					case SOLDADO:	nome = "Soldado Lagartixa";	break;
					case FILHOTE:	nome = "Filhote Lagartixa";	break;
					case VENDEDOR:	nome = "Vendedor Lagartixa";	break;
					case LIDER:		nome = "Líder Largatixa";		break;
					case MAE:		nome = "Mãe Largatixa";		break;
					case JOGADOR:	nome = ((CPersonagemJogador *)p1)->getName();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->armadura->getID();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->arma->getID();
						break;
				}
				break;
		case LIBELULA:
				switch(tipoPersonagem)
				{
					case SOLDADO:	nome = "Soldado Libélula";	break;
					case FILHOTE:	nome = "Filhote Libélula";	break;
					case VENDEDOR:	nome = "Vendedor Libélula";	break;
					case LIDER:		nome = "Líder Libélula";	break;
					case MAE:		nome = "Mãe Libélula";		break;
					case JOGADOR:	nome = ((CPersonagemJogador *)p1)->getName();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->armadura->getID();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->arma->getID();
						break;
				}
				break;
		case PERCEVEJO:
				switch(tipoPersonagem)
				{
					case SOLDADO:	nome = "Soldado Percevejo";		break;
					case FILHOTE:	nome = "Filhote Percevejo";		break;
					case VENDEDOR:	nome = "Vendedor Percevejo";	break;
					case LIDER:		nome = "Líder Percevejo";		break;
					case MAE:		nome = "Mãe Percevejo";			break;
					case JOGADOR:	nome = ((CPersonagemJogador *)p1)->getName();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->armadura->getID();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->arma->getID();
						break;
				}
				break;
		case SAPO:
				switch(tipoPersonagem)
				{
					case SOLDADO:	nome = "Soldado Sapo";	break;
					case FILHOTE:	nome = "Filhote Sapo";	break;
					case VENDEDOR:	nome = "Vendedor Sapo";	break;
					case LIDER:		nome = "Líder Sapo";	break;
					case MAE:		nome = "Mãe Sapo";		break;
					case JOGADOR:	nome = ((CPersonagemJogador *)p1)->getName();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->armadura->getID();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->arma->getID();
						break;
				}
				break;
		case TATUBOLINHA:
				switch(tipoPersonagem)
				{
					case SOLDADO:	nome = "Soldado Tatu Bolinha";	break;
					case FILHOTE:	nome = "Filhote Tatu Bolinha";	break;
					case VENDEDOR:	nome = "Vendedor Tatu Bolinha";	break;
					case LIDER:		nome = "Líder Tatu Bolinha";	break;
					case MAE:		nome = "Mãe Tatu Bolinha";		break;
					case JOGADOR:	nome = ((CPersonagemJogador *)p1)->getName();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->armadura->getID();
									idArmor = ((CPersonagemJogador *)p1)->getEquip()->arma->getID();
						break;
				}
				break;
	}

	mes.writeByte(idMensagem);

	mes.writeLong(p1->getID());
	mes.writeString(nome);
	mes.writeFloat(p1->getPosition()->x);
	mes.writeFloat(p1->getPosition()->z);
	mes.writeLong(p1->getStats()->getPV());
	mes.writeLong(p1->getStats()->getPM());
	mes.writeLong(p1->getStats()->getMaxPV());
	mes.writeLong(p1->getStats()->getMaxPM());
	
	//	AKI VAI TER QUE PREENCHER OS BUFFS CONFORME FOR, OLHA AE EDER
	
	short   buff = 0;	

	bool    buffer[15];
	CBuff * tempBuff;
	int     intBuff;

	for(int i = 0; i < p1->getBuffs()->size(); i++ )
	{
		tempBuff = p1->getBuffs()->getElementAt(i);

		if(tempBuff != NULL)
		{
			intBuff = (int)tempBuff->getTipo();
			if( intBuff > 0)
				buffer[intBuff] = true;		
		}
	}

		
	int potencia;

	for(int i = 0; i < 14; i--)
	{
		potencia = 1;
		for(int j = 0; j < i; j++)
			potencia = potencia * 2;

		buff = (short)(buffer[i] & potencia);
	}

	mes.writeShort(buff);

	
	//	END BUFF
	

	mes.writeLong(p1->getState());
	mes.writeLong(race);
	mes.writeLong(tipoClasse);
	mes.writeLong(idWeapon);
	mes.writeLong(idArmor);
	mes.writeFloat(p1->getDirection());
	mes.writeFloat(p1->getMoveSpeed());

	sendMessage(toAll, idCenario, destino, mes);
}

/*
	Manda os personagens que o jogador possui
*/
void CCoreServer::sendMessage(bool toAll, int idCenario, CBugSocket * destino, int idMensagem, int i1, CPeopleList * p1)
{
	char data[1400];
	CBugMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);

	mes.writeLong(i1);

	for(int j = 0; j < i1; j++)
	{
		CPersonagemJogador * personagem = (CPersonagemJogador *)p1->getElementAt(j);
		//Dados pessoais
		mes.writeLong(personagem->getID());
		mes.writeString(personagem->getName());
		mes.writeLong(personagem->getLevel());
		//Habilidades Primárias
		mes.writeLong(personagem->getAGI());
		mes.writeLong(personagem->getDES());
		mes.writeLong(personagem->getFOR());
		mes.writeLong(personagem->getINS());
		mes.writeLong(personagem->getRES());
		//Habilidades Secundárias
		mes.writeLong(personagem->getStats()->getAttackRate());
		mes.writeLong(personagem->getStats()->getChargeTime());
		mes.writeLong(personagem->getStats()->getDefense());
		mes.writeLong(personagem->getStats()->getMeleeAttack());
		mes.writeLong(personagem->getStats()->getMeleeDamage());
		mes.writeLong(personagem->getStats()->getRangedAttack());
		mes.writeLong(personagem->getStats()->getRangedDamage());
		//3D
		mes.writeLong(personagem->getModel());
		mes.writeLong(personagem->get3DTexture());
		mes.writeLong(personagem->get2DTexture());
	}

	sendMessage(toAll, idCenario, destino, mes);	
}


void CCoreServer::sendMessage(bool toAll, int idCenario, CBugSocket * destino, int idMensagem, int i1, int i2, float f1, float f2)
{
	char data[1400];
	CBugMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);

	mes.writeLong(i1);
	mes.writeLong(i2);
	mes.writeFloat(f1);
	mes.writeFloat(f2);

	sendMessage(toAll, idCenario, destino, mes);
}

void CCoreServer::sendMessage(bool toAll, int idCenario, CBugSocket * destino, int idMensagem, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9, int i10)
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

	sendMessage(toAll, idCenario, destino, mes);
}

void CCoreServer::sendMessage(bool toAll, int idCenario, CBugSocket * destino, int idMensagem, int i1)
{
	char data[1400];
	CBugMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);

	mes.writeLong(i1);

	sendMessage(toAll, idCenario, destino, mes);
}

void CCoreServer::sendMessage(bool toAll, int idCenario, CBugSocket * destino, int idMensagem, int i1, int i2)
{
	char data[1400];
	CBugMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);

	mes.writeLong(i1);
	mes.writeLong(i2);

	sendMessage(toAll, idCenario, destino, mes);
}

void CCoreServer::sendMessage(bool toAll, int idCenario, CBugSocket * destino, int idMensagem, int i1, int i2, int i3)
{
	char data[1400];
	CBugMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);

	mes.writeLong(i1);
	mes.writeLong(i2);
	mes.writeLong(i3);

	sendMessage(toAll, idCenario, destino, mes);
}

void CCoreServer::sendMessage(bool toAll, int idCenario, CBugSocket * destino, int idMensagem)
{ 
	char data[1400];
	CBugMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);

	sendMessage(toAll, idCenario, destino, mes);
}

void CCoreServer::sendMessage(bool toAll, int idCenario, CBugSocket * destino, int idMensagem, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9)
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
	
	sendMessage(toAll, idCenario, destino, mes);
}

void CCoreServer::sendMessage(bool toAll, int idCenario, CBugSocket * destino, int idMensagem, int i1, int i2, int i3, int i4, int i5, int i6)
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

	sendMessage(toAll, idCenario, destino, mes);
}

void CCoreServer::sendMessage(bool toAll, int idCenario, CBugSocket * destino, int idMensagem, char * mensagem)
{
	char data[1400];
	CBugMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);

	mes.writeString(mensagem);

	sendMessage(toAll, idCenario, destino, mes);
}

void CCoreServer::sendMessage(bool toAll, int idCenario, CBugSocket * destino, int idMensagem, int v1[30], int v2[30])
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

	sendMessage(toAll, idCenario, destino, mes);
}

void CCoreServer::sendMessagesFrame(CPlayerList * cList)
{
	CFrame ^ frame;
	if(cList != NULL)
	while(_buffer->Count > 0)
	{
		frame = (CFrame ^)_buffer[0];
		_buffer->RemoveAt(0);

		if(frame)
		{
			if(frame->_toAll)
			{
				for(int index = 0; index < cList->size(); index++)
				{
					if(frame->_idCenario == cList->getElementAt(index)->getScene()->getID())
					{
						try{
							cList->getElementAt(index)->getSocket()->SendLine(*frame->_message);
						}
						catch(...)
						{
							cList->removeJogadorByPosition(index);
						}
					}
				}
			}
			else
			{
				try{
					frame->_socket->SendLine(*frame->_message);
				}
				catch(...)
				{
					System::String ^ texto = L"Não foi possivel manda a mensagem!";
					WarBugsLog::_log->Items->Add(texto);
				}
			}
		}
	}
}


void CCoreServer::updateAll()
{
	_cenarioList->update();
}

void CCoreServer::sendAllMessages()
{
	//sendMessage(true,-1,NULL,END_FRAME);
	sendMessagesFrame(_playersList);
}