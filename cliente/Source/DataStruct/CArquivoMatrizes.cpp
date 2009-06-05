#pragma once

#include "GameSetup.h"
#include "PathSetup.h"

struct SMatrix
{
	bool isPassable[MAPMAXLIN][MAPMAXCOL];
};

struct SAllMatrix
{
	SMatrix map[NUMCENARIOS];
};

class CArquivoMatrizes
{

private:

	SAllMatrix _cenarios;
	bool isLoaded;

public:

	CArquivoMatrizes()
	{
		isLoaded = false;
	}

	void setMatriz( SMatrix matriz, int idMap)
	{
		_cenarios.map[idMap] = matriz;
	}

	SMatrix getMatrix(int idMap)
	{
		if(!isLoaded)
			loadMatrix();

		return _cenarios.map[idMap];
	}

	SAllMatrix loadMatrix()
	{
		ifstream load(pathMatrizSetup);
		load.read( (char *)&_cenarios, sizeof(_cenarios));

		isLoaded = true;

		return (_cenarios);
	}

	void saveMatrix()
	{
		ofstream save(pathMatrizSetup);
		save.write( (char *)&_cenarios, sizeof(_cenarios));
	}

	void setAllPassable(int idMap)
	{
		for(int linha=0; linha<MAPMAXLIN; linha++)
			for(int coluna=0; coluna<MAPMAXCOL; coluna++)
				_cenarios.map[idMap].isPassable[linha][coluna] = true;
	}

	void reset()
	{
		for(int i=0; i<NUMCENARIOS; i++)
			setAllPassable(i);

		saveMatrix();
	}
};
