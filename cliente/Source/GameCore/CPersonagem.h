#pragma once

#include "GameSetup.h"
#include "CTree.h"

struct SBolsa 
{
	int _idBolsa;
	int _listaItens[BOLSAMAXITENS];
	float _x;
	float _z;
	bool _isOpen;
};

struct SQuadrante 
{
	int _id;
	int _coluna;
	int _linha;
};

class CPersonagem 
{

private:

	int _agilidade;
	int _alcance;
	int _ataque;
	int _dano;
	int _defesa;
	int _destreza;
	int _dinheiro;
	int _dinheiroEnviarTroca;
	int _dinheiroReceberTroca;
	float _direcao;
	int _estado;
	int _ultimoEstado;
	int _forca;
	int _id;
	int _idAlvo;
	int _idArma;
	int _idArmadura;
	int _idQuest;
	int _instinto;
	int _inventario[INVENTARIOMAXITENS];
	int _itemEnviarTroca;
	int _itemReceberTroca;
	int _lealdade[RACASMAX];
	//int _listaPreco[MAXITENSVENDEDOR];
	int _listaProdutos[MAXITENSVENDEDOR];
	int _nivel;
	int _nivelPoder[NUMPODERES];
	char *_nome;
	int _objetivosQuest;
	int _pontosPoder;
	int _pontosHabilidadeDisponiveis;
	int _pontosPoderDisponiveis;
	int _pontosPoderMaximo;
	int _pontosVida;
	int _pontosVidaMaximo;
	float _posX;
	float _posZ;
	int _raca;
	int _resistencia;
	int _roleta[NUMROLETAOPCOES];
	int _taxaAtaque;
	int _tipoPersonagem;
	int _tempoCarga;
	int _velocidade;
	int _xp;
	int _xpMaximo;

	bool _buff[NUMBUFFERS];
	bool _modoAtaque;

	SQuadrante _listaQuadrante[AREABUSCA];
	SQuadrante _quadranteFinal;
	SQuadrante _quadranteSeguinte;

	ISound* _soundFX; // Efeito sonoro do personagem

	CTree Memoria;

public:

	CPersonagem();

	void abrirBolsa(int idBolsa);
	void aceitarQuest(int idQuest, int objetivo[]);
	void apanhar(int dano);
	void atacar(int tipoAtaque);
	void ativarBuff(int idBuff);
	void atualizar();
	void atualizarPrimarias(int forca, int destreza, int agilidade, int resistencia, int instinto);
	void atualizarSecundarias(int ataque, int dano, int defesa, int alcance, int taxaAtaque);
	void comprarItem(int idItem, int idVendedor);
	void desativarBuff(int idBuff);
	void desequipaArma();
	void desequiparArmadura();
	void entrarPortal(int idPortal);
	void enviarItem();
	void equiparArma(int idArma);
	void equiparArmadura(int idArmadura);
	int getId();
	void getQuadrante();
	void inicializar();
	void interpolarPosicao();
	void morrer(); 
	void parar();
	void pathFinder();
	void receberItem(int dinheiroReceber, int itemReceber);
	void receberListaProdutos();
	void respaw(int idCenario, int X, int Z);
	void setAlvo(int idAlvo);
	void setPosition(int X, int Z);
	void trocarItem();
	void trocarNivel();
	void usarItem(int idItem);
	void venderItem(int idItem, int idComprador);

	int       getQuadranteID(int linha, int coluna);
	float     getDistanceBetween( vector3d<f32> p1, vector3d<f32> p2 );
	vector3df getQuadranteCenter(int linha, int coluna);
	int       getDirectionTo(vector3d<f32> p2);
	float     getRotationTo(vector3d<f32> destino);

	void LRTAStar(SQuadrante origem, vector3df objetivo, SQuadrante &proximoPasso, bool Matriz[MAPMAXLIN][MAPMAXCOL]);
};