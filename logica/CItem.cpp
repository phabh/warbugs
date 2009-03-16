/*
* Classe CItem
*
* Versão: 0.41
*
* Autor: Eder Figueiredo
*
* Objetivo: Encapsular os dados básicos comuns a todos os itens
*
* Alterações: 
* 28/02/2009 - Criação da classe
* 07/03/2009 - Adição do apontador para o jogador
* 07/03/2009 - Adição dos métodos loot e drop
* 07/03/2009 - Adição do atributo dropavel
*/

#include <string>
using namespace std;
#ifndef _C3DOBJECT
#include "C3DObject.cpp"
#endif

//Define a criação da classe
#define _CITEM

enum EstadoItem{NAMOCHILA, NOCHAO};
enum TipoItem{USO, ARMA, ARMADURA, QUEST};
class CItem abstract : public C3DObject{
private:
	string _nome;
	string _descricao;
	EstadoItem _estado;
	int _preco;
	bool _dropavel;
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
	//Métodos da CObject
	virtual void inicializar(){
		C3DObject::inicializar();
	}
	virtual TipoClasse getClass(){
		return(CITEM);
	}
	//Métodos de manipulação de itens
	virtual void loot();
	virtual void drop();
};