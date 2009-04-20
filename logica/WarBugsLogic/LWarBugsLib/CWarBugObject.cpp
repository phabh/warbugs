/*
* Classe CObject
*
* Versão: 0.5
*
* Autor: Eder Figueiredo
*
* Objetivo: Objeto base para todas as outras classes
*
*/

//Define a criação da classe
#ifndef _COBJECT_CPP_
#define _COBJECT_CPP_

#include "CWarBugObject.h"

CWarBugObject::CWarBugObject(){}
	int CWarBugObject::getID()
	{
		return(_id);
	}
	/*void inicializar(CObjectCount &counter)
	 *inicializa o objeto, dando para ele um ID único e incrementando o contador de objetos
	 *
	 *@param: CObjectCount &counter: contador de objetos que irá gerar o ID
	 *        OBS: - CRIAR APENS UM CONTADOR DURANTE TODO O PROGRAMA, CASO CONTRÁRIO OS IDs NÃO SERÃO MAIS ÚNICOS
	 */
	void CWarBugObject::initialize(CObjectCount *counter)
	{
		_id = counter->giveID();
	}
	/* Retorna um valor citado no enum TipoClasse
	 * AVISOS COM RELAÇÃO AO GETCLASS:
	 * 1- TODA CLASSE DEVERÁ SER CADASTRADA NO ENUM TipoCLasse, COM EXCEÇÃO DA CObjectCount.
	 * 2- TODA CLASSE CADASTRADA NO ENUM DEVERÁ TER O MÉTODO REIMPLEMENTADO EM SUA DEFINIÇÃO, PARA QUE POSSA SER USADO
	 * Carrega informações do Banco de Dados
	 * NECESSITA DE IMPLEMENTAÇÃO DA PARTE DE COMUNICAÇÃO E DEFINIÇÃO DO PROTOCOLO DE COMUNICAÇÃO
	 */
// -------------------------------------------------------------------------------------------------------------------
/*
Classe CObjectCount
Classe criada excluisivamente no intuito de contar a quantidade de objetos, podendo assim 
atribuir IDs diferentes e únicos aos mesmos
*/
	CObjectCount::CObjectCount()
	{
		objCount = 0;
	}
	/*int giveID()
	 *incrementa o contador e retorna o valor que possuia no inicio do método
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