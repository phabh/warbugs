#include <mysql.h>
#include <string.h>
#include <vector>

typedef System::Collections::ArrayList TDadosBD;

/**
Classe para a manipulação de Banco de Dados
*/

class CDataBase{

	char       * _host;       //Local onde está o servidor
	char       * _user;       //Usuário do BD
	char       * _password;   //Senha do BD
	char       * _dataBase;   //BD que será utilizado
	bool       _connected;    //True quando é feita a conexão
	MYSQL      * _connection; //Conexão com o BD
	MYSQL_RES  * _resultSet;  //Resultados de Consultas, Alterações, etc..
	MYSQL_ROW    _row;        //Linha com as informações provindas da consulta

	public:
		CDataBase();
		CDataBase(char *host, char *bd, char *user, char *password);
		bool     connectNow(char *host, char *bd, char *user, char *password);
		bool     selectNow(char *query, unsigned int &numFields, unsigned int &numRegs, TDadosBD ^ dados);
		bool     isConnected();
		bool     insertNow(char *query);
		bool     updateNow(char *query);
		bool     deleteNow(char *query);
		void     closeNow();
};
// Fim da Interface da Classe

//Metodos

/*
	Construtor padrão
*/
CDataBase::CDataBase()
{
	_connection = mysql_init(NULL);
}

/*
	Construtor Secundário
	Ele ja cria a conexão com o BD
	@param host     - IP da máquina onde estará o BD 
	@param bd       - Nome do BD
	@param user     - Nome Usuario do BD
	@param password - Senha BD
*/
CDataBase::CDataBase(char *host, char *bd, char *user, char *password)
{
	_connection = mysql_init(NULL);
	_connected  = connectNow(host,bd,user,password);
}

/*
	Cria a Conexão com o BD
	@param  host     - IP da máquina onde estará o BD 
	@param  bd       - Nome do BD
	@param  user     - Nome Usuario do BD
	@param  password - Senha BD
	@return true se a conexão ocorreu
*/
bool CDataBase::connectNow(char *host, char *bd, char *user, char *password)
{
	_host      = host;
	_dataBase  = bd;
	_user      = user;
	_password  = password;
	_connected = mysql_real_connect(_connection,host,user,password,bd,0,NULL,0) != NULL;
	return (_connected);
}

/*
	Cria uma consulta com o BD
	@param query     - Instrução SQL;
	@param numFields - numero de campos que a linha possui
	@param numRegs   - numero de registros que foram selecionados
	@param - retorna as informações todas as linhas com seus respectivos dados
*/
bool CDataBase::selectNow(char *query, unsigned int &numFields, unsigned int &numRegs, TDadosBD ^dados)
{

	bool resultado = false;
	numFields = 0;
	numRegs   = 0;

	if(_connected)
	{
		if(strlen(query) > 0)
		{
			mysql_query(_connection,query);
		}
	
		_resultSet = mysql_store_result(_connection);
		if(_resultSet != NULL)
		{
			numRegs    = (unsigned)mysql_num_rows(_resultSet);
			numFields  = mysql_num_fields(_resultSet);
			MYSQL_FIELD * campo;

			System::String ^ teste;

			while((campo = mysql_fetch_field(_resultSet)))
			{
				char * tex = campo->name;
				teste = gcnew System::String(tex);
				dados->Add(teste);
			}
			
			
			while((_row = mysql_fetch_row(_resultSet)))
			{
				for(unsigned int i = 0; i < numFields; i++)
				{
					//dado = _row[i];
					teste = gcnew System::String(_row[i]);
					dados->Add(teste);
				}
			}
			resultado = true;
		}


		mysql_free_result(_resultSet); 
	}

	return resultado;
}

/*
	Insere dados no BD
	@param query - Instrução de inserção
	@return - se a instrução foi executada com sucesso
*/
bool CDataBase::insertNow(char *query)
{
	bool resultado = false;

	if(_connected)	
	{
		if(strlen(query) > 0)
		{			
			resultado = mysql_query(_connection,query) == 0;
		}
	}

	return resultado;
}

/*
	Deleta dados do BD
	@param query - Instrução de inserção
	@return - se a instrução foi executada com sucesso
*/
bool CDataBase::deleteNow(char *query)
{
	return insertNow(query);
}

/*
	Altera dados do BD
	@param query - Instrução de inserção
	@return - se a instrução foi executada com sucesso
*/
bool CDataBase::updateNow(char *query)
{
	return insertNow(query);
}

/*
	Fecha a conexão com o banco de dados
*/
void CDataBase::closeNow()
{
	mysql_close(_connection);
}

/*
	Verifica se está conectado com o bd
*/
bool CDataBase::isConnected()
{
	_connected = mysql_ping(_connection) == 0;

	return _connected;
}