/*
* Classe CObject
*
* Vers�o: 0.5
*
* Autor: Eder Figueiredo
*
* Objetivo: Objeto base para todas as outras classes
*
* Altera��es: 
* 01/03/2009 - Cria��o da classe
*
*/

//Define a cria��o da classe
#define _COBJECT

class CObject;

//Enumerador para retornar o tipo da classe
enum TipoClasse{
	COBJECT,
	C3DOBJECT,
	CLOGICOBJECT,
	CDOUBLELIST,
	CITEM,
	CCONSUMABLEITEM
};

/*
Classe CObjectCount
Classe criada excluisivamente no intuito de contar a quantidade de objetos, podendo assim 
atribuir IDs diferentes e �nicos aos mesmos
*/
class CObjectCount{
public:
    int objCount;//Contador de Objetos
	//Construtor do contador, apenas zera o inteiro objCont
	CObjectCount(){
		objCount = 0;
	}
	/*int giveID()
	 *incrementa o contador e retorna o valor que possuia no inicio do m�todo
	 *
	 *@return: valor de objCount antes de ser incrementado
	 */
	int giveID(){
		objCount = objCount+1;
		return(objCount-1);
	}
	/*int objectCount()
	 *conta a quantidade atual de objetos criados
	 *
	 *@return: valor atual do contador
	 */
	int objectCount(){ 
		return(objCount);
	}
};

class CObject abstract{
private:
	int _id;//ID �nico de um objeto
protected:
	int getID(){
		return(_id);
	}
	/*void inicializar(CObjectCount &counter)
	 *inicializa o objeto, dando para ele um ID �nico e incrementando o contador de objetos
	 *
	 *@param: CObjectCount &counter: contador de objetos que ir� gerar o ID
	 *        OBS: - CRIAR APENS UM CONTADOR DURANTE TODO O PROGRAMA, CASO CONTR�RIO OS IDs N�O SER�O MAIS �NICOS
	 */
	void inicializar(CObjectCount &counter){
		_id = counter.giveID();
	}
	TipoClasse getClass();//Retorna um valor citado no enum TipoClasse
	//AVISOS COM RELA��O AO GETCLASS:
	//1- TODA CLASSE DEVER� SER CADASTRADA NO ENUM TipoCLasse, COM EXCE��O DA CObjectCount.
	//2- TODA CLASSE CADASTRADA NO ENUM DEVER� TER O M�TODO REIMPLEMENTADO EM SUA DEFINI��O, PARA QUE POSSA SER USADO
	//Carrega informa��es do Banco de Dados
	//NECESSITA DE IMPLEMENTA��O DA PARTE DE COMUNICA��O E DEFINI��O DO PROTOCOLO DE COMUNICA��O
	void loadDBData();//Ir� carregar as informa��es necess�rias para preencher os atributos dos objetos
	void atualizar();//Ir� atualizar o objeto em seu estado atual, variar� drasticamente entre os tipos de objeto
};