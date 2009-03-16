/*
* Classe CItem
*
* Vers�o: 0.41
*
* Autor: Eder Figueiredo
*
* Objetivo: Encapsular os dados b�sicos comuns a todos os itens
*
*/

#include <string>
using namespace std;
#include "C3DObject.cpp"

#ifndef _CITEM
//Define a cria��o da classe
#define _CITEM

enum EstadoItem{NAMOCHILA, NOCHAO, EQUIPADO, USADO};
enum TipoItem{USO, ARMA, ARMADURA, QUEST};
class CItem abstract : public C3DObject{
private:
	string _nome;//Nome do item
	string _descricao;//Breve descri��o que ir� explicar o que � o item e o que ele faz
	EstadoItem _estado;//Estado atual do item, se ele esta no chao, no inventario de alguem, ou se ele esta equipado em alguem
	int _preco;//Pre�o de compra do item
	bool _dropavel;//Identifica se o item pode ou n�o ser dropado
	//NECESSITA CLASSE JOGADOR -> apontador pro dono do item
protected:
	string getNome(){
		return(_nome);
	}
	string getDescricao(){
		return(_descricao);
	}
	EstadoItem getEstado(){
		return(_estado);
	}
	int getEstadoAsInt(){
		return((int)_estado);
	}
	int getPreco(){
		return(_preco);
	}
	void setNome(string novoNome){
		_nome = novoNome;
	}
	void setDescricao(string novaDesc){
		_descricao = novaDesc;
	}
	void setEstado(EstadoItem novoEstado){
		_estado = novoEstado;
	}
	void setPreco(int novoPreco){
		_preco = novoPreco;
	}
	//M�todos da CObject
	virtual void initialize(CObjectCount &counter){
		C3DObject::initialize(counter);
	}
	virtual TipoClasse getClass(){
		return(CITEM);
	}
	//M�todos de manipula��o de itens
	virtual void loot(){}
	virtual void drop(){}
};
#endif