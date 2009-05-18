/*
	Classse para serializar dados para envio e recebimento via socket
	Baseada na classe dreamMessage.h do livro Programming Multiplayer Games
	@autor Paulo
*/
#include "CBugMessage.h"
#include <iostream>

/*
	Inicializa as variaveis
	@param d -> vetor de bytes
	@param lenght -> tamanho do vetor de bytes
*/
void CBugMessage::init(char *d, int length)
{
	_data = d;
	_maxSize = length;
	_size = 0;
	_readCount = 0;
	_overFlow = false;
}

/*
	Limpa as variaveis size, readCount e overflow
*/
void CBugMessage::clear(void)
{
	_size = 0;
	_readCount = 0;
	_overFlow = false;
}

/*
	Obtem um novo ponto para inclusão de dados
	@param length -> tamanho do dado a ser inserido
	@return -> ponteiro para a posição inicial de inserção
*/
char * CBugMessage::getNewPoint(int length)
{
	char *tempData;

	// Check for overflow
	if(_size + length > _maxSize)
	{
		clear();
		_overFlow = true;
	}

	tempData = _data + _size;
	_size += length;

	return tempData;
}

/*
	Escreve no vetor de bytes um tipo qualquer do tamanho qualquer
	@param *d -> qualquer tipo de dado
	@param length -> tamanho deste dado
*/
void CBugMessage::write(void *d, int length)
{
	memcpy(getNewPoint(length), d, length);
}

/*
	Escreve um byte no vetor
	@param c-> byte a ser escrito
*/
void CBugMessage::writeByte(char c)
{
	char *buf;
	buf = getNewPoint(1);
	memcpy(buf, &c, 1);
}

/*
	Escreve um short no vetor
	@param c-> short a ser escrito
*/
void CBugMessage::writeShort(short c)
{
	char *buf;
	buf = getNewPoint(2);
	memcpy(buf, &c, 2);
}

/*
	Escreve um long no vetor
	@param c-> long a ser escrito
*/
void CBugMessage::writeLong(long c)
{
	char *buf;
	buf = getNewPoint(4);
	memcpy(buf, &c, 4);
}

/*
	Escreve um float no vetor
	@param c-> float a ser escrito
*/
void CBugMessage::writeFloat(float c)
{
	char *buf;
	buf = getNewPoint(4);
	memcpy(buf, &c, 4);
}

/*
	Escreve uma string no vetor
	@param s-> string a ser escrito
*/
void CBugMessage::writeString(char *s)
{
	if(!s)
	{
		return;
	}
	else
		write(s, strlen(s)+1);
}


/*
	Inicializa a leitura do vetor
*/
void CBugMessage::beginReading(void)
{
	_readCount = 0;
}

/*
	Inicializa a leitura do vetor até o tamanho passado
	@param s-> tamanho do vetor
*/
void CBugMessage::beginReading(int s)
{
	_size = s;
	_readCount = 0;
}

/*
	Lê o vetor de bytes até o tamanho passado
	@param s -> tamanho até onde será realizada a leitura
	@return -> vetor da posição 0 até a posição passada
*/
char * CBugMessage::read(int s)
{
	static char c[2048];

	if(_readCount+s > _size)
		return NULL;
	else
		memcpy(&c, &_data[_readCount], s);

	_readCount += s;
	return c;
}

/*
	Lê um byte do vetor e atualiza a posição de leitura
	@return -> o byte lido
*/
char CBugMessage::readByte(void)
{
	char c = -1;

	if(_readCount+1 > _size)
		c = -1;
	else
		memcpy(&c, &_data[_readCount], 1);

	_readCount++;
	return c;
}

/*
	Lê um short do vetor e atualiza a posição de leitura
	@return -> o short lido
*/
short CBugMessage::readShort(void)
{
	short c = -1;

	if(_readCount+2 <= _size)
		memcpy(&c, &_data[_readCount], 2);

	_readCount += 2;
	return c;
}

/*
	Lê um long do vetor e atualiza a posição de leitura
	@return -> o long lido
*/
long CBugMessage::readLong(void)
{
	long c = -1;

	if(_readCount+4 <= _size)
		memcpy(&c, &_data[_readCount], 4);

	_readCount += 4;
	return c;
}

/*
	Lê um float do vetor e atualiza a posição de leitura
	@return -> o float lido
*/
float CBugMessage::readFloat(void)
{
	float c = -1;

	if(_readCount+4 <= _size)
		memcpy(&c, &_data[_readCount], 4);

	_readCount += 4;
	return c;
}

/*
	Lê uma string do vetor e atualiza a posição de leitura
	@return -> a string lida
*/
char * CBugMessage::readString(void)
{
	static char string[2048];
	int l, c;

	l=0;
	do
	{
		c = readByte();

		if (c == -1 || c == 0)
			break;

		string[l] = c;
		l++;
	} while(l < (sizeof(string)-1));

	string[l] = 0;
	return string;
}