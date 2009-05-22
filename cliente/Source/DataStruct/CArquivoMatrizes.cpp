#pragma once

#include "Setup.h"
#include "PathSetup.h"

struct SMatriz
{
	bool mtzAdj[MAPMAXLIN][MAPMAXCOL];
};

struct SMatrizesCenario
{
	SMatriz mapa[NUMCENARIOS];
};

class CArquivoMatrizes
{

private:

	SMatrizesCenario _allMaps;

public:

	CArquivoMatrizes(){}

	void updateMatriz( SMatriz matriz, int idMapa)
	{
		_allMaps.mapa[idMapa] = matriz;
	}

	SMatriz loadMatriz(int idMapa)
	{
		loadAll();
		return _allMaps.mapa[idMapa];
	}

	SMatrizesCenario loadAll()
	{
		ifstream load(pathMatrizSetup);
		load.read( (char *)&_allMaps, sizeof(_allMaps));
		return (_allMaps);
	}

	void saveConfig()
	{
		ofstream save(pathMatrizSetup);
		save.write( (char *)&_allMaps, sizeof(_allMaps));
	}

	void reset()
	{
		for(int map=0; map<NUMCENARIOS; map++)
			for(int linha=0; linha<MAPMAXLIN; linha++)
				for(int coluna=0; coluna<MAPMAXCOL; coluna++)
					_allMaps.mapa[map].mtzAdj[linha][coluna] = true;

		saveConfig();
	}
};
