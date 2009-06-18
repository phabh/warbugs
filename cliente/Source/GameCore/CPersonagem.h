#pragma once

#include "GameSetup.h"
#include "CTree.h"

struct SBolsa 
{
	int _idBolsa;
	int _listaItens[BOLSAMAXITENS];
	vector3df posicao;
	bool _isOpen;
};

struct SQuadrante 
{
	int _id;
	int _coluna;
	int _linha;
	vector3df _center;
};

class CPersonagem 
{

public:

	SQuadrante _quadranteFinal;
	SQuadrante _quadranteSeguinte;
	CTree _memoria;
	/*	
	
	

	bool _modoAtaque;
	
	int _dinheiro;

	int _itemEnviarTroca;
	int _itemReceberTroca;
	int _dinheiroEnviarTroca;
	int _dinheiroReceberTroca;

	int _idQuest;
	int _objetivosQuest;
	
	int _inventario[INVENTARIOMAXITENS];
	int _lealdade[RACASMAX];
	int _listaProdutos[MAXITENSVENDEDOR];
	
	int _nivelPoder[NUMPODERES];
	
	int _bonusHabilidade;
	int _bonusPoder;

	
	int _roleta[NUMROLETAOPCOES];
	
	*/

	int _id;
	char *_nome;
	vector3df _posicao;
	vector3df _destino;
	int _pv;
	int _pp;
	int _xp;
	int _pvMax;
	int _ppMax;
	int _xpMax;
	int _nivel;
	bool _buff[BUFF_COUNT];
	int _raca;
	int _classe;

	int _estado;
	int _ultimoEstado;

	float _velAnim;
	float _direcao;

	int _idAlvo;

	int _idBaseArma;
	int _idBaseArmadura;

	int _idRelArma;
	int _idRelArmadura;

	//primarias
	int _forca;
	int _destreza;
	int _agilidade;
	int _resistencia;
	int _instinto;

	//secundarias
	int _alcance;
	int _ataque;
	int _dano;
	int _defesa;
	int _taxaAtaque;
	//int _tempoCarga;


	ISound *_soundFX; // Efeito sonoro do personagem
	IAnimatedMeshSceneNode *_modelo;


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

	int getQuadranteID(int linha, int coluna);
	float getDistanceBetween( vector3d<f32> p1, vector3d<f32> p2 );
	vector3df getQuadranteCenter(int linha, int coluna);
	int getDirectionTo(vector3d<f32> p2);
	float getRotationTo(vector3d<f32> destino);

	void LRTAStar(SQuadrante origem, vector3df objetivo, SQuadrante &proximoPasso, bool Matriz[MAPMAXLIN][MAPMAXCOL]);
};