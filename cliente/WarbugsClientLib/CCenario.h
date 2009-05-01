#pragma once

#include "Irrlicht.h"
#include "Setup.h"
#include "CPersonagem.h"

struct SPortal 
{
	int _idCenarioDestino; 
	int _idPortal;	 
	SQuadrante _quadrante;
};

class CCenario 
{
	private:
 
	bool _mapa[MAPMAXLIN][MAPMAXCOL];
	CPersonagem _listaPersonagens;
	long _horario;
	int _id;
	int _luaCorrente;
	SBolsa _listaBolsas;
	SPortal _portal[MAXPORTAIS];
	 
	public:
	
	void addBolsa(int idBolsa, int posX, int posZ);
	void addPersonagem(CPersonagem personagem);
	void atualizar();
	void inicializar();
	void removeBolsa(int idBolsa);
	void removePersonagem();
	void resetar();
	void setHorario(long hora);
	void setLua(int idLua);
};