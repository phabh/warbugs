/*
* Classe CItem
*
* Autor: Eder Figueiredo
*
* Objetivo: Encapsular os dados básicos comuns a todos os itens
*
*/
#include <string>
using namespace std;
#include "C3DObject.cpp"
#ifndef _CITEM
//Define a criação da classe
#define _CITEM

#ifndef _SATRIB
#define _SATRIB
enum Atrib {NENHUM, PV, PM};
#endif
// ------------------------------------------------------------------------------------------------------------
enum EstadoItem{NAMOCHILA, NOCHAO, EQUIPADO, USADO};
// ------------------------------------------------------------------------------------------------------------
enum TipoItem{USO, ARMA, ARMADURA, QUEST};
// ------------------------------------------------------------------------------------------------------------
class CItem : public C3DObject{
private:
	string _nome;//Nome do item
	string _descricao;//Breve descrição que irá explicar o que é o item e o que ele faz
	EstadoItem _estado;//Estado atual do item, se ele esta no chao, no inventario de alguem, ou se ele esta equipado em alguem
	TipoItem _tipo;//Qual o tipo do item, pra dar o cast nas funções de outras classes que usarem itens
	int _preco;//Preço de compra do item
	bool _dropavel;//Identifica se o item pode ou não ser dropado
	//NECESSITA CLASSE JOGADOR -> apontador pro dono do item
public:
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
	TipoItem getTipo(){
		return(_tipo);
	}
	int getTipoAsInt(){
		return((int)_tipo);
	}
	int getPreco(){
		return(_preco);
	}
	bool isDropable()
	{
		return(_dropavel);
	}
	//CPersonagem getOwner(){}
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
	void setDropable(bool isdropable)
	{
		_dropavel = isdropable;
	}
	//void setOwner(CPersonagem *newOwner){}
	//Métodos da CObject
	virtual void initialize(CObjectCount *counter){
		C3DObject::initialize(counter);
	}
	virtual TipoClasse getClass(){
		return(CITEM);
	}
	//Métodos de manipulação de itens
	//virtual void use(CPersonagem *jogador)=0;
	//virtual void loot(CPersonagem *jogador)=0;
	//virtual void drop(CPersonagem *jogador)=0;
	//Métodos virtuais pra funcionar
	virtual int getValue(){}
	virtual Atrib getAtribute(){}
};
#endif