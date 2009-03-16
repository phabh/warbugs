class CCoreServer : CObject
{
		vector<CCenario>   _listaCenario;	//lista de cenários de todo o jogo
		vector<Socket>     _listaConexoes;  //lista das conexões feitas com o server do jogo
		CDataBase        * _BD;             //Receberá o BD da classe superior
	public:
		static CTime       _hora;           //Hora corrente do jogo
		static int         _luaCorrente;    //a lua que está em atividade

		CCoreServer(){}                    //Construtor Padrão
		CCoreServer(CDataBase &bd);        //Construtor Secundário enviando de parametro o BD
		void gravarBD();			       //Função que será incluida em uma Thread para gravar todas as alterações 
										   //feitas no jogo no  BD
		void verificarPlayersOnLine();				 //Manda uma mensagem para os players e os que não responderem são kikados
		void enviarDados(int idConexao, char * msg); //Manda mensagem especificada para o id especificado
		void receberDados(int idConexao);            //Espera dados da conexão especificada
}