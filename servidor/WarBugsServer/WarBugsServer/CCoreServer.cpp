#include "CCoreServer.h"


CCoreServer::CCoreServer(CDataBase *db, int fps, System::Windows::Forms::ListBox^ log)
{
	WarBugsLog::_log = log;

	if(db != NULL)
		return;

	_db = db;

	//seta os fps dos servidor
	_fps = fps;

	System::String^ texto = L"Inicializando o Server...";
	WarBugsLog::_log->Items->Add(texto);
	initialize();
}


void CCoreServer::initialize()
{
	TDadosBD	   ^ dados = gcnew System::Collections::ArrayList();
	System::String ^sql;
	unsigned int	numCampos;
	unsigned int    numRegs;

	
	System::String^ texto = L"Pegando os dados do BD...";
	WarBugsLog::_log->Items->Add(texto);	

	if(_db->isConnected())
	{
		//1. selecionará os cenários jogáveis que há no bando de dados e irá criar a lista de cenários
		sql = "SELECT * FROM CENARIO";
		_db->selectNow(toChar(sql), numCampos, numRegs, dados);

		for(int i = 0; i < numCampos; i++)
		{
			dados->RemoveAt(0);
		}

		CCenario * cenarioTemp;

		texto = L"Criando todos os cenários";
		WarBugsLog::_log->Items->Add(texto);

		//preenchimento de todos os cenários
		for(int i = 0; i < numRegs; i++)
		{

			cenarioTemp = new CCenario();
			cenarioTemp->setID(Int32::Parse(dados[0]->ToString());
			cenarioTemp->setNome(Int32::Parse(dados[1]->ToString());
			cenarioTemp->setIDModelo(Int32::Parse(dados[2]->ToString());
			cenarioTemp->setIDTextura(Int32::Parse(dados[3]->ToString());
			cenarioTemp->_next = NULL;

			//se for o primeiro cenário
			if(_cenarioList == NULL)
			{
				_cenarioList = cenarioTemp;
			}
			//do segundo em diante
			else
			{
				CCenario * temp = _cenarioList;

				for(; temp != NULL; temp = temp->_next)
				{
					
				}

				temp = cenarioTemp;				
			}

			for(int i = 0; i < numCampos; i++)
			{
				dados->RemoveAt(0);
			}
		}


		texto = L"Criando todos os persoangens e colocando-os em seus respectivos cenários";
		WarBugsLog::_log->Items->Add(texto);

		//colocando todos os personagem em seus cenários
		// 1 - Jogador
		// 2 - Inimigo
		// 3 - NPC
		// 4 - Vendedor
		
		dados     = gcnew System::Collections::ArrayList();
		numCampos = 0;
		numRegs   = 0;

		sql = "SELECT * FROM PERSONAGEM WHERE TIPO = 2";
		_db->selectNow(toChar(sql), numCampos, numRegs, dados);		
		
		for(int i = 0; i < numCampos; i++)
		{
			dados->RemoveAt(0);
		}

		CInimigo * inimigoTemp;
		CHabilidadesSecundarias * habiSecunTemp;

		texto = L"Inimigos";
		WarBugsLog::_log->Items->Add(texto);

		for(int i = 0; i < numRegs; i++)
		{
			habiSecunTemp = new CHabilidadesSecundarias(
				System::Int32::Parse(dados[12]->ToString()), //Pontos de Vida
				System::Int32::Parse(dados[13]->ToString()), //Pontos de Poder
				System::Int32::Parse(dados[15]->ToString()), //Ataque Corpo a Corpo
				System::Int32::Parse(dados[14]->ToString()), //Ataque a Distancia
				System::Int32::Parse(dados[16]->ToString()), //Dano Corpo a Corpo
				System::Int32::Parse(dados[17]->ToString()), //Dano a Distancia
				System::Int32::Parse(dados[18]->ToString()), //Defesa
				System::Int32::Parse(dados[19]->ToString()), //Taxa de Ataque
				System::Int32::Parse(dados[20]->ToString()));//Tempo de Carga

			inimigoTemp = new CInimigo();
			inimigoTemp->setID(System::Int32::Parse(dados[0]->ToString()));
			inimigoTemp->setNome(dados[1]->ToString());
			inimigoTemp->setNivel(System::Int32::Parse(dados[0]->ToString()));
			inimigoTemp->setPV(System::Int32::Parse(dados[0]->ToString()));
			inimigoTemp->setID(System::Int32::Parse(dados[0]->ToString()));
			inimigoTemp->setID(System::Int32::Parse(dados[0]->ToString()));
			inimigoTemp->setID(System::Int32::Parse(dados[0]->ToString()));
			inimigoTemp->setID(System::Int32::Parse(dados[0]->ToString()));
			inimigoTemp->setID(System::Int32::Parse(dados[0]->ToString()));
			inimigoTemp->setID(System::Int32::Parse(dados[0]->ToString()));
			inimigoTemp->setID(System::Int32::Parse(dados[0]->ToString()));
			inimigoTemp->setID(System::Int32::Parse(dados[0]->ToString()));
			inimigoTemp->setID(System::Int32::Parse(dados[0]->ToString()));
			inimigoTemp->setID(System::Int32::Parse(dados[0]->ToString()));
			inimigoTemp->setID(System::Int32::Parse(dados[0]->ToString()));
			inimigoTemp->setID(System::Int32::Parse(dados[0]->ToString()));
			inimigoTemp->setID(System::Int32::Parse(dados[0]->ToString()));
			inimigoTemp->setID(System::Int32::Parse(dados[0]->ToString()));
			inimigoTemp->setID(System::Int32::Parse(dados[0]->ToString()));
			inimigoTemp->setID(System::Int32::Parse(dados[0]->ToString()));
		}



	//Aki acontecerá o seguinte

	//1. selecionará os cenários jogáveis que há no bando de dados e irá criar a lista de cenários
	
	//2. selecionará os inimigos em cada cenário e irá criar para eles a lista de objetos em cada cenário

	//3. selecionará os npcs em cada cenário e irá criar para eles a lista de objetos em cada cenário

	//4. selecionará os vendedor em cada cenário e irá criar para eles a lista de objetos em cada cenário

	//5. selecionará os itens em cada cenário e irá criar para eles a lista de objetos em cada cenário

	//6. selecionará os personagens Jogadores em cada cenário e irá criar para eles a lista de objetos em cada cenário

	//7. selecionará os personagens Jogadores em cada cenário e irá criar para eles a lista de objetos em cada cenário

	}

}

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
						int    posX = mesRecebida.readFloat();
						int    posZ = mesRecebida.readFloat();

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
						int    posX         = mesRecebida.readFloat();
						int    posZ         = mesRecebida.readFloat();

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
						int    posX			= mesRecebida.readFloat();
						int    posZ			= mesRecebida.readFloat();

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

/*
	Tratamento do Evento de login enviado pelo cliente
	@param player -> endereço de qual veio a msg;
	@param message -> mensagem que foi enviada pelo cliente;
*/
void CCoreServer::makeLogin(sockaddr *player, dreamMessage *message)
{
	System::String^ texto = L"Recebido pacotes tipo MAKE_LOGIN...";
	_log->Items->Add(texto);

	texto = L"Pacote :"+message->_data;
	_log->Items->Add(texto);

	char resposta[1400];
	dreamMessage mes;

	System::String ^login;
	System::String ^senha;

	char * dados;

	System::String ^query;

	int d = 0;
	bool lerSenha = false;

	TDadosBD ^BDDados = gcnew System::Collections::ArrayList();

	unsigned int numCampos;
	unsigned int numRegs;

	message->beginReading();
	message->readByte();

	login = gcnew System::String(message->readString());
	senha = gcnew System::String(message->readString());

	query = L"SELECT * FROM JOGADOR WHERE LOGIN = \""+login+"\" AND SENHA = \""+senha+"\"";

	if(_db == NULL || !_db->isConnected())
		return;

	_db->selectNow(toChar(query), numCampos, numRegs, BDDados);


	mes.init(resposta,sizeof(resposta));
	
	if(numRegs == 0)
	{
		mes.writeByte(LOGIN_FAIL);	
	}
	else
	{
		//retira os titulos dos campos dos dados
		for(int i = 0; i < numCampos; i++)
		{
			BDDados->RemoveAt(0);
		}

		CJogador * jogador = new CJogador(
			System::Int32::Parse(BDDados[0]->ToString()),	//ID
			toChar(BDDados[1]->ToString()),					//Nome
			toChar(BDDados[2]->ToString()),					//dataNasc
			toChar(BDDados[3]->ToString()),					//E-mail
			toChar(BDDados[4]->ToString()),					//Login
			toChar(BDDados[5]->ToString()),					//Senha
			player		//endereço Socket
			);
		
		addPlayer(jogador);

		mes.writeByte(SELECT_PLAYER);
		mes.writeLong(jogador->getId());

		query = "SELECT * FROM PERSONAGEMBASE WHERE IDJOGADOR = "<<jogador->getId();

		if(_db == NULL || !_db->isConnected())
			return;

		numCampos = 0;
		numRegs = 0;
		BDDados = gcnew System::Collections::ArrayList();

		_db->selectNow(toChar(query), numCampos, numRegs, BDDados);

		mes.writeLong(numRegs);

		//se houver personagens o bd manda os personagens que ele possui, 
		//se não manda todos os persoangens base para ele criar um
		if(numRegs > 0)
		{
			for(int i = 0; i< numCampos; i++)			
			{
				BDDados->RemoveAt(0);
			}

			for(int i = 0; i < numRegs; i++)
			{
				mes.writeByte(System::Int32::Parse(BDDados[4+(i*numRegs)]->ToString())); //id do Modelo
				mes.writeByte(System::Int32::Parse(BDDados[4+(i*numRegs)]->ToString())); //id Personagem
				mes.writeString(toChar(BDDados[4+(i*numRegs)]->ToString())); //nome do Personagem
				mes.writeByte(System::Int32::Parse(BDDados[4+(i*numRegs)]->ToString())); //level
				mes.writeByte(System::Int32::Parse(BDDados[4+(i*numRegs)]->ToString())); //id Arma
				mes.writeByte(System::Int32::Parse(BDDados[4+(i*numRegs)]->ToString())); //id Armadura
				mes.writeByte(System::Int32::Parse(BDDados[4+(i*numRegs)]->ToString())); //id Cenario
				mes.writeString(toChar(BDDados[4+(i*numRegs)]->ToString())); //nome Cenario
			}
		}
		else
		if(numRegs == 0)
		{
			query = "SELECT * FROM PERSONAGEMBASE WHERE PERSONAGEMPADRAO = TRUE";

			if(_db == NULL || !_db->isConnected())
				return;

			numCampos = 0;
			numRegs = 0;
			BDDados = gcnew System::Collections::ArrayList();

			_db->selectNow(toChar(query), numCampos, numRegs, BDDados);
			
			for(int i = 0; i< numCampos; i++)			
			{
				BDDados->RemoveAt(0);
			}

			for(int i = 0; i < numRegs; i++)
			{
				mes.writeByte(System::Int32::Parse(BDDados[4+(i*numRegs)]->ToString())); //id do Modelo
				mes.writeByte(System::Int32::Parse(BDDados[4+(i*numRegs)]->ToString())); //id Personagem
				mes.writeString(toChar(BDDados[4+(i*numRegs)]->ToString())); //nome do Personagem
				mes.writeByte(System::Int32::Parse(BDDados[4+(i*numRegs)]->ToString())); //level
				mes.writeByte(System::Int32::Parse(BDDados[4+(i*numRegs)]->ToString())); //id Arma
				mes.writeByte(System::Int32::Parse(BDDados[4+(i*numRegs)]->ToString())); //id Armadura
				mes.writeByte(System::Int32::Parse(BDDados[4+(i*numRegs)]->ToString())); //id Cenario
				mes.writeString(toChar(BDDados[4+(i*numRegs)]->ToString())); //nome Cenario
			}		
		}

	}
	
	dreamClient * cList = _networkServer->getClientList();

	for(; cList != NULL; cList = cList->_next)
	{
		if(memcmp(cList->getSocketAddress(), player, sizeof(player)) == 0)
		{
			break;
		}
	}

	texto = L"Pacote Enviado:"+mes._data;
	_log->Items->Add(texto);

	cList->sendPacket(&mes);
}

/*
	Tratamento do Evento de criação de um novo personagem enviado pelo cliente
	@param player -> endereço de qual veio a msg;
	@param message -> mensagem que foi enviada pelo cliente;
*/
void CCoreServer::createPlayer(sockaddr *player, dreamMessage *message)
{
	System::String^ texto = L"Recebido pacotes tipo CREATE_PLAYER...";
	_log->Items->Add(texto);

	texto = L"Pacote: "+message->_data;
	_log->Items->Add(texto);

	char resposta[1400];
	dreamMessage mes;

	int idJogador;
	int idPersonagem;

	System::String ^ query;
	System::String ^ nomePersoangem;

	int d = 0;

	TDadosBD ^BDDados = gcnew System::Collections::ArrayList();

	unsigned int numCampos;
	unsigned int numRegs;
	int numPersonagens;


	query = "SELECT MAX(IDPERSONAGEM) FROM PERSONAGEMBASE";

	if(_db == NULL || !_db->isConnected())
		return;

	numCampos = 0;
	numRegs = 0;
	BDDados = gcnew System::Collections::ArrayList();

	_db->selectNow(toChar(query), numCampos, numRegs, BDDados);

	for(int i = 0; i < numCampos; i++)
	{
		BDDados->RemoveAt(0);
	}

	numPersonagens = System::Int32::Parse(BDDados[0]->ToString())+1;


	message->beginReading();
	message->readByte();

	idJogador		= message->readLong();
	idPersonagem	= message->readLong();

	nomePersonagem = gcnew System::String(message->readString());

	query = L"SELECT * FROM PERSONAGEMBASE WHERE IDPERSONAGEM = "+idPersonagem+" AND PERSONAGEMPADRAO = TRUE";

	if(_db == NULL || !_db->isConnected())
		return;

	_db->selectNow(toChar(query), numCampos, numRegs, BDDados);

	mes.init(resposta,sizeof(resposta));
	
	if(numRegs == 0)
	{
		mes.writeByte(CREATE_PLAYER_FAIL);	
	}
	else
	if(numRegs > 0)
	{
		//retira os titulos dos campos dos dados
		for(int i = 0; i < numCampos; i++)
		{
			BDDados->RemoveAt(0);
		}

		if(_db == NULL || !_db->isConnected())
			return;


		System::String ^q;

		q = gcnew System::String("INSERT INTO PERSONAGEMBASE VALUES("+numPersonagens);

		q = L""+q+",\""+nomePersonagem+"\"";

		for(int i = 2; i < numCampos-1; i++)
		{
			if(i == (numCampos-6))
				q = L""+q+","+idJogador;
			else
				q = L""+q+","+BDDados[i];
		}

		q = L""+q+", FALSE)";


		_db->insertNow(toChar(query));

		mes.writeByte(SELECT_PLAYER);
		mes.writeLong(jogador->getId());

		mes.writeLong(numRegs);

		mes.writeByte(System::Int32::Parse(BDDados[4]->ToString())); //id do Modelo
		mes.writeByte(System::Int32::Parse(BDDados[4]->ToString())); //id Personagem
		mes.writeString(toChar(BDDados[4]->ToString())); //nome do Personagem
		mes.writeByte(System::Int32::Parse(BDDados[4]->ToString())); //level
		mes.writeByte(System::Int32::Parse(BDDados[4]->ToString())); //id Arma
		mes.writeByte(System::Int32::Parse(BDDados[4]->ToString())); //id Armadura
		mes.writeByte(System::Int32::Parse(BDDados[4]->ToString())); //id Cenario
		mes.writeString(toChar(BDDados[4]->ToString())); //nome Cenario

	}
	
	dreamClient * cList = _networkServer->getClientList();

	for(; cList != NULL; cList = cList->_next)
	{
		if(memcmp(cList->getSocketAddress(), player, sizeof(player)) == 0)
		{
			break;
		}
	}

	texto = L"Pacote Enviado: "+mes._data;
	_log->Items->Add(texto);

	cList->sendPacket(&mes);
}

/*
	Irá tratar o evento de seleção do player executado pelo cliente
	@param player -> o player que enviou a mensagem
	@param message -> a mensagem enviada
*/
void CCoreServer::selectPlayer(sockaddr *player, dreamMessage *message)
{
	System::String^ texto = L"Recebido pacotes tipo SELECT_PLAYER...";
	_log->Items->Add(texto);

	texto = L"Pacote: "+message->_data;
	_log->Items->Add(texto);

	TDadosBD ^dados = gcnew System::Collections::ArrayList();

	System::String ^query;

	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;

	message->beginReading();
	message->readByte(); //id da mensagem

	int idJogador	 = (int)message->readLong();
	int idPersonagem = (int)message->readLong();

	if(_db == NULL || !_db->isConnected())
		return;

	query = L"SELECT * FROM PERSONAGEMBASE WHERE IDPERSONAGEM = "+idPersonagem+" AND IDJOGADOR = "+idJogador;

	_db->selectNow(toChar(query), numCampos, numRegs, dados);

	char resposta[1400];
	dreamMessage mes;
	mes.init(reposta,sizeof(resposta));

	if(numRegs <= 0)
	{
		mes.writeByte(SELECT_PLAYER_FAIL);
	}
	else
	if(numRegs > 0)
	{
		//remove os cabeçalhos dos campos
		for(int i = 0; i < numCampos; i++)
		{
			dados->RemoveAt(0);
		}

		//monta o objeto personagem para jogar
		CPersonagemJogador * tempJogador = new CPersonagemJogador();

			//setará todas as variaveis do jogador
			tempJogador->setPosition(dados[0]);
			tempJogador->setPosition(dados[0]);
			tempJogador->setPosition(dados[0]);
			tempJogador->setPosition(dados[0]);
			tempJogador->setPosition(dados[0]);
			tempJogador->setPosition(dados[0]);
			tempJogador->setPosition(dados[0]);
			tempJogador->setPosition(dados[0]);
			tempJogador->setPosition(dados[0]);
			tempJogador->setPosition(dados[0]);
			tempJogador->setPosition(dados[0]);
			tempJogador->setPosition(dados[0]);


			int idCenario = System::Int32::Parse(dados[0]->ToString());

			dados = gcnew System::Collections::ArrayList();
			numRegs   = 0;
			numCampos = 0;

			query = L"SELECT I.* FROM ITEMBASE I, PERSONAGEMITEM PI, PERSONAGEMBASE P"+
					 " WHERE PI.IDITEM = I.IDITEM AND PI.IDPERSONAGEM = P.IDPERSONAGEM"+
					 " AND P.IDPERSONAGEM = "+idPersonagem+" AND P.IDJOGADOR = "+idJogador;
			
			_db->selectNow(toChar(query), numCampos, numRegs, dados);

			CItem * temp;
			
			//irá criar os itens de acordo com o tipo
			for(int i = 0; i < numRegs; i++)
			{
				switch(System::Int32::Parse(dados[0]->ToString()))
				{
					case USO: 
						break;
					case ARMA:
						break;
					case ARMADURA:
						break;
					case QUEST:
						break;
					case SCROLL:
						break;
					case LSCROLL:
						break;
				}			
			}

			/*
				Para cada atrihbuto do jogador que dependa de outra classe
				será selecionado em uma consulta SQL e adicionado ao objeto do Jogador
				e por ultimo irá colocar o jogador em um ponto do cenário que estava no BD
			*/

			CCenarioServer * listCenarioTemp = _cenarioList;
			
			for(;listCenarioTemp != NULL; listCenarioTemp = listCenarioTemp->_next)
			{
				//achei o cenario que o personagem irá entrar
				if(listCenarioTemp->getId() == idCenario))
				{
					break;
				}
			}

			//listCenarioTemp->addPlayer(tempJogador);

			CPersonagem * listTemp = _limbo;
			
			for(;listTemp != NULL; listTemp = listTemp->_next)
			{
				//achei o cenario que o personagem irá entrar
				if(listTemp->getId() != idPersonagem && listTemp->getIdJogador() != ))
				{
					break;
				}
			}

			/*
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
			
			*/

			mes.writeByte(ENTER_CENARIO);
			mes.writeLong(idCenario);					 //id do cenário que irá entrar
			mes.writeString(listCenarioTemp->getNome()); // nome do cenário em que irá entrar
			mes.writeLong(tempJogador->getPosition().x); //posicao x em que o jogador irá começar
			mes.writeLong(tempJogador->getPosition().y); //posicao y em que o jogador irá começar
			mes.writeLong(tempJogador->getIdAnimation());
			mes.writeLong(tempJogador->getIdModelo());
			mes.writeLong(tempJogador->getIdWeapon());
			mes.writeLong(tempJogador->getIdArmor());
			mes.writeLong(tempJogador->getPV());
			mes.writeLong(tempJogador->getPM());
			mes.writeLong(tempJogador->getXP());
			mes.writeLong(tempJogador->getDirecao());

	
	}

	dreamClient * cList = _networkServer->getClientList();

	for(; cList != NULL; cList = cList->_next)
	{
		if(memcmp(cList->getSocketAddress(), player, sizeof(player)) == 0)
		{
			break;
		}
	}

	cList->sendPacket(&mes);		

	texto = L"Pacote Enviado: "+mes._data;
	_log->Items->Add(texto);
}

/*
	Irá tratar o evento de entrada em um cenário executado pelo cliente
	@param player -> o player que enviou a mensagem
	@param message -> a mensagem enviada
*/
void CCoreServer::enterCenario(sockaddr *player, dreamMessage *message)
{
	
}

/*
	Irá mandar uma mensagem para o player especificado na mensagem
	@param player -> o player que enviou a mensagem
	@param message -> a mensagem enviada
*/
void CCoreServer::messageToPlayer(sockaddr *player, dreamMessage *message)
{

	System::String^ texto = L"Recebido pacotes tipo MESSAGETOPLAYER...";
	_log->Items->Add(texto);

	texto = L"Pacote: "+message->_data;
	_log->Items->Add(texto);

	message->beginReading();
	message->readByte();

	int idJogador	 = (int)message->readLong(); //que enviou
	int idPersonagem = (int)message->readLong(); //que enviou

	System::String ^nome = gcnew System::String(message->readString()) //que vai receber
	System::String ^msg  = gcnew System::String(message->readString()) //que vai receber

	int idJogadorEnviar = -1;
	System::String ^nomeRemetente; 

	char resposta[1400];
	dreamMessage mes;
	mes.init(resposta,sizeof(resposta));

	CPersoangemJogador * cTempListPersonagem;

	CCenarioServer * cTempListCenario = _cenarioList;

	CJogador * cTempListJogador = _playersList;

	//procura o nome que foi enviado nos cenários
	for(;cTempListCenario != NULL; cTempListCenario = cTempListCenario->_next)
	{
	
		for(; cTempListPersonagem != NULL; cTempListPersonagem = cTempListPersonagem->_next)
		{
			if(cTempListPersonagem->getId() == idPersonagem && cTempListPersonagem->getIdJogador() == idJogador)
			{
				nomeRemetente = gcnew System::String(cTempListPersonagem->getName());
				break;
			}
		}
	}

	for(;cTempListCenario != NULL; cTempListCenario = cTempListCenario->_next)
	{
	
		for(; cTempListPersonagem != NULL; cTempListPersonagem = cTempListPersonagem->_next)
		{
			if(stricmp(toChar(nome),cTempListPersonagem->getName()) == 0)
			{
				idJogadorEnviar = cTempListPersonagem->getIdJogador();
				break;
			}
		}
	}

	mes.writeByte(CHAT);
	if(idJogadorEnviar == -1)
	{	
		mes.writeString("Sistema: ");
		mes.writeString("Não foi possivel achar o jogador desejado, ele pode estar offline.");

		dreamClient * cTempListClient = _networkServer->getClientList();

		for(; cTempListClient != NULL; cTempListClient = cTempListClient->_next)
		{
			if(memcmp(cTempListClient->getSocketAddress(), player, sizeof(player)) == 0)
			{
				break;
			}
		}

		cTempListClient->sendPacket(&mes);

	}
	else
	if(idJogadorEnviar >= 0)
	{
		mes.writeString(toChar(nomeRemetente));
		mes.writeString(toChar(msg));

		sockaddr * endPlayer;
		for(;cTempListJogador != NULL; cTempListJogador = cTempListJogador->_next)
		{
			if(idJogadorEnvia == cTempListJogador->getId())
			{
				endPlayer = cTempListJogador->getSocketAddress();
				break;
			}
		}

		dreamClient * cTempListClient = _networkServer->getClientList();

		for(; cTempListClient != NULL; cTempListClient = cTempListClient->_next)
		{
			if(memcmp(cTempListClient->getSocketAddress(), endPlayer, sizeof(endPlayer)) == 0)
			{
				break;
			}
		}

		cTempListClient->sendPacket(&mes);

	}

	texto = L"Pacote: "+mes._data;
	_log->Items->Add(texto);
	
}


/*
	Irá mandar uma mensagem para todos os players do cenário
	@param player -> o player que enviou a mensagem
	@param message -> a mensagem enviada
*/
void CCoreServer::messageToAll(sockaddr *player, dreamMessage *message)
{
	message->beginReading();
	message->readByte();

	int idJogador = message->readLong();
	int idPersonagem = message->readLong();
	int idCenario = message->readLong();
	char * mensagem = message->readString();

	System::String^ texto = L"Recebido pacotes tipo MESSAGE_TOALL...";
	_log->Items->Add(texto);

	texto = L"Pacote :"+message->_data;
	_log->Items->Add(texto);

	char resposta[1400];
	dreamMessage mes;

	CJogador * jogador = _playersList;

	for(; jogador != NULL; jogador = jogador->_next)
	{
		if(jogador->getId() == idJogador && jogador->getIdPersonagem == idPersonagem)
		{
			break;
		}
	}

	mes.init(resposta,sizeof(resposta));
	mes.writeByte(CHAT);
	mes.writeString(jogador->getNamePersonagem());
	mes.writeString(mensagem);

	jogador = _playersList;


	for(; jogador != NULL; jogador = jogador->_next)
	{
		if(jogador->getIdCenario() == idCenario)
		{
			jogador->_netWork->sendPacket(&mes);		
		}
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


void CCoreServer::sendMessage(bool toAll, sockaddr destino, int idMensagem, CPersoangem p1)
{
	char data[1400];
	dreamMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);

	mes.writeLong(p1.getId());
	mes.writeString(p1.getNome());
	mes.writeFloat(p1.getPosX());
	mes.writeFloat(p1.getPosZ());
	mes.writeLong(p1.getPV());
	mes.writeLong(p1.getPP());
	mes.writeLong(p1.getNivel());
	mes.writeLong(p1.getPVMax());
	mes.writeLong(p1.getPPMax());

	/*
		AKI VAI TER QUE PREENCHER OS BUFFS CONFORME FOR, OLHA AE EDER
	*/
	short   buff;	

	bool    buffer[15]  = p1.getBuff();

	for(int i = 0; i < 14; i--)
	{
		buff = (short)(buffer[i] & pow(2,i));
	}

	mes.writeShort(buff);

	/*
		END BUFF
	*/

	mes.writeLong(p1.getEstado());
	mes.writeLong(p1.getRaca());
	mes.writeLong(p1.getTipoPersonagem());
	mes.writeLong(p1.getIdArma());
	mes.writeLong(p1.getIdArmadura());
	mes.writeFloat(p1.getDirecao());
	mes.writeFloat(p1.getVelocidade());

	sendMessage(toAll, destino, &mes);
}

void CCoreServer::sendMessage(bool toAll, sockaddr destino, int idMensagem, int i1, int i2, float f1, float f2)
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

void CCoreServer::sendMessage(bool toAll, sockaddr destino, int idMensagem, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9, int i10)
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

void CCoreServer::sendMessage(bool toAll, sockaddr destino, int idMensagem, int i1)
{
	char data[1400];
	dreamMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);

	mes.writeLong(i1);

	sendMessage(toAll, destino, &mes);
}

void CCoreServer::sendMessage(bool toAll, sockaddr destino, int idMensagem, int i1, int i2)
{
	char data[1400];
	dreamMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);

	mes.writeLong(i1);
	mes.writeLong(i2);

	sendMessage(toAll, destino, &mes);
}

void CCoreServer::sendMessage(bool toAll, sockaddr destino, int idMensagem, int i1, int i2, int i3)
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

void CCoreServer::sendMessage(bool toAll, sockaddr destino, int idMensagem)
{
	char data[1400];
	dreamMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);

	sendMessage(toAll, destino, &mes);
}

void CCoreServer::sendMessage(bool toAll, sockaddr destino, int idMensagem, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9)
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

void CCoreServer::sendMessage(bool toAll, sockaddr destino, int idMensagem, int i1, int i2, int i3, int i4, int i5, int i6)
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

void CCoreServer::sendMessage(bool toAll, sockaddr destino, int idMensagem, char * mensagem)
{
	char data[1400];
	dreamMessage mes;
	mes.init(data,sizeof(data));

	mes.writeByte(idMensagem);

	mes.writeString(mensagem);

	sendMessage(toAll, destino, &mes);
}

void CCoreServer::sendMessage(bool toAll, sockaddr destino, int idMensagem, int v1[30], int v2[30])
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
