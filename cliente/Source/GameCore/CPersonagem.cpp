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
void CPersonagem::SetAnimation(int state, int nextState)
{
	switch (state)
	{

	case IDLE:

		m_startFrame = 251;
		m_endFrame = 310;
		break;

	case RUN:

		m_startFrame = 40;
		m_endFrame = 70;
		break;

	case ATTACK1:

		m_startFrame = 1;
		m_endFrame = 30;
		break;

	case ATTACK2:

		m_startFrame = 371;
		m_endFrame = 400;
		break;

	case ATTACK3:

		m_startFrame = 401;
		m_endFrame = 420;
		break;

	case POWER1:

		m_startFrame = 80;
		m_endFrame = 100;
		break;

	case POWER2:

		m_startFrame = 205;
		m_endFrame = 245;
		break;

	case POWER3:

		m_startFrame = 355;
		m_endFrame = 385;
		break;

	case PAIN:

		m_startFrame = 54;
		m_endFrame = 57;
		break;

	case BUFF_OFF:

		m_startFrame = 135;
		m_endFrame = 153;
		break;

	case BUFF_ON:

		m_startFrame = 154;
		m_endFrame = 159;
		break;

	case DEATH:

		m_startFrame = 173;
		m_endFrame = 177;
		break;

	case SELECTED:

		m_startFrame = 66;
		m_endFrame = 71;
		break;

	default:

		return;
	}

	if (m_state != state)
	{
		m_currentFrame = m_startFrame;
		m_nextFrame = m_startFrame + 1;
	}

	m_state = state;
	m_nextState = nextState;
}*/