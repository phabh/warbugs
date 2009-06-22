/*
Classse para serializar dados para envio e recebimento via socket
Baseada na classe dreamMessage.h do livro Programming Multiplayer Games
@autor Paulo
*/
#include "CBugMessage.h"
#include <iostream>

/*
Limpa as variaveis size, readCount e overflow
*/
void CBugMessage::clear(void)
{
	_readCount = 0;
}

/*
Escreve um byte no vetor
@param c-> byte a ser escrito
*/
void CBugMessage::writeByte(char c)
{
	_data += c;
	_data += '@';
}

/*
Escreve um short no vetor
@param c-> short a ser escrito
*/
void CBugMessage::writeShort(short c)
{
     std::ostringstream buff;
     buff<<c;
	 
	 _data.append(buff.str());
	_data += '@';
}

/*
Escreve um long no vetor
@param c-> long a ser escrito
*/
void CBugMessage::writeInt(int c)
{
     std::ostringstream buff;
     buff<<c;
	 
	 _data.append(buff.str());
	_data += '@';
}

/*
Escreve um float no vetor
@param c-> float a ser escrito
*/
void CBugMessage::writeFloat(float c)
{
     std::ostringstream buff;
     buff<<c;
	 
	 _data.append(buff.str());
	_data += '@';
}

/*
Escreve uma string no vetor
@param s-> string a ser escrito
*/
void CBugMessage::writeString(char *s)
{
	 _data.append(s);
	_data += '@';
}


/*
Inicializa a leitura do vetor
*/
void CBugMessage::beginReading(void)
{
	_readCount = 0;
}


/*
Lê um byte do vetor e atualiza a posição de leitura
@return -> o byte lido
*/
char CBugMessage::readByte(void)
{
	 char c = _data[_readCount];
	
	 _readCount += 2;

	 return c;
}

/*
Lê um short do vetor e atualiza a posição de leitura
@return -> o short lido
*/
short CBugMessage::readShort(void)
{
	 
	int posArroba = _readCount;

	while(_data[posArroba] != '@')
	{
		posArroba++;
	}


	std::string str = _data.substr( _readCount, posArroba);

	short s = (short)atoi(str.c_str());

	_readCount += posArroba;

	return s;
}

/*
Lê um long do vetor e atualiza a posição de leitura
@return -> o long lido
*/
int CBugMessage::readInt(void)
{
	int posArroba = _readCount;

	while(_data[posArroba] != '@')
	{
		posArroba++;
	}

	std::string s = _data.substr(_readCount,posArroba);

	int i = atoi(s.c_str());

	_readCount += posArroba;

	return i;
}

/*
Lê um float do vetor e atualiza a posição de leitura
@return -> o float lido
*/
float CBugMessage::readFloat(void)
{
	int posArroba = _readCount;

	while(_data[posArroba] != '@')
	{
		posArroba++;
	}

	std::string s = _data.substr(_readCount,posArroba);

	float f = atof(s.c_str());

	_readCount += posArroba;

	return f;
}

/*
Lê uma string do vetor e atualiza a posição de leitura
@return -> a string lida
*/
char * CBugMessage::readString(void)
{
	int posArroba = _readCount;

	while(_data[posArroba] != '@')
	{
		posArroba++;
	}

	std::string str = _data.substr(_readCount,posArroba);

	str+= '\0';

	_readCount += posArroba;

	return (char *)str.c_str();
}