/*
* Classe CConsumableItem
*
* Vers�o: 0.01
*
* Autor: Eder Figueiredo
*
* Objetivo: Descreve os itens consum�veis
*
* Altera��es: 
* 01/03/2009 - Cria��o da classe
* 07/03/2009 - Remo��o do atributo APONTADOR PRA JOGADOR
*/

#ifndef _CITEM
#include "CItem.cpp"
#endif
#define _CCONSUMABLEITEM

class CConsumableItem : public CItem{
private:
	//NECESSITA CLASSE HABILIDADES E HABILIDADES SECUNDARIAS -> apontador para o atributo a ser modificado
	int _valor; //Valor no qual o atributo ser� modificado
	bool _istemp;//indica se � um efeito tempor�rio ou n�o
	//NECESSITA DA CLASSE CONTADORA DE TEMPO -> dura��o caso seja temporario

};