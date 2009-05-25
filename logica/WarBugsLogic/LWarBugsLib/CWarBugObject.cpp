/*
* Classe CObject
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
void CWarBugObject::setID(int newID)
{
	_id = newID;
}
int CWarBugObject::getSceneID()
{
	return(_sceneId);
}
void CWarBugObject::setSceneID(int newID)
{
	_sceneId = newID;
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
	_objCount = 0;
}
/*int giveID()
 *incrementa o contador e retorna o valor que possuia no inicio do m�todo
 *
 *@return: valor de objCount antes de ser incrementado
 */
int CObjectCount::giveID()
{
    int idToReturn;
    if(_bufferSize > 0)
    {
		idToReturn = _buffer[0];
        int *tempBuffer;
        if(_bufferSize == 1)
        {
			tempBuffer = NULL;
		}
        else
        {
			tempBuffer = new int[_bufferSize-1];
		}
        for(int i = 0; i < _bufferSize-1; i = i + 1)
        {
			tempBuffer[i] = _buffer[i+1];        
		}
        _buffer = NULL;
        _buffer = tempBuffer;
        _bufferSize = _bufferSize-1;
	}
    else
    {
		_objCount = _objCount + 1;
        idToReturn = _objCount - 1;
    }
    return(idToReturn);
}
/*int removeID()
 *remove um elemento do contador e armazena-o em um buffer
 *
 *@param: int ID: ID a ser removido e acrescentado ao buffer
 */
void CObjectCount::removeID(int ID)
{
    if(_bufferSize == 0)
    {
		_buffer = new int[1];
        _buffer[0] = ID;
        _bufferSize = 1;
    }
    else
    {
		int *tempBuffer = new int[_bufferSize+1];
        for(int i = _bufferSize-1; i >= 0; i = i - 1)
        {
			tempBuffer[i] = _buffer[i];
		}
        tempBuffer[_bufferSize] = ID;
		_buffer = NULL;
        _buffer = tempBuffer;
        _bufferSize = _bufferSize+1;
	}
}
/*int objectCount()
 *conta a quantidade atual de objetos criados
 *
 *@return: valor atual do contador
 */
int CObjectCount::objectCount()
{ 
	return(_objCount);
}
#endif