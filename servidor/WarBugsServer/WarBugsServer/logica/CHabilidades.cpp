/*
* Classe CHabilidades
*
* Autor: Eder Figueiredo
*
* Objetivo: Descreve as habilidades primárias de um personagem
*
*/
#ifndef _CHABILIDADES
#define _CHABILIDADES
#include "CObject.cpp"
class CHabilidades : public CObject
{
private:
	int _forca;
	int _agilidade;
	int _destreza;
	int _instinto;
	int _resistencia;
public:
	CHabilidades()
	{
		_forca = 0;
		_agilidade = 0;
		_destreza = 0;
		_instinto = 0;
		_resistencia = 0;
	}
	CHabilidades(int FOR, int AGI, int DES, int INS, int RES)
	{
		_forca = FOR;
		_agilidade = AGI;
		_destreza = DES;
		_instinto = INS;
		_resistencia = RES;
	}
	CHabilidades(CHabilidades *base)
	{
		_forca = base->getFOR();
		_agilidade = base->getAGI();
		_destreza = base->getDES();
		_instinto = base->getINS();
		_resistencia = base->getRES();
	}
	int getFOR()
	{
		return(_forca);
	}
	int getAGI()
	{
		return(_agilidade);
	}
	int getDES()
	{
		return(_destreza);
	}
	int getINS()
	{
		return(_instinto);
	}
	int getRES()
	{
		return(_resistencia);
	}
	void setFOR(int valor)
	{
		_forca = valor;
	}
	void setAGI(int valor)
	{
		_agilidade = valor;
	}
	void setDES(int valor)
	{
		_destreza = valor;
	}
	void setINS(int valor)
	{
		_instinto = valor;
	}
	void setRES(int valor)
	{
		_resistencia = valor;
	}
	void addFOR(int valor)
	{
		_forca = _forca + valor;
	}
	void addAGI(int valor)
	{
		_agilidade = _agilidade + valor;
	}
	void addDES(int valor)
	{
		_destreza = _destreza + valor;
	}
	void addINS(int valor)
	{
		_instinto = _instinto + valor;
	}
	void addRES(int valor)
	{
		_resistencia = _resistencia + valor;
	}
};
#endif