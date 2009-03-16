class CCoreServer : CObject
{
		vector<CCenario>   _listaCenario;	//lista de cen�rios de todo o jogo
		vector<Socket>     _listaConexoes;  //lista das conex�es feitas com o server do jogo
		CDataBase        * _BD;             //Receber� o BD da classe superior
	public:
		static CTime       _hora;           //Hora corrente do jogo
		static int         _luaCorrente;    //a lua que est� em atividade

		CCoreServer(){}                    //Construtor Padr�o
		CCoreServer(CDataBase &bd);        //Construtor Secund�rio enviando de parametro o BD
		void gravarBD();			       //Fun��o que ser� incluida em uma Thread para gravar todas as altera��es 
										   //feitas no jogo no  BD
		void verificarPlayersOnLine();				 //Manda uma mensagem para os players e os que n�o responderem s�o kikados
		void enviarDados(int idConexao, char * msg); //Manda mensagem especificada para o id especificado
		void receberDados(int idConexao);            //Espera dados da conex�o especificada
}