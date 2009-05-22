#include "CTree.h"


#define SIM  1  // Auxiliares da funcao Procurar
#define NAO  0
#define NULL 0

// ----------------------------------------------- GLOBAIS


int START     = 0,  // Comeca da raiz em 0 ( contando os niveis )
MAXNIVEL  = 0,  // Maximo de niveis
TENDENCIA = 0;  // -1 = esquerda, 1 = direita e 0 = raiz.

// -------------------------------------------------------------------------

CTree :: CTree ( void )
{
	// Construtor padrao

	Raiz = NULL;

} 

// -------------------------------------------------------------------------

void CTree :: Reset ( void )
{
	// Construtor padrao
	Raiz = NULL;
	MAXNIVEL = 0;
} 

// -------------------------------------------------------------------------

float CTree :: Pesquisar ( int id )
{
	// procurar por um elemento na arvore
	STreeCell *P = Raiz;

	while ( P != NULL && P -> idQuadrante != id )
	{
		if ( id < P -> idQuadrante )
			P = P -> Esq;
		else
			P = P -> Dir;
	}

	if(P == NULL)
		return -1.0;
	else
		return P->Heuristica;
}

// -------------------------------------------------------------------------

void CTree :: Mostrar ( void )
{
	// Mostra arvore em ordem crescente
	int i;

	for ( i = 0; i <= MAXNIVEL; i++ )
	{
		cout  << "\nNivel " << i+1 << " : ";
		Mostra_Niveis ( Raiz, i );
	}

} 

// -------------------------------------------------------------------------

void CTree :: Inserir ( int id, float Heuristica )
{
	// Colocar novo elemento em ordem
	START = TENDENCIA = 0;     // Zera o nivel e a tendencia da folha
	Inserir ( id, Heuristica, Raiz );

}

// -------------------------------------------------------------------------

void CTree :: Inserir ( int id, float Heuristica, STreeCell * &Raiz )
{
	// Colocar um novo elemento a partir da referencia
	if ( Raiz == NULL )
	{
		if ( ( Raiz = new ( STreeCell ) ) == NULL )
			cout << "\nERRO: Memoria insuficiente.";
		else
		{
			Raiz->idQuadrante = id;
			Raiz-> Heuristica = Heuristica;
			Raiz-> Nivel = START;
			Raiz-> Esq   = Raiz -> Dir = NULL;
		}
	}
	else
	{
		if ( id < Raiz -> idQuadrante )
		{
			START++;
			TENDENCIA = -1; // ESQUERDA

			if ( MAXNIVEL < START )
				MAXNIVEL = START;

			Inserir ( id, Heuristica, Raiz -> Esq );
		}
		else
		{
			if ( id > Raiz -> idQuadrante )
			{
				START++;
				TENDENCIA = 1; // DIREITA

				if ( MAXNIVEL < START )
					MAXNIVEL = START;

				Inserir ( id, Heuristica, Raiz -> Dir );
			}
			else
			{
				if (id == Raiz -> idQuadrante) // já existe o quadrante
				{
					Raiz -> Heuristica = Heuristica;
				}
			}
		}
	}
}

// --------------------------------------------------------------------------

void CTree :: Mostra_Niveis ( STreeCell *Raiz, int Nivel )
{
	// Mostra os niveis da arvore

	if ( Raiz != NULL && Raiz -> Nivel <= Nivel)
	{
		// Se raiz nao chegar no final
		// e o nivel da raiz for menor ou igual ao nivel procurado.

		Mostra_Niveis ( Raiz -> Esq, Nivel );
		Mostra_Niveis ( Raiz -> Dir, Nivel );

		if ( Raiz -> Nivel == Nivel )
		{
			cout  << Raiz ->idQuadrante << ", " << Raiz->Heuristica; // Achou uma folha no nivel procurado.
		}
	}
}
