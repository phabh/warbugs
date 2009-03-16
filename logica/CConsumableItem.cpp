/*
* Classe CConsumableItem
*
* Versão: 0.01
*
* Autor: Eder Figueiredo
*
* Objetivo: Descreve os itens consumíveis
*
* Alterações: 
* 01/03/2009 - Criação da classe
* 07/03/2009 - Remoção do atributo APONTADOR PRA JOGADOR
*/

#ifndef _CITEM
#include "CItem.cpp"
#endif
#define _CCONSUMABLEITEM

class CConsumableItem : public CItem{
private:
	//NECESSITA CLASSE HABILIDADES E HABILIDADES SECUNDARIAS -> apontador para o atributo a ser modificado
	int _valor; //Valor no qual o atributo será modificado
	bool _istemp;//indica se é um efeito temporário ou não
	//NECESSITA DA CLASSE CONTADORA DE TEMPO -> duração caso seja temporario

};