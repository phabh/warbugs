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

class CGameScene
{
	private:
 
	SMatrix _cenario; // matriz de adjacências

	typedef CDoubleList<CPersonagem> ListaPersonagem;
	ListaPersonagem  *_listaPersonagens;
	
	typedef CDoubleList<SBolsa> ListaBolsa;
	ListaBolsa *_listaBolsas;

	int _idCenario;
	int _luaCorrente;

	SPortal _portal[MAXPORTAIS];

	public:

	CArquivoMatrizes *_fileMtx;
	
	CGameScene();
	void inicializar();
	void atualizar();
	void resetar();

	SMatrix loadMyMatrix(int idScene);
	void loadStaticData(int idCenario);

	void addBolsa(SBolsa);
	void removeBolsa(int idBolsa);

	void addPersonagem(CPersonagem *personagem);
	void removePersonagem(int idPersonagem);

	void setLua(int idLua);
};