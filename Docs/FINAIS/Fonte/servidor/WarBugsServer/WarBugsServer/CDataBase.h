#ifndef _CDATABASE_H_
#define _CDATABASE_H_

#include <mysql.h>
#include <string.h>
#include <vector>

typedef System::Collections::ArrayList TDadosBD;

/**
Classe para a manipula��o de Banco de Dados
*/

class CDataBase{

	char       * _host;       //Local onde est� o servidor
	char       * _user;       //Usu�rio do BD
	char       * _password;   //Senha do BD
	char       * _dataBase;   //BD que ser� utilizado
	bool       _connected;    //True quando � feita a conex�o
	MYSQL      * _connection; //Conex�o com o BD
	MYSQL_RES  * _resultSet;  //Resultados de Consultas, Altera��es, etc..
	MYSQL_ROW    _row;        //Linha com as informa��es provindas da consulta

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
#endif
