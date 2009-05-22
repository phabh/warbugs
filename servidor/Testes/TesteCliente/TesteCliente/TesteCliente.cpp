// TesteCliente.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <CBugSocket.h>

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

	TRADE_REQUEST, //ID PERSONAGEM, ID FREGUES
	TRADE_REQUEST_ACCEPTED, //ID PERSONAGEM, ID FREGUES
	TRADE_REQUEST_REFUSED, //ID PERSONAGEM, ID FREGUES
	TRADE_CHANGED, //ID PERSONAGEM, ID FREGUES, idItemPersonagem, idItemFregues, qtdDinheiroPersonagem, qtdDinheiroFregues
	TRADE_ACCEPTED, //ID PERSONAGEM
	TRADE_REFUSED, //ID PERSONAGEM, ID FREGUES
	TRADE_CONCLUDE, //ID PERSONAGEM, ID FREGUES

	EQUIP_ITEM, //ID PERSONAGEM, ID ARMA, ID ARMADURA
	SET_TARGET, //ID PERSONAGEM, ID ALVO
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

#define PORT 30003

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
		CBugSocketClient * _socketClient = new CBugSocketClient("127.0.0.1",PORT);

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
			if(mesRec.getSize() != 0)
			{
				//começa a ler o pacote
				mesRec.beginReading();


			
				cout<<"\nPacote Recebido = "<< mesRec.readByte(); //le o id da mensagem
				cout<<"\nPacote Recebido = "<< mesRec.readByte(); //le o id da mensagem
				//cout<<"\nPacote Recebido = "<< mesRec.readString(); //e por ae vai =D
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