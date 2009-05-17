/***************************************************************************

	Funções da Classe dreamMessage

****************************************************************************/
#include "CBugMessage.h"

void CBugMessage::init(char *d, int length)
{
	_data = d;
	_maxSize = length;
	_size = 0;
	_readCount = 0;
	_overFlow = false;
}

void CBugMessage::clear(void)
{
	_size = 0;
	_readCount = 0;
	_overFlow = false;
}

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

void CBugMessage::write(void *d, int length)
{
	memcpy(getNewPoint(length), d, length);
}

void CBugMessage::writeByte(char c)
{
	char *buf;
	buf = getNewPoint(1);
	memcpy(buf, &c, 1);
}

void CBugMessage::writeShort(short c)
{
	char *buf;
	buf = getNewPoint(2);
	memcpy(buf, &c, 2);
}

void CBugMessage::writeLong(long c)
{
	char *buf;
	buf = getNewPoint(4);
	memcpy(buf, &c, 4);
}

void CBugMessage::writeFloat(float c)
{
	char *buf;
	buf = getNewPoint(4);
	memcpy(buf, &c, 4);
}

void CBugMessage::writeString(char *s)
{
	if(!s)
	{
		return;
	}
	else
		write(s, strlen(s) + 1);
}

void CBugMessage::beginReading(void)
{
	_readCount = 0;
}

void CBugMessage::beginReading(int s)
{
	_size = s;
	_readCount = 0;
}

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

short CBugMessage::readShort(void)
{
	short c = -1;

	if(_readCount+2 <= _size)
		memcpy(&c, &_data[_readCount], 2);

	_readCount += 2;
	return c;
}

long CBugMessage::readLong(void)
{
	long c = -1;

	if(_readCount+4 <= _size)
		memcpy(&c, &_data[_readCount], 4);

	_readCount += 4;
	return c;
}

float CBugMessage::readFloat(void)
{
	float c = -1;

	if(_readCount+4 <= _size)
		memcpy(&c, &_data[_readCount], 4);

	_readCount += 4;
	return c;
}

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