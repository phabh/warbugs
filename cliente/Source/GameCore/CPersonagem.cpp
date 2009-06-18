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

/*
void CPersonagem::SetAnimation(int estado, int proxEstado)
{
	switch (state)
	{

	case PARADO:

		_startFrame = 1;
		_endFrame = 60;
		break;

	case SAUDACAO:

		_startFrame = 61;
		_endFrame = 90;
		break;

	case CORRENDO:

		_startFrame = 91;
		_endFrame = 120;
		break;

	case ATAQUE1:

		_startFrame = 121;
		_endFrame = 150;
		break;

	case ATAQUE2:

		_startFrame = 151;
		_endFrame = 180;
		break;

	case ATAQUE3:

		_startFrame = 181;
		_endFrame = 210;
		break;

	case ATAQUE4:

		_startFrame = 211;
		_endFrame = 240;
		break;

	case PODER1:

		_startFrame = 241;
		_endFrame = 270;
		break;

	case PODER2:

		_startFrame = 271;
		_endFrame = 300;
		break;

	case PODER3:

		_startFrame = 301;
		_endFrame = 330;
		break;

	case BUFF_BOM:

		_startFrame = 331;
		_endFrame = 360;
		break;

	case BUFF_RUIM:

		_startFrame = 361;
		_endFrame = 390;
		break;

	case APANHANDO:

		_startFrame = 391;
		_endFrame = 420;
		break;

	case MORRENDO:

		_startFrame = 421;
		_endFrame = 450;
		break;

	default:

		return;
	}

	if (_estado != estado)
	{
		_currentFrame = _startFrame;
		_nextFrame = _startFrame + 1;
	}

	_estado = estado;
	_proxEstado = proxEstado;
}*/