#pragma once

#include "GameSetup.h"
#include "CDoubleList.h"
#include "CPersonagem.h"
#include "CArquivoMatrizes.cpp"

struct SPortal 
{
	int _idCenarioDestino; 
	int _idPortal;	 
	SQuadrante _quadrante;
};

class CGameLogic 
{
	private:
 
	SMatriz _mapa;

	//bool _mapa[MAPMAXLIN][MAPMAXCOL];

	typedef CDoubleList<CPersonagem> CListaPersonagem;
	CListaPersonagem  *_listaPersonagens;
	
	long _horario;
	int _id;
	int _luaCorrente;
	SBolsa _listaBolsas;
	SPortal _portal[MAXPORTAIS];

	 
	public:
	
	CGameLogic();

	void loadStaticData(int idCenario);

	void addBolsa(int idBolsa, float posX, float posZ);
	void addPersonagem(CPersonagem *personagem);
	void atualizar();
	void inicializar();
	void removeBolsa(int idBolsa);
	void removePersonagem(CPersonagem *personagem);
	void resetar();
	void setHorario(long hora);
	void setLua(int idLua);
};