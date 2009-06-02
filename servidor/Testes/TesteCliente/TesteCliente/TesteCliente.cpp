// TesteCliente.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <CBugSocket.h>

using namespace std;

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
	CREATE_PLAYER_FAIL, //não foi possível criar o player
	DELETE_PLAYER_OK,	
	DELETE_PLAYER_FAIL,
	ENTER_CENARIO,//id cenario, POSICAO X, POSICAO Z, qtd Inimigos, qtdNPC, qtdVendedores, qtdPersonagensJogadores, qtdBolsa
	ADD_PERSONAGEM, //atributos do outros persoangens NPC, Jogadores
	ADD_BOLSA,//id bolsa, POSICAO X, POSICAO Z, estado bolsa
	UPDATE_POSITION, //ID PERSONAGEM, POSICAO X, POSICAO Z
	UPDATE_ESTADO, //IDPERSONAGEM, ESTADO
	UPDATE_ATACK, //ID PERSONAGEM, ID ALVO, ID ATAQUE
	OPENED_BOLSA, //ID BOLSA, ITENS DA BOLSA -1 se não houver nada
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
	SEND_ATACK, //ID PERSONAGEM, ID ALVO, ID ATAQUE, POSICAO X E POSICAO Z ALVO CHÃO //PODE SER PODER OU ATAQUE NORMAL
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

enum Raca 
{
	NONERACE, 
	ALLRACE, 
	ARANHA, 
	BESOURO, 
	ESCORPIAO, 
	LOUVADEUS, 
	VESPA, 
	CUPIM, 
	FORMIGA, 
	BARBEIRO, 
	BARATA, 
	TATUBOLINHA, 
	LIBELULA, 
	PERCEVEJO, 
	ABELHA, 
	LAGARTIXA, 
	CALANGO, 
	SAPO, 
	JOANINHA, 
	CAMALEAO
};

#define PORT 30003
#define NUMCONNECTIONS 54
#define NUMPERSONAGEMJOGADOR 2

int main()
{
	char	dadosRec[1400];
	char	dadosEnv[1400];

	CBugMessage mesRec;
	mesRec.init(dadosRec,1400);

	CBugMessage mesEnv;
	mesEnv.init(dadosEnv,1400);

	char login[15];
	char senha[15];

	CBugSocketClient * _socketClient;

	//tratamento de erro caso não seja possível conectar
	try{
		//endereço do server do warbugs
		//se você executar o server que fiz provavelmente pode dar erro
		//por não possuir o banco de dados, mas se não der erro ele irá
		//conseguir ler as mensagens e falar que o usuário é invalido
		CBugSocketClient * _socketClient = new CBugSocketClient("10.16.11.34",PORT);

		while(true) //so pra testar
		{

			cout<<"\nDigite o usuario: ";
			cin.getline(login,15);

			cout<<"\nDigite a senha: ";
			cin.getline(senha,15);

			mesEnv.writeByte(LOGIN_REQUEST); // requisição de login
			mesEnv.writeString(login);       // login
			mesEnv.writeString(senha);		 // senha

			//Envia a mensagem
			_socketClient->SendLine(mesEnv);



			cout<<"\nRecebendo Pacote...";
			//recebe o pacote
			_socketClient->ReceiveLine(mesRec);

			cout<<"\nRecebeu Pacote";
			int idJogador;
			if(mesRec.getSize() != 0)
			{
				cout<<"\nidMensagem = "<< mesRec.readByte(); //le o id da mensagem
				idJogador = mesRec.readInt();
				cout<<"\nidJogador = "<< idJogador; //le o id da mensagem
				//cout<<"\nPacote Recebido = "<< mesRec.readString(); //e por ae vai =D
			}


			mesEnv.clear();
			mesEnv.writeByte(PERSONAGENS_REQUEST); // requisição de login
			mesEnv.writeInt(idJogador);

			//Envia a mensagem
			_socketClient->SendLine(mesEnv);



			cout<<"\nRecebendo Pacote...";
			//recebe o pacote
			mesRec.clear();
			_socketClient->ReceiveLine(mesRec);

			cout<<"\nRecebeu Pacote";
			if(mesRec.getSize() != 0)
			{
				mesRec.readByte(); //le o id da mensagem

				if(mesRec.readInt() > 0)
				{
					cout<<"\nPacote Recebido = "<<mesRec.readInt();
					cout<<"\nPacote Recebido = "<<mesRec.readString();
					cout<<"\nPacote Recebido = "<<mesRec.readInt();
					//Habilidades Primárias
					cout<<"\nPacote Recebido = "<<mesRec.readInt();
					cout<<"\nPacote Recebido = "<<mesRec.readInt();
					cout<<"\nPacote Recebido = "<<mesRec.readInt();
					cout<<"\nPacote Recebido = "<<mesRec.readInt();
					cout<<"\nPacote Recebido = "<<mesRec.readInt();
					//Habilidades Secundárias
					cout<<"\nPacote Recebido = "<<mesRec.readInt();
					cout<<"\nPacote Recebido = "<<mesRec.readInt();
					cout<<"\nPacote Recebido = "<<mesRec.readInt();
					cout<<"\nPacote Recebido = "<<mesRec.readInt();
					cout<<"\nPacote Recebido = "<<mesRec.readInt();
					cout<<"\nPacote Recebido = "<<mesRec.readInt();
					cout<<"\nPacote Recebido = "<<mesRec.readInt();
					//3D
					cout<<"\nPacote Recebido = "<<mesRec.readInt();
					cout<<"\nPacote Recebido = "<<mesRec.readInt();
					cout<<"\nPacote Recebido = "<<mesRec.readInt();

					mesEnv.clear();
					mesEnv.writeByte(DELETE_PERSONAGEM); // requisição de login
					mesEnv.writeInt(idJogador);
					mesEnv.writeInt(19);
					mesEnv.writeString("Himureta");
					_socketClient->SendLine(mesEnv);

				}
				else
				{
					mesEnv.clear();
					mesEnv.writeByte(CREATE_PERSONAGEM); // requisição de login
					mesEnv.writeInt(idJogador);
					mesEnv.writeInt((int)VESPA);
					mesEnv.writeString("VespaPita");
					_socketClient->SendLine(mesEnv);
				}

				cout<<"\nRecebendo Pacote...";
				//recebe o pacote
				mesRec.clear();
				_socketClient->ReceiveLine(mesRec);
				cout<<"\nPacote Recebido = "<<mesRec.readByte();
			}
		}



	}catch(...)
	{
		cout<<"\nNão foi possivel Encontrar o servidor!";
		Sleep(2000);
		return 0;
	}
	return 0;

}