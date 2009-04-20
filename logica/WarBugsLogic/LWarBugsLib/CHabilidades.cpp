/*
* Classe CHabilidades
*
* Autor: Eder Figueiredo
*
* Objetivo: Descreve as habilidades primárias de um personagem
*
*/
#ifndef _CHABILIDADES_CPP_
#define _CHABILIDADES_CPP_

#include "CHabilidades.h"

CHabilidades::CHabilidades()
	{
		_forca = 0;
		_agilidade = 0;
		_destreza = 0;
		_instinto = 0;
		_resistencia = 0;
	}
	CHabilidades::CHabilidades(int FOR, int AGI, int DES, int INS, int RES)
	{
		_forca = FOR;
		_agilidade = AGI;
		_destreza = DES;
		_instinto = INS;
		_resistencia = RES;
	}
	CHabilidades::CHabilidades(CHabilidades *base)
	{
		_forca = base->getFOR();
		_agilidade = base->getAGI();
		_destreza = base->getDES();
		_instinto = base->getINS();
		_resistencia = base->getRES();
	}
	int CHabilidades::getFOR()
	{
		return(_forca);
	}
	int CHabilidades::getAGI()
	{
		return(_agilidade);
	}
	int CHabilidades::getDES()
	{
		return(_destreza);
	}
	int CHabilidades::getINS()
	{
		return(_instinto);
	}
	int CHabilidades::getRES()
	{
		return(_resistencia);
	}
	void CHabilidades::setFOR(int valor)
	{
		_forca = valor;
	}
	void CHabilidades::setAGI(int valor)
	{
		_agilidade = valor;
	}
	void CHabilidades::setDES(int valor)
	{
		_destreza = valor;
	}
	void CHabilidades::setINS(int valor)
	{
		_instinto = valor;
	}
	void CHabilidades::setRES(int valor)
	{
		_resistencia = valor;
	}
	void CHabilidades::addFOR(int valor)
	{
		_forca = _forca + valor;
	}
	void CHabilidades::addAGI(int valor)
	{
		_agilidade = _agilidade + valor;
	}
	void CHabilidades::addDES(int valor)
	{
		_destreza = _destreza + valor;
	}
	void CHabilidades::addINS(int valor)
	{
		_instinto = _instinto + valor;
	}
	void CHabilidades::addRES(int valor)
	{
		_resistencia = _resistencia + valor;
	}
#endif