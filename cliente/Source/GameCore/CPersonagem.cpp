#pragma once

#include "CPersonagem.h"


CPersonagem::CPersonagem()
{
}

void CPersonagem::abrirBolsa(int idBolsa)
{
}

void CPersonagem::aceitarQuest(int idQuest, int objetivo[])
{
}

void CPersonagem::apanhar(int dano)
{
}

void CPersonagem::atacar(int tipoAtaque)
{
}

void CPersonagem::ativarBuff(int idBuff)
{
}

void CPersonagem::atualizar()
{
}

void CPersonagem::atualizarPrimarias(int forca, int destreza, int agilidade, int resistencia, int instinto)
{
}

void CPersonagem::atualizarSecundarias(int ataque, int dano, int defesa, int alcance, int taxaAtaque)
{
}

void CPersonagem::comprarItem(int idItem, int idVendedor)
{
}

void CPersonagem::desativarBuff(int idBuff)
{
}

void CPersonagem::desequipaArma()
{
}

void CPersonagem::desequiparArmadura()
{
}

void CPersonagem::entrarPortal(int idPortal)
{
}

void CPersonagem::enviarItem()
{
}

void CPersonagem::equiparArma(int idArma)
{
}

void CPersonagem::equiparArmadura(int idArmadura)
{
}

int CPersonagem::getId()
{
	return this->_id;
}

void CPersonagem::getQuadrante()
{
}

void CPersonagem::inicializar()
{
}

void CPersonagem::interpolarPosicao()
{
}

void CPersonagem::morrer()
{
}
 
void CPersonagem::parar()
{
}

void CPersonagem::pathFinder()
{
}

void CPersonagem::receberItem(int dinheiroReceber, int itemReceber)
{
}

void CPersonagem::receberListaProdutos()
{
}

void CPersonagem::respaw(int idCenario, int X, int Z)
{
}

void CPersonagem::setAlvo(int idAlvo)
{
}

void CPersonagem::setPosition(int X, int Z)
{
}

void CPersonagem::trocarItem()
{
}

void CPersonagem::trocarNivel()
{
}

void CPersonagem::usarItem(int idItem)
{
}

void CPersonagem::venderItem(int idItem, int idComprador)
{
}

//----------------------------------------------------------------------------------------------------------------

float CPersonagem::getDistanceBetween( vector3d<f32> p1, vector3d<f32> p2 )
{
	// Função para calcular a distância entre dois pontos usando o Teorema de Pitágoras.
	float deltaX, 
		  deltaZ;
	
	deltaX = p1.X*1.0f - p2.X; 
	deltaZ = p1.Z*1.0f - p2.Z;

	return sqrt( (deltaX*deltaX) + (deltaZ*deltaZ) ) ; // Teorema de Pitágoras
}

// -----------------------------------------------------------------------------------------

int CPersonagem::getDirectionTo(vector3d<f32> p2)
{
	vector3df p1;
	
	p1.X = this->_posicao.X;
	p1.Z = this->_posicao.Z;

	float dx = p1.Z - p2.Z; // deltaZ
	float dz = p1.X - p2.X; // deltaX

	float rx = (dx - dz) * TAMQUADRANTE;
	float rz = (dx + dz) * TAMQUADRANTE;

	float ax = abs( rx );
	float az = abs( rz );

	int direcao;

	if( ((az/2) - ax) >= 0 )
		direcao = (rz > 0) ? D_UP : D_DOWN; // Acima ou Abaixo

	else if( ((ax/2) - az) >= 0 )
		direcao = (rx > 0) ? D_LEFT : D_RIGHT; // Esquerda ou Direita

	else if( rx >= 0 && rz >= 0 )
		direcao = D_WEST; // Oeste*

	else if( rx >= 0 && rz < 0 )
		direcao = D_SOUTH; // Sul*

	else if( rx < 0 && rz < 0 )
		direcao = D_EAST; // Leste*

	else
		direcao = D_NORTH; // Norte*

	return direcao;
}

// -----------------------------------------------------------------------------------------

float CPersonagem::getRotationTo(vector3d<f32> destino)
{
	int direcao = getDirectionTo(destino);

	switch(direcao)
	{
		case D_RIGHT: return 225.0; break; // Direita
		case D_NORTH: return 180.0; break; // Norte
		case D_UP:    return 135.0; break; // Acima
		case D_WEST:  return  90.0; break; // Oeste
		case D_LEFT:  return  45.0; break; // Esquerda
		case D_SOUTH: return   0.0; break; // Sul
		case D_DOWN:  return 315.0; break; // Abaixo
		case D_EAST:  return 270.0; break; // Leste
	};

	return 0.0;
}

// -----------------------------------------------------------------------------------------

void CPersonagem::LRTAStar(SQuadrante origem, vector3df objetivo, SQuadrante &proximoPasso, bool Matriz[MAPMAXLIN][MAPMAXCOL])
{
	int i, 
		linha, coluna, // linha e coluna relativa dos vizinhos em relação à origem
		linhaOrigem, colunaOrigem, // coordenadas do quadrante de origem
		lAbs, cAbs; // linha e coluna absolutas dos vizinhos

	float nota[8], // F(j)
		  custo, // custo 1 para laterais e 2 para diagonais
		  menor; // menor nota atual H(origem)

	linhaOrigem  = origem._linha;
	colunaOrigem = origem._coluna;
		
	proximoPasso._linha = linhaOrigem;
	proximoPasso._coluna = colunaOrigem;

	menor = 1000000;

	for (i = 0; i < 8; ++i )
	{
		switch ( i ) // 8 Vizinhos
		{
			default:
			case 0: linha =  1; coluna =  0; custo =  80; break; // Sul
			case 1: linha =  1; coluna =  1; custo = 160; break; // Abaixo
			case 2: linha =  0; coluna =  1; custo =  80; break; // Leste
			case 3: linha = -1; coluna =  1; custo = 160; break; // Direita
			case 4: linha = -1; coluna =  0; custo =  80; break; // Norte
			case 5: linha = -1; coluna = -1; custo = 160; break; // Acima
			case 6: linha =  0; coluna = -1; custo =  80; break; // Oeste
			case 7: linha =  1; coluna = -1; custo = 160; break; // Esquerda
		}

		nota[i] = -1;

		lAbs = linha  + linhaOrigem;   // linha absoluta
		cAbs = coluna + colunaOrigem; // coluna absoluta

		if(lAbs >= 0 && lAbs <MAPMAXLIN) // linha válida do tabuleiro
		{
			if(cAbs >= 0 && cAbs <MAPMAXCOL) // coluna válida do tabuleiro
			{
				if(!Matriz[lAbs][cAbs]) // quadrante nao passável
				{
					nota[i] = -1; 
				}
				else // quadrante passável
				{
					nota[i] = this->Memoria.Pesquisar(getQuadranteID(lAbs, cAbs)/*Matriz[lAbs][cAbs].id*/); // busca na memória a nota
					
					if(nota[i] == -1.0) // não tem na memória, então calcula
					{
						nota[i] = getDistanceBetween(objetivo, getQuadranteCenter(lAbs, cAbs)/*Matriz[lAbs][cAbs].coordenada*/) + custo; // F(i) = H[i] + Custo[origem,i]
					}
					else
						nota[i] += custo;

					if(nota[i] > 0 && nota[i] <= menor)
					{
						menor = nota[i]; 
						proximoPasso._linha = lAbs;
						proximoPasso._coluna = cAbs;
					}
				}
			}
			else
			{
				nota[i] = -1;
			}
		}
		else
		{
			nota[i] = -1;
		}
	}

	this->Memoria.Inserir(getQuadranteID(origem._linha, origem._coluna)/*origem.id*/, menor);
}

int CPersonagem::getQuadranteID(int linha, int coluna)
{
	return (coluna + (linha*MAPMAXCOL));
}

vector3df CPersonagem::getQuadranteCenter(int linha, int coluna)
{
	vector3df center;

	center.X = (coluna * TAMQUADRANTE) + TAMQUADRANTE/2.0f;
	center.Z = (linha  * TAMQUADRANTE) + TAMQUADRANTE/2.0f;

	center.Y = (f32)0.0f; // Lembrar de calcular via Heightmap depois

	return center;
}