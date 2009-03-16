/*
* Classe CConsumableItem
*
* Versão: 0.01
*
* Autor: Eder Figueiredo
*
* Objetivo: Descreve os itens consumíveis
*
*/

#include "CItem.cpp"

#ifndef _CCONSUMABLEITEM
#define _CCONSUMABLEITEM

class CConsumableItem : public CItem{
private:
	//NECESSITA CLASSE HABILIDADES E HABILIDADES SECUNDARIAS -> apontador para o atributo a ser modificado
	int _valor; //Valor no qual o atributo será modificado
	bool _istemp;//indica se é um efeito temporário ou não
	//NECESSITA DA CLASSE CONTADORA DE TEMPO -> duração caso seja temporario

};
#endif