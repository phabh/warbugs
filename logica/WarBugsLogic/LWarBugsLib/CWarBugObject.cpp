/*
* Classe CObject
*
* Vers�o: 0.5
*
* Autor: Eder Figueiredo
*
* Objetivo: Objeto base para todas as outras classes
*
*/

//Define a cria��o da classe
#ifndef _COBJECT_CPP_
#define _COBJECT_CPP_

#include "CWarBugObject.h"

CWarBugObject::CWarBugObject(){}
	int CWarBugObject::getID()
	{
		return(_id);
	}
	/*void inicializar(CObjectCount &counter)
	 *inicializa o objeto, dando para ele um ID �nico e incrementando o contador de objetos
	 *
	 *@param: CObjectCount &counter: contador de objetos que ir� gerar o ID
	 *        OBS: - CRIAR APENS UM CONTADOR DURANTE TODO O PROGRAMA, CASO CONTR�RIO OS IDs N�O SER�O MAIS �NICOS
	 */
	void CWarBugObject::initialize(CObjectCount *counter)
	{
		_id = counter->giveID();
	}
	/* Retorna um valor citado no enum TipoClasse
	 * AVISOS COM RELA��O AO GETCLASS:
	 * 1- TODA CLASSE DEVER� SER CADASTRADA NO ENUM TipoCLasse, COM EXCE��O DA CObjectCount.
	 * 2- TODA CLASSE CADASTRADA NO ENUM DEVER� TER O M�TODO REIMPLEMENTADO EM SUA DEFINI��O, PARA QUE POSSA SER USADO
	 * Carrega informa��es do Banco de Dados
	 * NECESSITA DE IMPLEMENTA��O DA PARTE DE COMUNICA��O E DEFINI��O DO PROTOCOLO DE COMUNICA��O
	 */
// -------------------------------------------------------------------------------------------------------------------
/*
Classe CObjectCount
Classe criada excluisivamente no intuito de contar a quantidade de objetos, podendo assim 
atribuir IDs diferentes e �nicos aos mesmos
*/
	CObjectCount::CObjectCount()
	{
		objCount = 0;
	}
	/*int giveID()
	 *incrementa o contador e retorna o valor que possuia no inicio do m�todo
	 *
	 *@return: valor de objCount antes de ser incrementado
	 */
	int CObjectCount::giveID()
	{
		objCount = objCount+1;
		return(objCount-1);
	}
	/*int objectCount()
	 *conta a quantidade atual de objetos criados
	 *
	 *@return: valor atual do contador
	 */
	int CObjectCount::objectCount()
	{ 
		return(objCount);
	}
#endif