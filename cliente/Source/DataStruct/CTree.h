#pragma once
#include <iostream>

using namespace std; 

class CTree
{

private:

	struct STreeCell
	{
		int idQuadrante,
			Nivel;
		float Heuristica;

		struct STreeCell *Esq, *Dir;
	};

	STreeCell *Raiz;

	void EmOrdem  ( STreeCell *Raiz );
	void PreOrdem ( STreeCell *Raiz );
	void PosOrdem ( STreeCell *Raiz );
	void Inserir  ( int id, float Heuristica, STreeCell * &Raiz );
	void Mostra_Niveis ( STreeCell *Raiz, int Nivel );

public:

	CTree     ( void );
	void Reset     ( void );
	void Mostrar   ( void );
	void Inserir   ( int id, float Heuristica );
	float  Pesquisar ( int id );

};
