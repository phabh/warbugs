/*
* Classe CVendedor
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever cada personagem vendedor
*
*/
#ifndef _CVENDEDOR_CPP_
#define _CVENDEDOR_CPP_

#include "CVendedor.h"
#ifndef _CCENARIO_H_
#include "CCenario.h"
#ifndef _CCENARIO_H_
class CCenario;
#endif
#endif

#ifndef _MARKET_
#define _MARKET_
SMarket *mercado;
#endif

CVendedor::CVendedor()
{
	initCPersonagem();
	setID(-1);
	coordenada = new Ponto();
	dinheiro = 0;
	habilidadesPrimarias = new CHabilidades();
	bonusPrimario = new CBonusPrimario();
	inventario = new CBolsa();
	habilidadesSecundarias = new CHabilidadesSecundarias();
	bonusSecundario = new CBonusSecundario();
	status = new CBuffList();	
	setState(E_PARADO);
	setMoney(0);
	setBolsa(new CBolsa());
	setStats(new CHabilidadesSecundarias());
	setBonus(new CBonusSecundario());
	setBaseStats(new CHabilidades());
	setBaseBonus(new CBonusPrimario());
	setBuffs(new CBuffList());
}
CVendedor::CVendedor(EstadoPersonagem estado, int dinheiro, CBolsa *inventario, Ponto *ancora)
{
	setID(-1);
	_ancora = ancora;
	setState(estado);
	setMoney(dinheiro);
	setBolsa(inventario);
	setPosition(ancora);
	setStats(new CHabilidadesSecundarias());
	setBonus(new CBonusSecundario());
	setBaseStats(new CHabilidades());
	setBaseBonus(new CBonusPrimario());
	setBuffs(new CBuffList());
}
void CVendedor::init()
{
	mercado->init();
}
//Métodos da economia
void CVendedor::plusDemand(int typeItem)
{
	if(typeItem < MAXITEMTYPES)
	{
		mercado->_itemDemanda[typeItem] = mercado->_itemDemanda[typeItem] + 1;
		if(mercado->_itemDemanda[typeItem] > mercado->_maxDemanda)
		{
			mercado->_maxDemanda = mercado->_itemDemanda[typeItem];
		}
	}
	else
	{
		//ERRO: Out of bounds
	}
}
void CVendedor::plusOffer(int typeItem)
{
	if(typeItem < MAXITEMTYPES)
	{
		mercado->_itemOferta[typeItem] = mercado->_itemOferta[typeItem] + 1;
		if(mercado->_itemOferta[typeItem] > mercado->_maxOferta)
		{
			mercado->_maxOferta = mercado->_itemOferta[typeItem];
		}
	}
	else
	{
		//ERRO: Out of bounds
	}
}
int CVendedor::normalizeDemand(int typeItem)
{
	if(typeItem < MAXITEMTYPES)
	{
		return((mercado->_itemDemanda[typeItem] + (0-mercado->_minDemanda))/((0-mercado->_minDemanda)+mercado->_maxDemanda));
	}
	else
	{
		return(0);
		//ERRO: Out of bounds
	}
}
int CVendedor::normalizeOffer(int typeItem)
{
	if(typeItem < MAXITEMTYPES)
	{
		return((mercado->_itemOferta[typeItem] + (0-mercado->_minOferta))/((0-mercado->_minOferta)+mercado->_maxOferta));
	}
	else
	{
		return(0);
		//ERRO: Out of bounds
	}
}
int CVendedor::stockValue(CItem *item)
{
	return(mercado->_precoBase[(int)item->getType()]+(mercado->_precoBase[(int)item->getType()]+((item->getDurability()-mercado->_MEDIANADURABILIDADE)/100))+(mercado->_precoBase[(int)item->getType()]+((normalizeDemand((int)item->getType())-mercado->_MEDIANADEMANDA)/100))+((normalizeOffer((int)item->getType())-mercado->_MEDIANAOFERTA)/100));
}
void CVendedor::setLeftToGoal()
{
	_restanteMeta = 0;
	for(int i = 0; i < inventario->size(); i = i + 1)
	{
		_restanteMeta = _restanteMeta + stockValue(inventario->getElementAt(i));
	}
	_restanteMeta = _restanteMeta + getMoney();
	_porcentagem = _meta/_restanteMeta;
}
int CVendedor::getSellingPrice(CItem *item)
{
	return(stockValue(item)*_porcentagem);
}
int CVendedor::getBuyPrice(CItem *item)
{
	return(stockValue(item)*_porcentagem/2);
}
int CVendedor::getFinalPriceSell(CItem *item, CPersonagemJogador *jogador)
{
	return(getSellingPrice(item)-(getSellingPrice(item)*(jogador->getLoyalty()->getLoyaltyTo(this->getRace())/1000)*(mercado->_DESCONTOLEALDADE/100))-(getSellingPrice(item)*(_tempoSemVender/10)*(mercado->_DESCONTOTEMPO/100)));
}
int CVendedor::getFinalPriceBuy(CItem *item, CPersonagemJogador *jogador)
{
	return(getBuyPrice(item)-(getBuyPrice(item)*(jogador->getLoyalty()->getLoyaltyTo(this->getRace())/1000)*(mercado->_DESCONTOLEALDADE/100))-(getBuyPrice(item)*(_tempoSemVender/10)*(mercado->_DESCONTOTEMPO/100)));
}
//Outros métodos
void CVendedor::takeDecision()
{
	int tempLinha = 0, tempColuna = 0;
	Ponto *tempPos = new Ponto();
	if(this->getDistanceToPoint(_ancora) >= 100)
	{
		destino = _ancora;
	}
	else
	{
		tempPos->x = this->getPosition()->x;
		tempPos->z = this->getPosition()->z;
		this->getScene()->getQuadLinhaColuna(tempPos, tempLinha, tempColuna);
		switch((clock()%8))
		{
		case 0:
			if((tempLinha > 0)&&(tempColuna < (MAPMAXCOL-1)))
			{
				tempPos = this->getScene()->getQuadCenter(tempLinha-1, tempColuna+1);
				if(this->getScene()->matrizDeCaminhamento[tempLinha][tempColuna] == PASSAVEL)
				{
					destino = this->getScene()->getQuadCenter(tempPos);
				}
				else
				{
					destino = this->getPosition();
				}
			}
			break;
		case 1:
			if(tempColuna < (MAPMAXCOL-1))
			{
				tempPos = this->getScene()->getQuadCenter(tempLinha, tempColuna+1);
				if(this->getScene()->matrizDeCaminhamento[tempLinha][tempColuna] == PASSAVEL)
				{
					destino = this->getScene()->getQuadCenter(tempPos);
				}
				else
				{
					destino = this->getPosition();
				}
			}
			break;
		case 2:
			if((tempLinha < (MAPMAXCOL-1))&&(tempColuna < (MAPMAXCOL-1)))
			{
				tempPos = this->getScene()->getQuadCenter(tempLinha+1, tempColuna+1);
				if(this->getScene()->matrizDeCaminhamento[tempLinha][tempColuna] == PASSAVEL)
				{
					destino = this->getScene()->getQuadCenter(tempPos);
				}
				else
				{
					destino = this->getPosition();
				}
			}
			break;
		case 3:
			if(tempLinha > 0)
			{
				tempPos = this->getScene()->getQuadCenter(tempLinha-1, tempColuna);
				if(this->getScene()->matrizDeCaminhamento[tempLinha][tempColuna] == PASSAVEL)
				{
					destino = this->getScene()->getQuadCenter(tempPos);
				}
				else
				{
					destino = this->getPosition();
				}
			}
			break;
		case 4:
			if(tempLinha < (MAPMAXCOL-1))
			{
				tempPos = this->getScene()->getQuadCenter(tempLinha+1, tempColuna);
				if(this->getScene()->matrizDeCaminhamento[tempLinha][tempColuna] == PASSAVEL)
				{
					destino = this->getScene()->getQuadCenter(tempPos);
				}
				else
				{
					destino = this->getPosition();
				}
			}
			break;
		case 5:
			if((tempLinha > 0)&&(tempColuna > 0))
			{
				tempPos = this->getScene()->getQuadCenter(tempLinha-1, tempColuna-1);
				if(this->getScene()->matrizDeCaminhamento[tempLinha][tempColuna] == PASSAVEL)
				{
					destino = this->getScene()->getQuadCenter(tempPos);
				}
				else
				{
					destino = this->getPosition();
				}
			}
			break;
		case 6:
			if(tempColuna > 0)
			{
				tempPos = this->getScene()->getQuadCenter(tempLinha, tempColuna-1);
				if(this->getScene()->matrizDeCaminhamento[tempLinha][tempColuna] == PASSAVEL)
				{
					destino = this->getScene()->getQuadCenter(tempPos);
				}
				else
				{
					destino = this->getPosition();
				}
			}
			break;
		case 7:
			if((tempLinha < (MAPMAXCOL-1))&&(tempColuna > 0))
			{
				tempPos = this->getScene()->getQuadCenter(tempLinha+1, tempColuna-1);
				if(this->getScene()->matrizDeCaminhamento[tempLinha][tempColuna] == PASSAVEL)
				{
					destino = this->getScene()->getQuadCenter(tempPos);
				}
				else
				{
					destino = this->getPosition();
				}
			}
			break;
		}
	}
}
void CVendedor::speak()
{
	destino->x = this->getPosition()->x;
	destino->z = this->getPosition()->z;
}
void CVendedor::buy(CPersonagemJogador *vendedor, CItem *item)
{
	int preco = getFinalPriceBuy(item, vendedor);
	if((vendedor->haveItem(item)) && (getMoney() >= preco))
	{
		vendedor->getBolsa()->removeItem(item->getID());
		vendedor->addMoney(preco);
		this->addMoney((-1)*preco);
		getBolsa()->addItem(item);
		plusOffer(item->getType());
	}
}
void CVendedor::sell(CPersonagemJogador *comprador, CItem *item)
{
	int preco = getFinalPriceSell(item, comprador);
	if((getBolsa()->haveItem(item->getID())) && (comprador->getMoney() >= preco))
	{
		getBolsa()->removeItem(item->getID());
		comprador->addMoney((-1)*preco);
		this->addMoney(preco);
		comprador->getBolsa()->addItem(item);
		plusDemand(item->getType());
	}	
}
bool CVendedor::tryAttack()
{
	return(true);
}
void CVendedor::attack()
{
}
void CVendedor::takeDamage(int damage, CPersonagem *atkr)
{
	this->getStats()->addPV((-1)*damage);
	divisorxp->addAttacker(atkr, damage);
}
void CVendedor::die()
{
}
void CVendedor::useItem(CItem *item)
{
}
void CVendedor::update()
{
	status->executeBuffs(this, this->status);
	if((destino->x != this->getPosition()->x)||(destino->z != this->getPosition()->z))
	{
		this->move();
	}
	else
	{
		this->takeDecision();
	}
}
#endif