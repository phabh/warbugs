/***************************************************************************

	Funções da Classe dreamMessage

****************************************************************************/
#include "dreamMessage.h"
#include "dreamClient.h"

void dreamMessage::init(char *d, int length)
{
	_data = d;
	_maxSize = length;
	_size = 0;
	_readCount = 0;
	_overFlow = false;
}

void dreamMessage::clear(void)
{
	_size = 0;
	_readCount = 0;
	_overFlow = false;
}

char *dreamMessage::getNewPoint(int length)
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

void dreamMessage::addSequences(dreamClient *client)
{
	writeShort(client->getOutgoingSequence());
	writeShort(client->getIncomingSequence());
}

void dreamMessage::write(void *d, int length)
{
	memcpy(getNewPoint(length), d, length);
}

void dreamMessage::writeByte(char c)
{
	char *buf;
	buf = getNewPoint(1);
	memcpy(buf, &c, 1);
}

void dreamMessage::writeShort(short c)
{
	char *buf;
	buf = getNewPoint(2);
	memcpy(buf, &c, 2);
}

void dreamMessage::writeLong(long c)
{
	char *buf;
	buf = getNewPoint(4);
	memcpy(buf, &c, 4);
}

void dreamMessage::writeFloat(float c)
{
	char *buf;
	buf = getNewPoint(4);
	memcpy(buf, &c, 4);
}

void dreamMessage::writeString(char *s)
{
	if(!s)
	{
		return;
	}
	else
		write(s, strlen(s) + 1);
}

void dreamMessage::beginReading(void)
{
	_readCount = 0;
}

void dreamMessage::beginReading(int s)
{
	_size = s;
	_readCount = 0;
}

char *dreamMessage::read(int s)
{
	static char c[2048];

	if(_readCount+s > _size)
		return NULL;
	else
		memcpy(&c, &_data[_readCount], s);

	_readCount += s;
	return c;
}

char dreamMessage::readByte(void)
{
	char c;

	if(_readCount+1 > _size)
		c = -1;
	else
		memcpy(&c, &_data[_readCount], 1);

	_readCount++;
	return c;
}

short dreamMessage::readShort(void)
{
	short c = -1;

	if(_readCount+2 <= _size)
		memcpy(&c, &_data[_readCount], 2);

	_readCount += 2;
	return c;
}

long dreamMessage::readLong(void)
{
	long c = -1;

	if(_readCount+4 <= _size)
		memcpy(&c, &_data[_readCount], 4);

	_readCount += 4;
	return c;
}

float dreamMessage::readFloat(void)
{
	float c = -1;

	if(_readCount+4 <= _size)
		memcpy(&c, &_data[_readCount], 4);

	_readCount += 4;
	return c;
}

char *dreamMessage::readString(void)
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