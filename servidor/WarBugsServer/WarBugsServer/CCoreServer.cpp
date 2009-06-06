#include "CCoreServer.h"
#include "FunctionsCommom.h"
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
			newJogador = NULL;
			delete newJogador;
		}
		
	}

	for(int indexJogador = 0; indexJogador < _playersList->size(); indexJogador++)
	{

		//recebe a mensagem do socket 
		mesRecebida.clear();
		_playersList->getElementAt(indexJogador)->getSocket()->ReceiveLine(mesRecebida);
		//_playersList->getElementAt(indexJogador)->getSocket()->ReceiveLine(mesRecebida);
		
		tipoMensagem = 0;

		mesRecebida.beginReading();
		tipoMensagem = mesRecebida.readByte();	

		switch(tipoMensagem)
		{
				case DISCONNECT:
					{
						_playersList->getElementAt(indexJogador)->getSocket()->Close();
						_playersList->removeJogadorAt(indexJogador);
						break;
					}
		
				case LOGIN_REQUEST: //LOGIN, SENHA
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						char login[15];
						char senha[15];

						strcpy_s(login,sizeof(login),mesRecebida.readString());
						strcpy_s(senha,sizeof(senha),mesRecebida.readString());
						
						CJogador * tempJogador = new CJogador();

						//se fez login
						if(_dataManager->doLogin(login,senha,*tempJogador))
						{
							sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)LOGIN_OK,tempJogador->getID());
							tempJogador->setSocket(_playersList->getElementAt(indexJogador)->getSocket());
							_playersList->removeJogadorAt(indexJogador);
							_playersList->addJogador(tempJogador);
						}
						else
						{
							sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)LOGIN_FAIL);

						}
						tempJogador = NULL;
						delete tempJogador;

						break;
					}
				case PERSONAGENS_REQUEST:  //ID PESSOA
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int idJogador = mesRecebida.readInt();
						
						CPeopleList * tempList = &_dataManager->getPersonagemJogador(idJogador);

						if(tempList->size() > 0)
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

						int    idJogador = mesRecebida.readInt();
						int    idRaca	 = mesRecebida.readInt();
						char   nome[15];
						strcpy_s(nome,sizeof(nome),mesRecebida.readString());
						
						if(_dataManager->qtdPersonagemJogador(idJogador) >= NUMPERSONAGEMJOGADOR) 
						{
							sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)CREATE_PLAYER_FAIL);
							break;
						}


						CPeopleList * tempList = &_dataManager->getPersonagem((int)JOGADOR,idRaca,true);

						if(tempList == NULL)
						{
							sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)CREATE_PLAYER_FAIL);
						}
						else
						{
								((CPersonagemJogador *)tempList->getElementAt(0))->setName(nome);

								if(_dataManager->insertPersonagemJogador(((CPersonagemJogador *)tempList->getElementAt(0)),_playersList->getElementAt(indexJogador)->getID()))
								{
									sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)CREATE_PLAYER_OK);
								}
								else
								{
									sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)CREATE_PLAYER_FAIL);
								}
						}

						break;
					}
				case DELETE_PERSONAGEM: //ID JOGADOR, IDPERSONAGEM, NOME PERSONAGEM
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idJogador	 = mesRecebida.readInt();
						int    idPersonagem	 = mesRecebida.readInt();
						char   nome[15];
						strcpy_s(nome,sizeof(nome),mesRecebida.readString());
						
						if(_dataManager->qtdPersonagemJogador(idJogador) <= 0)
						{
							sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)DELETE_PLAYER_FAIL);
						}
						else
						{
							//se não foi possível deletar
							if(!_dataManager->deletePersonagemJogador(idJogador,idPersonagem,nome))
							{
								sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)DELETE_PLAYER_FAIL);
							}
							else
							{
								sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)DELETE_PLAYER_OK);
							}
						}

						break;
					}

				case START_GAME: //ID PERSONAGEM
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idJogador	 = mesRecebida.readInt();
						int    idPersonagem	 = mesRecebida.readInt();

						CPersonagem * tempPersonagem = _dataManager->getPersonagem(idPersonagem);

						int idCenario = -1;
						int posCenario = -1;

						if(tempPersonagem == NULL)
						{
							sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)START_GAME_FAIL);
							break;
						}
						else
						{
							_playersList->getElementAt(indexJogador)->setCharacter(((CPersonagemJogador *) tempPersonagem));

							idCenario = _dataManager->getCenarioId(idPersonagem,idJogador);

							if(idCenario == -1)
							{
								sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)START_GAME_FAIL);
								break;								
							}

							if(!_cenarioList->haveCenario(idCenario))
							{
								sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)START_GAME_FAIL);
								break;								
							}

							for(int p = 0; p < _cenarioList->size(); p++)
							{
								if(_cenarioList->getElementAt(p)->getID() == idCenario)
								{
									posCenario = p;
									p = _cenarioList->size();
								}

							}

							if(posCenario == -1)
							{
								sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)START_GAME_FAIL);
								break;								
							}

							//coloca o personagem no cenário
							_cenarioList->getElementAt(posCenario)->addPlayer(tempPersonagem);

							//manda para todos do cenário adicionar o novo personagem
							sendMessage(true,_cenarioList->getElementAt(posCenario)->getID(),_playersList->getElementAt(indexJogador)->getSocket(),(int)ADD_PERSONAGEM, JOGADOR, tempPersonagem);

							//manda o cenário em que o jogador está
							sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)ENTER_CENARIO, _playersList->getElementAt(indexJogador)->getScene()->getID(),tempPersonagem->getSceneID());

							//manda para o player os inimigos
							for(int p = 0; p < _cenarioList->getElementAt(posCenario)->monsterCount(); p++)
							{
								CInimigo * tempInimigo = _cenarioList->getElementAt(posCenario)->getMonsterAt(p);

								if(tempInimigo == NULL)
								{
									sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)START_GAME_FAIL);	
								}
								else
								{
									sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)ADD_PERSONAGEM, tempInimigo->getType(), tempInimigo);
								}
							}

							//manda para o player os NPCS
							for(int p = 0; p < _cenarioList->getElementAt(posCenario)->NPCCount(); p++)
							{
								CNPC * tempNPC = _cenarioList->getElementAt(posCenario)->getNpcAt(p);

								if(tempNPC == NULL)
								{
									sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)START_GAME_FAIL);	
								}
								else
								{
									sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)ADD_PERSONAGEM, tempNPC->getType(), tempNPC);
								}
							}

							//manda para o player as Bolsas
							for(int p = 0; p < _cenarioList->getElementAt(posCenario)->bagCount(); p++)
							{
								CBolsa * tempBolsa = _cenarioList->getElementAt(posCenario)->getBagAt(p);

								if(tempBolsa == NULL)
								{
									sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)START_GAME_FAIL);	
								}
								else
								{
									sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)ADD_BOLSA, tempBolsa->getSceneID(), tempBolsa->getPosition()->x, tempBolsa->getPosition()->z);
								}
							}

							//manda para o player os Vendedores
							for(int p = 0; p < _cenarioList->getElementAt(posCenario)->salesmanCount(); p++)
							{
								CVendedor * tempVendedor = _cenarioList->getElementAt(posCenario)->getSalesmanAt(p);

								if(tempVendedor == NULL)
								{
									sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)START_GAME_FAIL);	
								}
								else
								{
									sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)ADD_PERSONAGEM, tempVendedor->getType(), tempVendedor);
								}
							}

							//manda para o player os outros Players
							for(int p = 0; p < _cenarioList->getElementAt(posCenario)->playerCount(); p++)
							{
								CPersonagemJogador * tempPersonagemJogador = _cenarioList->getElementAt(posCenario)->getPlayerAt(p);

								if(tempPersonagemJogador == NULL)
								{
									sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)START_GAME_FAIL);	
								}
								else if(tempPersonagemJogador->getSceneID() != _playersList->getElementAt(indexJogador)->getCharacter()->getSceneID())
								{
									sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)ADD_PERSONAGEM, JOGADOR, tempPersonagemJogador);
								}
							}

						}

						break;
					}
				case SEND_POSITION: //ID PERSONAGEM, POSICAO X, POSICAO Z
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idJogador    = mesRecebida.readInt();
						int    idPersonagem = mesRecebida.readInt();
						float  posX = mesRecebida.readFloat();
						float  posZ = mesRecebida.readFloat();

						_playersList->getElementAt(indexJogador)->getCharacter()->setPosition(posX,posZ);

						sendMessage(true,_playersList->getElementAt(indexJogador)->getScene()->getID(),_playersList->getElementAt(indexJogador)->getSocket(),(int)UPDATE_POSITION, _playersList->getElementAt(indexJogador)->getCharacter()->getSceneID(), _playersList->getElementAt(indexJogador)->getCharacter()->getPosition()->x, _playersList->getElementAt(indexJogador)->getCharacter()->getPosition()->z);

						break;
					}
				case SEND_ESTADO: //IDPERSONAGEM, ESTADO
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idJogador    = mesRecebida.readInt();
						int    idPersonagem = mesRecebida.readInt();
						int    estado       = mesRecebida.readInt();

						_playersList->getElementAt(indexJogador)->getCharacter()->setState((EstadoPersonagem)estado);

						sendMessage(true,_playersList->getElementAt(indexJogador)->getScene()->getID(),_playersList->getElementAt(indexJogador)->getSocket(),(int)UPDATE_ESTADO, _playersList->getElementAt(indexJogador)->getCharacter()->getSceneID(), (int)_playersList->getElementAt(indexJogador)->getCharacter()->getState());

						break;
					}
				case SEND_ATACK: //ID PERSONAGEM, ID ALVO, ID ATAQUE, POSICAO X E POSICAO Z ALVO CHÃO //PODE SER PODER OU ATAQUE NORMAL
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idJogador    = mesRecebida.readInt();
						int    idPersonagem = mesRecebida.readInt();
						int    idAlvo       = mesRecebida.readInt();
						int    idAtaque     = mesRecebida.readInt();
						float  posX         = mesRecebida.readFloat();
						float  posZ         = mesRecebida.readFloat();

						CPersonagem * tempPersonagem = _playersList->getElementAt(indexJogador)->getScene()->getPlayer(idAlvo);
						
						if(tempPersonagem ==NULL)
							tempPersonagem = _playersList->getElementAt(indexJogador)->getScene()->getMonster(idAlvo);
							

						if(tempPersonagem != NULL)
						{
							_playersList->getElementAt(indexJogador)->getCharacter()->setTarget(tempPersonagem);
							_playersList->getElementAt(indexJogador)->getCharacter()->attack();

						}

						/*
							posX e posZ não vi função para eles
						*/

						sendMessage(true,_playersList->getElementAt(indexJogador)->getScene()->getID(),_playersList->getElementAt(indexJogador)->getSocket(),(int)UPDATE_ATACK, _playersList->getElementAt(indexJogador)->getCharacter()->getSceneID(), _playersList->getElementAt(indexJogador)->getCharacter()->getTarget()->getSceneID(), idAtaque);

						break;
					}
				case USE_ITEM: //IDPERSONAGEM, IDITEM
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idJogador    = mesRecebida.readInt();
						int    idPersonagem = mesRecebida.readInt();
						int    idItem       = mesRecebida.readInt();

						CItem * tempItem = _playersList->getElementAt(indexJogador)->getCharacter()->getBolsa()->getItem(idItem);

						_playersList->getElementAt(indexJogador)->getCharacter()->useItem(tempItem);

						break;
					}
				case DROP_ITEM: //IDPERSONAGEM, IDITEM
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idJogador    = mesRecebida.readInt();
						int    idPersonagem = mesRecebida.readInt();
						int    idItem       = mesRecebida.readInt();

						CItem * tempItem = _playersList->getElementAt(indexJogador)->getCharacter()->getBolsa()->getItem(idItem);
						CBolsa * tempBolsa = new CBolsa();
						tempBolsa->addItem(tempItem);

						tempBolsa->setPosition(_playersList->getElementAt(indexJogador)->getCharacter()->getPosition());

						_playersList->getElementAt(indexJogador)->getScene()->addBag(tempBolsa);

						sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int) REMOVE_ITEM, tempItem->getID(), 0);

						sendMessage(true,_playersList->getElementAt(indexJogador)->getScene()->getID(),_playersList->getElementAt(indexJogador)->getSocket(),(int)ADD_BOLSA, tempBolsa->getSceneID(),tempBolsa->getPosition()->x,tempBolsa->getPosition()->z);

						break;
					}
				case OPEN_BOLSA: //ID PERSONAGEM, ID BOLSA
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idJogador    = mesRecebida.readInt();
						int    idPersonagem	= mesRecebida.readInt();
						int    idBolsa		= mesRecebida.readInt();

						CBolsa * tempBolsa = _playersList->getElementAt(indexJogador)->getScene()->getBag(idBolsa);

						if(tempBolsa != NULL)
						{
							if(!tempBolsa->isOpen())
							{
								tempBolsa->setOpen(true);

								int temp[9];

								for(int p = 0; p < 9; p++)
								{
									if(tempBolsa->getElementAt(p) != NULL)
									{
										try{
											temp[p] = tempBolsa->getElementAt(p)->getID();
										} catch(...)
										{
											temp[p] = -1;
										}
									}
									else
									{
										temp[p] = -1;
									}
								}

								sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)OPENED_BOLSA, tempBolsa->getSceneID(), temp[0], temp[1], temp[2], temp[3], temp[4], temp[5], temp[6], temp[7], temp[8]);
							}
							else
							{
								sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)OPEN_BOLSA_FAIL);
							}
						}
						else
						{
							sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)OPEN_BOLSA_FAIL);
						}

						tempBolsa = NULL;
						delete tempBolsa;

						break;
					}
				case CLOSE_BOLSA: //ID BOLSA
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idBolsa		= mesRecebida.readInt();
						
						CBolsa * tempBolsa = _playersList->getElementAt(indexJogador)->getScene()->getBag(idBolsa);

						if(tempBolsa == NULL)
						{
							sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)CLOSE_BOLSA_FAIL);
							tempBolsa = NULL;
							delete tempBolsa;

							break;
						}

						if(tempBolsa->isOpen())
						{
							tempBolsa->setOpen(false);
							sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)CLOSED_BOLSA, tempBolsa->getSceneID());
						}

						tempBolsa = NULL;
						delete tempBolsa;

						break;
					}
				case GET_ITEM_BOLSA: //ID PERSONAGEM, ID BOLSA, ID ITEM
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idJogador    = mesRecebida.readInt();
						int    idPersonagem	= mesRecebida.readInt();
						int    idBolsa		= mesRecebida.readInt();
						int    idItem		= mesRecebida.readInt();

						CItem * tempItem = NULL;
						
						try{
							tempItem = _playersList->getElementAt(indexJogador)->getScene()->getBag(idBolsa)->removeItem(idItem);

						}catch(...)
						{
							WarBugsLog::_log->Items->Add(gcnew System::String(L"Erro ao pegar item da Bolsa"));
							break;	
						}
							
						if(tempItem != NULL)
						{
							if(_playersList->getElementAt(indexJogador)->getCharacter()->getBolsa()->size() < MAXITENS)
							{
								_playersList->getElementAt(indexJogador)->getCharacter()->addItem(tempItem);
								sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)ADD_ITEM, tempItem->getID(), 0);
							}
							else
							{
								sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)INVENTORY_FULL);
							}
						}

						break;
					}
				case INSERT_ITEM_BOLSA: //ID BOLSA, ID ITEM
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idBolsa		= mesRecebida.readInt();
						int    idItem		= mesRecebida.readInt();

						CItem * tempItem = NULL;

						try{
							tempItem = _playersList->getElementAt(indexJogador)->getCharacter()->getBolsa()->removeItem(idItem);
						}catch(...)
						{
							WarBugsLog::_log->Items->Add(gcnew System::String(L"Erro ao inserir o item na Bolsa"));
							break;								
						}

						if(tempItem != NULL)
						{
							if(_playersList->getElementAt(indexJogador)->getScene()->getBag(idBolsa)->size() < MAXITENS)
							{
								_playersList->getElementAt(indexJogador)->getScene()->getBag(idBolsa)->addItem(tempItem);
								sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)REMOVE_ITEM, tempItem->getID(), 0);
							}
							else
							{
								sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)INVENTORY_FULL);
							}							
						
						}

						break;
					}
				case SEND_EQUIP: //ID PERSONAGEM, ID ARMA, ID ARMADURA
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idJogador    = mesRecebida.readInt();
						int    idPersonagem	= mesRecebida.readInt();
						int    idArma		= mesRecebida.readInt();
						int    idArmadura	= mesRecebida.readInt();

						CItem * tempArma = NULL;
						CItem * tempArmadura = NULL;

						try
						{
							if(idArma != -1 && _playersList->getElementAt(indexJogador)->getCharacter()->getEquip()->arma->getID() != idArma)
							{
								tempArma = _playersList->getElementAt(indexJogador)->getCharacter()->getBolsa()->removeItem(idArma);
								sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)REMOVE_ITEM, tempArma->getID(), 0);

							}

							if(idArmadura != -1 && _playersList->getElementAt(indexJogador)->getCharacter()->getEquip()->armadura->getID() != idArmadura)
							{
								tempArmadura = _playersList->getElementAt(indexJogador)->getCharacter()->getBolsa()->removeItem(idArmadura);
								sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)REMOVE_ITEM, tempArmadura->getID(), 0);
							}
						}
						catch(...)
						{
							WarBugsLog::_log->Items->Add(gcnew System::String(L"Erro ao Equipar o personagem!"));
							break;								
						}

						if(tempArma != NULL)
						{
							_playersList->getElementAt(indexJogador)->getCharacter()->equip(tempArma);
						}

						if(tempArmadura != NULL)
						{
							_playersList->getElementAt(indexJogador)->getCharacter()->equip(tempArmadura);
						}

						sendMessage(true,_playersList->getElementAt(indexJogador)->getScene()->getID(),_playersList->getElementAt(indexJogador)->getSocket(),(int)UPDATE_EQUIP, _playersList->getElementAt(indexJogador)->getCharacter()->getSceneID(), tempArmadura->getID(), tempArma->getID());
						break;
					}
				case SEND_TARGET: //ID PERSONAGEM, ID ALVO
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem	= mesRecebida.readInt();
						int    idAlvo		= mesRecebida.readInt();

						CPersonagemJogador * alvo = NULL;

						try
						{
							alvo = _playersList->getElementAt(indexJogador)->getScene()->getPlayer(idAlvo);
							_playersList->getElementAt(indexJogador)->getCharacter()->setTarget(alvo);
							sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)UPDATE_TARGET, alvo->getSceneID());
						}
						catch(...)
						{
							WarBugsLog::_log->Items->Add(gcnew System::String(L"Erro ao setar o alvo!"));
							break;						
						}

						break;
					}
				case SEND_MESSAGE: //ID DESTINO, MENSAGEM
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						//-1 para todos
						int    idPersonagem	= mesRecebida.readInt();
						char * mensagem = mesRecebida.readString();

						System::String ^ nome = gcnew System::String(_playersList->getElementAt(indexJogador)->getCharacter()->getName());
						System::String ^ mensagemString = gcnew System::String(mensagem);
						System::String ^ mes = gcnew System::String(L""+nome+": "+mensagemString);

						if(idPersonagem == -1)
						{
							sendMessage(true,_playersList->getElementAt(indexJogador)->getScene()->getID(),_playersList->getElementAt(indexJogador)->getSocket(),(int)CHAT, toChar(mes));
						}
						else
						{
							sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)CHAT, toChar(mes));
						}


						break;
					}
				case START_SHOT: //ID PERSONAGEM, ID ALVO, IDSHOT, POSICAO X E POSICAO Z INICIAL
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem	= mesRecebida.readInt();
						int    idAlvo		= mesRecebida.readInt();
						int    idShot		= mesRecebida.readInt();
						float  posX			= mesRecebida.readFloat();
						float  posZ			= mesRecebida.readFloat();

						sendMessage(true,_playersList->getElementAt(indexJogador)->getScene()->getID(),_playersList->getElementAt(indexJogador)->getSocket(),(int)SHOT, idShot, idAlvo, posX, posZ);

						break;
					}
				case REQUEST_FULL_STATUS: //ID PERSONAGEM
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int idJogador 	 = mesRecebida.readInt();
						int idPersonagem = mesRecebida.readInt();
						
						int agilidade	= _playersList->getElementAt(indexJogador)->getCharacter()->getAGI();
						int destreza	= _playersList->getElementAt(indexJogador)->getCharacter()->getDES();
						int forca		= _playersList->getElementAt(indexJogador)->getCharacter()->getFOR();
						int instinto	= _playersList->getElementAt(indexJogador)->getCharacter()->getINS();
						int resistencia = _playersList->getElementAt(indexJogador)->getCharacter()->getRES();

						int ataque		= _playersList->getElementAt(indexJogador)->getCharacter()->getAttack();
						int dano		= _playersList->getElementAt(indexJogador)->getCharacter()->getDamage();
						int defesa		= _playersList->getElementAt(indexJogador)->getCharacter()->getStats()->getDefense();
						int velocidade  = _playersList->getElementAt(indexJogador)->getCharacter()->getStats()->getAttackRate();

						int lealdade_aranha		= _playersList->getElementAt(indexJogador)->getCharacter()->getLoyalty()->getLoyaltyToSpider();
						int lealdade_besouro	= _playersList->getElementAt(indexJogador)->getCharacter()->getLoyalty()->getLoyaltyToBeetle();
						int lealdade_escorpiao	= _playersList->getElementAt(indexJogador)->getCharacter()->getLoyalty()->getLoyaltyToScorpion();
						int lealdade_louva		= _playersList->getElementAt(indexJogador)->getCharacter()->getLoyalty()->getLoyaltyToMantis();
						int lealdade_vespa		= _playersList->getElementAt(indexJogador)->getCharacter()->getLoyalty()->getLoyaltyToWasp();

						int poder1 = _playersList->getElementAt(indexJogador)->getCharacter()->getSkillLevel(0);
						int poder2 = _playersList->getElementAt(indexJogador)->getCharacter()->getSkillLevel(1);
						int poder3 = _playersList->getElementAt(indexJogador)->getCharacter()->getSkillLevel(2);

						sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)SHOW_FULL_STATUS, agilidade, destreza, forca, instinto, resistencia, ataque, dano, defesa, velocidade, lealdade_aranha, lealdade_besouro, lealdade_escorpiao, lealdade_louva, lealdade_vespa, poder1, poder2, poder3);
						break;
					}
				case SEND_BONUS_POINTS: //ID PERSONAGEM,VETOR EM ORDEM ALFABETICA COM QTD PONTOS DA HABILIDADE PRIMARIA USADA E A QUANTIDADE DE PONTOS DE SKILL(PODER)[PODER1,PODER2,PODER3]
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idJogador	= mesRecebida.readInt();

						int    agilidade	= mesRecebida.readInt();
						int    destreza		= mesRecebida.readInt();
						int    forca		= mesRecebida.readInt();
						int    instinto		= mesRecebida.readInt();
						int    resistencia  = mesRecebida.readInt();

						int    poder1		= mesRecebida.readInt();
						int    poder2		= mesRecebida.readInt();
						int    poder3		= mesRecebida.readInt();
						
						_playersList->getElementAt(indexJogador)->getCharacter()->distibutePoints(agilidade, (int)AGI);
						_playersList->getElementAt(indexJogador)->getCharacter()->distibutePoints(destreza, (int)DES);
						_playersList->getElementAt(indexJogador)->getCharacter()->distibutePoints(forca, (int)FOR);
						_playersList->getElementAt(indexJogador)->getCharacter()->distibutePoints(instinto, (int)INS);
						_playersList->getElementAt(indexJogador)->getCharacter()->distibutePoints(resistencia, (int)RES);

						_playersList->getElementAt(indexJogador)->getCharacter()->distibuteSkillPoints(poder1, 0);
						_playersList->getElementAt(indexJogador)->getCharacter()->distibuteSkillPoints(poder2, 1);
						_playersList->getElementAt(indexJogador)->getCharacter()->distibuteSkillPoints(poder3, 2);

						int ataque		= _playersList->getElementAt(indexJogador)->getCharacter()->getAttack();
						int dano		= _playersList->getElementAt(indexJogador)->getCharacter()->getDamage();
						int defesa		= _playersList->getElementAt(indexJogador)->getCharacter()->getStats()->getDefense();
						int velocidade  = _playersList->getElementAt(indexJogador)->getCharacter()->getStats()->getAttackRate();

						int lealdade_aranha		= _playersList->getElementAt(indexJogador)->getCharacter()->getLoyalty()->getLoyaltyToSpider();
						int lealdade_besouro	= _playersList->getElementAt(indexJogador)->getCharacter()->getLoyalty()->getLoyaltyToBeetle();
						int lealdade_escorpiao	= _playersList->getElementAt(indexJogador)->getCharacter()->getLoyalty()->getLoyaltyToScorpion();
						int lealdade_louva		= _playersList->getElementAt(indexJogador)->getCharacter()->getLoyalty()->getLoyaltyToMantis();
						int lealdade_vespa		= _playersList->getElementAt(indexJogador)->getCharacter()->getLoyalty()->getLoyaltyToWasp();

						poder1 = _playersList->getElementAt(indexJogador)->getCharacter()->getSkillLevel(0);
						poder2 = _playersList->getElementAt(indexJogador)->getCharacter()->getSkillLevel(1);
						poder3 = _playersList->getElementAt(indexJogador)->getCharacter()->getSkillLevel(2);

						agilidade	= _playersList->getElementAt(indexJogador)->getCharacter()->getAGI();
						destreza	= _playersList->getElementAt(indexJogador)->getCharacter()->getDES();
						forca		= _playersList->getElementAt(indexJogador)->getCharacter()->getFOR();
						instinto	= _playersList->getElementAt(indexJogador)->getCharacter()->getINS();
						resistencia = _playersList->getElementAt(indexJogador)->getCharacter()->getRES();
						
						sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),(int)SHOW_FULL_STATUS, agilidade, destreza, forca, instinto, resistencia, ataque, dano, defesa, velocidade, lealdade_aranha, lealdade_besouro, lealdade_escorpiao, lealdade_louva, lealdade_vespa, poder1, poder2, poder3);

						break;
					}
				case ACCEPT_QUEST: // ID PERSONAGEM, ID QUEST
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem	= mesRecebida.readInt();
						int    idQuest		= mesRecebida.readInt();



						break;
					}
				case START_SHOP: //ID PERSONAGEM, ID NPC VENDEDOR
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idJogador	= mesRecebida.readInt();
						int    idPersonagem	= mesRecebida.readInt();
						int    idNPC		= mesRecebida.readInt();

						char data[1400];
						CBugMessage tempMes;
						tempMes.init(data,sizeof(data));

						CVendedor * tempVendedor = _playersList->getElementAt(indexJogador)->getScene()->getSalesman(idNPC);

						tempMes.writeByte(SHOW_SHOP);
						for(int p = 0; p < tempVendedor->getBolsa()->size(); p++)
						{
							tempMes.writeInt(tempVendedor->getBolsa()->getElementAt(p)->getID());
						}

						sendMessage(false,-1,_playersList->getElementAt(indexJogador)->getSocket(),tempMes);

						break;
					}
				case BUY_ITEM: //IDPERSONAGEM, IDNPC VENDEDOR, ID ITEM
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem	= mesRecebida.readInt();
						int    idNPC		= mesRecebida.readInt();
						int    idItem		= mesRecebida.readInt();


						break;
					}
				case REQUEST_PRICE_ITEM: //ID PERSONAGEM, ID NPCVENDEDOR, ID ITEM
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem	= mesRecebida.readInt();
						int    idNPC		= mesRecebida.readInt();
						int    idItem		= mesRecebida.readInt();


						break;
					}
				case SELL_ITEM: //IDPERSOANGEM, ID NPCVENDEDOR, ID ITEM, PRECO
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int    idPersonagem	= mesRecebida.readInt();
						int    idNPC		= mesRecebida.readInt();
						int    idItem		= mesRecebida.readInt();
						int    preco		= mesRecebida.readInt();

						
						
						break;
					}	
				case TRADE_REQUEST: //ID PERSONAGEM, ID FREGUES
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();
						
						int idJogador	  = mesRecebida.readInt();
						int idPersonagem1 = mesRecebida.readInt();
						int idPersonagem2 = mesRecebida.readInt();
						
						CPersonagemJogador * tempPers = _playersList->getElementAt(indexJogador)->getScene()->getPlayer(idPersonagem2);

						if(!tempPers->isTradeOn())
						{
							sendMessage( false,-1, tempPers->getSocket(), (int)TRADE_REQUEST, idPersonagem2, idPersonagem1);
						}
						else
						{
							sendMessage( false, -1, _playersList->getElementAt(indexJogador)->getCharacter()->getSocket(), (int)TRADE_REQUEST_REFUSED, idPersonagem2, idPersonagem1);
						}

						break;
					}
				case TRADE_REQUEST_ACCEPTED: //ID PERSONAGEM, ID FREGUES
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int idJogador	  = mesRecebida.readInt();
						int idPersonagem1 = mesRecebida.readInt();
						int idPersonagem2 = mesRecebida.readInt();

						_playersList->getElementAt(indexJogador)->getCharacter()->setTradeOn(true);
						_playersList->getElementAt(indexJogador)->getCharacter()->setIDTrader(idPersonagem2);
						
						CPersonagemJogador * tempPers = _playersList->getElementAt(indexJogador)->getScene()->getPlayer(idPersonagem2);

						sendMessage( false, -1,tempPers->getSocket(), (int)TRADE_REQUEST_ACCEPTED, idPersonagem2, idPersonagem1);

						break;
					}
				case TRADE_REQUEST_REFUSED: //ID PERSONAGEM, ID FREGUES
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int idJogador	  = mesRecebida.readInt();
						int idPersonagem1 = mesRecebida.readInt();
						int idPersonagem2 = mesRecebida.readInt();

						_playersList->getElementAt(indexJogador)->getCharacter()->setTradeOn(false);
						_playersList->getElementAt(indexJogador)->getCharacter()->setIDTrader(-1);
						
						CPersonagemJogador * tempPers = _playersList->getElementAt(indexJogador)->getScene()->getPlayer(idPersonagem2);

						sendMessage( false, -1,tempPers->getSocket(), (int)TRADE_REQUEST_REFUSED, idPersonagem2, idPersonagem1);

						break;
					}
				case TRADE_CHANGED: //ID PERSONAGEM, ID FREGUES, idItemPersonagem, idItemFregues, qtdDinheiroPersonagem, qtdDinheiroFregues
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int idJogador			= mesRecebida.readInt();
						int idPersonagem1		= mesRecebida.readInt();
						int idPersonagem2		= mesRecebida.readInt();
						int idItemPersonagem1	= mesRecebida.readInt();
						int idItemPersonagem2	= mesRecebida.readInt();
						int dinheiroPersonagem1 = mesRecebida.readInt();
						int dinheiroPersonagem2 = mesRecebida.readInt();
						
						_playersList->getElementAt(indexJogador)->getCharacter()->setIDTrader(idPersonagem2);
						_playersList->getElementAt(indexJogador)->getCharacter()->setIDItemTrade(idItemPersonagem2);
						_playersList->getElementAt(indexJogador)->getCharacter()->setIDMoneyTrade(dinheiroPersonagem2);
						_playersList->getElementAt(indexJogador)->getCharacter()->setTradeConfirmated(false);

						CPersonagemJogador * tempPers = _playersList->getElementAt(indexJogador)->getScene()->getPlayer(idPersonagem2);

						tempPers->setIDTrader(idPersonagem1);
						tempPers->setIDItemTrade(idItemPersonagem1);
						tempPers->setIDMoneyTrade(dinheiroPersonagem1);
						tempPers->setTradeConfirmated(false);

						sendMessage( false, -1, tempPers->getSocket(), (int)TRADE_CHANGED, idPersonagem2, idPersonagem1, idItemPersonagem2, idItemPersonagem1, dinheiroPersonagem2, dinheiroPersonagem1);

						break;
					}
				case TRADE_ACCEPTED: //ID PERSONAGEM
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int idJogador			= mesRecebida.readInt();
						int idPersonagem1		= mesRecebida.readInt();
						int idPersonagem2		= mesRecebida.readInt();
						int idItem1;
						int dinheiro1;
						int idItem2;
						int dinheiro2;

						_playersList->getElementAt(indexJogador)->getCharacter()->setTradeConfirmated(true);

						CPersonagemJogador * tempPers = _playersList->getElementAt(indexJogador)->getScene()->getPlayer(idPersonagem2);

						//se os dois envolvidos na troca confirmarem a troca
						if(tempPers->isTradeConfirmated())
						{
							idItem1   = _playersList->getElementAt(indexJogador)->getCharacter()->getIDItemTrade();
							dinheiro1 = _playersList->getElementAt(indexJogador)->getCharacter()->getIDMoneyTrade();

							idItem2   = tempPers->getIDItemTrade();
							dinheiro2 = tempPers->getIDMoneyTrade();

							CItem * tempItem1 = _playersList->getElementAt(indexJogador)->getCharacter()->getBolsa()->removeItem(idItem1);
							CItem * tempItem2 = tempPers->getBolsa()->removeItem(idItem2);

							_playersList->getElementAt(indexJogador)->getCharacter()->addItem(tempItem2);
							_playersList->getElementAt(indexJogador)->getCharacter()->addMoney(dinheiro2);

							tempPers->addItem(tempItem1);
							tempPers->addMoney(dinheiro1);

							sendMessage( false, -1, _playersList->getElementAt(indexJogador)->getCharacter()->getSocket(), (int)TRADE_CONCLUDE, idPersonagem1, idPersonagem2, idItem1, idItem2, dinheiro1, dinheiro2);
							sendMessage( false, -1, tempPers->getSocket(), (int)TRADE_CONCLUDE, idPersonagem2, idPersonagem1, idItem2, idItem1, dinheiro2, dinheiro1);

							_playersList->getElementAt(indexJogador)->getCharacter()->setIDTrader(-1);
							_playersList->getElementAt(indexJogador)->getCharacter()->setIDItemTrade(-1);
							_playersList->getElementAt(indexJogador)->getCharacter()->setIDMoneyTrade(-1);
							_playersList->getElementAt(indexJogador)->getCharacter()->setTradeConfirmated(false);
							_playersList->getElementAt(indexJogador)->getCharacter()->setTradeOn(false);

							tempPers->setIDTrader(-1);
							tempPers->setIDItemTrade(-1);
							tempPers->setIDMoneyTrade(-1);
							tempPers->setTradeConfirmated(false);
							tempPers->setTradeOn(false);
					
						}
						else
						{
							sendMessage( false, -1, tempPers->getSocket(), (int)TRADE_ACCEPTED, idPersonagem2, idPersonagem1, idItem2, idItem1, dinheiro2, dinheiro1);
						}

						break;
					}
				case TRADE_REFUSED: //ID PERSONAGEM, ID FREGUES
					{
						mesRecebida.beginReading();
						mesRecebida.readByte();

						int idJogador			= mesRecebida.readInt();
						int idPersonagem1		= mesRecebida.readInt();
						int idPersonagem2		= mesRecebida.readInt();

						_playersList->getElementAt(indexJogador)->getCharacter()->setIDTrader(-1);
						_playersList->getElementAt(indexJogador)->getCharacter()->setIDItemTrade(-1);
						_playersList->getElementAt(indexJogador)->getCharacter()->setIDMoneyTrade(-1);
						_playersList->getElementAt(indexJogador)->getCharacter()->setTradeConfirmated(false);
						_playersList->getElementAt(indexJogador)->getCharacter()->setTradeOn(false);

						CPersonagemJogador * tempPers = _playersList->getElementAt(indexJogador)->getScene()->getPlayer(idPersonagem2);

						tempPers->setIDTrader(-1);
						tempPers->setIDItemTrade(-1);
						tempPers->setIDMoneyTrade(-1);
						tempPers->setTradeConfirmated(false);
						tempPers->setTradeOn(false);

						sendMessage( false, -1, tempPers->getSocket(), (int)TRADE_REFUSED, idPersonagem2, idPersonagem1);
						sendMessage( false, -1, _playersList->getElementAt(indexJogador)->getSocket(), (int)TRADE_REFUSED, idPersonagem2, idPersonagem1);

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
	mes.writeInt(i1);
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

	mes.writeInt(p1->getID());
	mes.writeString(nome);
	mes.writeFloat(p1->getPosition()->x);
	mes.writeFloat(p1->getPosition()->z);
	mes.writeInt(p1->getStats()->getPV());
	mes.writeInt(p1->getStats()->getPM());
	mes.writeInt(p1->getStats()->getMaxPV());
	mes.writeInt(p1->getStats()->getMaxPM());

	mes.writeInt(p1->getLevel());

	
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
	
	mes.writeInt(race);
	mes.writeInt(tipoClasse);

	mes.writeInt(p1->getState());

	mes.writeFloat(p1->getMoveSpeed());
	mes.writeInt(p1->getDirection());

	mes.writeInt(idWeapon);
	mes.writeInt(idArmor);

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

	mes.writeInt(i1);

	for(int j = 0; j < i1; j++)
	{
		CPersonagemJogador * personagem = (CPersonagemJogador *)p1->getElementAt(j);
		//Dados pessoais
		mes.writeInt(personagem->getID());
		mes.writeString(personagem->getName());
		mes.writeInt(personagem->getLevel());
		//Habilidades Primárias
		mes.writeInt(personagem->getAGI());
		mes.writeInt(personagem->getDES());
		mes.writeInt(personagem->getFOR());
		mes.writeInt(personagem->getINS());
		mes.writeInt(personagem->getRES());
		//Habilidades Secundárias
		mes.writeInt(personagem->getStats()->getAttackRate());
		mes.writeInt(personagem->getStats()->getChargeTime());
		mes.writeInt(personagem->getStats()->getDefense());
		mes.writeInt(personagem->getStats()->getMeleeAttack());
		mes.writeInt(personagem->getStats()->getMeleeDamage());
		mes.writeInt(personagem->getStats()->getRangedAttack());
		mes.writeInt(personagem->getStats()->getRangedDamage());
		//3D
		mes.writeInt(personagem->getModel());
		mes.writeInt(personagem->get3DTexture());
		mes.writeInt(personagem->get2DTexture());
	}

	sendMessage(toAll, idCenario, destino, mes);	
}


void CCoreServer::sendMessage(bool toAll, int idCenario, CBugSocket * destino, int idMensagem, int i1, int i2, float f1, float f2)
{
	char data[1400];
	CBugMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);

	mes.writeInt(i1);
	mes.writeInt(i2);
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

	mes.writeInt(i1);
	mes.writeInt(i2);
	mes.writeInt(i3);
	mes.writeInt(i4);
	mes.writeInt(i5);
	mes.writeInt(i6);
	mes.writeInt(i7);
	mes.writeInt(i8);
	mes.writeInt(i9);
	mes.writeInt(i10);

	sendMessage(toAll, idCenario, destino, mes);
}

void CCoreServer::sendMessage(bool toAll, int idCenario, CBugSocket * destino, int idMensagem, int i1)
{
	char data[1400];
	CBugMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);
///
	mes.writeInt(i1);

	sendMessage(toAll, idCenario, destino, mes);
}

void CCoreServer::sendMessage(bool toAll, int idCenario, CBugSocket * destino, int idMensagem, int i1, int i2)
{
	char data[1400];
	CBugMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);

	mes.writeInt(i1);
	mes.writeInt(i2);

	sendMessage(toAll, idCenario, destino, mes);
}

void CCoreServer::sendMessage(bool toAll, int idCenario, CBugSocket * destino, int idMensagem, int i1, int i2, int i3)
{
	char data[1400];
	CBugMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);

	mes.writeInt(i1);
	mes.writeInt(i2);
	mes.writeInt(i3);

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

	mes.writeInt(i1);
	mes.writeInt(i2);
	mes.writeInt(i3);
	mes.writeInt(i4);
	mes.writeInt(i5);
	mes.writeInt(i6);
	mes.writeInt(i7);
	mes.writeInt(i8);
	mes.writeInt(i9);
	
	sendMessage(toAll, idCenario, destino, mes);
}

void CCoreServer::sendMessage(bool toAll, int idCenario, CBugSocket * destino, int idMensagem, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9, int i10, int i11, int i12, int i13, int i14, int i15, int i16, int i17)
{
	char data[1400];
	CBugMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);

	mes.writeInt(i1);
	mes.writeInt(i2);
	mes.writeInt(i3);
	mes.writeInt(i4);
	mes.writeInt(i5);
	mes.writeInt(i6);
	mes.writeInt(i7);
	mes.writeInt(i8);
	mes.writeInt(i9);
	mes.writeInt(i10);
	mes.writeInt(i11);
	mes.writeInt(i12);
	mes.writeInt(i13);
	mes.writeInt(i14);
	mes.writeInt(i15);
	mes.writeInt(i16);
	mes.writeInt(i17);	
	sendMessage(toAll, idCenario, destino, mes);
}

void CCoreServer::sendMessage(bool toAll, int idCenario, CBugSocket * destino, int idMensagem, int i1, int i2, int i3, int i4, int i5, int i6)
{
	char data[1400];
	CBugMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);

	mes.writeInt(i1);
	mes.writeInt(i2);
	mes.writeInt(i3);
	mes.writeInt(i4);
	mes.writeInt(i5);
	mes.writeInt(i6);

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
		mes.writeInt(v1[i]);
	}

	for(int i = 0; i < 30; i++)
	{
		mes.writeInt(v2[i]);
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
					if(frame->_idCenario == -1)
					{
						try{
							cList->getElementAt(index)->getSocket()->SendLine(*frame->_message);
						}
						catch(...)
						{
							cList->removeJogadorAt(index);
							index--;
						}
					}
					else
					if(frame->_idCenario == cList->getElementAt(index)->getScene()->getID())
					{
						try{
							cList->getElementAt(index)->getSocket()->SendLine(*frame->_message);
						}
						catch(...)
						{
							cList->removeJogadorAt(index);
							index--;
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
					System::String ^ texto = L"Não foi possivel mandar a mensagem!";
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


/*
	Salvará todas as informações que estão na memória, para o servidor
*/
void CCoreServer::backupAll()
{

	// 1. Salva Persoangens
		// 1.1 Update do personagem e todas as suas variaveis
	// 2. Salva Itens Personagens
		// 2.1 Remove itens que não estão mais com o personagem
		// 2.2 Atualiza os que ainda estão com ele(inclusive a durabilidade, mas no relacionamento)
		// 2.3 Insere os novos itens que o persoangem possui
	// 3. Salva Poderes do Personagem
		// 3.1 Atualiza as informações dos poderes que o personagem possui
	// 4. Salva Informações da formula de mercado se o personagem for o vendedor
		// 4.1 Insere as informações que o vendedor possui naquele momento
	// 5. Salva o Cénario
		// 5.1 Atualiza a Localização de todos os Personagens

	//
}
